#ifndef REMLANG_LEXER_HPP
#define REMLANG_LEXER_HPP

#include "Token.hpp"
#include <vector>

class Lexer {
private:
    bool peek(std::string& line, char c,int pos){
        if (pos <= line.size() && line[pos] == c){
            return pos < line.size() && line[pos] == c;
        }
        return false;
    }
public:
    std::vector<Token> tokeNize(std::string line);
};


#endif