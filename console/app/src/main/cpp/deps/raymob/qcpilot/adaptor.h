#ifndef QCPILOTCONSOLE_QCPILOT_ADAPTOR_H
#define QCPILOTCONSOLE_QCPILOT_ADAPTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void readPacket();
uint8_t *getBuffer();
size_t  getBufferSize();

#ifdef __cplusplus
}
#endif

#endif //QCPILOTCONSOLE_QCPILOT_ADAPTOR_H
