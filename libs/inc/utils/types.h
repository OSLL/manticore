#ifndef __TYPES_H__
#define __TYPES_H__

#if ARCH == I386
#include <utils/i386/types.h>
#endif

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#define DECLARE_PTRS(ClassName)                               \
typedef boost::shared_ptr<ClassName> ClassName ## Ptr;        \
typedef boost::weak_ptr<ClassName> ClassName ## WeakPtr;      \
typedef boost::scoped_ptr<ClassName> ClassName ## ScopedPtr

template <typename T, typename ... Types>
inline boost::shared_ptr<T> make_shared(Types ... args) { return boost::shared_ptr<T>(new T(args ...)); }

template <typename T, typename ... Types>
inline boost::scoped_ptr<T> make_scoped(Types ... args) { return boost::scoped_ptr<T>(new T(args ...)); }

#endif /*__TYPES_H__*/
