#ifndef __I_REGISTERS_H__
#define __I_REGISTERS_H__

#include <utils/casts.h>
#include <utils/types.h>

#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <memory>

#include <cassert>

namespace manticore { namespace process {

enum RegisterCapacity {
    BIT8 = 8,
    BIT16 = 16,
    BIT32 = 32,
    BIT64 = 64,
    BIT128 = 128
};

enum RegisterType {
    INTEGER = 0,
    FLOATING_POINT = 1
};

class Register {
private:
    const std::string name_;
    const RegisterType type_;
    const RegisterCapacity capacity_;

    std::vector<u8> value_;

public:
    Register(std::string const &name, RegisterType const type, RegisterCapacity const capacity, u8 const * value)
    : name_(name)
    , type_(type)
    , capacity_(capacity)
    { SetValue(value); }

    Register(std::string const &name, RegisterType const type, std::vector<u8> const & value)
    : name_(name)
    , type_(type)
    , capacity_(static_cast<RegisterCapacity>(value.size() * 8))
    , value_(value)
    { }

    Register(std::string const &name, RegisterType const type, RegisterCapacity const capacity)
    : name_(name)
    , type_(type)
    , capacity_(capacity)
    { }

    virtual ~Register() {}

    virtual size_t GetSize() const { return capacity_ / 8; }

    virtual RegisterType GetType() const { return type_; }
    virtual RegisterCapacity GetCapacity() const { capacity_; }
    virtual std::string GetName() const { return name_; }
    virtual std::vector<u8> GetValue() const { return value_; }

    void SetValue(const u8 * value) {
        value_.clear();
        std::copy(value, value + GetSize(), std::back_inserter(value_));
    }

    void SetValue(std::vector<u8> const & value) {
        assert(value.size() == GetSize());
        value_.clear();
        std::copy(value.begin(), value.end(), std::back_inserter(value_));
    }
};
DECLARE_PTRS(Register);

RegisterPtr make_i8_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::INTEGER, RegisterCapacity::BIT8);
}

RegisterPtr make_i16_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::INTEGER, RegisterCapacity::BIT16);
}

RegisterPtr make_i32_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::INTEGER, RegisterCapacity::BIT32);
}

RegisterPtr make_i64_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::INTEGER, RegisterCapacity::BIT64);
}

RegisterPtr make_i128_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::INTEGER, RegisterCapacity::BIT128);
}

RegisterPtr make_f32_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::FLOATING_POINT, RegisterCapacity::BIT32);
}

RegisterPtr make_f64_register(std::string const & name) {
    return std::make_shared<Register>(name, RegisterType::FLOATING_POINT, RegisterCapacity::BIT64);
}

} }

#endif /*__I_REGISTERS_H__*/
