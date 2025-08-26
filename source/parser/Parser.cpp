#include "Parser.hpp"

#include "ast/Assign.hpp"
#include "ast/Echo.hpp"
#include "ast/BinaryNode.hpp"
#include "ast/NumberConstant.hpp"
#include "ast/Variable.hpp"

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
        case TokenType::ID:
            if (peek(TokenType::TYPE)) {
                return declaration();
            }
            else if (peek(TokenType::ASSIGN)) {
                return reassigment();
            }
            else if (peek(TokenType::LPAREN)) {

            }
            break;
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
            return new NumberConstant(std::stod(tok.getValue()));
        case TokenType::ID:
            eat(TokenType::ID);
            return new Variable(tok.getValue());
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

Node *Parser::declaration() {
    std::string name = current().getValue();
    eat(TokenType::ID);
    std::string type = current().getValue();
    if (type == "int") { }
    eat(TokenType::ASSIGN);
    Node* right = expression();
    return new Assign(name, right);
}

Node *Parser::reassigment() {

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