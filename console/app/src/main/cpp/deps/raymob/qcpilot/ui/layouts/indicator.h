#ifndef __QCPILOT_UI_LAYOUTS_INDICATOR_H__
#define __QCPILOT_UI_LAYOUTS_INDICATOR_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "qcpilot/ui/settings.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {


class Indicator : public AbsoluteLayout {
public:
  Indicator(CanvasArea canvasArea) : AbsoluteLayout {canvasArea}, enabled_ {false} {}

  void setEnabled(bool enabled) {
    enabled_ = enabled;
  }

private:
  void render() override {
    if (enabled_) {
      rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, Color {2, 169, 247, 255});
    } else {
      rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, kBackground);
    }
  }

  bool enabled_ {false};
};
}    // namespace ui
}    // namespace qcpilot
#endif
