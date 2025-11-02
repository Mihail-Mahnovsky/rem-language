#ifndef REMLANG_BREAK_HPP
#define REMLANG_BREAK_HPP

#include "Node.hpp"

class BreakNode : public Node {
public:
    BreakNode() = default;
    std::any evaluate(Context &context) override {
        context.setBreakState();
        return {};
    }
};

#endif