#ifndef __QCPILOT_UI_LAYOUTS_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include <vector>
#include "raylib.h"

namespace qcpilot {
namespace ui {
class Layout {
  public:
    virtual void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) = 0;
    virtual void addChild(Layout &layout) {
        children_.push_back(&layout);
    }

    virtual void setBackgroundColor(const Color color) {
        hasBackgroundColor_ = true;
        backgroundColor_ = color;
    }

  protected:
    virtual void drawBackground() {
        if (hasBackgroundColor_) {
            DrawRectangle(viewportX_, viewportY_, viewportW_, viewportH_, backgroundColor_);
        }
    }

    virtual void drawContent() {
        for (Layout *child : children_) {
            child->render(viewportX_, viewportY_, viewportW_, viewportH_, viewportScale_);
        }
    }

    std::size_t viewportX_ {0U};
    std::size_t viewportY_ {0U};
    std::size_t viewportW_ {0U};
    std::size_t viewportH_ {0U};
    float viewportScale_ {1.0F};

  private:
    std::vector<Layout *> children_;

    bool hasBackgroundColor_ {false};
    Color backgroundColor_ {BLACK};
};
}    // namespace ui
}    // namespace qcpilot

#endif