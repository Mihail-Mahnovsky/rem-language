#include "utils.hpp"

bool checkExpressionType(Node* expression, Type type){
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

    else if (const auto func = dynamic_cast<FunctionCall*>(expression) ) {
        return func->getType() == type;
    }

    return false;
}

Type chechExprType(Node* expression){
if (!expression) return Type::VOID;
else if ( dynamic_cast<NumberLiteral*>(expression) != nullptr ) {
    return Type::INT;
}

else if ( dynamic_cast<StringLiteral*>(expression) != nullptr ) {
    return Type::STRING;
}

else if (dynamic_cast<BooleanLiteral*>(expression) != nullptr) {
    return Type::BOOLEAN;
}
else if (dynamic_cast<CharLiteral*>(expression) != nullptr) {
    return Type::CHAR;
}

else if (auto var = dynamic_cast<Variable*>(expression)) {
    return var->getType();
}

else if (auto* bin = dynamic_cast<BinaryNode*>(expression) ) {
    return chechExprType(bin);
}

else if (auto func = dynamic_cast<FunctionCall*>(expression) ) {
    return func->getType();
}

return Type::VOID;
}