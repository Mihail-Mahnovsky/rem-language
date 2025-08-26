#ifndef REMLANG_LEXER_HPP
#define REMLANG_LEXER_HPP

#include "Token.hpp"
#include <vector>

class Lexer {
public:
    std::vector<Token> tokeNize(std::string line);
};


#endif