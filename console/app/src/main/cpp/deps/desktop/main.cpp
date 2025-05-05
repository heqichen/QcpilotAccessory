#include "raymob/qcpilot/ui/entry.h"

int main(int argc, const char *argv[], const char *envs[]) {
    qcpilot::ui::Entry entry {2340, 1080};
    entry.start();
    return 0;
}
