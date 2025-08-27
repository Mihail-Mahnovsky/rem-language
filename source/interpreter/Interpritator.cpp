#include "Interpritator.hpp"

#include "../parser/ast/Assign.hpp"
#include "../parser/ast/BinaryNode.hpp"
#include "../parser/ast/Echo.hpp"

Interpreter::Interpreter() :context(){
}

Interpreter::~Interpreter(){
}

void Interpreter::execute(std::vector<Node*> nodes) {
    for (auto executeNode : nodes) {
        executeNode->evaluate(context);
    }
}