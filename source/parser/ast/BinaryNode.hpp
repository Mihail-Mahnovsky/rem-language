#ifndef REMLANG_BINARYNODE_HPP
#define REMLANG_BINARYNODE_HPP

#include "Operations.hpp"
#include "Node.hpp"

class BinaryNode : public Node{
private:
    Node* left;
    Node* right;
    Operations operation;
public:
    BinaryNode(Node* left, Node* right, Operations operation);
    std::any evaluate(Context& context) override;
};


#endif