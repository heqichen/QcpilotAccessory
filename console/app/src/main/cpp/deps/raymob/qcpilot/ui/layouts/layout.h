#ifndef __QCPILOT_UI_LAYOUTS_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include "raylib.h"

namespace qcpilot {
namespace ui {
class Layout {
  public:
    Layout(std::size_t w, std::size_t h) : virtualWidth_ {w}, virtualHeight_ {h} {}

    void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h) {
        canvasX_ = x;
        canvasY_ = y;
        canvasW_ = w;
        canvasH_ = h;

        computeViewport();
        drawBackground();
    }

    void setBackgroundColor(const Color color) {
        hasBackgroundColor_ = true;
        backgroundColor_ = color;
    }

  private:
    std::size_t virtualWidth_ {0U};
    std::size_t virtualHeight_ {0U};

    std::size_t canvasX_ {0U};
    std::size_t canvasY_ {0U};
    std::size_t canvasW_ {0U};
    std::size_t canvasH_ {0U};

    std::size_t viewportX_ {0U};
    std::size_t viewportY_ {0U};
    std::size_t viewportW_ {0U};
    std::size_t viewportH_ {0U};
    float viewportScale {1.0F};

    bool hasBackgroundColor_ {false};
    Color backgroundColor_ {BLACK};

    void computeViewport() {
        // Compute viewport
        const float expectedRatio = static_cast<float>(virtualWidth_) / static_cast<float>(virtualHeight_);
        const float canvasRatio = static_cast<float>(canvasW_) / static_cast<float>(canvasH_);

        if (canvasRatio > expectedRatio) {
            viewportH_ = canvasH_;
            viewportW_ = canvasH_ * expectedRatio;
            viewportScale = static_cast<float>(canvasH_) / static_cast<float>(virtualHeight_);
            viewportX_ = canvasX_ + ((canvasW_ - viewportW_) / 2);
            viewportY_ = canvasY_;
        } else {
            viewportW_ = canvasW_;
            viewportH_ = canvasW_ / expectedRatio;
            viewportScale = static_cast<float>(canvasW_) / static_cast<float>(virtualWidth_);
            viewportX_ = canvasX_;
            viewportY_ = canvasY_ + ((canvasH_ - viewportH_) / 2);
        }
    }


    void drawBackground() {
        if (hasBackgroundColor_) {
            DrawRectangle(viewportX_, viewportY_, viewportW_, viewportH_, backgroundColor_);
        }
    }
};
}    // namespace ui
}    // namespace qcpilot

#endif