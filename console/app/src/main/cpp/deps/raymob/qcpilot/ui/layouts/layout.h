#ifndef __QCPILOT_UI_LAYOUTS_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include <vector>
#include "qcpilot/ui/input/touch_manager.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {

template<typename T>
T map(T x, T in_min, T in_max, T out_min, T out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

struct ScreenViewport {
  std::size_t x {0U};
  std::size_t y {0U};
  std::size_t w {0U};
  std::size_t h {0U};
};

struct CanvasSize {
  std::size_t w {0U};
  std::size_t h {0U};
};

struct CanvasPosition {
  std::size_t x {0U};
  std::size_t y {0U};
};

struct CanvasArea {
  std::size_t x {0U};
  std::size_t y {0U};
  std::size_t w {0U};
  std::size_t h {0U};
};


class Layout {
public:
  virtual void addChild(Layout &layout) {
    children_.push_back(&layout);
  }

  virtual void setBackgroundColor(const Color &color) {
    hasBackgroundColor_ = true;
    backgroundColor_ = color;
  }

  virtual void renderAll(ScreenViewport screenViewport, float scale) {
    computeViewport(screenViewport, scale);
    drawBackground();

    render();
    drawChildren();
  }

  virtual bool handleTouchEvent(const TouchManager::TouchEvent &screenTouchEvent) {
    // 1. Is this touch an effective touch?
    if (screenTouchEvent.event == TouchManager::Event::NONE) {
      return false;
    }

    // 2. Is this touch inside the layout?
    if (isPointInside(screenTouchEvent.touchPos)) {
      // Convert to local coordinate
      CanvasPosition canvasPos {convert(screenTouchEvent.touchPos.x, screenTouchEvent.touchPos.y)};

      if (onTouch(canvasPos.x, canvasPos.y, screenTouchEvent.event)) {
        return true;
      }

      for (Layout *child : children_) {
        if (child->handleTouchEvent(screenTouchEvent)) {
          return true;
        }
      }
      return false;
    } else {
      return false;
    }
  }

  virtual CanvasPosition convert(float screenX, float screenY) {
    CanvasPosition canvasPos;
    canvasPos.x = static_cast<std::size_t>(screenX - screenViewport_.x);
    canvasPos.y = static_cast<std::size_t>(screenY - screenViewport_.y);
    return canvasPos;
  }

  virtual bool onTouch(std::size_t x, std::size_t y, TouchManager::Event event) {
    return false;
  }

  // Customer should implement this functions
  virtual void render() {};    // Let customer to implement this function
  virtual bool onTouchDown(std::size_t x, std::size_t y) {
    return false;
  };


protected:
  virtual void computeViewport(ScreenViewport screenViewport, float scale) {
    screenViewport_ = screenViewport;
    viewportScale_ = scale;
  }
  virtual void drawBackground() {
    if (hasBackgroundColor_) {
      DrawRectangle(screenViewport_.x, screenViewport_.y, screenViewport_.w, screenViewport_.h, backgroundColor_);
    }
  }

  virtual bool isPointInside(const Vector2 &point) {
    return (point.x >= screenViewport_.x) && (point.x <= screenViewport_.x + screenViewport_.w) &&
           (point.y >= screenViewport_.y) && (point.y <= screenViewport_.y + screenViewport_.h);
  }

  virtual void drawChildren() {
    for (Layout *child : children_) {
      child->renderAll(screenViewport_, viewportScale_);
    }
  }
  virtual void rectangle(CanvasArea canvasArea, Color color) {
    DrawRectangle(screenViewport_.x + (canvasArea.x * viewportScale_),
                  screenViewport_.y + (canvasArea.y * viewportScale_),
                  canvasArea.w * viewportScale_,
                  canvasArea.h * viewportScale_,
                  color);
  }
  void ring(std::size_t x,
            std::size_t y,
            std::size_t innerRadius,
            std::size_t outerRadius,
            float startAngle,
            float endAngle,
            int segments,
            Color color) {
    DrawRing(Vector2 {(x * viewportScale_) + screenViewport_.x, (y * viewportScale_) + screenViewport_.y},
             innerRadius * viewportScale_,
             outerRadius * viewportScale_,
             startAngle,
             endAngle,
             segments,
             color);
  }

  virtual void circle(std::size_t x, std::size_t y, std::size_t radius, Color color) {
    DrawCircle((x * viewportScale_) + screenViewport_.x,
               (y * viewportScale_) + screenViewport_.y,
               radius * viewportScale_,
               color);
  }

  virtual void line(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, float thick, Color color) {
    DrawLineEx({(x1 * viewportScale_) + screenViewport_.x, (y1 * viewportScale_) + screenViewport_.y},
               {(x2 * viewportScale_) + screenViewport_.x, (y2 * viewportScale_) + screenViewport_.y},
               thick * viewportScale_,
               color);
  }

  virtual void text(const char *text, std::size_t x, std::size_t y, std::size_t height, Color color) {
    DrawText(text,
             screenViewport_.x + (x * viewportScale_),
             screenViewport_.y + (y * viewportScale_),
             height * viewportScale_,
             color);
  }

  virtual void textAlignRight(const char ch, std::size_t x, std::size_t y, std::size_t height, Color color) {
    if (ch == '\0') {
      return;
    }
    char buffer[2] = {ch, '\0'};
    textAlignRight(buffer, x, y, height, color);
  }

  virtual void textAlignRight(const char *text, std::size_t x, std::size_t y, std::size_t height, Color color) {
    // Calculate the width of the text
    int textWidth = MeasureText(text, height * viewportScale_);
    const std::size_t px = screenViewport_.x + (x * viewportScale_) - textWidth;
    const std::size_t py = screenViewport_.y + (y * viewportScale_);
    DrawText(text, px, py, height * viewportScale_, color);
  }
  virtual void textAlignCenterCenter(const char *text, std::size_t x, std::size_t y, std::size_t height, Color color) {
    Vector2 textSize = {0.0f, 0.0f};
    int fontSize = height * viewportScale_;

    constexpr int defaultFontSize = 10;    // Default Font chars height in pixel
    if (fontSize < defaultFontSize)
      fontSize = defaultFontSize;
    const int spacing = fontSize / defaultFontSize;

    // Check if default font has been loaded
    if (GetFontDefault().texture.id != 0) {
      textSize = MeasureTextEx(GetFontDefault(), text, (float)fontSize, (float)spacing);
    }

    {
      const std::size_t px = screenViewport_.x + (x * viewportScale_) - (textSize.x / 2);
      const std::size_t py = screenViewport_.y + (y * viewportScale_) - (textSize.y / 2);
      DrawText(text, px, py, fontSize, color);
    }
  }
  virtual void textAlignCenterCenter(
    const char *text, std::size_t x, std::size_t y, std::size_t height, Color color, Color backColor) {
    Vector2 textSize = {0.0f, 0.0f};
    int fontSize = height * viewportScale_;

    constexpr int defaultFontSize = 10;    // Default Font chars height in pixel
    if (fontSize < defaultFontSize)
      fontSize = defaultFontSize;
    const int spacing = fontSize / defaultFontSize;

    // Check if default font has been loaded
    if (GetFontDefault().texture.id != 0) {
      textSize = MeasureTextEx(GetFontDefault(), text, (float)fontSize, (float)spacing);
    }

    constexpr std::size_t padding = 3;
    {
      const std::size_t px = screenViewport_.x + (x * viewportScale_) - (textSize.x / 2) - padding;
      const std::size_t py = screenViewport_.y + (y * viewportScale_) - (textSize.y / 2) - padding;
      DrawRectangle(px, py, textSize.x + 2 * padding, textSize.y + 2 * padding, backColor);
    }
    {
      const std::size_t px = screenViewport_.x + (x * viewportScale_) - (textSize.x / 2);
      const std::size_t py = screenViewport_.y + (y * viewportScale_) - (textSize.y / 2);
      DrawText(text, px, py, fontSize, color);
    }
  }


  ScreenViewport screenViewport_ {0U, 0U, 0U, 0U};
  float viewportScale_ {1.0F};

private:
  std::vector<Layout *> children_;

  bool hasBackgroundColor_ {false};
  Color backgroundColor_ {BLACK};
};
}    // namespace ui
}    // namespace qcpilot

#endif