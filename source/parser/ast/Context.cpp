#include "Context.hpp"

#include <stdexcept>

Context::Context() :stack{},frameStack{} {}

Context::~Context(){
    stack.clear();
}

std::any Context::get(int offSet){
    if (offSet >= 0 && offSet < stack.size()){
        return stack[offSet];
    }
    throw std::out_of_range("out of range you tru get local variable?");
}

void Context::set(int offSet, const std::any& val) {
    if (offSet >= stack.size()) {
        stack.resize(offSet + 1);
    }
    stack[offSet] = val;
}

void Context::pushNewFrame() {
    frameStack.push_back(stack.size());
}

void Context::popFrame() {
    if (!frameStack.empty()) {
        size_t frameStart = frameStack.back();
        frameStack.pop_back();
        stack.resize(frameStart);
    } else {
        throw std::runtime_error("frame no exits");
    }
}


