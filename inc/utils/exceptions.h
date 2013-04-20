#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <utils/string_utils.h>

#include <exception>
#include <string>

namespace manticore { namespace utils {

struct FileNotFoundException : public std::exception {
    const std::string message_;
    const std::string name_;

    FileNotFoundException(std::string const & name) : message_(stringify("file ", name, " not found\n")), name_(name) { }
    virtual ~FileNotFoundException() noexcept { }

    std::string const & GetFileName() const { return name_; }

    virtual std::string const & GetMessage() const { return message_; }
    virtual std::string const & ToString() const { return GetMessage(); }

    virtual char const * what() const noexcept { return GetMessage().data(); }
};

} }

#endif /*__EXCEPTIONS_H__*/
