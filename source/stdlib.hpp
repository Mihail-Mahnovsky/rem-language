#ifndef REMLANG_STDLIB_HPP
#define REMLANG_STDLIB_HPP

#include <iostream>
#include <ostream>

#include "parser/ast/Node.hpp"

#include <vector>

std::any println(std::vector<std::any> args) {
    if (!args.empty()) {
        try {
            for (auto& i : args) {
                if (i.type() == typeid(std::string)) {
                    std::cout << std::any_cast<std::string>(i);
                } else if (i.type() == typeid(int)) {
                    std::cout << std::any_cast<int>(i);
                } else if (i.type() == typeid(double)) {
                    std::cout << std::any_cast<double>(i);
                }else if (i.type() == typeid(std::vector<std::any>)) {
                    std::cout << "{";
                    for (size_t i = 0; i < std::any_cast<std::vector<std::any>>(args[0]).size(); ++i) {
                        std::cout << std::any_cast<double>(std::any_cast<std::vector<std::any>>(args[i])[i]);
                        if (i + 1 < args.size()) std::cout << ", ";
                    }
                    std::cout << "}";
                }
            }
            std::cout << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return {};
}

std::any print(std::vector<std::any> arg) {
    if (!arg.empty()) {
        try {
            for (auto& i : arg) {
                if (i.type() == typeid(std::string)) {
                    std::cout << std::any_cast<std::string>(i);
                } else if (i.type() == typeid(int)) {
                    std::cout << std::any_cast<int>(i);
                } else if (i.type() == typeid(double)) {
                    std::cout << std::any_cast<double>(i);
                }
            }
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return {};
}


std::any toint(std::vector<std::any> arg) {
    if (!arg.empty()) {
        try {
            for (auto& i : arg) {
                if (i.type() == typeid(std::string)) {
                    return std::stod(std::any_cast<std::string>(i));
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

std::any len(std::vector<std::any> arg) {
    return static_cast<double>(std::any_cast<std::vector<std::any>>(arg.at(0)).size());
}


#endif