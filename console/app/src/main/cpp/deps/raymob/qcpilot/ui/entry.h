#ifndef __QCPILOT_UI_ENTRY_H__
#define __QCPILOT_UI_ENTRY_H__

#include "qcpilot/ui/input/touch_manager.h"
#include "qcpilot/ui/layouts/acceleration.h"
#include "qcpilot/ui/layouts/button.h"
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/engine_rpm_text.h"
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/indicator.h"
#include "qcpilot/ui/layouts/link_state.h"
#include "qcpilot/ui/layouts/pedal.h"
#include "qcpilot/ui/layouts/speed_text.h"
#include "qcpilot/ui/layouts/text_box.h"

namespace qcpilot {
namespace ui {

class Entry {
public:
  Entry(int width, int height);
  void start();

private:
  void tick();

  TouchManager touchManager_;

  FittingLayout mainLayout_;
  EngineRpmBar engineRpmBar_;
  EngineRpmText engineRpmText_;
  SpeedText speedText_;
  Acceleration acceleration_;
  Pedal brakePedal_;
  Pedal gasPedal_;
  LinkState linkState_;
  TextBox textBox_;
  Button meterButton_;
  Button adasButton_;
  Indicator meterIndicator_;
  Indicator adasIndicator_;
};

}    // namespace ui
}    // namespace qcpilot

#endif
