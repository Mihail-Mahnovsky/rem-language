#include "Assign.hpp"

Assign::Assign(std::string name, Node* right) :name(name),right(right){}

std::any Assign::evaluate() {
    return right->evaluate();
}
