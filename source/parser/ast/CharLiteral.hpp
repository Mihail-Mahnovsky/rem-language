#ifndef REMLANG_CHARLITERAL_HPP
#define REMLANG_CHARLITERAL_HPP

class CharLiteral : public Node {
private:
    char value;
public:
    CharLiteral(char value) : value(value) {};
    std::any evaluate(Context& context) override {
        return value;
    }
};


#endif