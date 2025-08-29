#ifndef REMLANG_UTILS_HPP
#define REMLANG_UTILS_HPP
#include "parser/ast/BinaryNode.hpp"
#include "parser/ast/NumberLiteral.hpp"
#include "parser/ast/StringLiteral.hpp"
#include "parser/ast/BoolLiteral.hpp"
#include "parser/ast/CharLiteral.hpp"
#include "parser/ast/FunctionCall.hpp"
#include "parser/ast/Variable.hpp"

class FunctionCall;

bool checkExpressionType(Node* expression, Type type);
Type chechExprType(Node* expression);

#endif