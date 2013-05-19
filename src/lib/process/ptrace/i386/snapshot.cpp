#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <linux/ptrace.h>
#include <sys/uio.h>
#include <elf.h>

#include <cstdlib>
#include <cstring>

#include <utils/types.h>
#include <process/ptrace/snapshot.h>
#include <process/ptrace/ptrace.h>

namespace manticore { namespace process {

#define PUSHREG(reg, type, cap)                        \
registers.push_back(                                   \
    std::make_shared<const Register>(                  \
        #reg,                                          \
        RegisterType::type,                            \
        RegisterCapacity::cap,                         \
        reinterpret_cast<char const *>(&general.reg)   \
    )                                                  \
)

std::vector<RegisterConstPtr> I386SnapshotMaker::MakeSnapshot(pid_t id) const {
    errno = 0;

    user_regs_struct general;
    memset(reinterpret_cast<void *>(&general), 0, sizeof(general));

    iovec iov;
    iov.iov_len = sizeof(general);
    iov.iov_base = reinterpret_cast<void *>(&general);

    if (ptrace(static_cast<__ptrace_request>(PTRACE_GETREGSET), id, NT_PRSTATUS, &iov) == -1) {
         Ptrace::Error(id, static_cast<int>(PTRACE_GETREGSET));
    }
    std::vector<RegisterConstPtr> registers;
    PUSHREG(ebx, INTEGER, BIT32);
    PUSHREG(ecx, INTEGER, BIT32);
    PUSHREG(edx, INTEGER, BIT32);
    PUSHREG(esi, INTEGER, BIT32);
    PUSHREG(edi, INTEGER, BIT32);
    PUSHREG(ebp, INTEGER, BIT32);
    PUSHREG(eax, INTEGER, BIT32);
    PUSHREG(xds, INTEGER, BIT32);
    PUSHREG(xes, INTEGER, BIT32);
    PUSHREG(xfs, INTEGER, BIT32);
    PUSHREG(xgs, INTEGER, BIT32);
    PUSHREG(orig_eax, INTEGER, BIT32);
    PUSHREG(eip, INTEGER, BIT32);
    PUSHREG(xcs, INTEGER, BIT32);
    PUSHREG(eflags, INTEGER, BIT32);
    PUSHREG(esp, INTEGER, BIT32);
    PUSHREG(xss, INTEGER, BIT32);
    return registers;
}

#undef PUSHREG

} }
