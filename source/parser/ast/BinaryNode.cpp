#include "BinaryNode.hpp"
#include <any>
#include <stdexcept>

#include "NumberLiteral.hpp"
#include "StringLiteral.hpp"
#include "../types.hpp"

BinaryNode::BinaryNode(Node *left, Node *right, Operations operation) :left(left),right(right),operation(operation){}

std::any BinaryNode::evalDouble(std::any leftVal,std::any rightVal)
{
    double l = std::any_cast<double>(leftVal);
    double r = std::any_cast<double>(rightVal);

    switch (operation) {
    case Operations::PLUS:
        return l + r;
    case Operations::MINUS:
        return l - r;
    case Operations::MULTIPLY:
        return l * r;
    case Operations::DIVISION:
        if (r == 0) throw std::runtime_error("Division by zero");
        return l / r;
    case Operations::EQUAL:
        return l == r;
    case Operations::NOTEQUAL:
        return l != r;
    case Operations::MIN:
        return l < r;
    case Operations::MAX:
        return l > r;
    case Operations::MINEQUAL:
        return l <= r;
    case Operations::MAXEQUAL:
        return l >= r;
    default:
        throw std::runtime_error("Unknown operation");
    }
}

std::any BinaryNode::evalBool(std::any rightVal, std::any leftVal){
    bool l = std::any_cast<bool>(leftVal);
    bool r = std::any_cast<bool>(rightVal);

    switch (operation) {
    case Operations::AND:
        return l && r;
    case Operations::OR:
        return l || r;
    case Operations::EQUAL:
        return l == r;
    case Operations::NOTEQUAL:
        return l != r;
    default:
        throw std::runtime_error("Unsupported boolean operation");
    }
}

std::any BinaryNode::evalString(std::any rightVal, std::any leftVal){
    std::string l = std::any_cast<std::string>(leftVal);
    std::string r = std::any_cast<std::string>(rightVal);

    switch (operation) {
    case Operations::PLUS:
        return l + r;
    case Operations::EQUAL:
        return l == r;
    case Operations::NOTEQUAL:
        return l != r;
    default:
        throw std::runtime_error("Unknown operation for string");
    }
}

std::any BinaryNode::evalChar(std::any rightVal, std::any leftVal){
    std::string l = (leftVal.type() == typeid(char) && rightVal.type() == typeid(std::string))
                ? std::string(1, std::any_cast<char>(leftVal))
                : std::any_cast<std::string>(leftVal);
    std::string r = (rightVal.type() == typeid(char))
                    ? std::string(1, std::any_cast<char>(rightVal))
                    : std::any_cast<std::string>(rightVal);
    switch (operation) {
    case Operations::PLUS:
        return l + r;
    default:
        throw std::runtime_error("Unknown operation for string and char");
    }
}



std::any BinaryNode::evaluate(Context& context) {
    std::any leftVal = left->evaluate( context);
    std::any rightVal = right->evaluate(context);
    if (!left || !right) {
        throw std::runtime_error("null operand in BinaryNode");
    }


    if (leftVal.type() == typeid(double) && rightVal.type() == typeid(double)) {return evalDouble(leftVal,rightVal);}
    else if (leftVal.type() == typeid(bool) && rightVal.type() == typeid(bool)) { return evalBool(leftVal,rightVal); }
    else if (leftVal.type() == typeid(std::string) && rightVal.type() == typeid(std::string)) {return evalString(leftVal,rightVal);}
    else if ((leftVal.type() == typeid(char) && rightVal.type() == typeid(std::string)) || (leftVal.type() == typeid(std::string) && rightVal.type() == typeid(char))) {return evalChar(leftVal,rightVal);}

    //тут просто через елз иф пишешь другие реальзацы(строки чары и тд)

    //throw std::runtime_error("Unsupported operand types");
}

bool BinaryNode::isExpressionType(Type type) {
    switch (operation)
    {
    case Operations::PLUS:
        if (checkExpressionType(left, Type::STRING) && checkExpressionType(right, Type::STRING))
            return type == Type::STRING;
        else if (checkExpressionType(left, Type::INT) && checkExpressionType(right, Type::INT))
            return type == Type::INT;
        break;

    case Operations::MINUS:
    case Operations::MULTIPLY:
    case Operations::DIVISION:
        if (checkExpressionType(left, Type::INT) && checkExpressionType(right, Type::INT))
            return type == Type::INT;
        break;

    case Operations::EQUAL:
    case Operations::NOTEQUAL:
    case Operations::MIN:
    case Operations::MAX:
    case Operations::MINEQUAL:
    case Operations::MAXEQUAL:
        if (checkExpressionType(left, Type::INT) && checkExpressionType(right, Type::INT)) return type == Type::BOOLEAN;
        if (checkExpressionType(left, Type::CHAR) && checkExpressionType(right, Type::CHAR)) return type == Type::BOOLEAN;
        if (checkExpressionType(left, Type::BOOLEAN) && checkExpressionType(right, Type::BOOLEAN)) return type == Type::BOOLEAN;
        if (checkExpressionType(left, Type::STRING) && checkExpressionType(right, Type::STRING)) return type == Type::BOOLEAN;
        break;

    case Operations::AND:
    case Operations::OR:
        if (checkExpressionType(left, Type::BOOLEAN) && checkExpressionType(right, Type::BOOLEAN))
            return type == Type::BOOLEAN;
        break;
    }

    return false;
}
