#ifndef __QCPILOT_UI_LAYOUTS_ENGINE_RPM_BAR_H__
#define __QCPILOT_UI_LAYOUTS_ENGINE_RPM_BAR_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class EngineRpmBar : public AbsoluteLayout {
  public:
    EngineRpmBar(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {}

    void setRpm(std::uint32_t rpm) {
        rpm_ = rpm;
    }

  private:
    std::uint32_t rpm_ {0U};
    void render() override {
        drawBars();
    }


    void drawBars() {
        constexpr Color kDarkRed {CLITERAL(Color) {82, 5, 0, 255}};
        constexpr Color kLightRed {CLITERAL(Color) {255, 37, 23, 255}};
        constexpr Color kDarkGreen {CLITERAL(Color) {0, 46, 3, 255}};
        constexpr Color kLightGreen {CLITERAL(Color) {28, 255, 42, 255}};


        constexpr std::size_t padding = 25;
        constexpr std::size_t barNums = 40;
        constexpr std::size_t borderWidth = 4;

        const std::size_t barSpan = (canvasArea_.w - (padding * 2U) + borderWidth) / barNums;
        const std::size_t barWidth = barSpan - borderWidth;
        const std::size_t barHeight = (canvasArea_.h - (padding * 2U));

        const std::size_t redZoneNum = static_cast<std::size_t>(barNums * 0.8F);
        std::size_t barValue = static_cast<std::size_t>((static_cast<float>(rpm_) / 8000.0) * barNums);
        for (std::size_t i {0U}; i < barNums; ++i) {
            const std::size_t x = padding + (i * barSpan);
            Color color = WHITE;

            if (i > barValue) {
                if (i > (redZoneNum)) {
                    color = kDarkRed;
                } else {
                    color = kDarkGreen;
                }
            } else {
                if (i > (redZoneNum)) {
                    color = kLightRed;
                } else {
                    color = kLightGreen;
                }
            }


            rectangle(CanvasArea {x, padding, barWidth, barHeight}, color);
        }
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
