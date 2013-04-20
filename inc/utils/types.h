#ifndef __TYPES_H__
#define __TYPES_H__

#if ARCH == i386
#include <utils/i386/types.h>
#endif

#include <memory>

template <typename Interface, typename ... ArgTypes> struct Creator;

#define DECLARE_IMPLEMENTATION(Interface, Implementation)            \
template <>                                                          \
struct Creator<Interface> {                                          \
    template <typename ... ArgTypes>                                 \
    std::shared_ptr<Interface> Get(ArgTypes const & ... args) const { \
        return std::make_shared<Implementation>(args ...);           \
    }                                                                \
};


template <typename Interface, typename ... ArgTypes>
std::shared_ptr<Interface> Implementation(ArgTypes const & ... args) {
    return Creator<Interface>().Get(args ...);
};

#define DECLARE_PTRS(ClassName)                                  \
typedef std::shared_ptr<ClassName> ClassName ## Ptr;             \
typedef std::shared_ptr<const ClassName> ClassName ## ConstPtr;  \
typedef std::weak_ptr<ClassName> ClassName ## WeakPtr;           \
typedef std::unique_ptr<ClassName> ClassName ## UniquePtr

#endif /*__TYPES_H__*/
