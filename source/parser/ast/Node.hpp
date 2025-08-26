
#ifndef REMLANG_NODE_HPP
#define REMLANG_NODE_HPP

#include <any>

#include "Context.hpp"

class Node {
public:
    virtual std::any evaluate(Context& context) = 0;
    virtual ~Node() = default;
};

#endif