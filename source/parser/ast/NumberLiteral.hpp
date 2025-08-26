#ifndef REMLANG_NUMBERCONSTANT_HPP
#define REMLANG_NUMBERCONSTANT_HPP

#include "Node.hpp"

class NumberLiteral : public Node {
private:
    double value;
public:
    NumberLiteral(double value) : value(value) {};
    std::any evaluate(Context& context) override {
        return value;
    }
};

#endif