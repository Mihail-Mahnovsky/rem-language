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
    Context& context;

private:
    bool peek(TokenType wantType);
    void eat(TokenType type);
    Token current() { if (pos < tokens.size()) {return tokens[pos];} else return tokens.back(); };
    std::vector<Node*> statement_list();
    Node* statement();
    Node* expression();
    Node* orExpression();
    Node* andExpression();
    Node* equality();
    Node* relational();
    Node* addSub();
    Node* mulMiv();
    Node* unary();
    Node* factor();
    Node* declaration(const std::string& type, const std::string& name);
    Node* reassigment();
    Node* parseIf();
    Node* parseWhile();
    std::vector<Node*> parseScope();
    Node* parseFunction(std::string& type,std::string name);
    Node* parseFunctionCall(std::string& name);
    Node* parseArray(const std::string& name,size_t size);
public:
    Parser(Context& ctx);
    std::vector<Node*> parse(std::vector<Token>& tokens);
};


#endif