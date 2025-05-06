#ifndef __QCPILOT_UI_ENTRY_H__
#define __QCPILOT_UI_ENTRY_H__


#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/engine_rpm_text.h"
#include "qcpilot/ui/layouts/fitting_layout.h"


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
};

}    // namespace ui
}    // namespace qcpilot

#endif
