#ifndef REMLANG_VARIABLE_HPP
#define REMLANG_VARIABLE_HPP

#include "Node.hpp"
#include "../types.hpp"

class Variable : public Node {
private:
    unsigned int offSet;
    Type type;
public:
    Variable(unsigned int offSet,Type type)
    : offSet(offSet)
    ,type(type)
    {}

    Type getType() { return type; }

    std::any evaluate(Context& context) override {
        return context.get(offSet);
    }
};

#endif