#ifndef REMLANG_INTERPRITATOR_HPP
#define REMLANG_INTERPRITATOR_HPP

#include <any>

#include "../parser/ast/Context.hpp"
#include "../parser/Parser.hpp"

class Interpreter {
private:
    Context context;
public:
    Interpreter();
    ~Interpreter();
    void execute(std::vector<Node*> nodes);
};


#endif