#ifndef __QCPILOT_UI_LAYOUTS_BUTTON_H__
#define __QCPILOT_UI_LAYOUTS_BUTTON_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {

class Button : public AbsoluteLayout {
  public:
    Button(CanvasArea canvasArea) : AbsoluteLayout {canvasArea}, isTouchDown_ {false} {}

    void render() override {
        Color color = WHITE;
        bool isCurrentTouchDown = {GetTouchPointCount() > 0};
        if (isCurrentTouchDown) {
            color = RED;
            if (isTouchDown_) {
                // Hold
            } else {
                // down
                Vector2 touchPos {GetTouchPosition(0)};
                if (CheckCollisionPointRec(touchPos,
                                           {(float)screenViewport_.x,
                                            (float)screenViewport_.y,
                                            (float)screenViewport_.w,
                                            (float)screenViewport_.h})) {
                    // Click
                    std::printf("Click\r\n");
                }
            }
        } else {
            color = WHITE;
            if (isTouchDown_) {
                // release
            } else {
                // nothing
            }
        }

        isTouchDown_ = isCurrentTouchDown;

        rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, color);
    }

  private:
    bool isTouchDown_ {false};
};
}    // namespace ui
}    // namespace qcpilot
#endif
