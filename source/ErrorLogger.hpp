
#ifndef REMLANG_ERRORLOGGER_HPP
#define REMLANG_ERRORLOGGER_HPP

#include <string>

class ErrorLogger {
public:
    static void throwWarning(const std::string& message);
    static void throwError(const std::string& message);
};


#endif