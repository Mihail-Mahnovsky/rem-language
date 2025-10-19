#include "Lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "interpreter/Interpritator.hpp"
#include <iostream>
#include "parser/ast/BinaryNode.hpp"
#include <fstream>

int main(void) {

    Interpreter interpreter = Interpreter();
    Lexer lexer = Lexer();
    Parser parser = Parser(interpreter.getContext());

    std::ifstream inputFile("../examples/factorial.rem");
    if (inputFile.is_open()) {
        std::string res;
        while (!inputFile.eof()) {
            std::string line;
            std::getline(inputFile, line);
            res += line + "\n";
        }
        std::vector<Token> tokens = lexer.tokeNize(res);
        std::vector<Node*> nodes = parser.parse(tokens);
        interpreter.execute(nodes);
    }else {
        std::cerr << "Could not open file" << std::endl;
    }
    return 0;
}