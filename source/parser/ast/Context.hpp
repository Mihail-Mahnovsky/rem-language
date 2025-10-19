#ifndef REMLANG_CONTEXT_HPP
#define REMLANG_CONTEXT_HPP

#include <any>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <unordered_map>

#include "../types.hpp"

class FunctionHeaderNode;

struct FunctionInfo {
    std::function<std::any(std::vector<std::any>)> function;
    Type returnType;
};

class Context {
private:
    std::vector<std::any> stack;
    std::vector<size_t> frameStack;
    std::unordered_map<std::string, FunctionHeaderNode*> userFunctions;
    std::unordered_map<std::string, FunctionInfo> functions;
    std::any currentReturn;
public:
    Context();
    ~Context();

    bool hasReturn() const {
        return currentReturn.has_value();
    }

    void setReturn(const std::any& returnValue) {
        currentReturn = returnValue;
    }

    std::any getReturn() const {
        return currentReturn;
    }

    void addUserFunction(std::string name, FunctionHeaderNode* function){
        userFunctions[name] = function;
    }
    std::any callFunction(std::string name, std::vector<std::any> args) {
        auto iter = functions.find(name);
        if (iter != functions.end()) {
            return iter->second.function(args);
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

    Type getFunctionType(const std::string& name) const {
        auto iter = functions.find(name);
        if (iter != functions.end()) {
            return iter->second.returnType;
        }

        return Type::VOID;
    }
};


#endif