#ifndef REMLANG_INTERPRITATOR_HPP
#define REMLANG_INTERPRITATOR_HPP

#include <any>

#include "../parser/ast/Context.hpp"
#include "../parser/Parser.hpp"

class Interpritator {
private:
    Context context;
public:
    Interpritator();
    void execute(std::vector<Node*> nodes);
};


#endif