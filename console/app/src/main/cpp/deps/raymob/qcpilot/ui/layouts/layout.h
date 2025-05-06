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
    virtual void textAlignRight(const char *text, std::size_t x, std::size_t y, std::size_t height, Color color) {
        // Calculate the width of the text
        int textWidth = MeasureText(text, height);
        DrawText(text,
                 screenViewport_.x + x * viewportScale_ - textWidth,
                 screenViewport_.y * viewportScale_,
                 height * viewportScale_,
                 color);
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