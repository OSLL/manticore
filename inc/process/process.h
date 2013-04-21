#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <unistd.h>

#include <map>

#include <process/ptrace/ptrace.h>
#include <process/proc/proc.h>
#include <utils/types.h>
#include <utils/range.h>

namespace manticore { namespace process {

class Process {
private:
    struct SeizureSession {
        pid_t id_;

        SeizureSession(pid_t id) : id_(id) {
            Ptrace::Attach(GetId()); //attach process
            Ptrace::Stop(GetId());   //send stop signal
            Ptrace::Wait(GetId());   //wait until process stopped
        }
        ~SeizureSession() {
            try {
                //Ptrace::Kill(id);
                Ptrace::Detach(GetId());
            } catch (std::exception const & e) {}
        }
        pid_t GetId() const { return id_; }
    };
    DECLARE_PTRS(SeizureSession);

    pid_t id_;
    SeizureSessionUniquePtr session_;
public:
    Process(pid_t id) : id_(id), session_(nullptr) { }
    virtual ~Process() { }

    virtual void Seize() { session_.reset(new SeizureSession(GetId())); }
    virtual void Release() { session_.reset(); }
    virtual void Kill() { Release(); Ptrace::Kill(GetId()); }
    virtual std::vector<RegisterConstPtr> Snapshot() const { return Ptrace::Snapshot(GetId()); }
    virtual std::vector<MemoryRegionConstPtr> Regions() const { return Proc::Ranges(GetId()); }

    virtual bool Exists() const { return Ptrace::Exists(GetId()); }
    virtual pid_t GetId() const { return id_; };
};
DECLARE_PTRS(Process);

} }

#endif /*__PROCESS_H__*/
