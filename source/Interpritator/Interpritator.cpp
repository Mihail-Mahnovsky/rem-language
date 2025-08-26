#include "Interpritator.hpp"

#include "../parser/ast/Assign.hpp"
#include "../parser/ast/BinaryNode.hpp"
#include "../parser/ast/Echo.hpp"

Interpritator::Interpritator() :variables{} {}

void Interpritator::execute(std::vector<Node*> nodes) {
    for (auto executeNode : nodes) {
        if (auto echo = dynamic_cast<Echo*>(executeNode)) {
            echo->print(variables);
        }else if (auto assign = dynamic_cast<Assign*>(executeNode)) {
            variables[assign->getName()] = assign->evaluate();
        }else if (auto binOp = dynamic_cast<BinaryNode*>(executeNode)) {
            binOp->evaluate();
        }
    }
}