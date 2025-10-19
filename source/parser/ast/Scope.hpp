#ifndef REMLANG_SCOPE_HPP
#define REMLANG_SCOPE_HPP

#include "Node.hpp"
#include <vector>

#include "ReturnNode.hpp"

class Scope : public Node {
private:
    std::vector<Node*> nodes;
public:
    Scope(std::vector<Node*> nodes)
        :nodes(std::move(nodes))
    {}

    std::any evaluate(Context& context) override;
    Node* getReturn() const;
};

#endif