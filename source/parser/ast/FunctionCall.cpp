#include "FunctionCall.hpp"

std::any FunctionCall::evaluate(Context& context){

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

Type FunctionCall::getType() const {
    if (scope) {
        return checkExprType(scope->getReturn());
    }
    return contextRef.getFunctionType(name);
}