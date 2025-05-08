#ifndef __QCPILOT_UI_LAYOUTS_ACCELERATION_H__
#define __QCPILOT_UI_LAYOUTS_ACCELERATION_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {

constexpr std::size_t kHistoryAccSize {60U};
constexpr float kCircleGap {2.0F};
constexpr float kOuterRing {0.9F};                  // 0.5G
constexpr float kInnerRing {0.9F / 0.5F * 0.3F};    // 0.3G

class Acceleration : public AbsoluteLayout {
  public:
    Acceleration(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {
        for (std::size_t i {0U}; i < kHistoryAccSize; ++i) {
            historyAcc_[i][0] = 0.0F;
            historyAcc_[i][1] = 0.0F;
        }
    }

    void setAcceleration(float ax, float ay) {
        ax_ = ax;
        ay_ = ay;
    };

  private:
    float ax_ {0.0F};
    float ay_ {0.0F};


    float historyAcc_[kHistoryAccSize][2];

    void render() override {
        drawGrid();
        drawTrails();
    }

    long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    inline void drawTrails() {
        // 1. shift history
        for (int i = kHistoryAccSize - 1; i > 0; --i) {
            historyAcc_[i][0] = historyAcc_[i - 1][0];
            historyAcc_[i][1] = historyAcc_[i - 1][1];
        }
        historyAcc_[0][0] = ax_;
        historyAcc_[0][1] = ay_;


        // 2. Draw
        const std::size_t radius = std::min(canvasArea_.w, canvasArea_.h) / 2;
        const std::size_t cx = canvasArea_.w / 2;
        const std::size_t cy = canvasArea_.h / 2;
        for (int i = kHistoryAccSize - 1; i >= 0; --i) {
            const float ax = historyAcc_[i][0];
            const float ay = historyAcc_[i][1];
            const float x = cx + radius * kOuterRing / 0.5F * ax;
            const float y = cy + radius * kOuterRing / 0.5F * ay;

            const unsigned char r = map(i, 0, kHistoryAccSize - 1, 230, 100);
            const unsigned char g = map(i, 0, kHistoryAccSize - 1, 41, 64);
            const unsigned char b = map(i, 0, kHistoryAccSize - 1, 55, 0);
            const unsigned char a = map(i, 0, kHistoryAccSize - 1, 255, 90);


            circle(x, y, 5, Color {r, g, b, a});
        }
    }

    inline void drawGrid() {
        const std::size_t radius = std::min(canvasArea_.w, canvasArea_.h) / 2;
        const std::size_t cx = canvasArea_.w / 2;
        const std::size_t cy = canvasArea_.h / 2;
        circle(cx, cy, 4, WHITE);

        // Outer up and down
        ring(cx, cy, (radius * kOuterRing) - 3, radius * kOuterRing, 225 + kCircleGap, 315 - kCircleGap, 20, WHITE);
        ring(cx, cy, (radius * kOuterRing) - 3, radius * kOuterRing, 45 + kCircleGap, 135 - kCircleGap, 20, WHITE);

        // Outer ring left and right
        ring(cx, cy, (radius * kOuterRing) - 2, radius * kOuterRing, 135 + kCircleGap, 225 - kCircleGap, 20, WHITE);
        ring(cx, cy, (radius * kOuterRing) - 2, radius * kOuterRing, -45 + kCircleGap, 45 - kCircleGap, 20, WHITE);

        // Inner up and down
        ring(cx, cy, (radius * kInnerRing) - 3, radius * kInnerRing, 225 + kCircleGap, 315 - kCircleGap, 20, WHITE);
        ring(cx, cy, (radius * kInnerRing) - 3, radius * kInnerRing, 45 + kCircleGap, 135 - kCircleGap, 20, WHITE);

        // Inner ring left and right
        ring(cx, cy, (radius * kInnerRing) - 8, radius * kInnerRing, 135 + kCircleGap, 225 - kCircleGap, 20, WHITE);
        ring(cx, cy, (radius * kInnerRing) - 8, radius * kInnerRing, -45 + kCircleGap, 45 - kCircleGap, 20, WHITE);

        // Axis
        rectangle(CanvasArea {cx - static_cast<std::size_t>(radius * kInnerRing) - 2,
                              cy - 5,
                              static_cast<std::size_t>(radius * kInnerRing * 2) + 4,
                              10},
                  BLACK);    // Background
        rectangle(CanvasArea {0, cy - 2, canvasArea_.w, 2}, WHITE);
        rectangle(CanvasArea {cx - 1, 0, 2, canvasArea_.h}, WHITE);

        // Orion
        circle(cx, cy, 11, BLACK);
        circle(cx, cy, 7, WHITE);

        textAlignCenterCenter("0.5", cx, cy - (radius * kOuterRing) + 5, 22, WHITE, BLACK);    // 5 is offset for font
        textAlignCenterCenter("0.3", cx, cy - (radius * kInnerRing) + 5, 22, WHITE, BLACK);    // 5 is offset for font
    }
};
}    // namespace ui
}    // namespace qcpilot
#endif
