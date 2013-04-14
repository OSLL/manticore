#ifndef __I386_SNAPSHOT_H__
#define __I386_SNAPSHOT_H__

#include <process/ptrace/snapshot.h>

#include <process/registers.h>
#include <vector>

namespace manticore { namespace process {

class I386SnapshotMaker : public ISnapshotMaker {
public:
    I386SnapshotMaker() { }
    virtual ~I386SnapshotMaker() { }

    virtual std::vector<RegisterPtr> MakeSnapshot(pid_t pid) const;
};
DECLARE_PTRS(I386SnapshotMaker);

} }

DECLARE_IMPLEMENTATION(manticore::process::ISnapshotMaker, manticore::process::I386SnapshotMaker);

#endif /*__I386_SNAPSHOT_H__*/
