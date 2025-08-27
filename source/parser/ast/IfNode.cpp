#include "IfNode.hpp"

IfNode::IfNode(std::vector<Block> blocks)
: blocks(blocks)
{}

std::any IfNode::evaluate(Context& context) {
    for (auto& block : blocks) {
        if (block.getCondition().has_value()) {
            Node* condNode = block.getCondition().value();
            if (condNode == nullptr) goto naxyi;;
            std::any result = condNode->evaluate(context);
            if (static_cast<bool>(std::any_cast<bool>(result))) {
                return block.getScope()->evaluate(context);
            }
        }else{
            naxyi:
            return block.getScope()->evaluate(context);
        }
    }

    return {};
}
