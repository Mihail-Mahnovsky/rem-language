#ifndef REMLANG_ARRAYLITERAL_HPP
#define REMLANG_ARRAYLITERAL_HPP

#include "Node.hpp"

class ArrayLiteral : public Node {
private:
    std::vector<Node*> value;
public:
    ArrayLiteral(const std::vector<Node*>& vals)
          : value(vals) {}

    std::any evaluate(Context &context) override {
        std::vector<std::any> result;
        result.reserve(value.size());
        for (auto* el : value) {
            result.push_back(el->evaluate(context));
        }
        return result;
    }
};

#endif