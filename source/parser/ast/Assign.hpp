#ifndef REMLANG_ASSIGN_HPP
#define REMLANG_ASSIGN_HPP

#include "Node.hpp"

#include <string>

class Assign : public Node {
private:
    std::string name;
    Node* right;
public:
    Assign(std::string name, Node* right);
    std::any evaluate() override;
    std::string getName() { return name; }
};

#endif