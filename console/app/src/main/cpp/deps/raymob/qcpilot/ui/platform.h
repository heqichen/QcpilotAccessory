#ifndef __QCPILOT_UI_PLATFORM_H__
#define __QCPILOT_UI_PLATFORM_H__

#include <cstdint>
#include <vector>
#include "qcpilot/data_def.h"

namespace qcpilot {
namespace platform {

namespace ui {

struct KeyboardEvent {
  enum class Type { KeyDown, KeyUp, KeyRepeat };
  std::int32_t keyCode {0U};
  Type type {Type::KeyDown};
};

}    // namespace ui

shott::ConsoleFrame fetchConsoleFrame();
std::uint64_t getLastReceivedElapsedMillis();

std::vector<ui::KeyboardEvent> fetchKeyboardEvents();


}    // namespace platform
}    // namespace qcpilot

#endif
