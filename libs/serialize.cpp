#include <process/serialize.h>
#include <utils/string_utils.h>

#include "snapshot.pb.h"

namespace manticore { namespace serialize {

using namespace manticore::process;
using namespace protobuf;

std::ostream & operator<<(std::ostream & out, RegisterPtr const & reg) {
    protobuf::Register buff;
    buff.set_name(reg->GetName());
    buff.set_type(static_cast<Register_Type>(reg->GetType()));
    buff.set_capacity(static_cast<Register_Capacity>(reg->GetCapacity()));
    buff.set_value(manticore::utils::from_vector(reg->GetValue()));
    buff.SerializeToOstream(&out);
    return out;
}

std::ostream & operator<<(std::ostream & out, std::vector<RegisterPtr> const & regs) {
    for (auto it = regs.begin(); it != regs.end(); ++it) {
        out << (*it);
    }
    return out;
}

std::istream & operator>>(std::istream & in, RegisterPtr & reg) {
    protobuf::Register buff;
    buff.ParseFromIstream(&in);
    reg.reset(new Register(buff.name(), static_cast<RegisterType>(buff.type()), static_cast<RegisterCapacity>(buff.capacity())));
    reg->SetValue(manticore::utils::from_string(buff.value()));
    return in;
}

std::istream & operator>>(std::istream & in, std::vector<manticore::process::RegisterPtr> & regs) {
    return in;
}

} }
