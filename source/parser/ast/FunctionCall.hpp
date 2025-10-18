#ifndef REMLANG_FUNCTIONCALL_HPP
#define REMLANG_FUNCTIONCALL_HPP

#include <stdexcept>

#include "Node.hpp"

#include <string>
#include <vector>

#include "FunctionHeaderNode.hpp"
#include "../../utils.hpp"

#include "../../utils.hpp"

class FunctionCall : public Node
{
private:
    Context& contextRef;
    std::string name;
    std::vector<Node*> args;
    Scope* scope;
public:
    FunctionCall(Context& context, std::string& name, std::vector<Node*>& args)
        : contextRef(context)
        , name(name)
        , args(args)
        , scope(nullptr)
    {}

    std::any evaluate(Context& context) override{

        if (context.isHave(name)) {
            std::vector<std::any> aargs;
            for (Node* arg : args) {
                aargs.push_back(arg->evaluate(context));
            }
            return context.callFunction(name,aargs);
        }else {
            FunctionHeaderNode* header = context.getUserFunction(name);
            scope = header->getScope();

            std::vector<Arg> hArgs = header->getArgs();
            for (int i = 0; i < hArgs.size(); ++i){
                //if (!checkExpressionType(args[i],hArgs[i].getType())){
                //    throw std::invalid_argument("arugment type not eqvial(frim func call)");
                //}else{
                context.set(hArgs[i].getOffset(),args[i]->evaluate(context));
                //}
            }

            std::any result = scope->evaluate(context);
            delete header;
            return result;
        }
    }

    Type getType() const {
        if (scope) {
            return checkExprType(scope->getReturn());
        }
        return contextRef.getFunctionType(name);
    }
};

#endif