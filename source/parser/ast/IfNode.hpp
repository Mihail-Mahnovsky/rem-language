#ifndef REMLANG_IFNODE_HPP
#define REMLANG_IFNODE_HPP

#include "Node.hpp"
#include "Scope.hpp"
#include <optional>

struct Block{
private:
    std::optional<Node*> condition;
    Scope* scope;
public:
    Block(Node* condition, Scope* scope) : condition(condition), scope(scope){}
    std::optional<Node*> getCondition(){return condition;}
    Scope* getScope(){return scope;}
};

class IfNode : public Node
{
private:
    std::vector<Block> blocks;
public:
    IfNode(std::vector<Block> blocks);
    std::any evaluate(Context& context) override;
};


#endif