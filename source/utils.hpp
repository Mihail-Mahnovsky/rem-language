#ifndef REMLANG_UTILS_HPP
#define REMLANG_UTILS_HPP
#include "parser/ast/BinaryNode.hpp"
#include "parser/ast/NumberLiteral.hpp"
#include "parser/ast/StringLiteral.hpp"
#include "parser/ast/BoolLiteral.hpp"
#include "parser/ast/CharLiteral.hpp"
#include "parser/ast/Variable.hpp"

#include "Lexer/Token.hpp"

class FunctionCall;

bool checkExpressionType(Node* expression, Type type);
Type checkExprType(Node* expression);

inline std::string typeToString(TokenType type) {
    switch(type) {
        case TokenType::ID:
            return "ID";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::STRING:
            return "STRING";
        case TokenType::TRUE:
            return "TRUE";
        case TokenType::FALSE:
            return "FALSE";
        case TokenType::AND:
            return "AND";
        case TokenType::OR:
            return "OR";
        case  TokenType::IF:
            return "IF";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::ELIF:
            return "ELIF";
        case TokenType::ASSIGN:
            return "ASSIGN";
        case TokenType::BREAK:
            return "BREAK";
        default:
            return "UNKNOWN";
    }
}

#endif