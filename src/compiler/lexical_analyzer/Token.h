#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TokenType.h"

class Token {
public:
    std::string text;
    TokenType type;
    int line;
    int column;

    Token(int line, int column, TokenType type, const std::string& text = "")
        : line(line), column(column), type(type), text(text) {
    }

    Token(int line, int column, TokenType type)
        : line(line), column(column), type(type), text("") {
    }
};

#endif