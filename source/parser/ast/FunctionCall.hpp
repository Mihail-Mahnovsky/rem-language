#ifndef REMLANG_FUNCTIONCALL_HPP
#define REMLANG_FUNCTIONCALL_HPP

#include <stdexcept>

#include "Node.hpp"

#include <string>
#include <vector>

#include "FunctionHeaderNode.hpp"
#include "../../utils.hpp"

#include "../../utils.hpp"

class FunctionCall : public Node
{
private:
    Context& contextRef;
    std::string name;
    std::vector<Node*> args;
    Scope* scope;
public:
    FunctionCall(Context& context, std::string& name, std::vector<Node*>& args)
        : contextRef(context)
        , name(name)
        , args(args)
        , scope(nullptr)
    {}

    std::any evaluate(Context& context) override;
    Type getType() const;
};

#endif