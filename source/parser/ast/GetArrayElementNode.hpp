#ifndef REMLANG_GETARRAYELEMENTNODE_HPP
#define REMLANG_GETARRAYELEMENTNODE_HPP

#include "Node.hpp"

class GetArrayElementNode : public Node {
private:
    Node* indexOfArray;
    int offsetArray;
public:
    GetArrayElementNode(Node* indexOfArray, int offsetArray)
        :indexOfArray(indexOfArray)
        ,offsetArray(offsetArray)
    {}

    std::any evaluate(Context &context) override {
        std::any arrayAny = context.get(offsetArray);

        if (!arrayAny.has_value()) {
            throw std::runtime_error("Array not initialized");
        }

        if (arrayAny.type() != typeid(std::vector<std::any>)) {
            throw std::runtime_error("Variable is not an array");
        }

        auto array = std::any_cast<std::vector<std::any>>(arrayAny);

        std::any indexAny = indexOfArray->evaluate(context);
        if (indexAny.type() != typeid(double)) {
            throw std::runtime_error("Array index must be a number");
        }

        int index = static_cast<int>(std::any_cast<double>(indexAny));

        if (index < 0 || index >= array.size()) {
            throw std::runtime_error("Array index out of bounds");
        }

        return array[index];
    }
};


#endif