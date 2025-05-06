#include "raymob/qcpilot/data_def.h"
#include "raymob/qcpilot/ui/platform.h"

namespace qcpilot {
namespace platform {

static int v = 0;

shott::ConsoleFrame fetchConsoleFrame() {
    v += 100;
    if (v > 8000)
        v = 0;
    shott::ConsoleFrame ret {};
    ret.engineRpm = v;
    return ret;
}

}    // namespace platform
}    // namespace qcpilot