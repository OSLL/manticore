#include <process/ptrace/ptrace.h>
#include <process/ptrace/snapshot.h>

#include <sys/wait.h>
#include <cerrno>

namespace manticore { namespace process {

void Ptrace::Attach(pid_t id) {
    errno = 0;
    if (ptrace(static_cast<__ptrace_request>(Ptrace::ATTACH), id, 0, 0) == -1)
        Error(id, static_cast<int>(Ptrace::ATTACH));
}

void Ptrace::Detach(pid_t id) {
    errno = 0;
    if (ptrace(static_cast<__ptrace_request>(Ptrace::DETACH), id, 0, 0) == -1)
        Error(id, static_cast<int>(Ptrace::DETACH));
}

void Ptrace::Stop(pid_t id) {
    errno = 0;
    if (ptrace(static_cast<__ptrace_request>(Ptrace::STOP), id, 0, 0) == -1)
        Error(id, static_cast<int>(Ptrace::STOP));
}

void Ptrace::Wait(pid_t id) {
    int status = 0;
    errno = 0;
    if (waitpid(id, &status, 0) == -1)
        Error(id, static_cast<int>(Ptrace::WAIT));
    if (!WIFSTOPPED(status))
        throw ProcessAlreadyTerminated(id);
}

void Ptrace::Kill(pid_t id) {
    errno = 0;
    if (kill(id, static_cast<int>(Ptrace::KILL)) == -1)
        Error(id, static_cast<int>(Ptrace::KILL));
}

bool Ptrace::Exists(pid_t id) {
    errno = 0;
    return (kill(id, 0) == 0);
}

std::vector<RegisterPtr> Ptrace::Snapshot(pid_t id) {
    errno = 0;
    return Implementation<ISnapshotMaker>()->MakeSnapshot(id);
}

void Ptrace::Error(pid_t id, int op) {
    int err = errno;
    switch (err) {
    case EBUSY:
        throw NotEnoughResources(id, op); 
    case EINVAL:
        throw InvalidOptions(id, op);
    case EPERM:
        throw PermissionViolation(id, op);
    case ESRCH:
    case ECHILD:
        throw ProcessDoesNotExists(id, op);
    case EFAULT:
    case EIO:
    default:
        throw PtraceException(id, manticore::utils::stringify("unknown error when ptrace ", id, " process\n"), op);
    }
}

} }
