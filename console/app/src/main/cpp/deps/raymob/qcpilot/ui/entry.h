#ifndef __QCPILOT_UI_ENTRY_H__
#define __QCPILOT_UI_ENTRY_H__

#include "qcpilot/ui/layouts/layout.h"

namespace qcpilot {
namespace ui {

class Entry {
  public:
    Entry(int width, int height);
    void start();

  private:
    void tick();

    Layout mainLayout_;
};

}    // namespace ui
}    // namespace qcpilot

#endif
