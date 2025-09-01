#ifndef REMLANG_FUNCTIONHEADERNODE_HPP
#define REMLANG_FUNCTIONHEADERNODE_HPP

#include "Node.hpp"
#include "Scope.hpp"
//#include "Context.hpp"

#include <string>
#include <vector>

#include "../types.hpp"

class Context;


struct Arg{
private:
    Type type;
    std::string name;
    unsigned int offset;
public:
    Arg(Type type,std::string name,unsigned int ooffset) : type(type), name(name), offset(ooffset) {}
    Type getType(){return type;}
    std::string getName(){return name;}
    unsigned int getOffset(){return offset;}
};

class FunctionHeaderNode : public Node{
private:
    std::vector<Arg> args;
    Scope* scope;
    std::string name;
public:
    FunctionHeaderNode(std::string name, Scope* scope,std::vector<Arg> args) : Node(), name(name), scope(scope), args(args) {};
    std::any evaluate(Context& context) override;
    Scope* getScope(){return scope;}
    std::vector<Arg> getArgs(){return args;}
};

#endif