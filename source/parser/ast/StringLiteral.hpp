#ifndef REMLANG_STRINGLITERAL_HPP
#define REMLANG_STRINGLITERAL_HPP

#include <string>

#include "Node.hpp"

class StringLiteral : public Node {
private:
    std::string value;
public:
    StringLiteral(std::string value) : value(value) {};
    std::any evaluate(Context& context) override {
        return value;
    }
};

#endif