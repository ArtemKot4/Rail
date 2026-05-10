#include "LexicalAnalyzer.h"
#include <string>

char LexicalAnalyzer::peek(int offset) {
    int pos = position + offset;
    return pos < (int)text.length() ? text[pos] : '\0';
}

void LexicalAnalyzer::advance(int count) {
    for (int i = 0; i < count; i++) {
        if (currentChar == '\n') {
            line++;
            column = 1;
        }
        else {
            column++;
        }
        position++;
        currentChar = position < (int)text.length() ? text[position] : '\0';
    }
}

void LexicalAnalyzer::skipWhitespace() {
    while (isWhitespace(currentChar)) {
        advance();
    }
}

bool LexicalAnalyzer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool LexicalAnalyzer::isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

Token LexicalAnalyzer::tokenizeNumber() {
    return Token(line, column, TokenType::NUMBER_LITERAL, "");
}

Token LexicalAnalyzer::tokenizeString() {
    return Token(line, column, TokenType::STRING_LITERAL, "");
}

Token LexicalAnalyzer::tokenizeIdentifier() {
    return Token(line, column, TokenType::IDENTIFIER, "");
}

Token LexicalAnalyzer::tokenizeKeyword(const std::string& word) {
    return Token(line, column, TokenType::KEYWORD, word);
}

Token LexicalAnalyzer::next() {
    return Token(line, column, TokenType::UNKNOWN, "");
}

LexicalAnalyzer::LexicalAnalyzer(const std::string& source) : text(source) {}

std::vector<Token> LexicalAnalyzer::tokenize() {
    if (text.length() == 0) {
        return tokens;
    }
    currentChar = text[0];

    do {
        Token token = next();
        tokens.push_back(token);
        if (token.type == TokenType::UNKNOWN || currentChar == '\0') {
            break;
        }
    } while (true);

    return tokens;
}