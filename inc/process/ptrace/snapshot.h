#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include <unistd.h>

#include <process/registers.h>
#include <vector>

namespace manticore { namespace process {

struct ISnapshotMaker {
    ISnapshotMaker() { }
    virtual ~ISnapshotMaker() { }

    virtual std::vector<RegisterConstPtr> MakeSnapshot(pid_t pid) const = 0;
};
DECLARE_PTRS(ISnapshotMaker);

} }

#if ARCH == i386
#include <process/ptrace/i386/snapshot.h>
#endif

#endif /*__SNAPSHOT_H__*/
