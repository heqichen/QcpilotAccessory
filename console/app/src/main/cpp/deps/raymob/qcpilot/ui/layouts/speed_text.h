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

        // constexpr Color kDarkRed {CLITERAL(Color) {82, 5, 0, 255}};
        // constexpr Color kLightRed {CLITERAL(Color) {255, 37, 23, 255}};
        // constexpr Color kDarkGreen {CLITERAL(Color) {0, 46, 3, 255}};
        // constexpr Color kLightGreen {CLITERAL(Color) {28, 255, 42, 255}};


        // constexpr std::size_t padding = 25;

        // // align same position
        // constexpr std::size_t charNum = 5;
        // const std::size_t charSpan = (canvasArea_.w - padding - padding) / charNum;

        // char text[5] = {'0', '0', '0', '0', '0'};
        // std::size_t exp = 1U;
        // std::size_t rpm = rpm_;
        // for (std::size_t i = 0U; i < charNum; ++i) {
        //     text[i] = '0' + rpm % 10;
        //     rpm /= 10;
        //     if (rpm == 0U) {
        //         break;
        //     }
        //     exp++;
        // }

        // const bool redzone = (rpm_ >= 6000U);


        // const std::size_t height = canvasArea_.h - (padding * 2U);

        // for (std::size_t i = 0; i < charNum; ++i) {
        //     const std::size_t x = canvasArea_.w - padding - (i * charSpan);
        //     const std::size_t y = padding;
        //     Color color = WHITE;
        //     if (redzone) {
        //         if (i < exp) {
        //             color = kLightRed;
        //         } else {
        //             color = kDarkRed;
        //         }

        //     } else {
        //         if (i < exp) {
        //             color = kLightGreen;
        //         } else {
        //             color = kDarkGreen;
        //         }
        //     }
        //     textAlignRight(text[i], x, y, height, color);
        // }
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
