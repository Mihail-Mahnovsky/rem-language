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

    NUMBER,
    STRING,
    CHARACTER,

    TYPE,

    INT_TYPE,
    STRING_TYPE,
    CHAR_TYPE,
    BOOLEAN_TYPE,

    TRUE,
    FALSE,

    //for test
    PRINT
};

#endif