#include "Parser.hpp"

#include "ast/Assign.hpp"
#include "ast/Echo.hpp"
#include "ast/BinaryNode.hpp"
#include "ast/NumberLiteral.hpp"
#include "ast/BoolLiteral.hpp"
#include "ast/StringLiteral.hpp"
#include "ast/Variable.hpp"
#include "fmt/base.h"

Parser::Parser() :pos(0),tokens{} {}

std::vector<Node*> Parser::parse(std::vector<Token>& tokens) {
    pos = 0;
    this->tokens = tokens;
    return statement_list();
}

std::vector<Node*> Parser::statement_list() {
    std::vector<Node*> nodes;

    while (pos < tokens.size()) {
        if(current().getType() == TokenType::RBRACE){
            break;
        }
        nodes.push_back(statement());
        eat(TokenType::SEMICOLON);
    }

    return nodes;
}

Node* Parser::statement() {
    Token tok = current();

    switch (tok.getType()) {
        case TokenType::TYPE:
            if (peek(TokenType::ID)){
                std::string type = current().getValue();
                eat(TokenType::TYPE);
                std::string name = current().getValue();
                eat(TokenType::ID);
                if (current().getType() == TokenType::ASSIGN){
                    return declaration(type, name);
                }//тут еще будет обработка фуункцый
            }
            break;
        case TokenType::ID:
            if (peek(TokenType::ASSIGN)){
                return reassigment();
            }
        case TokenType::PRINT:
            eat(TokenType::PRINT);
            return new Echo(expression());
         default:
            return expression();
            break;
    }

    throw std::runtime_error("Unexpected token");
}

Node* Parser::expression() {
    return plusMinus();
}

Node *Parser::plusMinus() {
    Node* node = mulMiv();
    while (current().getValue() == "+" || current().getValue() == "-") {
        Token op = current();
        eat(op.getType());
        Node* right = mulMiv();

        Operations oper = (op.getValue() == "+") ? Operations::PLUS : Operations::MINUS;
        node = new BinaryNode(node,right,oper);
    }
    return node;
}

Node *Parser::mulMiv() {
    Node* node = factor();
    while (current().getValue() == "*" || current().getValue() == "/") {
        Token op = current();
        eat(op.getType());
        Node* right = factor();

        Operations oper = (op.getValue() == "*") ? Operations::MULTIPLY : Operations::DIVISION;
        node = new BinaryNode(node,right,oper);
    }
    return node;
}

Node *Parser::factor() {
    Token tok = current();

    switch (tok.getType()) {
        case TokenType::NUMBER:
            eat(TokenType::NUMBER);
            return new NumberLiteral(std::stod(tok.getValue()));
        case TokenType::STRING:
            eat(TokenType::STRING);
            return new StringLiteral(tok.getValue());
        case TokenType::TRUE:
            eat(TokenType::TRUE);
            return new BooleanLiteral(true);
        case TokenType::FALSE:
            eat(TokenType::FALSE);
            return new BooleanLiteral(false);
        case TokenType::ID:{
                std::string name = tok.getValue();
                eat(TokenType::ID);
                if (offsets.find(name) == offsets.end()) {
                    throw std::runtime_error("not find this variable : " + name);
                }
                return new Variable(offsets[name]);
        }
        case TokenType::LPAREN: {
            eat(TokenType::LPAREN);
            Node* expr = expression();
            eat(TokenType::RPAREN);
            return expr;
        }
        default:
            throw std::runtime_error("Unexpected token");
    }
}

Node *Parser::declaration(std::string type,std::string name) {
    if (type == "int") { types[name] = Type::INT; }
    else if (type == "string") { types[name] = Type::STRING; }
    else if (type == "char") { types[name] = Type::CHAR; }
    else if (type == "bool") { types[name] = Type::BOOLEAN; }
    eat(TokenType::ASSIGN);
    Node* right = expression();

    Type expectedType = types[name];

    bool isTypeValid = false;

    switch (expectedType) {
        case Type::INT:
            isTypeValid = dynamic_cast<NumberLiteral*>(right) != nullptr;
            break;
        case Type::STRING:
            isTypeValid = dynamic_cast<StringLiteral*>(right) != nullptr;
            break;
        case Type::BOOLEAN:
            isTypeValid = dynamic_cast<BooleanLiteral*>(right) != nullptr;
            break;
        default:
            std::cerr << "unsupported type" << std::endl;
            exit(1);
    }

    if (!isTypeValid) {
        std::cerr << "error type dont euavial value : " << name << std::endl;
        exit(1);
    }

    offsets[name] = currentOffset;
    auto assign = new Assign(currentOffset, right);
    ++currentOffset;
    return assign;
}

Node *Parser::reassigment() {
    std::string name = current().getValue();
    eat(TokenType::ID);

    if (offsets.find(name) == offsets.end()) {
        throw std::runtime_error("don`t find this variable : " + name);
    }

    eat(TokenType::ASSIGN);

    Node* right = expression();
    int offset = offsets[name];
    return new Assign(offset, right);
}


bool Parser::peek(TokenType wantType) {
    if (pos < tokens.size() && tokens[pos + 1].getType() == wantType) {
        return true;
    }
    return false;
}

void Parser::eat(TokenType type) {
    if (pos < tokens.size() && current().getType() == type) {
        ++pos;
    }
    else {
        throw std::invalid_argument("Invalid token type " + current().toString());
    }
}