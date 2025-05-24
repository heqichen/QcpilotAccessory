#ifndef __QCPILOT_UI_LAYOUTS_BUTTON_H__
#define __QCPILOT_UI_LAYOUTS_BUTTON_H__

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {
namespace {

constexpr float kShadowWidth {4.0F};
constexpr Color kCoreShadowColor {CLITERAL(Color) {99, 99, 99, 255}};
constexpr Color kCastShadowColor {CLITERAL(Color) {0, 0, 0, 255}};
constexpr Color kBackgroundColor {CLITERAL(Color) {134, 134, 134, 255}};
std::uint32_t kButtonPushdownDuration {70U};    // ms

}    // namespace

class Button : public AbsoluteLayout {
public:
  Button(CanvasArea canvasArea) :
      AbsoluteLayout {canvasArea},
      isTouchDown_ {false},
      pushDownAnimationStartTime_ {std::chrono::time_point<std::chrono::steady_clock>::min()} {
    text_[0] = '\0';
  }

  void render() override {
    const std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - pushDownAnimationStartTime_);

    bool isShowPushDown = (static_cast<std::uint64_t>(duration.count()) < kButtonPushdownDuration);

    rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, kBackgroundColor);
    if (isShowPushDown) {
      // Core Shadow
      line(kShadowWidth, kShadowWidth, canvasArea_.w - kShadowWidth, kShadowWidth, kShadowWidth, kCoreShadowColor);
      line(kShadowWidth, kShadowWidth, kShadowWidth, canvasArea_.h - kShadowWidth, kShadowWidth, kCoreShadowColor);
      // Highlight
      line(0, canvasArea_.h, canvasArea_.w, canvasArea_.h, kShadowWidth, WHITE);
      line(canvasArea_.w, 0, canvasArea_.w, canvasArea_.h, kShadowWidth, WHITE);
      // Cast Shadow
      line(0, 0, canvasArea_.w, 0, kShadowWidth, kCastShadowColor);
      line(0, 0, 0, canvasArea_.h, kShadowWidth, kCastShadowColor);
    } else {
      // Core Shadow
      line(
        canvasArea_.w - kShadowWidth, 0, canvasArea_.w - kShadowWidth, canvasArea_.h, kShadowWidth, kCoreShadowColor);
      line(
        0, canvasArea_.h - kShadowWidth, canvasArea_.w, canvasArea_.h - kShadowWidth, kShadowWidth, kCoreShadowColor);
      // Highlight
      line(0, 0, canvasArea_.w, 0, kShadowWidth, WHITE);
      line(0, 0, 0, canvasArea_.h, kShadowWidth, WHITE);
      // Cast Shadow
      line(0, canvasArea_.h, canvasArea_.w, canvasArea_.h, kShadowWidth, kCastShadowColor);
      line(canvasArea_.w, 0, canvasArea_.w, canvasArea_.h, kShadowWidth, kCastShadowColor);
    }
    textAlignCenterCenter(text_, canvasArea_.w / 2, canvasArea_.h / 2, canvasArea_.h / 2, WHITE);
  }
  virtual bool onTouch(std::size_t x, std::size_t y, TouchManager::Event event) override {
    if (event == TouchManager::Event::DOWN) {
      isTouchDown_ = true;
      pushDownAnimationStartTime_ = std::chrono::steady_clock::now();
    } else {
      isTouchDown_ = false;
    }
    return true;
  }

  virtual void setText(const char *text) {
    std::strncpy(text_, text, 127);
    text_[127] = '\0';
  }

private:
  bool isTouchDown_ {false};
  char text_[128];

  std::chrono::time_point<std::chrono::steady_clock> pushDownAnimationStartTime_;
};
}    // namespace ui
}    // namespace qcpilot
#endif
