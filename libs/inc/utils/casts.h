#ifndef __CASTS_H__
#define __CASTS_H__

#include <sstream>
#include <string>

#include "typetraits.h"

namespace manticore { namespace utils {

namespace detail {

    using manticore::typetraits::true_type;
    using manticore::typetraits::false_type;

    template <typename T, std::string (T::*)()> struct to_string {};
    template <typename T, std::string (T::*)() const> struct const_to_string {};
    template <typename T> true_type CheckToString(T*, to_string<T, &T::ToString> = to_string<T, &T::ToString>()) {}
    template <typename T> true_type CheckToString(T*, const_to_string<T, &T::ToString> = const_to_string<T, &T::ToString>()) {}
    template <typename T> false_type CheckToString(...) {}

    template <typename T>
    struct ContainsToString {
        enum { Value = ( sizeof(CheckToString<T>(static_cast<T*>(0))) == sizeof(true_type) ) };
    };

    template <typename T, int (T::*)()> struct to_int {};
    template <typename T, int (T::*)() const> struct const_to_int {};
    template <typename T> true_type CheckToInt(T*, to_int<T, &T::ToInt> = to_int<T, &T::ToInt>()) {}
    template <typename T> true_type CheckToInt(T*, const_to_int<T, &T::ToInt> = const_to_int<T, &T::ToInt>()) {}
    template <typename T> false_type CheckToInt(...) {}

    template <typename T>
    struct ContainsToInt {
        enum { Value = ( sizeof(CheckToInt<T>(static_cast<T*>(0))) == sizeof(true_type) ) };
    };

    template <typename T>
    std::string string_cast_impl(T const &obj, manticore::typetraits::IntToType<true> tag) {
        return obj.ToString();
    }

    template <typename T>
    std::string string_cast_impl(T &obj, manticore::typetraits::IntToType<true> tag) {
        return obj.ToString();
    }

    template <typename T>
    std::string string_cast_impl(T const * const obj, manticore::typetraits::IntToType<true> tag) {
        return obj->ToString();
    }

    template <typename T>
    std::string string_cast_impl(T * const obj, manticore::typetraits::IntToType<true> tag) {
        return obj->ToString();
    }

    template <typename T>
    std::string string_cast_impl(T const &obj, manticore::typetraits::IntToType<false> tag) {
        std::stringstream buffer;
        buffer << obj;
        return buffer.str();
    }

    template <typename T>
    std::string string_cast_impl(T &obj, manticore::typetraits::IntToType<false> tag) {
        std::stringstream buffer;
        buffer << obj;
        return buffer.str();
    }

    template <typename T>
    int int_cast_impl(T const &obj, manticore::typetraits::IntToType<true> tag) {
        return obj.ToInt();
    }

    template <typename T>
    int int_cast_impl(T &obj, manticore::typetraits::IntToType<true> tag) {
        return obj.ToInt();
    }

    template <typename T>
    int int_cast_impl(T const * const obj, manticore::typetraits::IntToType<true> tag) {
        return obj->ToInt();
    }

    template <typename T>
    int int_cast_impl(T * const obj, manticore::typetraits::IntToType<true> tag) {
        return obj->ToInt();
    }

    template <typename T>
    int int_cast_impl(T const &obj, manticore::typetraits::IntToType<false> tag) {
        return static_cast<int>(obj);
    }

    template <typename T>
    int int_cast_impl(T &obj, manticore::typetraits::IntToType<false> tag) {
        return static_cast<int>(obj);
    }

}

template <typename T>
std::string string_cast(T const & obj) {
    return detail::string_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T & obj) {
    return detail::string_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T const * const obj) {
    return detail::string_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T * const obj) {
    return detail::string_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
int case_cast(T const & obj) {
    return detail::int_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T & obj) {
    return detail::int_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T const * const obj) {
    return detail::int_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T * const obj) {
    return detail::int_cast_impl<T>(obj, manticore::typetraits::IntToType<detail::ContainsToInt<T>::Value>());
}

} }

#endif /*__CASTS_H__*/
