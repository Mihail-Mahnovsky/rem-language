#ifndef REMLANG_ECHO_HPP
#define REMLANG_ECHO_HPP

#include <iostream>
#include "Node.hpp"
#include "Context.hpp"
#include <typeinfo>

class Echo : public Node {
private:
    Node* expression;
public:
    Echo(Node* expression) : expression(expression) {}

    std::any evaluate(Context& context) override {
        std::any value = expression->evaluate(context);

        if (value.type() == typeid(double)) {
            std::cout << std::any_cast<double>(value) << std::endl;
        } else if (value.type() == typeid(std::string)) {
            std::cout << std::any_cast<std::string>(value) << std::endl;
        } else if (value.type() == typeid(bool)) {
            std::cout << (std::any_cast<bool>(value) ? "true" : "false") << std::endl;
        } else if (value.type() == typeid(char))
        {
            std::cout << std::any_cast<char>(value) << std::endl;
        }
        else if (!value.has_value()) {
            std::cout << "null" << std::endl;
        } else {
            std::cout << "Echo: Unknown or unsupported type: " << value.type().name() << std::endl;
        }

        return {};
    }
};

#endif
