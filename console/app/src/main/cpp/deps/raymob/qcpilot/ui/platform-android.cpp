#include <qcpilot/helper.h>
#include "qcpilot/data_def.h"
#include "qcpilot/ui/platform.h"


namespace qcpilot {
namespace platform {

shott::ConsoleFrame fetchConsoleFrame() {
    const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
    return frame;
}
}    // namespace platform
}    // namespace qcpilot