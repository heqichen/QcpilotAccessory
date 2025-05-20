#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
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

    ret.ax = std::cos(static_cast<float>(count % 89) / 89.0 * 2 * 3.1415) * 6;
    // if (ret.ax < 0)
    //     ret.ax = 0;
    ret.ay = std::sin(static_cast<float>(count % 53) / 53.0 * 2 * 3.1415) * 1;

    ret.brake = (float)((count / 1) % 256) / 256.0;
    ret.gas = (float)((count / 1) % 256) / 256.0;

    return ret;
}

std::uint64_t getLastReceivedElapsedMillis() {
    // const std::chrono::time_point<std::chrono::steady_clock> start =
    //   std::chrono::time_point<std::chrono::steady_clock>::min();
    // const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    // std::printf("%lu\r\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 500;
}

}    // namespace platform
}    // namespace qcpilot