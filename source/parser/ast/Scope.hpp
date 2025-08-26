#ifndef REMLANG_SCOPE_HPP
#define REMLANG_SCOPE_HPP

#include "Node.hpp"
#include <vector>

class Scope : public Node {
private:
    std::vector<Node*> nodes;
public:
    Scope(std::vector<Node*> nodes) :nodes(nodes) {};
    std::any evaluate() override {
        return std::any();
    }
};

#endif