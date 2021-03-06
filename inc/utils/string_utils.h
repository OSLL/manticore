#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

#include <utils/types.h>
#include <utils/casts.h>

namespace manticore { namespace utils {

namespace detail {
    template <typename T>
    void stringify_impl(std::stringstream & stream, T const & arg) {
        stream << string_cast(arg);
    }

    template <typename T, typename ... Types>
    void stringify_impl(std::stringstream & stream, T const & arg, Types const & ... args) {
        stream << string_cast(arg);
        stringify_impl(stream, args ...);
    }
}

inline std::string from_vector(std::vector<char> const & data) {
    return std::string(data.data(), data.data() + data.size());
}

inline std::vector<char> from_string(std::string const & data) {
    return std::vector<char>(data.data(), data.data() + data.size());
}

template <typename Iterator>
std::string format_hex(Iterator const & begin, Iterator const & end) {
    std::ostringstream out;
    for (Iterator it = begin; it != end; ++it) {
        out << std::setw(2 * sizeof(*it)) << std::setfill('0') << std::hex << static_cast<u64>(*reinterpret_cast<u8 const * const>(&(*it)));
    }
    return out.str();
}

template <typename Number>
std::string format_hex(Number const & number) {
    std::ostringstream out;
    out << std::setw(2 * sizeof(number)) << std::setfill('0') << std::hex << number;
    return out.str();
}

template <typename Type>
Type parse(std::string const & str) {
    std::stringstream stream;
    Type value;
    stream << str; stream >> value;
    return value;
}

template <typename ... Types>
std::string stringify(Types const & ... args) {
    std::stringstream stream;
    detail::stringify_impl(stream, args ...);
    return stream.str();
}

} }

#endif /*__STRING_UTILS_H__*/
