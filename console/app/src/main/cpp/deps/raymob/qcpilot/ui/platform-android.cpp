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
            std::uint8_t buffer[kBufferSize];
            int intBuffer[kBufferSize];

            constexpr std::size_t kConsoleFramePackedSize{23U};


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

        std::vector<ui::KeyboardEvent> fetchKeyboardEvents() {
            std::size_t bufferReadSize{0U};
            fetchKeyboardEventList(intBuffer, kBufferSize, &bufferReadSize);
            std::vector<ui::KeyboardEvent> events;
            if ((bufferReadSize % 2) == 0) {
                for (std::size_t i = 0; i < bufferReadSize; i += 2) {
                    ui::KeyboardEvent evt;
                    evt.keyCode = intBuffer[i];
                    if (intBuffer[i + 1] == 1) {
                        evt.type = ui::KeyboardEvent::Type::KeyDown;
                    } else {
                        evt.type = ui::KeyboardEvent::Type::KeyUp;
                    }
                    events.push_back(evt);
                }
            } else {
                // __android_log_print(ANDROID_LOG_ERROR, "QC", "keyboard event list size is not even: [%u]", bufferReadSize);
            }
            return events;
        }

    }    // namespace platform
}    // namespace qcpilot
