#ifndef __I_REGISTERS_H__
#define __I_REGISTERS_H__

#include <utils/casts.h>
#include <utils/types.h>

#include <functional>
#include <algorithm>
#include <string>
#include <vector>

namespace manticore { namespace process {

enum RegisterCapacity {
    BIT16 = 16,
    BIT32 = 32,
    BIT64 = 64,
    BIT128 = 128
};

enum RegisterType {
    INTEGER = 0,
    FLOATING_POINT = 1
};

class IRegister {
public:
    virtual ~IRegister() {}
    virtual RegisterType GetType() const = 0;
    virtual RegisterCapacity GetCapacity() const = 0;
    virtual size_t GetSize() const = 0;
    virtual std::string GetName() const = 0;
    virtual std::vector<u8> GetValue() const = 0;
};
DECLARE_PTRS(IRegister);

template <int BYTES, int TYPE>
class Register : public IRegister {
private:
    enum { SIZE = BYTES, BITS = BYTES * 8 };

    std::string name_;
    u8 value_[SIZE];

public:
    Register(std::string const &name, const u8 * value) : IRegister(), name_(name) { SetValue(value); }
    Register(std::string const &name) : IRegister(), name_(name) {}
    virtual ~Register() {}

    virtual size_t GetSize() const { return SIZE; }

    virtual RegisterType GetType() const { return static_cast<RegisterType>(SIZE); }
    virtual RegisterCapacity GetCapacity() const { static_cast<RegisterCapacity>(BITS); }
    virtual std::string GetName() const { return name_; }

    virtual std::vector<u8> GetValue() const { return std::vector<u8>(value_, value_ + SIZE); }
    void SetValue(const u8 * value) { std::copy(value, value + SIZE, value_); }
};

typedef Register<1, INTEGER> I8Register;
typedef Register<2, INTEGER> I16Register;
typedef Register<4, INTEGER> I32Register;
typedef Register<8, INTEGER> I64Register;
typedef Register<16, INTEGER> I128Register;

typedef Register<1, FLOATING_POINT> F8Register;
typedef Register<2, FLOATING_POINT> F16Register;
typedef Register<4, FLOATING_POINT> F32Register;
typedef Register<8, FLOATING_POINT> F64Register;
typedef Register<16, FLOATING_POINT> F128Register;

} }

#endif /*__I_REGISTERS_H__*/
