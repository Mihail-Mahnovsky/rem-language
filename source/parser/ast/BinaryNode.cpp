#include "BinaryNode.hpp"
#include <any>
#include <stdexcept>

#include "NumberLiteral.hpp"
#include "StringLiteral.hpp"
#include "Variable.hpp"
#include "../types.hpp"

BinaryNode::BinaryNode(Node *left, Node *right, Operations operation) :left(left),right(right),operation(operation){}

std::any BinaryNode::evaluate(Context& context) {
    std::any leftVal = left->evaluate( context);
    std::any rightVal = right->evaluate(context);

    if (leftVal.type() == typeid(double) && rightVal.type() == typeid(double)) {
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
            default:
                throw std::runtime_error("Unknown operation");
        }
    }
    else if (leftVal.type() == typeid(std::string) && rightVal.type() == typeid(std::string)) {
        std::string l = std::any_cast<std::string>(leftVal);
        std::string r = std::any_cast<std::string>(rightVal);

        switch (operation) {
            case Operations::PLUS:
                return l + r;
            default:
                throw std::runtime_error("Unknown operation for string");
        }
    }
    else if ((leftVal.type() == typeid(char) && rightVal.type() == typeid(std::string)) || (leftVal.type() == typeid(std::string) && rightVal.type() == typeid(char))) {
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

    //тут просто через елз иф пишешь другие реальзацы(строки чары и тд)

    throw std::runtime_error("Unsupported operand types");
}

bool BinaryNode::isExpressionType(Type type) {
    const bool res = checkExpressionType(left, type);
    return res && checkExpressionType(right, type);
}
