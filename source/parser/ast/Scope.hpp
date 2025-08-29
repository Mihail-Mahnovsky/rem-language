#ifndef REMLANG_SCOPE_HPP
#define REMLANG_SCOPE_HPP

#include "Node.hpp"
#include <vector>

#include "ReturnNode.hpp"

class Scope : public Node {
private:
    std::vector<Node*> nodes;
public:
    Scope(std::vector<Node*> nodes) :nodes(nodes) {};
    std::any evaluate(Context& context) override {
        context.pushNewFrame();
        for (auto node : nodes){
            if (dynamic_cast<ReturnNode*>(node)){
                return node->evaluate(context);
            }
            else { node->evaluate(context); }
        }
        context.popFrame();
        return {};
    }
    Node* getReturn(){
        for (auto node : nodes){
            if (ReturnNode* ret = dynamic_cast<ReturnNode*>(node)){
                return ret;
            }
        }
        return nullptr;
    }
};

#endif