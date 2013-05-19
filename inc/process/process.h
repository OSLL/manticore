#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <boost/utility.hpp>

#include <unistd.h>

#include <map>

#include <process/ptrace/ptrace.h>
#include <process/ptrace/snapshot.h>
#include <process/proc/proc.h>
#include <utils/types.h>
#include <utils/range.h>

namespace manticore { namespace process {

class Process : boost::noncopyable {
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

    void Seize() { session_.reset(new SeizureSession(GetId())); }
    void Release() { session_.reset(); }
    void Kill() { Release(); Ptrace::Kill(GetId()); }
    std::vector<RegisterConstPtr> Snapshot() const { return Implementation<ISnapshotMaker>()->MakeSnapshot(GetId()); }
    std::vector<MemoryRegionConstPtr> Regions() const { return Proc::Ranges(GetId()); }
    std::shared_ptr<std::vector<char> > Load(MemoryRegionConstPtr const & desc) const { return Proc::Load(GetId(), desc); }

    bool Exists() const { return Ptrace::Exists(GetId()); }
    pid_t GetId() const { return id_; };
};

} }

#endif /*__PROCESS_H__*/
