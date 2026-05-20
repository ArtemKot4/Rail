#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <vector>
#include <string>
#include <optional>

#include "Token.h"

class LexicalAnalyzer {
private:
    std::string code;
    int position = 0;
    int line = 0;
    int column = 1;
    char currentChar = '\0';
    std::vector<Token> tokens;

    std::string buildIdentifier();
    char peek(int offset = 1);
    char advance(int count = 1);
    void throwError(std::string message, std::string reason, int& line, int& column);
    void throwError(std::string message, std::string reason);
    void skipWhitespace();
    void skipComment();
    void skipMultilineComment();
    [[noreturn]] void callError(const std::string& message, int line, int column, const std::string& keyword, const std::string& reason);
    bool isDigit(char c);
    bool isWhitespace(char c);
    bool isValidCurrentChar();
    bool isEnd();
    Token tokenizeNumber();
    Token tokenizeString();
    Token tokenizeIdentifier();
    std::optional<Token> getOperatorToken();
    std::optional<Token> getKeywordToken(const std::string& word, int line, int column);
    std::optional<Token> next();
    Token newToken(TokenType type, std::string text = "");

public:
    std::string fileName;

    LexicalAnalyzer(const std::string& code, const std::string& fileName);
    std::vector<Token> tokenize();
    std::vector<Token> getTokensCopy();
};

#endif