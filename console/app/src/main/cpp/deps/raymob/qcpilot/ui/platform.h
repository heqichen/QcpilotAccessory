#ifndef __QCPILOT_UI_PLATFORM_H__
#define __QCPILOT_UI_PLATFORM_H__

#include <cstdint>
#include "qcpilot/data_def.h"
namespace qcpilot {
namespace platform {

shott::ConsoleFrame fetchConsoleFrame();
std::uint64_t getLastReceivedElapsedMillis();

}    // namespace platform
}    // namespace qcpilot

#endif
