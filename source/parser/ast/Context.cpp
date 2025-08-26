#include "Context.hpp"

#include <stdexcept>

Context::Context() :stack{} {}

Context::~Context(){
    stack.clear();
}

std::any Context::get(int offSet){
    if (offSet >= 0 && offSet < stack.size()){
        return stack[offSet];
    }
    throw std::out_of_range("out of range");
}

void Context::set(int offSet, const std::any& val){
    if (offSet > 0 && offSet < stack.size()){
        stack[offSet] = val;
    }

    if (offSet >= stack.size()){
        stack.resize(offSet + 10);
        stack[offSet] = val;
    }
}



