#ifndef REMLANG_CONTEXT_HPP
#define REMLANG_CONTEXT_HPP

#include <any>
#include <string>
#include <vector>
#include <unordered_map>

class FunctionHeaderNode;

class Context{
private:
    std::vector<std::any> stack;
    std::vector<size_t> frameStack;
    std::unordered_map<std::string, FunctionHeaderNode*> userFunctions;
public:
    Context();
    ~Context();
    void addUserFunction(std::string name, FunctionHeaderNode* function){
        userFunctions[name] = function;
    }
    FunctionHeaderNode* getUserFunction(std::string name){ return userFunctions[name]; }
    void pushNewFrame();
    void popFrame();
    std::any get(int offSet);
    void set(int offSet, const std::any& val);
};


#endif