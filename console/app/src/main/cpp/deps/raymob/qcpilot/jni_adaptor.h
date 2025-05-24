#ifndef QCPILOTCONSOLE_QCPILOT_ADAPTOR_H
#define QCPILOTCONSOLE_QCPILOT_ADAPTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// void readPacket();
// uint8_t *getBuffer();
// size_t  getBufferSize();
// uint64_t a_getLastReceivedElapsedMillis();

void fetchPacket(char *buffer, size_t size, size_t *outSize);
void fetchKeyboardEventList(int *buffer, size_t size, size_t *outSize);

#ifdef __cplusplus
}
#endif

#endif //QCPILOTCONSOLE_QCPILOT_ADAPTOR_H
