#include "ErrorLogger.hpp"

#include <fmt/color.h>

void ErrorLogger::throwWarning(const std::string& message) {
    fmt::print(fg(fmt::color::yellow),"{}",message);
}

void ErrorLogger::throwError(const std::string& message) {
    fmt::print(fg(fmt::color::red),"{}",message);
    exit(1);
}