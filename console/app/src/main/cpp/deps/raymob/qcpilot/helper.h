//
// Created by heqichen on 2025/5/5.
//

#ifndef QCPILOTCONSOLE_HELPER_H
#define QCPILOTCONSOLE_HELPER_H

#include "qcpilot/adaptor.h"
#include "qcpilot/data_def.h"
#include "qcpilot/adaptor.h"
#include <cstdint>
#include <cstdio>
#include <android/log.h>
#include <sstream>
#include <string>
#include <cereal/archives/portable_binary.hpp>

namespace qcpilot {
    namespace shott {
        ConsoleFrame getConsoleFrame() {
            readPacket();
            ConsoleFrame frame{};
            const std::uint8_t *buffer = getBuffer();
            const std::uint32_t bufferSize = getBufferSize();

            if (bufferSize != 23U) {
                __android_log_print(ANDROID_LOG_ERROR, "QC", "buffer size incorrect: [%u]",
                                    bufferSize);
            } else {
                std::istringstream iss(std::string((char *)buffer, bufferSize), std::ios::binary);
                cereal::PortableBinaryInputArchive ar(iss);
                ar(frame);
            }


            return frame;
        }
    }
}


#endif //QCPILOTCONSOLE_HELPER_H
