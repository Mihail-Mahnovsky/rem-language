#ifndef REMLANG_TOKENTYPE_HPP
#define REMLANG_TOKENTYPE_HPP

enum class TokenType {
    OPERATOR,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LMS,
    RMS,

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
    WHILE,
    RETURN,
    BREAK,
    NEW,

    NUMBER,
    STRING,
    CHARACTER,

    TYPE,

    TRUE,
    FALSE,

};

#endif