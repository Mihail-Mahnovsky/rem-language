#include "Parser.hpp"

#include <bits/fs_fwd.h>
#include <iostream>


#include "ast/ArrayLiteral.hpp"
#include "ast/Assign.hpp"
#include "ast/Echo.hpp"
#include "ast/BinaryNode.hpp"
#include "ast/NumberLiteral.hpp"
#include "ast/BoolLiteral.hpp"
#include "ast/Break.hpp"
#include "ast/StringLiteral.hpp"
#include "ast/Variable.hpp"
#include "ast/FunctionHeaderNode.hpp"
#include "ast/CharLiteral.hpp"
#include "ast/IfNode.hpp"
#include "ast/ReturnNode.hpp"
#include "ast/Scope.hpp"
#include "ast/UnaryNode.hpp"
#include "ast/while.hpp"
#include "ast/FunctionCall.hpp"
#include "ast/GetArrayElementNode.hpp"
#include "ast/SetArrayElementNode.hpp"
#include "../ErrorLogger.hpp"
#include "../utils.hpp"

Parser::Parser(Context& ctx)
    : pos(0)
    , tokens()
    , offsets()
    , types()
    , currentOffset(0)
    , context(ctx)
{}

std::vector<Node*> Parser::parse(std::vector<Token>& tokens) {
    pos = 0;
    this->tokens = tokens;
    return statement_list();
}


Type stringToType(std::string type){
    if (type.find('[') != std::string::npos) {
        return Type::ARRAY;
    }

    static std::pair<std::string_view, Type> typesView[] = {
        { "int", Type::INT },
        { "str", Type::STRING },
        { "char", Type::CHAR },
        { "boolean", Type::BOOLEAN },
        { "void", Type::VOID },
    };

    for (const auto& view : typesView) {
        if (view.first == type) {
            return view.second;
        }
    }

    ErrorLogger::throwError("Unsupported type: " + type);
}

std::vector<Node*> Parser::statement_list() {
    std::vector<Node*> nodes;

    while (pos < tokens.size()) {
        if(current().getType() == TokenType::RBRACE){
            break;
        }
        nodes.push_back(statement());
    }

    return nodes;
}

Node* Parser::statement() {
    Token tok = current();

    switch (tok.getType()) {
        case TokenType::TYPE: {
            std::string type = current().getValue();
            eat(TokenType::TYPE);

            if (current().getType() == TokenType::LMS) {


                if (tokens[pos + 4].getType() == TokenType::LPAREN) {
                    eat(TokenType::LMS);
                    eat(TokenType::NUMBER);
                    eat(TokenType::RMS);

                    std::string name = current().getValue();
                    eat(TokenType::ID);
                    eat(TokenType::LPAREN);

                    return parseFunction(type, name);
                }

                return parseArray();
            }

            std::string name = current().getValue();
            eat(TokenType::ID);

            if (current().getType() == TokenType::ASSIGN) {
                return declaration(type, name);
            } else if (current().getType() == TokenType::LPAREN) {
                eat(TokenType::LPAREN);
                return parseFunction(type, name);
            }
            break;
        }

        case TokenType::RETURN:
            eat(TokenType::RETURN);
            return new ReturnNode(expression());
        case TokenType::ID:{
                if (peek(TokenType::ASSIGN)){
                    return reassigment();
                }
                else if (peek(TokenType::LPAREN)){
                    std::string name = current().getValue();
                    eat(TokenType::ID);
                    return parseFunctionCall(name);
                } else if (peek(TokenType::LMS)) {
                    std::string name = current().getValue();
                    eat(TokenType::ID);
                    eat(TokenType::LMS);
                    Node* index = expression();
                    eat(TokenType::RMS);
                    eat(TokenType::ASSIGN);
                    Node* value = expression();
                    return new SetArrayElementNode(index, value, offsets[name]);
                }
            }
        case TokenType::BREAK:
            eat(TokenType::BREAK);
            return new BreakNode();
        case TokenType::WHILE:
            return parseWhile();
        case TokenType::IF:
            return parseIf();
         default:
            return expression();
    }

    ErrorLogger::throwError("Unexpected token");
}

Node* Parser::parseFunctionCall(std::string& name)
{
    eat(TokenType::LPAREN);
    std::vector<Node*> args;
    int i = 0;
    while (current().getType() != TokenType::RPAREN) {
        args.push_back(expression());
        if (current().getType() == TokenType::RPAREN){
            eat(TokenType::RPAREN);
            ++i;
            break;
        }
        else {eat(TokenType::COMMA);}
    } if (i == 0 && current().getType() == TokenType::RPAREN){eat(TokenType::RPAREN);}

    return new FunctionCall(context, name,args);
}


Node* Parser::expression() {
    return orExpression();
}

Node* Parser::orExpression(){
    Node* node = andExpression();
    while (current().getValue() == "or"){
        eat(TokenType::OR);
        Node* right = andExpression();
        node = new BinaryNode(node, right,Operations::OR);
    }
    return node;
}

