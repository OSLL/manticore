#ifndef __CASTS_H__
#define __CASTS_H__

#include <utils/types.h>

#include <memory>
#include <sstream>
#include <string>

namespace manticore { namespace utils {

namespace detail {

    CHECK_METHOD(ToString);
/*
    template <typename T, std::string (T::*)()> struct to_string {};
    template <typename T, std::string (T::*)() const> struct const_to_string {};
    template <typename T> true_type CheckToString(T*, to_string<T, &T::ToString> = to_string<T, &T::ToString>())
    { return true_type(); }
    template <typename T> true_type CheckToString(T*, const_to_string<T, &T::ToString> = const_to_string<T, &T::ToString>())
    { return true_type(); }
    template <typename T> false_type CheckToString(...)
    { return false_type(); }

    template <typename T>
    struct ContainsToString {
        enum { Value = ( sizeof(CheckToString<T>(static_cast<T*>(0))) == sizeof(true_type) ) };
    };
 */

    template <typename T>
    std::string string_cast_impl(T const &obj, IntToType<true> tag) {
        return obj.ToString();
    }

    template <typename T>
    std::string string_cast_impl(T &obj, IntToType<true> tag) {
        return obj.ToString();
    }

    template <typename T>
    std::string string_cast_impl(T const * const obj, IntToType<true> tag) {
        return obj->ToString();
    }

    template <typename T>
    std::string string_cast_impl(T * const obj, IntToType<true> tag) {
        return obj->ToString();
    }

    template <typename T>
    std::string string_cast_impl(T obj, IntToType<false> tag) {
        std::stringstream buffer;
        buffer << obj;
        return buffer.str();
    }

}

template <typename T>
std::string string_cast(T const & obj) {
    return detail::string_cast_impl<T>(obj, IntToType<detail::HasToString<T>::Value>());
}

template <typename T>
std::string string_cast(T & obj) {
    return detail::string_cast_impl<T>(obj, IntToType<detail::HasToString<T>::Value>());
}

template <typename T>
std::string string_cast(T const * const obj) {
    return detail::string_cast_impl<T>(obj, IntToType<detail::HasToString<T>::Value>());
}

template <typename T>
std::string string_cast(T * const obj) {
    return detail::string_cast_impl<T>(obj, IntToType<detail::HasToString<T>::Value>());
}

template <typename T>
std::string string_cast(std::shared_ptr<T> const & obj) {
    return detail::string_cast_impl<T>(obj.get(), IntToType<detail::HasToString<T>::Value>());
}

template <typename T>
std::string string_cast(std::shared_ptr<const T> const & obj) {
    return detail::string_cast_impl<T>(obj.get(), IntToType<detail::HasToString<T>::Value>());
}

inline std::string string_cast(char const * const str) {
    return std::string(str);
}

inline std::string string_cast(std::string const & str) {
    return str;
}

} }

#endif /*__CASTS_H__*/
