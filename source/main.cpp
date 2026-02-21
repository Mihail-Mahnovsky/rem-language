#include "Lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "interpreter/Interpritator.hpp"
#include "parser/ast/BinaryNode.hpp"

#include <fstream>
#include <iostream>

#include "fmt/compile.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {

#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    Interpreter interpreter = Interpreter();
    Lexer lexer = Lexer();
    Parser parser = Parser(interpreter.getContext());

    if (argc > 1 && std::string(argv[1]) == "version") {
        fmt::print("remlang version : 0.1.0 \n");
    }

    std::ifstream inputFile("../examples/arraytest.rem");
    if (inputFile.is_open()) {
        std::string res;
        while (!inputFile.eof()) {
            std::string line;
            std::getline(inputFile, line);
            if (line.front() == '#') {
                 continue;
            }
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