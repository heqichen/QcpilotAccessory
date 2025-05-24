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
    explicit FittingLayout(CanvasSize canvasSize) : canvasSize_ {canvasSize} {}


  private:
    const CanvasSize canvasSize_ {};

    virtual void computeViewport(ScreenViewport screenViewport, float scale) override {
        // Compute viewport
        const float expectedRatio = static_cast<float>(canvasSize_.w) / static_cast<float>(canvasSize_.h);
        const float screenRatio = static_cast<float>(screenViewport.w) / static_cast<float>(screenViewport.h);

        if (screenRatio > expectedRatio) {
            screenViewport_.w = static_cast<std::size_t>(screenViewport.h * expectedRatio);
            screenViewport_.h = screenViewport.h;

            screenViewport_.x = static_cast<std::size_t>((screenViewport.w - screenViewport_.w) / 2);
            screenViewport_.y = screenViewport.y;

            viewportScale_ = static_cast<float>(screenViewport.h) / static_cast<float>(canvasSize_.h);


        } else {
            screenViewport_.w = screenViewport.w;
            screenViewport_.h = static_cast<std::size_t>(screenViewport.w / expectedRatio);

            screenViewport_.x = screenViewport.x;
            screenViewport_.y = screenViewport.y + ((screenViewport.h - screenViewport_.h) / 2);

            viewportScale_ = static_cast<float>(screenViewport.w) / static_cast<float>(canvasSize_.w);
        }
    }

    virtual void render() override {
        // DrawText(
        //   TextFormat(
        //     "x:%lu y:%lu w:%lu h:%lu", screenViewport_.x, screenViewport_.y, screenViewport_.w, screenViewport_.h),
        //   // screenViewport_.w,
        //   // screenViewport_.h - 25,
        //   0,
        //   0,
        //   25,
        //   WHITE);
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
