#include "qcpilot/ui/input/touch_manager.h"
#include <cstdint>
#include "raylib.h"

namespace qcpilot {
namespace ui {

TouchManager::TouchManager() : lastTouchCount_ {0U}, touchEvent_ {} {}
TouchManager::~TouchManager() {}

void TouchManager::tick() {
    std::size_t currentTouchCount = GetTouchPointCount();
    Vector2 touchPos {GetTouchPosition(0)};

    if ((lastTouchCount_ == 0) && (currentTouchCount > 0)) {
        touchEvent_.touchPos = touchPos;
        touchEvent_.event = Event::DOWN;
    } else if ((lastTouchCount_ > 0) && (currentTouchCount > 0)) {
        touchEvent_.touchPos = touchPos;
        touchEvent_.event = Event::MOVE;
    } else if ((lastTouchCount_ > 0) && (currentTouchCount == 0)) {
        touchEvent_.touchPos = touchPos;
        touchEvent_.event = Event::UP;
    } else {
        touchEvent_.touchPos = touchPos;
        touchEvent_.event = Event::NONE;
    }
    lastTouchCount_ = currentTouchCount;
}


}    // namespace ui
}    // namespace qcpilot
