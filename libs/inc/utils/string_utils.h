#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>

#include <utils/types.h>

namespace manticore { namespace utils {

std::string from_vector(std::vector<u8> const & data) {
    return std::string((const char *)data.data(), (const char *)(data.data() + data.size()));
}

std::vector<u8> from_string(std::string const & data) {
    return std::vector<u8>((const u8 *)data.data(), (const u8 *)(data.data() + data.size()));
}

} }

#endif /*__STRING_UTILS_H__*/
