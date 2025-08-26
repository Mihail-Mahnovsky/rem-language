#ifndef REMLANG_NUMBERCONSTANT_HPP
#define REMLANG_NUMBERCONSTANT_HPP

#include "Node.hpp"

class NumberConstant : public Node {
private:
    double value;
public:
    NumberConstant(double value) : value(value) {};
    std::any evaluate() override {
        return value;
    }
};

#endif