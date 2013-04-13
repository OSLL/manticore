#ifndef __CASTS_H__
#define __CASTS_H__

#include <memory>
#include <sstream>
#include <string>

#include <type_traits>

namespace manticore { namespace utils {

namespace detail {

    typedef char true_type;
    struct false_type { true_type dummy[2]; };

    template <int value>
    struct IntToType {
        enum { Value = value };
    };

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

    template <typename T, int (T::*)()> struct to_int {};
    template <typename T, int (T::*)() const> struct const_to_int {};
    template <typename T> true_type CheckToInt(T*, to_int<T, &T::ToInt> = to_int<T, &T::ToInt>())
    { return true_type(); }
    template <typename T> true_type CheckToInt(T*, const_to_int<T, &T::ToInt> = const_to_int<T, &T::ToInt>())
    { return true_type(); }
    template <typename T> false_type CheckToInt(...)
    { return false_type(); }

    template <typename T>
    struct ContainsToInt {
        enum { Value = ( sizeof(CheckToInt<T>(static_cast<T*>(0))) == sizeof(true_type) ) };
    };

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
    std::string string_cast_impl(T const &obj, IntToType<false> tag) {
        std::stringstream buffer;
        buffer << obj;
        return buffer.str();
    }

    template <typename T>
    std::string string_cast_impl(T &obj, IntToType<false> tag) {
        std::stringstream buffer;
        buffer << obj;
        return buffer.str();
    }

    template <typename T>
    int int_cast_impl(T const &obj, IntToType<true> tag) {
        return obj.ToInt();
    }

    template <typename T>
    int int_cast_impl(T &obj, IntToType<true> tag) {
        return obj.ToInt();
    }

    template <typename T>
    int int_cast_impl(T const * const obj, IntToType<true> tag) {
        return obj->ToInt();
    }

    template <typename T>
    int int_cast_impl(T * const obj, IntToType<true> tag) {
        return obj->ToInt();
    }

    template <typename T>
    int int_cast_impl(T const &obj, IntToType<false> tag) {
        return static_cast<int>(obj);
    }

    template <typename T>
    int int_cast_impl(T &obj, IntToType<false> tag) {
        return static_cast<int>(obj);
    }

}

template <typename T>
std::string string_cast(T const & obj) {
    return detail::string_cast_impl<T>(obj, detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T & obj) {
    return detail::string_cast_impl<T>(obj, detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T const * const obj) {
    return detail::string_cast_impl<T>(obj, detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(T * const obj) {
    return detail::string_cast_impl<T>(obj, detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(std::shared_ptr<T> const & obj) {
    return detail::string_cast_impl<T>(obj.get(), detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
std::string string_cast(std::shared_ptr<const T> const & obj) {
    return detail::string_cast_impl<T>(obj.get(), detail::IntToType<detail::ContainsToString<T>::Value>());
}

template <typename T>
int case_cast(T const & obj) {
    return detail::int_cast_impl<T>(obj, detail::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T & obj) {
    return detail::int_cast_impl<T>(obj, detail::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T const * const obj) {
    return detail::int_cast_impl<T>(obj, detail::IntToType<detail::ContainsToInt<T>::Value>());
}

template <typename T>
int case_cast(T * const obj) {
    return detail::int_cast_impl<T>(obj, detail::IntToType<detail::ContainsToInt<T>::Value>());
}

} }

#endif /*__CASTS_H__*/