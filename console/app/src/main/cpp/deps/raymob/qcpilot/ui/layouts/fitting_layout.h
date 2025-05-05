#ifndef __QCPILOT_UI_LAYOUTS_FITTING_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_FITTING_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class FittingLayout : public Layout {
  public:
    FittingLayout(std::size_t w, std::size_t h) : virtualWidth_ {w}, virtualHeight_ {h} {}

    virtual void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) override {
        canvasX_ = x;
        canvasY_ = y;
        canvasW_ = w;
        canvasH_ = h;

        computeViewport();
        drawBackground();
        drawContent();
    }


  private:
    std::size_t virtualWidth_ {0U};
    std::size_t virtualHeight_ {0U};

    std::size_t canvasX_ {0U};
    std::size_t canvasY_ {0U};
    std::size_t canvasW_ {0U};
    std::size_t canvasH_ {0U};


    void computeViewport() {
        // Compute viewport
        const float expectedRatio = static_cast<float>(virtualWidth_) / static_cast<float>(virtualHeight_);
        const float canvasRatio = static_cast<float>(canvasW_) / static_cast<float>(canvasH_);

        if (canvasRatio > expectedRatio) {
            viewportH_ = canvasH_;
            viewportW_ = canvasH_ * expectedRatio;
            viewportScale_ = static_cast<float>(canvasH_) / static_cast<float>(virtualHeight_);
            viewportX_ = canvasX_ + ((canvasW_ - viewportW_) / 2);
            viewportY_ = canvasY_;
        } else {
            viewportW_ = canvasW_;
            viewportH_ = canvasW_ / expectedRatio;
            viewportScale_ = static_cast<float>(canvasW_) / static_cast<float>(virtualWidth_);
            viewportX_ = canvasX_;
            viewportY_ = canvasY_ + ((canvasH_ - viewportH_) / 2);
        }
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
