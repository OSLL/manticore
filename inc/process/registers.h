#ifndef __I_REGISTERS_H__
#define __I_REGISTERS_H__

#include <utils/casts.h>
#include <utils/types.h>
#include <utils/string_utils.h>

#include <functional>
#include <algorithm>
#include <iterator>
#include <sstream>
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
    virtual RegisterCapacity GetCapacity() const { return capacity_; }
    virtual std::string GetName() const { return name_; }
    virtual std::vector<u8> const & GetValue() const { return value_; }

    void SetValue(const u8 * value) {
        value_.clear();
        std::copy(value, value + GetSize(), std::back_inserter(value_));
    }

    void SetValue(std::vector<u8> const & value) {
        assert(value.size() == GetSize());
        value_.clear();
        std::copy(value.begin(), value.end(), std::back_inserter(value_));
    }

    std::string ToString() const {
        std::ostringstream out;
        out << "{name:" << GetName()
            << ";type:" << (GetType() == RegisterType::INTEGER ? "integer" : "false")
            << ";capacity:" << GetCapacity()
            << ";value:" << manticore::utils::format_hex(value_.begin(), value_.end())
            << "}";
	return out.str();
    }
};

inline bool operator==(Register const & left, Register const & right) {
    std::vector<u8> const & left_value = left.GetValue();
    std::vector<u8> const & right_value = right.GetValue();
    return left.GetCapacity() == right.GetCapacity() &&
           left.GetType() == right.GetType() &&
           left.GetName() == right.GetName() &&
           left_value.size() == right_value.size() &&
           std::equal(left_value.begin(), left_value.end(), right_value.begin());
}

DECLARE_PTRS(Register);

} }

#endif /*__I_REGISTERS_H__*/
