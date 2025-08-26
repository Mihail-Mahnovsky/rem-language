#ifndef REMLANG_VARIABLE_HPP
#define REMLANG_VARIABLE_HPP

#include "Node.hpp"

class Variable : public Node {
private:
    std::any value;
public:
    std::any evaluate() override {
        return value;
    }
    Variable(std::any value) : value(value) {}
};

#endif