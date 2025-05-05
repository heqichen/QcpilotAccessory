#ifndef __QCPILOT_UI_ENTRY_H__
#define __QCPILOT_UI_ENTRY_H__

#include "qcpilot/ui/layouts/absolute_layout.h"
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/horizontal_layout.h"
#include "qcpilot/ui/layouts/layout.h"

namespace qcpilot {
namespace ui {

class Entry {
  public:
    Entry(int width, int height);
    void start();

  private:
    void tick();

    FittingLayout mainLayout_;
    AbsoluteLayout absoluteLayout_;
    EngineRpmBar engineRpmBar_;
};

}    // namespace ui
}    // namespace qcpilot

#endif
