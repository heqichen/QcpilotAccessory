#include "raymob/qcpilot/ui/entry.h"

int main(int argc, const char *argv[], const char *envs[]) {
    qcpilot::ui::Entry entry {800, 600};
    // qcpilot::ui::Entry entry {1900, 600};
    entry.start();
    return 0;
}
