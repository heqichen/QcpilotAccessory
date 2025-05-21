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

namespace {
Color mapColor(const std::size_t size, const std::size_t idx) {
    // 230 41 55 255 -> 100 64 0 90
    // 255 95 109 255 -> 255 195 113 90

    const unsigned char r = map<std::size_t>(idx, 0, size - 1, 255, 255);
    const unsigned char g = map<std::size_t>(idx, 0, size - 1, 95, 150);
    const unsigned char b = map<std::size_t>(idx, 0, size - 1, 109, 113);
    const unsigned char a = map<std::size_t>(idx, 0, size - 1, 130, 90);
    return Color {r, g, b, a};
}
}    // namespace

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


    inline void drawTrails() {
        // 1. shift history
        for (int i = kHistoryAccSize - 1; i > 0; --i) {
            historyAcc_[i][0] = historyAcc_[i - 1][0];
            historyAcc_[i][1] = historyAcc_[i - 1][1];
        }
        constexpr float kAccMax {5.0F};
        // constrain range to +=5.0G
        historyAcc_[0][0] = std::min(std::max(ax_, -kAccMax), kAccMax);
        historyAcc_[0][1] = std::min(std::max(ay_, -kAccMax), kAccMax);

        // 2. Draw
        // Positive X toward down

        const std::size_t radius = std::min(canvasArea_.w, canvasArea_.h) / 2;
        const std::size_t cx = canvasArea_.w / 2;
        const std::size_t cy = canvasArea_.h / 2;
        const std::size_t lastIdx {kHistoryAccSize - 1U};
        const float lastAx = historyAcc_[lastIdx][0] / 9.80665F;
        float lastPy = cy + (radius * (kOuterRing / 0.5F) * lastAx);
        const float lastAy = historyAcc_[lastIdx][1] / 9.80665F;
        float lastPx = cx + (radius * kOuterRing / 0.5F * lastAy);

        for (int i = kHistoryAccSize - 2U; i >= 0; --i) {
            const float ax = historyAcc_[i][0] / 9.80665F;    // ACCEL TO G
            const float py = cy + (radius * (kOuterRing / 0.5F) * ax);

            const float ay = historyAcc_[i][1] / 9.80665F;    // ACCEL TO G
            const float px = cx + (radius * kOuterRing / 0.5F * ay);


            // circle(px, py, 5, mapColor(kHistoryAccSize, i));
            line(px, py, lastPx, lastPy, 5.0F, mapColor(kHistoryAccSize, i));

            lastPx = px;
            lastPy = py;
        }

        // Highlight the latest point
        const std::size_t latestIdx {0U};
        const float ax = historyAcc_[latestIdx][0] / 9.80665F;    // ACCEL TO G
        const float py = cy + (radius * (kOuterRing / 0.5F) * ax);
        const float ay = historyAcc_[latestIdx][1] / 9.80665F;    // ACCEL TO G
        const float x = cx + (radius * kOuterRing / 0.5F * ay);
        circle(x, py, 5, Color {255, 255, 255, 255});
        circle(x, py, 3, Color {255, 0, 0, 255});
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
