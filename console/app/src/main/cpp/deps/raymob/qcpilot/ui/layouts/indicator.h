#ifndef __QCPILOT_UI_LAYOUTS_INDICATOR_H__
#define __QCPILOT_UI_LAYOUTS_INDICATOR_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {

class Indicator : public AbsoluteLayout {
public:
  Indicator(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {}

private:
  void render() override {
    rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, WHITE);
  }
};
}    // namespace ui
}    // namespace qcpilot
#endif
