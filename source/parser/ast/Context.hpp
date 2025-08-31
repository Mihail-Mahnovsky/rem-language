#ifndef REMLANG_CONTEXT_HPP
#define REMLANG_CONTEXT_HPP

#include <any>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <unordered_map>

class FunctionHeaderNode;

class Context{
private:
    std::vector<std::any> stack;
    std::vector<size_t> frameStack;
    std::unordered_map<std::string, FunctionHeaderNode*> userFunctions;
    std::unordered_map<std::string, std::function<std::any(std::vector<std::any>)>> functions;
public:
    Context();
    ~Context();
    void addUserFunction(std::string name, FunctionHeaderNode* function){
        userFunctions[name] = function;
    }
    std::any callFunction(std::string name, std::vector<std::any> args) {
        auto iter = functions.find(name);
        if (iter != functions.end()) {
            return iter->second(args);
        }
        throw std::runtime_error("func not found: " + name);
    }
    bool isHave(std::string name) {
        return functions.find(name) != functions.end();
    }
    FunctionHeaderNode* getUserFunction(std::string name){ return userFunctions[name]; }
    void pushNewFrame();
    void popFrame();
    std::any get(int offSet);
    void set(int offSet, const std::any& val);
};


#endif