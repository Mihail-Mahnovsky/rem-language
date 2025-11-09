#ifndef REMLANG_SETARRAYELEMENTNODE_HPP
#define REMLANG_SETARRAYELEMENTNODE_HPP

#include "Node.hpp"

class SetArrayElementNode : public Node {
private:
    Node* indexNode;
    Node* valueNode;
    int arrayOffset;
public:
    SetArrayElementNode(Node* indexNode, Node* valueNode, int arrayOffset)
        : indexNode(indexNode), valueNode(valueNode), arrayOffset(arrayOffset) {}

    std::any evaluate(Context &context) override {
        auto array = std::any_cast<std::vector<std::any>>(context.get(arrayOffset));
        auto index = static_cast<size_t>(std::any_cast<double>(indexNode->evaluate(context)));

        if (index >= array.size()) {
            throw std::runtime_error("Index out of bounds");
        }

        array[index] = valueNode->evaluate(context);
        context.set(arrayOffset, array);
        return array[index];
    }
};

#endif