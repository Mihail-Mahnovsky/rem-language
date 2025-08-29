#include "FunctionHeaderNode.hpp"

std::any FunctionHeaderNode::evaluate(Context& context){
    context.addUserFunction(name, this);
    return {};
}