#ifndef REMLANG_BOOLLITERAL_HPP
#define REMLANG_BOOLLITERAL_HPP

class BooleanLiteral : public Node {
private:
    bool value;
public:
    BooleanLiteral(bool value) : value(value) {};
    std::any evaluate(Context& context) override {
        return value;
    }
};

#endif