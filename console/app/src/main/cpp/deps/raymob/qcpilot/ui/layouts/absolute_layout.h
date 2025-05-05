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
    AbsoluteLayout(std::size_t x, std::size_t y, std::size_t w, std::size_t h) :
        virtualX_ {x},
        virtualY_ {y},
        virtualW_ {w},
        virtualH_ {h} {}

    virtual void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) override {
        updateViewport(x, y, w, h, scale);
        drawBackground();
        drawContent();
    }


  private:
    std::size_t virtualX_ {0U};
    std::size_t virtualY_ {0U};
    std::size_t virtualW_ {0U};
    std::size_t virtualH_ {0U};

    void updateViewport(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) {
        viewportX_ = static_cast<std::size_t>(x + (static_cast<float>(virtualX_) * scale));
        viewportY_ = static_cast<std::size_t>(y + (static_cast<float>(virtualY_) * scale));
        viewportW_ = static_cast<std::size_t>((static_cast<float>(virtualW_) * scale));
        viewportH_ = static_cast<std::size_t>((static_cast<float>(virtualH_) * scale));
        viewportScale_ = scale;
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
