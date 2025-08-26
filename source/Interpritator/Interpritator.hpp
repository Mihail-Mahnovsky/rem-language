#ifndef REMLANG_INTERPRITATOR_HPP
#define REMLANG_INTERPRITATOR_HPP

#include <vector>
#include <any>
#include <unordered_map>

#include "../parser/Parser.hpp"

class Interpritator {
private:
    //std::vector<std::any> stack;
    std::unordered_map<std::string, std::any> variables;
public:
    Interpritator();
    void execute(std::vector<Node*> nodes);
};


#endif