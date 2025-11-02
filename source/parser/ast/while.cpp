#include "while.hpp"

std::any While::evaluate(Context& context){
    while (std::any_cast<bool>(this->condition->evaluate(context))){
        if (context.getBreakState()) {
            context.setBreakState();
            break;
        }
        scope->evaluate(context);
    }

    return {};
}