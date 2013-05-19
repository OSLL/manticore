#ifndef __PTRACE_H__
#define __PTRACE_H__

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include <exception>
#include <vector>

#include <utils/string_utils.h>

namespace manticore { namespace process {

struct Ptrace {
    enum { ATTACH = PTRACE_SEIZE, STOP = PTRACE_INTERRUPT, DETACH = PTRACE_DETACH, KILL = SIGKILL, WAIT, UNKNOWN };

    static void Attach(pid_t id);
    static void Detach(pid_t id);
    static void Stop(pid_t id);
    static void Wait(pid_t id);
    static void Kill(pid_t id);
    static bool Exists(pid_t id);
    static void Error(pid_t id, int op);
};

struct PtraceException : public std::exception {
    const pid_t id_;
    const std::string message_;
    const int operation_;

    PtraceException(pid_t id, std::string const & message, int operation = Ptrace::UNKNOWN)
    : id_(id), message_(message), operation_(operation) { }
    virtual ~PtraceException() noexcept { }

    virtual pid_t GetId() const { return id_; }
    virtual int GetOperation() const { return operation_; }
    virtual std::string const & GetMessage() const { return message_; }
    virtual std::string const & ToString() const { return GetMessage(); }

    virtual char const * what() const noexcept { return GetMessage().data(); }
};

struct ProcessDoesNotExists : public PtraceException {
    ProcessDoesNotExists(pid_t id, int op = Ptrace::UNKNOWN)
    : PtraceException(id, manticore::utils::stringify("process ", id, " doesn't exists or isn't stopped"), op)
    { }
    virtual ~ProcessDoesNotExists() noexcept { }
};

struct NotEnoughResources : public PtraceException {
    NotEnoughResources(pid_t id, int op = Ptrace::UNKNOWN)
    : PtraceException(id, manticore::utils::stringify("not enough resources to ptrace process ", id), op)
    { }
    virtual ~NotEnoughResources() noexcept { }
};

struct InvalidOptions : public PtraceException {
    InvalidOptions(pid_t id, int op = Ptrace::UNKNOWN)
    : PtraceException(id, manticore::utils::stringify("invalid options when ptrace process ", id), op)
    { }
    virtual ~InvalidOptions() noexcept { }
};

struct PermissionViolation : public PtraceException {
    PermissionViolation(pid_t id, int op = Ptrace::UNKNOWN)
    : PtraceException(id, manticore::utils::stringify("permission violation when ptrace process ", id), op)
    { }
    virtual ~PermissionViolation() noexcept { }
};

struct ProcessAlreadyTerminated : public PtraceException {
    ProcessAlreadyTerminated(pid_t id)
    : PtraceException(id, manticore::utils::stringify("process ", id, " terminated"), Ptrace::WAIT)
    { }
    virtual ~ProcessAlreadyTerminated() noexcept {}
};

} }

#endif /*__PTRACE_H__*/
