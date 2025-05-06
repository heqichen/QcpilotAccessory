#ifndef __QCPILOT_UI_LAYOUTS_ENGINE_RPM_TEXT_H__
#define __QCPILOT_UI_LAYOUTS_ENGINE_RPM_TEXT_H__

#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
class EngineRpmText : public AbsoluteLayout {
  public:
    EngineRpmText(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {}

    void setRpm(std::uint32_t rpm) {
        rpm_ = rpm;
    }

  private:
    std::uint32_t rpm_ {0U};
    void render() override {
        drawText();
    }


    void drawText() {
        constexpr std::size_t padding = 25;
        const std::size_t x = canvasArea_.w - padding;
        const std::size_t y = padding;
        const std::size_t height = canvasArea_.h - (padding * 2U);
        int v = (rpm_ / 100) % 2 == 0 ? 1111 : 8888;
        textAlignRight(TextFormat("%05i", v), x, y, height, WHITE);
        // constexpr Color kDarkRed {CLITERAL(Color) {82, 5, 0, 255}};
        // constexpr Color kLightRed {CLITERAL(Color) {255, 37, 23, 255}};
        // constexpr Color kDarkGreen {CLITERAL(Color) {0, 46, 3, 255}};
        // constexpr Color kLightGreen {CLITERAL(Color) {28, 255, 42, 255}};


        // constexpr std::size_t barNums = 40;
        // constexpr std::size_t borderWidth = 0;
        // char buffer[10];
        // std::sprintf(buffer, "%d", rpm_);
        // std::size_t x = screenViewport_.x + padding * viewportScale_;
        // std::size_t y = screenViewport_.y + padding * viewportScale_;
        // std::size_t height = screenViewport_.h - (padding * 2U) * viewportScale_;
        // // DrawText(buffer, x, screenViewport_.y + padding * viewportScale_, height, LIGHTGRAY);

        // int v = (rpm_ / 100) % 2 == 0 ? 1111 : 8888;
        // DrawText(TextFormat("%05i", v), x, screenViewport_.y + padding * viewportScale_, height, LIGHTGRAY);

        // for (int i = 0; i < 10; ++i) {
        //     int w = GetGlyphInfo(GetFontDefault(), '0' + i).image.width;
        //     std::printf("%d ", w);
        // }
        // std::printf("\r\n");
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
