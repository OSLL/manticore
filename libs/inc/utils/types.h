#ifndef __TYPES_H__
#define __TYPES_H__

#if ARCH == i386
#include <utils/i386/types.h>
#endif

#include <memory>

#define DECLARE_PTRS(ClassName)                             \
typedef std::shared_ptr<ClassName> ClassName ## Ptr;        \
typedef std::weak_ptr<ClassName> ClassName ## WeakPtr;      \
typedef std::unique_ptr<ClassName> ClassName ## UniquePtr

#endif /*__TYPES_H__*/
