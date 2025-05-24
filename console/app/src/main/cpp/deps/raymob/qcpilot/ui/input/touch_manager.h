#ifndef __QCPILOT_UI_INPUT_TOUCH_MANAGER_H__
#define __QCPILOT_UI_INPUT_TOUCH_MANAGER_H__

#include <cstdint>
#include <cstdio>
#include "raylib.h"

namespace qcpilot {
namespace ui {
class TouchManager {
  public:
    enum class Event : uint8_t {
        NONE = 0,
        DOWN,
        MOVE,
        UP,
    };

    struct TouchEvent {
        Vector2 touchPos {0.0F, 0.0F};
        Event event {Event::NONE};
    };


    TouchManager();
    virtual ~TouchManager();

    void tick();
    TouchEvent getTouchEvent() const {
        return touchEvent_;
    }

  private:
    std::size_t lastTouchCount_ {0U};
    TouchEvent touchEvent_ {};
};
}    // namespace ui
}    // namespace qcpilot


#endif
