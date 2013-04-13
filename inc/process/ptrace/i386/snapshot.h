#ifndef __I386_SNAPSHOT_H__
#define __I386_SNAPSHOT_H__

#include <process/registers.h>

#include <vector>

extern "C" {
#include <sys/user.h>
}

namespace manticore { namespace ptrace {

using manticore::process::RegisterPtr;

std::vector<RegisterPtr> make_snapshot(user_regs_struct const & regs);

} }

#endif /*__I386_SNAPSHOT_H__*/
