#include <cmath>
#include "raymob/qcpilot/data_def.h"
#include "raymob/qcpilot/ui/platform.h"

namespace qcpilot {
namespace platform {

static int v = 0;

float speed[] = {0.0F, 9999.0F, 1.0F, -0.0001F, 13.2F, 123.4F, 9999999.9F, -40.0F, -5.99, 23.5};

int count = 0;
shott::ConsoleFrame fetchConsoleFrame() {
    count++;

    v += 100;
    if (v > 8000)
        v = 0;
    shott::ConsoleFrame ret {};
    ret.engineRpm = v;

    // ret.speedKph = 54.1F;
    ret.speedKph = speed[(count / 10) % (sizeof(speed) / sizeof(float))];

    ret.ax = std::cos(static_cast<float>(count % 89) / 89.0 * 2 * 3.1415) * 0.3;
    ret.ay = std::sin(static_cast<float>(count % 53) / 53.0 * 2 * 3.1415) * 0.3;

    ret.brake = (count / 1) % 255;
    ret.gas = (count / 1) % 255;

    return ret;
}

}    // namespace platform
}    // namespace qcpilot