#ifndef REMLANG_RETURNNODE_HPP
#define REMLANG_RETURNNODE_HPP

#include "Node.hpp"

class ReturnNode : public Node{
private:
    Node* returnValue;
public:
    ReturnNode(Node* returnValue) : returnValue(returnValue){};
    std::any evaluate(Context& context) override{
        const auto val = returnValue->evaluate(context);

        context.setReturn(val);

        return val;
    }

    //сделанно только для проверки типов
    Node* getReturnValue() { return returnValue; }
};

#endif