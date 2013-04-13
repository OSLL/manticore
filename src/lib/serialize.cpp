#include <process/serialize.h>
#include <utils/string_utils.h>
#include <utils/casts.h>

#include <iostream>

#include "snapshot.pb.h"

namespace manticore { namespace serialize {

using namespace manticore::process;
using namespace protobuf;

namespace detail {

    void fill_protobuff(protobuf::Register & buff, RegisterPtr const & reg) {
        buff.set_name(reg->GetName());
        buff.set_type(static_cast<Register_Type>(reg->GetType()));
        buff.set_capacity(static_cast<Register_Capacity>(reg->GetCapacity()));
        buff.set_value(manticore::utils::from_vector(reg->GetValue())); 
    }

}

std::ostream & operator<<(std::ostream & out, RegisterPtr const & reg) {
    protobuf::Register buff;
    detail::fill_protobuff(buff, reg);
    buff.SerializeToOstream(&out);
    return out;
}

std::ostream & operator<<(std::ostream & out, std::vector<RegisterPtr> const & regs) {
    protobuf::RegistersSnapshot buff;
    for (auto it = regs.begin(); it != regs.end(); ++it) {
        protobuf::Register * reg = buff.add_register_();
        detail::fill_protobuff(*reg, *it);
    }
    buff.SerializeToOstream(&out);
    return out;
}

std::istream & operator>>(std::istream & in, RegisterPtr & reg) {
    protobuf::Register buff;
    buff.ParseFromIstream(&in);
    reg.reset(new Register(buff.name(), static_cast<RegisterType>(buff.type()), static_cast<RegisterCapacity>(buff.capacity())));
    reg->SetValue(manticore::utils::from_string(buff.value()));
    return in;
}

std::istream & operator>>(std::istream & in, std::vector<RegisterPtr> & regs) {
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

} }
