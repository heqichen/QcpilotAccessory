#ifndef __QCPILOT_UI_LAYOUTS_BRAKE_PEDAL_LAYOUT_H__
#define __QCPILOT_UI_LAYOUTS_BRAKE_PEDAL_LAYOUT_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class Pedal : public AbsoluteLayout {
  public:
    Pedal(const char *text, CanvasArea canvasArea, Color fillColor) :
        AbsoluteLayout {canvasArea},
        text_ {text},
        fillColor_ {fillColor} {}
    void setValue(float value) {
        value_ = value;
    }

  protected:
  private:
    const char *text_;
    const Color fillColor_;
    float value_ {0U};
    virtual void render() override {
        text(text_, 10, 5, 30, WHITE);

        const std::size_t x = 30;
        const std::size_t y = 50;
        const std::size_t w = canvasArea_.w - 60;
        const std::size_t h = 30;
        const std::size_t b = 4;
        // outline
        rectangle({x - b, y - b, w + b * 2, h + b * 2}, WHITE);
        rectangle({x, y, w, h}, BLACK);
        // fill
        const std::size_t fillWidth = static_cast<std::size_t>(w * value_);
        rectangle({x, y, fillWidth, h}, fillColor_);
    }
};

}    // namespace ui
}    // namespace qcpilot
#endif
