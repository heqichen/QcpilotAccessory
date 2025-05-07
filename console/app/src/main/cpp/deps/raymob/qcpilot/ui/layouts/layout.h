#ifndef __QCPILOT_UI_LAYOUTS_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include <vector>
#include "raylib.h"

namespace qcpilot {
namespace ui {

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

    virtual void setBackgroundColor(const Color color) {
        hasBackgroundColor_ = true;
        backgroundColor_ = color;
    }

    virtual void renderAll(ScreenViewport screenViewport, float scale) {
        computeViewport(screenViewport, scale);
        drawBackground();

        render();
        drawChildren();
    }

    virtual void render() {};    // Let customer to implement this function

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

    void circle(std::size_t x, std::size_t y, std::size_t radius, Color color) {
        DrawCircle((x * viewportScale_) + screenViewport_.x,
                   (y * viewportScale_) + screenViewport_.y,
                   radius * viewportScale_,
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