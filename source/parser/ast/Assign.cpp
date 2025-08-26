#include "Assign.hpp"

Assign::Assign(int offSet, Node* right) :offSet(offSet),right(right){}

std::any Assign::evaluate(Context& context) {
    std::any value = right->evaluate(context);
    context.set(offSet, value);
    return value;
}
