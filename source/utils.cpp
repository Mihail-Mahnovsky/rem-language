#include "utils.hpp"

#include  <iostream>

#include "parser/ast/FunctionCall.hpp"

bool checkExpressionType(Node* expression, Type type) {
    return checkExprType(expression) == type;
}

Type checkExprType(Node* expression) {
    if (!expression) return Type::VOID;

    if ( dynamic_cast<NumberLiteral*>(expression) != nullptr ) {
        return Type::INT;
    }

    if ( dynamic_cast<StringLiteral*>(expression) != nullptr ) {
        return Type::STRING;
    }

    if (dynamic_cast<BooleanLiteral*>(expression) != nullptr) {
        return Type::BOOLEAN;
    }

    if (dynamic_cast<CharLiteral*>(expression) != nullptr) {
        return Type::CHAR;
    }

    if (auto var = dynamic_cast<Variable*>(expression)) {
        return var->getType();
    }

    if (auto* bin = dynamic_cast<BinaryNode*>(expression) ) {
        //return checkExprType(bin);
            Type leftType = checkExprType(bin->getLeft());
            Type rightType = checkExprType(bin->getRight());

            if (leftType == rightType) {
                return leftType;
            } else {
                std::cerr << "type mismatch in binnode: "
                          << "left = " << (int)leftType << " right = " << (int)rightType << std::endl;
                return Type::VOID;
        }
    }

    if (auto func = dynamic_cast<FunctionCall*>(expression) ) {
        return func->getType();
    }

    return Type::VOID;
}