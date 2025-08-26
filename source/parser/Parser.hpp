#ifndef REMLANG_PARSER_HPP
#define REMLANG_PARSER_HPP

#include <unordered_map>
#include <vector>

#include "../Lexer/Token.hpp"
#include "ast/Node.hpp"
#include "types.hpp"

class Parser {
private:
    int pos;
    std::vector<Token> tokens;
    std::unordered_map <std::string, int> offsets;
    std::unordered_map <std::string, Type> types;
    int currentOffset;

    bool peek(TokenType wantType);
    void eat(TokenType type);
    Token current() {return tokens[pos];};
    std::vector<Node*> statement_list();
    Node* statement();
    Node* expression();
    Node* plusMinus();
    Node* mulMiv();
    Node* factor();
    Node* declaration(std::string type,std::string name);
    Node* reassigment();
public:
    Parser();
    std::vector<Node*> parse(std::vector<Token>& tokens);
};


#endif