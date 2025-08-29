#ifndef REMLANG_FUNCTIONCALL_HPP
#define REMLANG_FUNCTIONCALL_HPP

#include <stdexcept>

#include "Node.hpp"

#include <string>
#include <vector>

#include "FunctionHeaderNode.hpp"
#include "../../utils.hpp"
#include "../../utils.hpp"

#include "../../utils.hpp"

class FunctionCall : public Node{
private:
    std::string name;
    std::vector<Node*> args;
    Scope* scope;
public:
    FunctionCall(std::string& name, std::vector<Node*> args) : name(name), args(args) {};
    std::any evaluate(Context& context) override{
        FunctionHeaderNode* header = context.getUserFunction(name);
        scope = header->getScope();

        std::vector<Arg> hArgs = header->getArgs();
        for (int i = 0; i < hArgs.size(); ++i){
            if (!checkExpressionType(args[i],hArgs[i].getType())){
                throw std::invalid_argument("arugment type not eqvial(frim func call)");
            }else{
                context.set(hArgs[i].getOffset(),args[i]->evaluate(context));
            }
        }

        return scope->evaluate(context);

        delete header;
        return {};
    }

    Type getType(){
        return chechExprType(scope->getReturn());
    }
};

#endif