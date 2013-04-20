#ifndef __PROC_H__
#define __PROC_H__

#include <unistd.h>

#include <string>
#include <vector>

#include <utils/string_utils.h>
#include <utils/range.h>
#include <utils/types.h>

namespace manticore { namespace process {

struct UnexpectedProcFormatException : public std::exception {
    const std::string message_;

    UnexpectedProcFormatException() : message_("unexpected proc file format") { }
    virtual ~UnexpectedProcFormatException() noexcept { }

    virtual std::string const & GetMessage() const { return message_; }
    virtual std::string const & ToString() const { return GetMessage(); }

    virtual char const * what() const noexcept { return GetMessage().data(); }
};

class MemoryRegion {
public:
    enum PermissionOffset { ReadOffset = 0, WriteOffset = 1, ExecuteOffset = 2, PrivateOffset = 3 };
    enum PermissionFlag { Read = 1 << PermissionOffset::ReadOffset,
                          Write = 1 << PermissionOffset::WriteOffset,
                          Execute = 1 << PermissionOffset::ExecuteOffset,
                          Private = 1 << PermissionOffset::PrivateOffset };
    typedef manticore::utils::Range<size_t> MemoryRange;

    

    std::string GetPath() const { return path_; }
    void SetPath(std::string const & path) { path_ = path; }

    MemoryRange GetRange() const { return range_; }
    void SetRange(MemoryRange const & range) { range_ = range; }

    u8 GetPermission() const { return permission_; }
    void SetPermission(u8 perm) { permission_ = perm; }

    void SetPermissionFlag(PermissionFlag flag) { permission_ |= static_cast<u8>(flag); }
    void DropPermissionFlag(PermissionFlag flag) { permission_ &= ~static_cast<u8>(flag); }

    size_t GetLower() const { return GetRange().GetLower(); }
    size_t GetUpper() const { return GetRange().GetUpper(); }

    bool IsReadable() const { return GetPermission() & static_cast<u8>(PermissionFlag::Read); }
    bool IsWritable() const { return GetPermission() & static_cast<u8>(PermissionFlag::Write); }
    bool IsExecutable() const { return GetPermission() & static_cast<u8>(PermissionFlag::Execute); }
    bool IsPrivate() const { return GetPermission() & static_cast<u8>(PermissionFlag::Private); }

    std::string ToString() const {
        return utils::stringify("{path:", GetPath(),
                                ";permissions:", (IsReadable() ? 'r' : '-'),
                                                 (IsWritable() ? 'w' : '-'),
                                                 (IsExecutable() ? 'x' : '-'),
                                                 (IsPrivate() ? 'p' : '-'),
                                ";range:{lower:", utils::format_hex(GetLower()),
                                       ";upper:", utils::format_hex(GetUpper()), 
                                "}}");
    }
private:
    MemoryRange range_;
    u8 permission_;
    std::string path_;
};
DECLARE_PTRS(MemoryRegion);

struct Proc {
    static std::vector<MemoryRegionConstPtr> Ranges(pid_t id);
    static void Dump(pid_t id, std::vector<u8> & memory, MemoryRegionConstPtr const & region);
};

} }

#endif /*__PROC_H__*/
