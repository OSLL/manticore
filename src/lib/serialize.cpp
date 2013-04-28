#include <process/serialize.h>
#include <utils/string_utils.h>
#include <utils/casts.h>
#include <utils/types.h>
#include <utils/range.h>

#include <iostream>

#include "snapshot.pb.h"
#include "memory.pb.h"

namespace manticore { namespace serialize {

using namespace manticore::process;
using namespace protobuf;

namespace detail {

    void fill_register(protobuf::Register & buff, RegisterConstPtr const & reg) {
        buff.set_name(reg->GetName());
        buff.set_type(static_cast<Register_Type>(reg->GetType()));
        buff.set_capacity(static_cast<Register_Capacity>(reg->GetCapacity()));
        buff.set_value(manticore::utils::from_vector(reg->GetValue())); 
    }

    void fill_region(protobuf::MemoryRegion & buff, MemoryRegionConstPtr const & region) {
        buff.set_lower(static_cast<u64>(region->GetLower()));
        buff.set_upper(static_cast<u64>(region->GetUpper()));
        buff.set_path(region->GetPath());
        buff.set_readable(region->IsReadable());
        buff.set_writable(region->IsWritable());
        buff.set_executable(region->IsExecutable());
        buff.set_shared(!region->IsPrivate());
    }

    void fill_region(MemoryRegionConstPtr & reg, protobuf::MemoryRegion const & buff) {
        MemoryRegionPtr r(new MemoryRegion(static_cast<size_t>(buff.lower()), static_cast<size_t>(buff.upper())));
        r->SetPath(buff.path());
        if (buff.readable()) {
            r->SetPermissionFlag(MemoryRegion::PermissionFlag::Read);
        } else {
            r->DropPermissionFlag(MemoryRegion::PermissionFlag::Read);
        }
        if (buff.writable()) {
            r->SetPermissionFlag(MemoryRegion::PermissionFlag::Write);
        } else {
            r->DropPermissionFlag(MemoryRegion::PermissionFlag::Write);
        }
        if (buff.executable()) {
            r->SetPermissionFlag(MemoryRegion::PermissionFlag::Execute);
        } else {
            r->DropPermissionFlag(MemoryRegion::PermissionFlag::Execute);
        }
        if (!buff.shared()) {
            r->SetPermissionFlag(MemoryRegion::PermissionFlag::Private);
        } else {
            r->DropPermissionFlag(MemoryRegion::PermissionFlag::Private);
        }
        reg = r;
    }

}

std::ostream & operator<<(std::ostream & out, RegisterConstPtr const & reg) {
    protobuf::Register buff;
    detail::fill_register(buff, reg);
    buff.SerializeToOstream(&out);
    return out;
}

std::ostream & operator<<(std::ostream & out, MemoryRegionConstPtr const & region) {
    protobuf::MemoryRegion buff;
    detail::fill_region(buff, region);
    buff.SerializeToOstream(&out);
    return out;
}

std::ostream & operator<<(std::ostream & out, std::vector<RegisterConstPtr> const & regs) {
    protobuf::RegistersSnapshot buff;
    for (auto it = regs.begin(); it != regs.end(); ++it) {
        protobuf::Register * reg = buff.add_register_();
        detail::fill_register(*reg, *it);
    }
    buff.SerializeToOstream(&out);
    return out;
}

std::ostream & operator<<(std::ostream & out, std::vector<MemoryRegionConstPtr> const & regs) {
    protobuf::MemoryRegions buff;
    for (auto it = regs.begin(); it != regs.end(); ++it) {
        protobuf::MemoryRegion * reg = buff.add_region();
        detail::fill_region(*reg, *it);
    }
    buff.SerializeToOstream(&out);
    return out;
}

std::istream & operator>>(std::istream & in, RegisterConstPtr & reg) {
    protobuf::Register buff;
    buff.ParseFromIstream(&in);
    RegisterPtr r(new Register(buff.name(), static_cast<RegisterType>(buff.type()), static_cast<RegisterCapacity>(buff.capacity())));
    r->SetValue(manticore::utils::from_string(buff.value()));
    reg = r;
    return in;
}

std::istream & operator>>(std::istream & in, MemoryRegionConstPtr & reg) {
    protobuf::MemoryRegion buff;
    buff.ParseFromIstream(&in);
    detail::fill_region(reg, buff);
    return in;
}

std::istream & operator>>(std::istream & in, std::vector<RegisterConstPtr> & regs) {
    protobuf::RegistersSnapshot buff;
    buff.ParseFromIstream(&in);
    for (int index = 0; index < buff.register__size(); ++index) {
        protobuf::Register const & preg = buff.register_(index);
        RegisterPtr reg(new Register(preg.name(), static_cast<RegisterType>(preg.type()), static_cast<RegisterCapacity>(preg.capacity())));
        reg->SetValue(manticore::utils::from_string(preg.value()));
        regs.push_back(reg);
    }
    return in;
}

std::istream & operator>>(std::istream & in, std::vector<MemoryRegionConstPtr> & regs) {
    protobuf::MemoryRegions buff;
    buff.ParseFromIstream(&in);
    for (int index = 0; index < buff.region_size(); ++index) {
        MemoryRegionConstPtr r;
        detail::fill_region(r, buff.region(index));
        regs.push_back(r);
    }
    return in;
}

} }
