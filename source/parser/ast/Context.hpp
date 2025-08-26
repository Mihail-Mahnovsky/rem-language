#ifndef REMLANG_CONTEXT_HPP
#define REMLANG_CONTEXT_HPP

#include <any>
#include <vector>

class Context{
private:
    std::vector<std::any> stack;
public:
    Context();
    ~Context();
    void push(const std::any& val) {stack.push_back(val);}
    void pop() {stack.pop_back();}
    std::any get(int offSet);
    void set(int offSet, const std::any& val);
};


#endif