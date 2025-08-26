#ifndef REMLANG_VARIABLE_HPP
#define REMLANG_VARIABLE_HPP

#include "Node.hpp"

class Variable : public Node {
private:
    unsigned int offSet;
public:
    std::any evaluate(Context& context) override {
        return context.get(offSet);
    }
    Variable(unsigned int offSet) : offSet(offSet) {}
};

#endif