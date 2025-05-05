#include "raymob/qcpilot/data_def.h"
#include "raymob/qcpilot/ui/platform.h"

namespace qcpilot {
namespace platform {

shott::ConsoleFrame fetchConsoleFrame() {
    shott::ConsoleFrame ret {};
    ret.engineRpm = 123;
    return ret;
}

}    // namespace platform
}    // namespace qcpilot