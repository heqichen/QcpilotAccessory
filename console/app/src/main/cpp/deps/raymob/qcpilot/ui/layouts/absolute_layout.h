#ifndef __QCPILOT_UI_LAYOUTS_ABSOLUTE_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_ABSOLUTE_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class AbsoluteLayout : public Layout {
  public:
    AbsoluteLayout(CanvasArea canvasArea) : canvasArea_ {canvasArea} {}

  protected:
    const CanvasArea canvasArea_ {};

  private:
    virtual void computeViewport(ScreenViewport screenViewport, float scale) override {
        screenViewport_.x = screenViewport.x + canvasArea_.x * scale;
        screenViewport_.y = screenViewport.y + canvasArea_.y * scale;
        screenViewport_.w = canvasArea_.w * scale;
        screenViewport_.h = canvasArea_.h * scale;
        viewportScale_ = scale;
    }
};

}    // namespace ui
}    // namespace qcpilot
#endif
