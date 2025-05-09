#ifndef __QCPILOT_UI_ENTRY_H__
#define __QCPILOT_UI_ENTRY_H__


#include "qcpilot/ui/layouts/acceleration.h"
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/engine_rpm_text.h"
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/pedal.h"
#include "qcpilot/ui/layouts/speed_text.h"

namespace qcpilot {
namespace ui {

class Entry {
  public:
    Entry(int width, int height);
    void start();

  private:
    void tick();

    FittingLayout mainLayout_;
    EngineRpmBar engineRpmBar_;
    EngineRpmText engineRpmText_;
    SpeedText speedText_;
    Acceleration acceleration_;
    Pedal brakePedal_;
    Pedal gasPedal_;
};

}    // namespace ui
}    // namespace qcpilot

#endif
