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
        if (std::any_cast<double>(indexOfArray->evaluate(context)) < static_cast<double>(std::any_cast<std::vector<std::any>>(context.get(offsetArray)).size())) {
            return std::any_cast<std::vector<std::any>>(context.get(offsetArray)).at(std::any_cast<double>(indexOfArray->evaluate(context)));
        }else {
            throw std::runtime_error("error with array size");
        }
    }
};


#endif