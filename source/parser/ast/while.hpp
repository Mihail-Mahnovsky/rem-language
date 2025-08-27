#ifndef REMLANG_WHILE_HPP
#define REMLANG_WHILE_HPP

#include "Node.hpp"
#include "Scope.hpp"

class While : public Node{
private:
    Node* condition;
    Scope* scope;
public:
    While(Node* condition, Scope* scope) :condition(condition), scope(scope){}
    std::any evaluate(Context& context) override{
        while (std::any_cast<bool>(this->condition->evaluate(context))){
            context.pushNewFrame();
            scope->evaluate(context);
            context.popFrame();
        }

        return {};
    }
};

#endif