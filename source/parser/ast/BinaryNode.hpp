#ifndef REMLANG_BINARYNODE_HPP
#define REMLANG_BINARYNODE_HPP

#include <string>

#include "Operations.hpp"
#include "Node.hpp"

enum class Type;

bool checkExpressionType(Node* expression, Type type) ;

class BinaryNode : public Node{
private:
    Node* left;
    Node* right;
    Operations operation;
    std::any evalDouble(std::any leftVal,std::any rightVal);
    std::any evalBool(std::any leftVal,std::any rightVal);
    std::any evalString(std::any leftVal, std::any rightVal);
    std::any evalChar(std::any leftVal,std::any rightVal);
public:
    BinaryNode(Node* left, Node* right, Operations operation);
    std::any evaluate(Context& context) override;
    bool isExpressionType(Type type);
    Node* getLeft() { return left; }
    Node* getRight() { return right; }
};


#endif