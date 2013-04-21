#ifndef __MANTICORE_MEMORY_H__
#define __MANTICORE_MEMORY_H__

#include <utils/range.h>
#include <utils/types.h>
#include <utils/string_utils.h>

#include <string>

namespace manticore { namespace process {

class MemoryRegion {
public:
    enum PermissionOffset { ReadOffset = 0, WriteOffset = 1, ExecuteOffset = 2, PrivateOffset = 3 };
    enum PermissionFlag { Read = 1 << PermissionOffset::ReadOffset,
                          Write = 1 << PermissionOffset::WriteOffset,
                          Execute = 1 << PermissionOffset::ExecuteOffset,
                          Private = 1 << PermissionOffset::PrivateOffset };
    typedef manticore::utils::Range<size_t> MemoryRange;

    MemoryRegion(size_t lower, size_t upper, u8 permission = static_cast<u8>(0), std::string const & path = "")
    : range_(lower, upper), permission_(permission), path_(path) { }

    std::string GetPath() const { return path_; }
    void SetPath(std::string const & path) { path_ = path; }

    MemoryRange GetRange() const { return range_; }

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

    std::shared_ptr<const std::vector<char> > GetMemory() const { return memory_; }
    void SetMemory(std::shared_ptr<const std::vector<char> > memory) { memory_ = memory; }
    void ResetMemory() { memory_.reset(); }

    std::string ToString() const {
        return utils::stringify("{path:", GetPath(),
                                ";permissions:", (IsReadable() ? 'r' : '-'),
                                                 (IsWritable() ? 'w' : '-'),
                                                 (IsExecutable() ? 'x' : '-'),
                                                 (IsPrivate() ? 'p' : '-'),
                                ";range:{lower:0x", utils::format_hex(GetLower()),
                                       ";upper:0x", utils::format_hex(GetUpper()), 
                                "}}");
    }
private:
    MemoryRange range_;
    u8 permission_;
    std::string path_;

    std::shared_ptr<const std::vector<char> > memory_;
};
DECLARE_PTRS(MemoryRegion);

} }

#endif /*__MANTICORE_MEMORY_H__*/
