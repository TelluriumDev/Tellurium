#pragma once
#include "TSEssential.h" // IWYU pragma: export

#include <exception>
#include <stdexcept> // IWYU pragma: keep
#include <string>

#define _CATCH_CODES(IN)                                      \
    LOGGER.error("Error In {}!",IN);                          \
    std::exception_ptr exc_ptr = std::current_exception();    \
    TSEssential::Exception::ProcessException(exc_ptr);

namespace TSEssential::Exception {
class DirCannotCreatedException : public std::exception {
public:
    DirCannotCreatedException(const std::string& _Message) { msg += _Message; }
    DirCannotCreatedException(const char* _Message) { msg += std::string(_Message); }
    const char* what() const override { return msg.c_str(); }


private:
    std::string msg = "[DirCannotCreatedException] ";
};

void ProcessException(std::exception_ptr);
} // namespace LL3Mine2_Class::Exception