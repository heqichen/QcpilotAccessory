//
// Created by heqichen on 2025/5/5.
//

#ifndef QCPILOTCONSOLE_DATA_DEF_H
#define QCPILOTCONSOLE_DATA_DEF_H

#include <cstdint>

namespace qcpilot {
namespace shott {

struct ConsoleFrame {
    std::uint16_t engineRpm {0U};    // RPM
    float speedKph {0.0F};           // km/h
    float brake {0.0F};              // [0, 1]
    float gas {0.0F};                // [0, 1]
    float ax {0.0F};                 // longitudinal m/s
    float ay {0.0F};                 // lateral m/s

    template<class Archive>
    void serialize(Archive &ar) {
        ar(engineRpm, speedKph, brake, gas, ax, ay);
    }
};

}    // namespace shott
}    // namespace qcpilot

#endif //QCPILOTCONSOLE_DATA_DEF_H
