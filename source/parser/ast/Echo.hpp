//this construction add for test in wait full lang version
#ifndef REMLANG_ECHO_HPP
#define REMLANG_ECHO_HPP

#include <iostream>
#include <unordered_map>

#include "Node.hpp"

class Echo : public Node {
private:
    Node* expression;
    std::any* findVariable(std::unordered_map<std::string, std::any>& variables,std::string var_name) {
        if (variables.find(var_name) != variables.end()) {
            return &variables[var_name];
        }
        return nullptr;
    }
public:
    Echo(Node* expression) : expression(expression) {};
    void print(std::unordered_map<std::string, std::any>& variables) {
        std::any value = evaluate();
        if (value.type() == typeid(double)) {
            std::cout << std::any_cast<double>(value) << std::endl;
        } else if (value.type() == typeid(std::string)) {
            std::any* var = findVariable(variables, std::any_cast<std::string>(value));
            if (var != nullptr) {
                std::cout << std::any_cast<double>(*var) << std::endl;
            } else {
                std::cout << std::any_cast<std::string>(value) << std::endl;
            }
        } else {
            std::cout << "Unknown type in Echo" << std::endl;
        }
    }
    std::any evaluate() override {
        return expression->evaluate();
    }
};

#endif