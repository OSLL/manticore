#ifndef __PROC_H__
#define __PROC_H__

#include <unistd.h>

#include <string>
#include <vector>

#include <process/memory.h>

#include <utils/string_utils.h>
#include <utils/types.h>

namespace manticore { namespace process {

struct UnexpectedProcFormatException : public std::exception {
    const std::string message_;

    UnexpectedProcFormatException(std::string const & line) : message_("unexpected proc file format in line " + line) { }
    virtual ~UnexpectedProcFormatException() noexcept { }

    virtual std::string const & GetMessage() const { return message_; }
    virtual std::string const & ToString() const { return GetMessage(); }

    virtual char const * what() const noexcept { return GetMessage().data(); }
};

struct Proc {
    static std::vector<MemoryRegionConstPtr> Ranges(pid_t id);
    static std::shared_ptr<std::vector<char> > Load(pid_t id, MemoryRegionConstPtr const & region);
};

} }

#endif /*__PROC_H__*/
