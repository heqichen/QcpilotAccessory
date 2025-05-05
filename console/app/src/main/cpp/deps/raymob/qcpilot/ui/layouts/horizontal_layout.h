#ifndef __QCPILOT_UI_LAYOUTS_HORIZONTAL_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_HORIZONTAL_LAYOUT_H__

#include <cstdint>
#include "qcpilot/ui/layouts/layout.h"


namespace qcpilot {
namespace ui {
class HorizontalLayout : public Layout {
  public:
    HorizontalLayout() {}
    virtual void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h) {}

  private:
};
}    // namespace ui
}    // namespace qcpilot

#endif