Node* Parser::andExpression(){
    Node* node = equality();
    while (current().getValue() == "and"){
        eat(TokenType::AND);
        Node* right = equality();
        node = new BinaryNode(node, right,Operations::AND);
    }
    return node;
}

Node* Parser::equality(){
    Node* node = relational();
    while (current().getValue() == "==" || current().getValue() == "!="){
        Token op = current();
        eat(op.getType());
        Node* right = relational();

        Operations oper = (op.getValue() == "==") ? Operations::EQUAL : Operations::NOTEQUAL;
        node = new BinaryNode(node,right,oper);
    }
    return node;
}

Node* Parser::relational(){
    Node* node = addSub();
    while (current().getValue() == "<" || current().getValue() == ">" || current().getValue() == "<=" || current().getValue() == ">=") {
        Token op = current();
        eat(op.getType());
        Node* right = addSub();

        if (op.getValue() == "<"){node = new BinaryNode(node,right,Operations::MIN);}
        else if (op.getValue() == ">"){node = new BinaryNode(node,right,Operations::MAX);}
        else if (op.getValue() == "<="){ node = new BinaryNode(node,right,Operations::MINEQUAL); }
        else if (op.getValue() == ">="){node = new BinaryNode(node,right,Operations::MAXEQUAL);}
    }
    return node;
}

Node *Parser::addSub() {
    Node* node = mulMiv();
    while (current().getValue() == "+" || current().getValue() == "-") {
        Token op = current();
        eat(op.getType());
        Node* right = mulMiv();

        Operations oper = (op.getValue() == "+") ? Operations::PLUS : Operations::MINUS;
        node = new BinaryNode(node,right,oper);
    }
    return node;
}

Node *Parser::mulMiv() {
    Node* node = unary();
    while (current().getValue() == "*" || current().getValue() == "/") {
        Token op = current();
        eat(op.getType());
        Node* right = unary();

        Operations oper = (op.getValue() == "*") ? Operations::MULTIPLY : Operations::DIVISION;
        node = new BinaryNode(node,right,oper);
    }
    return node;
}

Node* Parser::unary(){
    if (current().getValue() == "-" || current().getValue() == "!") {
        Token op = current();
        eat(op.getType());
        Node* right = unary();

        auto oper = (op.getValue() == "-") ? UnaryOperation::NEGATE : UnaryOperation::NOT;
        return new UnaryNode(oper, right);
    }

    return factor();
}


Node *Parser::factor() {
    Token tok = current();

    switch (tok.getType()) {
        case TokenType::NUMBER:
            eat(TokenType::NUMBER);
            return new NumberLiteral(std::stod(tok.getValue()));
        case TokenType::STRING:
            eat(TokenType::STRING);
            return new StringLiteral(tok.getValue());
        case TokenType::TRUE:
            eat(TokenType::TRUE);
            return new BooleanLiteral(true);
        case TokenType::FALSE:
            eat(TokenType::FALSE);
            return new BooleanLiteral(false);
        case TokenType::CHARACTER:
            eat(TokenType::CHARACTER);
            return new CharLiteral(static_cast<char>(std::stoi(tok.getValue())));
        case TokenType::ID:{
                std::string name = tok.getValue();
                eat(TokenType::ID);
                if (current().getType() == TokenType::LPAREN){
                    return parseFunctionCall(name);
                }else if (current().getType() == TokenType::LMS) {
                    eat(TokenType::LMS);
                    Node* indexOfArray = expression();
                    eat(TokenType::RMS);
                    return new GetArrayElementNode(indexOfArray,offsets[name]);
                }
              //  if (offsets.find(name) == offsets.end()) {
               //     throw std::runtime_error("not find this variable : " + name);
               // }
                return new Variable(offsets[name],types[name]);
        }
        case TokenType::LPAREN: {
            eat(TokenType::LPAREN);
            Node* expr = expression();
            eat(TokenType::RPAREN);
            return expr;
        }
        default:
            throw std::runtime_error("Unexpected token");
    }
}

Node *Parser::declaration(const std::string& type, const std::string& name) {
    //if (type == "int") { types[name] = Type::INT; }
    //else if (type == "str") { types[name] = Type::STRING; }
    //else if (type == "char") { types[name] = Type::CHAR; }
    //else if (type == "boolean") { types[name] = Type::BOOLEAN; }

    types[name] = stringToType(type);

    offsets[name] = currentOffset;
    int assignedOffset = currentOffset;
    ++currentOffset;

    eat(TokenType::ASSIGN);
    Node* right = expression();

    if (!checkExpressionType(right, types[name])) {
        ErrorLogger::throwError("error: type mismatch in declaration of " + name + "\n");
       exit(1);
    }

    return new Assign(assignedOffset,right);
}

