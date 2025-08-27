#ifndef REMLANG_CONTEXT_HPP
#define REMLANG_CONTEXT_HPP

#include <any>
#include <vector>

class Context{
private:
    std::vector<std::any> stack;
    std::vector<size_t> frameStack;
public:
    Context();
    ~Context();
    void pushNewFrame();
    void popFrame();
    std::any get(int offSet);
    void set(int offSet, const std::any& val);
};


#endif