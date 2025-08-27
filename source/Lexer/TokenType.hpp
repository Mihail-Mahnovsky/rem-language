#ifndef REMLANG_TOKENTYPE_HPP
#define REMLANG_TOKENTYPE_HPP

enum class TokenType {
    OPERATOR,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    COMMA,
    COLON,
    SEMICOLON,
    ASSIGN,

    ID,

    OR,
    AND,

    IF,
    ELIF,
    ELSE,

    NUMBER,
    STRING,
    CHARACTER,

    TYPE,

    TRUE,
    FALSE,

    //for test
    PRINT
};

#endif