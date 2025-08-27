#ifndef REMLANG_UNARYNODE_HPP
#define REMLANG_UNARYNODE_HPP

#include "Node.hpp"

enum class UnaryOperation{
    NOT,
    NEGATE,
};

struct UnaryNode : public Node {
private:
    UnaryOperation operation;
    Node* right;
public:
    UnaryNode(UnaryOperation operation, Node* right) : operation(operation), right(right) {}
    std::any evaluate(Context& context) override{
        switch (operation){
            case UnaryOperation::NOT:
                return !std::any_cast<bool>(right->evaluate(context));
            case UnaryOperation::NEGATE:
                return -std::any_cast<double>(std::any_cast<double>(right->evaluate(context)));
        }
    }
};

#endif