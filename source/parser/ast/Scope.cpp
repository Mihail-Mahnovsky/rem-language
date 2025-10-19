#include "Scope.hpp"

std::any Scope::evaluate(Context& context)  {
    context.pushNewFrame();
    for (auto node : nodes){
        if (dynamic_cast<ReturnNode*>(node)){
            return node->evaluate(context);
        }
        else { node->evaluate(context); }
    }
    context.popFrame();
    return {};
}

Node* Scope::getReturn() const {
    for (auto node : nodes){
        if (ReturnNode* ret = dynamic_cast<ReturnNode*>(node)){
            return ret;
        }
    }
    return nullptr;
}