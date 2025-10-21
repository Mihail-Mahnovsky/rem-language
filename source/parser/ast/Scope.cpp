#include "Scope.hpp"

std::any Scope::evaluate(Context& context)  {
    context.pushNewFrame();

    for (auto node : nodes){
        auto res = node->evaluate(context);

        if (context.hasReturn()){
            context.popFrame();
            return context.getReturn();
        }
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