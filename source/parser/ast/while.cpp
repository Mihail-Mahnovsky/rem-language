#include "while.hpp"

std::any While::evaluate(Context& context){
    while (std::any_cast<bool>(this->condition->evaluate(context))){
        scope->evaluate(context);
    }

    return {};
}