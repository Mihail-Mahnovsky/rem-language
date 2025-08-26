#include "Lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "Interpritator/Interpritator.hpp"
#include <iostream>
#include "parser/ast/BinaryNode.hpp"
#include <fstream>

int main(void) {
    Lexer lexer = Lexer();
    Parser parser = Parser();
    Interpritator interpreter = Interpritator();
    std::ifstream inputFile("../examples/hello_world.rem");
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

    //for (Node* node : nodes) {
      //  auto binOp = dynamic_cast<BinaryNode*>(node);
        //if (!binOp) {
          //  std::cerr << "Error in operation" << std::endl;
        //}
     //   std::cout << std::any_cast<double>(binOp->evaluate());
    //}
    return 0;
}