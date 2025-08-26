#include "BinaryNode.hpp"
#include <any>
#include <stdexcept>

BinaryNode::BinaryNode(Node *left, Node *right, Operations operation) :left(left),right(right),operation(operation){}

std::any BinaryNode::evaluate() {
    std::any leftVal = left->evaluate();
    std::any rightVal = right->evaluate();

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
    if (leftVal.type() == typeid(std::string) && rightVal.type() == typeid(std::string)) {
        std::string l = std::any_cast<std::string>(leftVal);
        std::string r = std::any_cast<std::string>(rightVal);

        switch (operation) {
            case Operations::PLUS:
                return l + r;
            default:
                throw std::runtime_error("Unknown operation for string");
        }
    }
    //тут просто через елз иф пишешь другие реальзацы(строки чары и тд)

    throw std::runtime_error("Unsupported operand types");
}
