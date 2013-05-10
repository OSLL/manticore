#ifndef __TYPES_H__
#define __TYPES_H__

#if ARCH == i386
#include <utils/i386/types.h>
#endif

#include <type_traits>
#include <memory>

typedef char true_type;
struct false_type { true_type dummy[2]; };

template <int value>
struct IntToType {
    enum { Value = value };
};

#define CHECK_METHOD(Method)                                               \
template <typename T, bool IsClass = !std::is_scalar<T>::value >           \
class Has##Method {                                                        \
    struct Fallback { void Method() { } };                                 \
    struct Derived : T, Fallback { };                                      \
    template <typename U, U> struct Check;                                 \
    template <typename U>                                                  \
    static false_type check(Check<void (Fallback::*)(), &U::Method> *)     \
    { return false_type(); }                                               \
    template <typename U>                                                  \
    static true_type check(...)                                            \
    { return true_type(); }                                                \
public:                                                                    \
    enum { Value = (sizeof(check<Derived>(0)) != sizeof(false_type)) };    \
};                                                                         \
template <typename T>                                                      \
class Has##Method <T, false> {                                             \
public:                                                                    \
    enum { Value = false };                                                \
};

template <typename Interface, typename ... ArgTypes> struct Creator;

#define DECLARE_IMPLEMENTATION(Interface, Implementation)                  \
template <>                                                                \
struct Creator<Interface> {                                                \
    template <typename ... ArgTypes>                                       \
    std::shared_ptr<Interface> Get(ArgTypes const & ... args) const {      \
        return std::make_shared<Implementation>(args ...);                 \
    }                                                                      \
};


template <typename Interface, typename ... ArgTypes>
std::shared_ptr<Interface> Implementation(ArgTypes const & ... args) {
    return Creator<Interface>().Get(args ...);
};

#define DECLARE_PTRS(ClassName)                                            \
typedef std::shared_ptr<ClassName> ClassName ## Ptr;                       \
typedef std::shared_ptr<const ClassName> ClassName ## ConstPtr;            \
typedef std::weak_ptr<ClassName> ClassName ## WeakPtr;                     \
typedef std::unique_ptr<ClassName> ClassName ## UniquePtr

#endif /*__TYPES_H__*/
