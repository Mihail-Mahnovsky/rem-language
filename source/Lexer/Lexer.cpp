#include "Lexer.hpp"

#include <stdexcept>

std::vector<Token> Lexer::tokeNize(std::string line) {
    std::vector<Token> tokens;

    for (auto it = line.begin(); it != line.end(); ++it) {
        switch (*it) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                break;
            case '+':
                tokens.push_back(Token(TokenType::OPERATOR, "+"));
                break;
            case '-':
                tokens.push_back(Token(TokenType::OPERATOR, "-"));
                break;
            case '*':
                tokens.push_back(Token(TokenType::OPERATOR,"*"));
                break;
            case '/':
                tokens.push_back(Token(TokenType::OPERATOR,"/"));
                break;
            case ';':
                tokens.push_back(Token(TokenType::SEMICOLON,";"));
                break;
            case ':':
                tokens.push_back(Token(TokenType::COLON,":"));
                break;
            case ',':
                tokens.push_back(Token(TokenType::COMMA,","));
                break;
            case '=':
                if (peek(line,'=',std::distance(line.begin(), it) + 1)){tokens.push_back(Token(TokenType::OPERATOR, "==")); ++it;}
                else {tokens.push_back(Token(TokenType::ASSIGN, "="));}
                break;
            case '!':
                if (peek(line,'=',std::distance(line.begin(), it) + 1)){tokens.push_back(Token(TokenType::OPERATOR, "!=")); ++it;}
                else {tokens.push_back(Token(TokenType::OPERATOR, "!"));}
                break;
            case '<':
                if (peek(line,'=',std::distance(line.begin(), it) + 1)){tokens.push_back(Token(TokenType::OPERATOR, "<=")); ++it;}
                else {tokens.push_back(Token(TokenType::OPERATOR, "<"));}
                break;
            case '>':
                if (peek(line,'=',std::distance(line.begin(), it) + 1)){tokens.push_back(Token(TokenType::OPERATOR, ">=")); ++it;}
                else {tokens.push_back(Token(TokenType::OPERATOR, ">"));}
                break;
            case '(':
                tokens.push_back(Token(TokenType::LPAREN, "("));
                break;
            case ')':
                tokens.push_back(Token(TokenType::RPAREN, ")"));
                break;
            case '{':
                tokens.push_back(Token(TokenType::LBRACE, "{"));
                break;
            case '}':
                tokens.push_back(Token(TokenType::RBRACE, "}"));
                break;
            default:
                if (std::isdigit(*it)) {
                    std::string res = std::string(1,*it);
                    ++it;
                    while (isdigit(*it) && it != line.end()) {
                        res += *it;
                        ++it;
                    }
                    --it;
                    tokens.push_back(Token(TokenType::NUMBER, res));
                }
                else if (std::isalpha(*it)) {
                    std::string res = std::string(1,*it);
                    ++it;
                    while (isalpha(*it) && it != line.end()) {
                        res += *it;
                        ++it;
                    }
                    --it;
                    if (res == "true") {tokens.push_back(Token(TokenType::TRUE, res)); }
                    else if (res == "false") {tokens.push_back(Token(TokenType::FALSE, res)); }
                    else if (res == "void") {tokens.push_back(Token(TokenType::TYPE, res));}
                    else if (res == "int") {tokens.push_back(Token(TokenType::TYPE,res));}
                    else if (res == "boolean") {tokens.push_back(Token(TokenType::TYPE, res));}
                    else if (res == "str") {tokens.push_back(Token(TokenType::TYPE, res));}
                    else if (res == "char") {tokens.push_back(Token(TokenType::TYPE, res));}
                    else if (res == "or") { tokens.push_back(Token(TokenType::OR, res));}
                    else if (res == "and") { tokens.push_back(Token(TokenType::AND, res));}
                    else if (res == "if") { tokens.push_back(Token(TokenType::IF, res));}
                    else if (res == "else") { tokens.push_back(Token(TokenType::ELSE, res));}
                    else if (res == "elif") {tokens.push_back(Token(TokenType::ELIF, res));}
                    else if (res == "while") {tokens.push_back(Token(TokenType::WHILE, res));}
                    else if (res == "return") { tokens.push_back(Token(TokenType::RETURN, res)); }
                    else if (res == "break") { tokens.push_back(Token(TokenType::BREAK, res)); }
                    else { tokens.push_back(Token(TokenType::ID, res)); }
                }
                else if (*it == '\"') {
                    ++it;
                    std::string res = "";
                    while ((*it) != '\"' && it != line.end()) {
                        res += *it;
                        ++it;
                    }
                    if (it == line.end())
                        throw std::runtime_error("Unterminated string literal");
                    //++it;
                    tokens.push_back(Token(TokenType::STRING, res));
                }
                else if (*it == '\'') {
                    ++it;
                    std::string res = std::to_string(*it);
                    if (it == line.end())
                        throw std::runtime_error("Unterminated char literal");
                    ++it;
                    tokens.push_back(Token(TokenType::CHARACTER, res));
                }
                else {
                    throw std::runtime_error("Unexpected character: " + std::string(1, *it));
                }
        }
    }

    return tokens;
}
