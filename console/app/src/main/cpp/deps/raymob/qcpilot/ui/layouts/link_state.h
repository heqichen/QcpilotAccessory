#ifndef __QCPILOT_UI_LAYOUTS_LINK_STATE_H__
#define __QCPILOT_UI_LAYOUTS_LINK_STATE_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {

class LinkState : public AbsoluteLayout {
  public:
    LinkState(CanvasArea canvasArea) : AbsoluteLayout {canvasArea}, millis_ {0ULL} {}

    void setLastReceivedPacketElapsedMillis(std::uint64_t millis) {
        millis_ = millis;
    };

    void render() override {
        Color color = millis_ > 1000ULL ? RED : GREEN;
        circle(canvasArea_.w / 2, canvasArea_.h / 2, canvasArea_.w / 4, color);
    }

  private:
    std::uint64_t millis_ {0ULL};
};
}    // namespace ui
}    // namespace qcpilot
#endif
