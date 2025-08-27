#include "Interpritator.hpp"

#include "../parser/ast/Assign.hpp"
#include "../parser/ast/BinaryNode.hpp"
#include "../parser/ast/Echo.hpp"

Interpritator::Interpritator() :context(){
}

Interpritator::~Interpritator(){
}

void Interpritator::execute(std::vector<Node*> nodes) {
    for (auto executeNode : nodes) {
        executeNode->evaluate(context);
    }
}