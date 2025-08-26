#ifndef REMLANG_PARSER_HPP
#define REMLANG_PARSER_HPP

#include "ast/Node.hpp"
#include "../Lexer/Token.hpp"
#include <vector>

class Parser {
private:
    int pos;
    std::vector<Token> tokens;
    bool peek(TokenType wantType);
    void eat(TokenType type);
    Token current() {return tokens[pos];};
    std::vector<Node*> statement_list();
    Node* statement();
    Node* expression();
    Node* plusMinus();
    Node* mulMiv();
    Node* factor();
    Node* declaration();
    Node* reassigment();
public:
    Parser();
    std::vector<Node*> parse(std::vector<Token>& tokens);
};


#endif