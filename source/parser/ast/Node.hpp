
#ifndef REMLANG_NODE_HPP
#define REMLANG_NODE_HPP

#include <any>

class Node {
public:
    virtual std::any evaluate() = 0;
    virtual ~Node() = default;
};

#endif