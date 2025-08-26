#ifndef REMLANG_UTILS_HPP
#define REMLANG_UTILS_HPP
#include "parser/ast/BinaryNode.hpp"
#include "parser/ast/NumberLiteral.hpp"
#include "parser/ast/StringLiteral.hpp"
#include "parser/ast/BoolLiteral.hpp"
#include "parser/ast/CharLiteral.hpp"
#include "parser/ast/Variable.hpp"

bool checkExpressionType(Node* expression, Type type)
{
    if (!expression) return false;
    else if ( dynamic_cast<NumberLiteral*>(expression) != nullptr ) {
        return type == Type::INT;
    }

    else if ( dynamic_cast<StringLiteral*>(expression) != nullptr ) {
        return type == Type::STRING;
    }

    else if (dynamic_cast<BooleanLiteral*>(expression) != nullptr) {
        return type == Type::BOOLEAN;
    }
    else if (dynamic_cast<CharLiteral*>(expression) != nullptr) {
        return type == Type::CHAR;
    }

    else if (auto var = dynamic_cast<Variable*>(expression)) {
        return var->getType() == type;
    }

    else if (const auto bin = dynamic_cast<BinaryNode*>(expression) ) {
        return bin->isExpressionType(type);
    }

    return false;
}

#endif