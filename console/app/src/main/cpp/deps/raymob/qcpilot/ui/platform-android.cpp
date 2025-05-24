#include <android/log.h>
#include <cereal/archives/portable_binary.hpp>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <string>
#include "qcpilot/data_def.h"
#include "qcpilot/jni_adaptor.h"
#include "qcpilot/ui/platform.h"


namespace qcpilot {
    namespace platform {
        namespace {

            constexpr std::size_t kBufferSize{10240U};
            constexpr std::size_t kConsoleFramePackedSize{23U};
            const std::uint8_t *buffer[kBufferSize];

            std::chrono::time_point<std::chrono::steady_clock> lastFrameReceivedTime =
                    std::chrono::time_point<std::chrono::steady_clock>::min();

            shott::ConsoleFrame lastSuccessFrame{};
        }    // namespace

        shott::ConsoleFrame fetchConsoleFrame() {
            std::size_t bufferReadSize{0U};
            shott::ConsoleFrame frame{};
            fetchPacket((char *) buffer, kBufferSize, &bufferReadSize);
            if (bufferReadSize == kConsoleFramePackedSize) {
                std::istringstream iss(std::string((char *)buffer,
                                       bufferReadSize), std::ios::binary);
                cereal::PortableBinaryInputArchive ar(iss);
                ar(frame);

                lastFrameReceivedTime = std::chrono::steady_clock::now();
                lastSuccessFrame = frame;
            } else {
                // __android_log_print(ANDROID_LOG_ERROR, "QC", "buffer size incorrect: [%u]", bufferSize);
            }
            return lastSuccessFrame;
        }

        std::uint64_t getLastReceivedElapsedMillis() {
            std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
            const std::chrono::milliseconds duration =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                            currentTime - lastFrameReceivedTime);
            return static_cast<std::uint64_t>(duration.count());
        }


// ConsoleFrame getConsoleFrame() {
//   readPacket();
//   ConsoleFrame frame {};
//   const std::uint8_t *buffer = getBuffer();
//   const std::uint32_t bufferSize = getBufferSize();


//   if (bufferSize != 23U) {
//     //                __android_log_print(ANDROID_LOG_ERROR, "QC", "buffer size incorrect: [%u]",
//     //                                    bufferSize);
//   } else {
//     std::istringstream iss(std::string((char *)buffer, bufferSize), std::ios::binary);
//     cereal::PortableBinaryInputArchive ar(iss);
//     ar(frame);
//   }
//   return frame;
// }

// std::uint64_t getLastReceivedElapsedMillis() {
//   return a_getLastReceivedElapsedMillis();
// }

    }    // namespace shott
}    // namespace qcpilot

// namespace qcpilot {
// namespace platform {

// shott::ConsoleFrame fetchConsoleFrame() {
//   const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
//   return frame;
// }

// std::uint64_t getLastReceivedElapsedMillis() {
//   return qcpilot::shott::getLastReceivedElapsedMillis();
// }
// }    // namespace platform
// }    // namespace qcpilot