#include <process/ptrace/i386/snapshot.h>

namespace manticore { namespace ptrace {

std::vector<RegisterPtr> make_snapshot(user_regs_struct const & regs) {
    std::vector<RegisterPtr> registers;
    return registers;
}

} }
