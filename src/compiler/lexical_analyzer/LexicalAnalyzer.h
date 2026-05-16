#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <vector>
#include <string>
#include "Token.h"

class LexicalAnalyzer {
private:
    std::string text;
    int position = 0;
    int line = 1;
    int column = 1;
    char currentChar = '\0';
    std::vector<Token> tokens;

    char peek(int offset = 1);
    char advance(int count = 1);
    void throwError(std::string message, std::string reason, int& line, int& column);
    void throwError(std::string message, std::string reason);
    void skipWhitespace();
    void skipComment();
    void skipMultilineComment();
    bool isDigit(char c);
    bool isWhitespace(char c);
    bool isValidCurrentChar();
    Token tokenizeNumber();
    Token tokenizeString();
    Token tokenizeIdentifier();
    Token tokenizeKeyword(const std::string& word);
    Token next();
    Token newToken(TokenType type, std::string text = "");

public:
    LexicalAnalyzer(const std::string& source);
    std::vector<Token> tokenize();
    std::vector<Token> getTokensCopy();
};

#endif