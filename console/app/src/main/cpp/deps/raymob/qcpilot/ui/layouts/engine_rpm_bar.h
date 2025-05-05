#ifndef __QCPILOT_UI_LAYOUTS_ENGINE_RPM_BAR_H__
#define __QCPILOT_UI_LAYOUTS_ENGINE_RPM_BAR_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class EngineRpmBar : public Layout {
  public:
    EngineRpmBar(std::size_t x, std::size_t y, std::size_t w, std::size_t h) :
        virtualX_ {x},
        virtualY_ {y},
        virtualW_ {w},
        virtualH_ {h} {}

    virtual void render(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) override {
        updateViewport(x, y, w, h, scale);
        drawBackground();
        drawBars();
    }

    void setRpm(std::uint32_t rpm) {
        rpm_ = rpm;
    }

  private:
    std::size_t virtualX_ {0U};
    std::size_t virtualY_ {0U};
    std::size_t virtualW_ {0U};
    std::size_t virtualH_ {0U};


    std::uint32_t rpm_ {0U};

    void updateViewport(std::size_t x, std::size_t y, std::size_t w, std::size_t h, float scale) {
        viewportX_ = static_cast<std::size_t>(x + (static_cast<float>(virtualX_) * scale));
        viewportY_ = static_cast<std::size_t>(y + (static_cast<float>(virtualY_) * scale));
        viewportW_ = static_cast<std::size_t>((static_cast<float>(virtualW_) * scale));
        viewportH_ = static_cast<std::size_t>((static_cast<float>(virtualH_) * scale));
        viewportScale_ = scale;
    }

    void rectangle(std::size_t vx, std::size_t vy, std::size_t vw, std::size_t vh, Color color) {
        DrawRectangle(viewportX_ + (vx * viewportScale_),
                      viewportY_ + (vy * viewportScale_),
                      vw * viewportScale_,
                      vh * viewportScale_,
                      color);
    }

    void drawBars() {
        constexpr Color kDarkRed {CLITERAL(Color) {82, 5, 0, 255}};
        constexpr Color kLightRed {CLITERAL(Color) {255, 37, 23, 255}};
        constexpr Color kDarkGreen {CLITERAL(Color) {0, 46, 3, 255}};
        constexpr Color kLightGreen {CLITERAL(Color) {28, 255, 42, 255}};


        constexpr std::size_t padding = 25;
        constexpr std::size_t barNums = 40;
        constexpr std::size_t borderWidth = 4;

        const std::size_t barSpan = (virtualW_ - (padding * 2U) + borderWidth) / barNums;
        const std::size_t barWidth = barSpan - borderWidth;
        const std::size_t barHeight = (virtualH_ - (padding * 2U));

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


            rectangle(x, padding, barWidth, barHeight, color);
        }
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