Node *Parser::reassigment() {
    std::string name = current().getValue();
    eat(TokenType::ID);

    eat(TokenType::ASSIGN);

    Node* right = expression();
    if (!checkExpressionType(right, types[name])) {
        ErrorLogger::throwError("error: type mismatch in declaration of " + name + "\n");
    }
    int offset = offsets[name];
    return new Assign(offset, right);
}

std::vector<Node*> Parser::parseScope(){
    eat(TokenType::LBRACE);
    std::vector<Node*> nodes = statement_list();
    eat(TokenType::RBRACE);
    return nodes;
}


Node* Parser::parseIf(){
    std::vector<Block> blocks;
    eat(TokenType::IF);
    eat(TokenType::LPAREN);
    Node* condition = expression();
    eat(TokenType::RPAREN);
    Scope* scope = new Scope(parseScope());
    blocks.push_back(Block(condition,scope));

    while (current().getType() == TokenType::ELIF || current().getType() == TokenType::ELSE){
        switch (current().getType()){
            case TokenType::ELIF:{
                eat(TokenType::ELIF);
                eat(TokenType::LPAREN);
                Node* condition = expression();
                eat(TokenType::RPAREN);
                Scope* scope = new Scope(parseScope());
                blocks.push_back(Block(condition,scope));
                break;
            }
            case TokenType::ELSE:{
                eat(TokenType::ELSE);
                scope = new Scope(parseScope());
                blocks.push_back(Block(nullptr,scope));
                break;
            }
        }
    }

    return new IfNode(blocks);
}

Node* Parser::parseWhile(){
    eat(TokenType::WHILE);
    eat(TokenType::LPAREN);
    Node* condition = expression();
    eat(TokenType::RPAREN);
    Scope* scope = new Scope(parseScope());
    return new While(condition,scope);
}


Node* Parser::parseFunction(std::string& type,std::string name){
    types[name] = stringToType(type);

    std::vector<Arg> args;

    while (current().getType() != TokenType::RPAREN){
        Type type = stringToType(current().getValue());
        eat(TokenType::TYPE);
        if (current().getType() == TokenType::LMS) {
            eat(TokenType::LMS);
            Node* size = expression();
            eat(TokenType::RMS);
        }
        std::string argName = current().getValue();

        eat(TokenType::ID);

        offsets[argName] = currentOffset;
        int argOffSet = currentOffset;
        ++currentOffset;
        args.push_back(Arg(type,argName,argOffSet));
        if (current().getType() == TokenType::RPAREN){
            eat(TokenType::RPAREN);
            break;
        }
        else {eat(TokenType::COMMA);}
    }
    if (current().getType() == TokenType::RPAREN){ eat(TokenType::RPAREN); }

    Scope* scope = new Scope(parseScope());

    if (types[name] != Type::VOID && scope->getReturn() != nullptr){
        if (!checkExpressionType(dynamic_cast<ReturnNode*>(scope->getReturn())->getReturnValue(), types[name])){
            //ErrorLogger::throwError("return type mismatch in function");
        }
    }

    return new FunctionHeaderNode(name,scope,args);
}

Node *Parser::parseArray() {
    eat(TokenType::LMS);
    size_t size = std::stoi(current().getValue());
    if (size == 0) {
        ErrorLogger::throwError("Array size can't be 0");
    }
    eat(TokenType::NUMBER);
    eat(TokenType::RMS);

    std::string name = current().getValue();
    eat(TokenType::ID);

    types[name] = Type::ARRAY;
    offsets[name] = currentOffset;
    int assignedOffset = currentOffset;
    ++currentOffset;

    if (current().getType() != TokenType::ASSIGN) {
        ErrorLogger::throwError("Array must be init");
    }

    eat(TokenType::ASSIGN);

    Node* right = nullptr;

    if (current().getType() == TokenType::LBRACE) {

        eat(TokenType::LBRACE);

        std::vector<Node*> elements;

        for (size_t i = 0; i < size; ++i) {

            if (current().getType() != TokenType::RBRACE) {
                elements.push_back(expression());

                if (current().getType() == TokenType::COMMA) {
                    eat(TokenType::COMMA);
                }
            } else {
                elements.push_back(new NumberLiteral(0));
            }
        }

        if (current().getType() != TokenType::RBRACE) {
            ErrorLogger::throwError("Too many elements in array initialization");
        }

        eat(TokenType::RBRACE);

        right = new ArrayLiteral(elements);
    }
    else {

        right = expression();
    }

    return new Assign(assignedOffset, right);
}

bool Parser::peek(TokenType wantType) const {
    if (pos < tokens.size() && tokens[pos + 1].getType() == wantType) {
        return true;
    }
    return false;
}

void Parser::eat(TokenType type) {
    if (pos < tokens.size() && current().getType() == type) {
        ++pos;
    }
    else {
        ErrorLogger::throwError("Syntax Error: Expected token " + typeToString(current().getType()) + " , but found " + typeToString(type) + " at line . ");
    }
}