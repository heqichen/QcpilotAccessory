#ifndef __QCPILOT_UI_LAYOUTS_SPEED_TEXT_H__
#define __QCPILOT_UI_LAYOUTS_SPEED_TEXT_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class SpeedText : public AbsoluteLayout {
  public:
    SpeedText(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {}

    void setSpeed(float speed) {
        speed_ = speed;
    }

  private:
    float speed_ {0.0F};
    void render() override {
        drawText();
    }


    void drawText() {
        bool isNegative = false;
        int speedDigit = static_cast<int>(speed_ * 10);
        if (speedDigit < 0) {
            speedDigit = -speedDigit;
            isNegative = true;
        }
        char text[4] = {'\0', '\0', '\0', '\0'};    // (sign + 3 digits) + decimal

        std::size_t i {0U};
        for (; i < 4U; ++i) {
            if (speedDigit == 0) {
                break;
            }
            text[i] = '0' + (speedDigit % 10);
            speedDigit /= 10;
        }
        if (i < 2U) {
            i = 2U;
            text[0] = '0';
            text[1] = '0';
        }
        if (isNegative && i < 4U) {
            text[i] = '-';
        }
        textAlignRight(text[0], canvasArea_.w - 25, 75, 100, GRAY);
        textAlignRight('.', canvasArea_.w - 90, 100, 75, GRAY);
        textAlignRight(text[1], canvasArea_.w - 130, 55, 125, WHITE);
        textAlignRight(text[2], canvasArea_.w - 205, 55, 125, WHITE);
        textAlignRight(text[3], canvasArea_.w - 280, 55, 125, WHITE);
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
