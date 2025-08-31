#ifndef REMLANG_STDLIB_HPP
#define REMLANG_STDLIB_HPP

#include <iostream>
#include <ostream>

#include "parser/ast/Node.hpp"

#include <vector>

std::any println(std::vector<std::any> arg) {
    if (!arg.empty()) {
        try {
            for (auto& i : arg) {
                if (i.type() == typeid(std::string)) {
                    std::cout << std::any_cast<std::string>(i) << '\n';
                } else if (i.type() == typeid(int)) {
                    std::cout << std::any_cast<int>(i) << '\n';
                } else if (i.type() == typeid(double)) {
                    std::cout << std::any_cast<double>(i) << '\n';
                }
            }
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return {};
}

std::any scan(std::vector<std::any> arg) {
    std::string str;
    std::cin >> str;
    return str;
}


#endif