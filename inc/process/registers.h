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

    std::vector<char> value_;

public:
    Register(std::string const &name, RegisterType const type, RegisterCapacity const capacity, char const * value)
    : name_(name)
    , type_(type)
    , capacity_(capacity)
    { SetValue(value); }

    Register(std::string const &name, RegisterType const type, std::vector<char> const & value)
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
    virtual std::vector<char> const & GetValue() const { return value_; }

    void SetValue(const char * value) {
        value_.clear();
        std::copy(value, value + GetSize(), std::back_inserter(value_));
    }

    void SetValue(std::vector<char> const & value) {
        assert(value.size() == GetSize());
        value_.clear();
        std::copy(value.begin(), value.end(), std::back_inserter(value_));
    }

    std::string ToString() const {
        return utils::stringify("{name:", GetName(),
                                ";type:", (GetType() == RegisterType::INTEGER ? "integer" : "false"),
                                ";capacity:", GetCapacity(),
                                ";value:", utils::format_hex(value_.begin(), value_.end()), "}");
    }
};
DECLARE_PTRS(Register);

inline bool operator==(Register const & left, Register const & right) {
    std::vector<char> const & left_value = left.GetValue();
    std::vector<char> const & right_value = right.GetValue();
    return left.GetCapacity() == right.GetCapacity() &&
           left.GetType() == right.GetType() &&
           left.GetName() == right.GetName() &&
           left_value.size() == right_value.size() &&
           std::equal(left_value.begin(), left_value.end(), right_value.begin());
}

} }

#endif /*__I_REGISTERS_H__*/
