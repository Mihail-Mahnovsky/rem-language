#ifndef REMLANG_ASSIGN_HPP
#define REMLANG_ASSIGN_HPP

#include "Node.hpp"

#include <string>

class Assign : public Node {
private:
    int offSet;
    Node* right;
public:
    Assign(int offSet, Node* right);
    std::any evaluate(Context& context) override;
    int getOffSet() { return offSet; }
};

#endif