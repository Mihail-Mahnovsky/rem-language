#ifndef REMLANG_TOKEN_HPP
#define REMLANG_TOKEN_HPP

#include <stdexcept>

#include "TokenType.hpp"
#include <string>

struct Token {
private:
    TokenType type;
    std::string value;
public:
    Token(const TokenType type, std::string value) : type(type), value(value) {}
    TokenType getType() const { return type; }
    std::string getValue() const { return value; }
    std::string toString() const {
        switch (type) {
            case TokenType::ASSIGN:
                return "=";
            case TokenType::ID:
                return "id";
            case TokenType::NUMBER:
                return "number";
            default:
                return "t";
        }
    }
};

#endif