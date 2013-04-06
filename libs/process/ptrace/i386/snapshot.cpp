#include <process/ptrace/i386/snapshot.h>

namespace manticore { namespace ptrace {

std::vector<IRegisterPtr> make_snapshot(user_regs_struct const & regs) {
    std::vector<IRegisterPtr> registers;
    return registers;
}

} }
