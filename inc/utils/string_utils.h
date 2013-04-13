#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <sstream>
#include <vector>
#include <string>

#include <utils/types.h>

namespace manticore { namespace utils {

inline std::string from_vector(std::vector<u8> const & data) {
    return std::string((const char *)data.data(), (const char *)(data.data() + data.size()));
}

inline std::vector<u8> from_string(std::string const & data) {
    return std::vector<u8>((const u8 *)data.data(), (const u8 *)(data.data() + data.size()));
}

template <typename Iterator>
std::string format_hex(Iterator const & begin, Iterator const & end) {
    std::ostringstream out;
    for (Iterator it = begin; it != end; ++it) {
        out << std::hex << static_cast<int>(*it);
    }
    return out.str();
}

} }

#endif /*__STRING_UTILS_H__*/
