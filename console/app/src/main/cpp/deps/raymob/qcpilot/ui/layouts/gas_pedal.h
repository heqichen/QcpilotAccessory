#ifndef __QCPILOT_UI_LAYOUTS_GAS_PEDAL_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_GAS_PEDAL_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class GasPedal : public AbsoluteLayout {
  public:
    GasPedal(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {}

  protected:
  private:
};

}    // namespace ui
}    // namespace qcpilot
#endif
