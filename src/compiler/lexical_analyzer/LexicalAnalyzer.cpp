#include "LexicalAnalyzer.h"
#include <string>
#include <unordered_map>

char LexicalAnalyzer::peek(int offset) {
    int pos = position + offset;
    return pos < (int)text.length() ? text[pos] : '\0';
}

char LexicalAnalyzer::advance(int count) {
    char result = '\0';
    for (int i = 0; i < count; i++) {
        if(currentChar == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        position++;
        result = currentChar = position < (int)text.length() ? text[position] : '\0';
    }
    return result;
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

bool LexicalAnalyzer::isValidCurrentChar() {
    return currentChar != '\0';
}

void LexicalAnalyzer::skipComment() {
    while(isValidCurrentChar() && advance() != '\n') {}
}

void LexicalAnalyzer::skipMultilineComment() {
    while(isValidCurrentChar() && !(advance() == '*' && peek() == '/')) {}
    advance(2);
}

Token LexicalAnalyzer::tokenizeNumber() {
    std::string number;
    int startLine = line;
    int startColumn = column;
    bool hasDot = false;

    char current = peek(0);
    do {
        if(isDigit(current)) {
            number += current;
        }
        if(current == '.') {
            number += ".";
            hasDot = true;
        }
        current = advance();
    } while (isDigit(current) || current == ' ' || !hasDot && current == '.' || (current == '_' && isDigit(peek(1))));
    return Token(startLine, startColumn, TokenType::NUMBER_LITERAL, number);
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

Token LexicalAnalyzer::newToken(TokenType type, std::string text) {
    return Token(line, column, type, text);
}

Token LexicalAnalyzer::next() {
    skipWhitespace();
    char letter = peek(0);

    if(letter == '/') {
        char letterNext = peek();
        if(letterNext == '/') {
            skipComment();
            return next();
        }
        if(letterNext == '*') {
            skipMultilineComment();
            return next();
        }
    }

    if(isDigit(letter)) {
        return tokenizeNumber();
    }

    return newToken(TokenType::UNSUPPORTED);
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
        if(token.type == TokenType::UNSUPPORTED || !isValidCurrentChar()) {
            break;
        }
    } while (true);

    return tokens;
}

std::vector<Token> LexicalAnalyzer::getTokensCopy() {
    return std::vector(tokens);
}

static const std::unordered_map<std::string, TokenType> keywords = {
    { "function", TokenType::FUNCTION },
    { "procedure", TokenType::PROCEDURE },

    { "return", TokenType::RETURN },
    { "throws", TokenType::THROWS },
    { "defer", TokenType::DEFER },

    { "thread", TokenType::THREAD },

    { "train", TokenType::TRAIN },
    { "yield", TokenType::YIELD },

    { "new", TokenType::NEW },
    { "delete", TokenType::DELETE },

    { "struct", TokenType::STRUCTURE },
    { "class", TokenType::CLASS },
    { "interface", TokenType::INTERFACE },
    { "enumeration", TokenType::ENUMERATION },
    { "unit", TokenType::UNIT },

    { "public", TokenType::PUBLIC },
    { "private", TokenType::PRIVATE },
    { "protected", TokenType::PROTECTED },
    { "abstract", TokenType::ABSTRACT },
    { "static", TokenType::STATIC },

    { "native", TokenType::NATIVE },

    { "operator", TokenType::OPERATOR },
    { "keyword", TokenType::KEYWORD },

    { "satisfies", TokenType::SATISFIES },
    { "extends", TokenType::EXTENDS },
    { "implements", TokenType::IMPLEMENTS },
    { "typeof", TokenType::TYPEOF },

    { "of", TokenType::OF },
    { "in", TokenType::IN },
    { "as", TokenType::AS },

    { "namespace", TokenType::NAMESPACE },

    { "if", TokenType::IF },
    { "else", TokenType::ELSE },
    { "match", TokenType::MATCH },
    { "case", TokenType::CASE },

    { "try", TokenType::TRY },
    { "catch", TokenType::CATCH },
    { "finally", TokenType::FINALLY },

    { "throw", TokenType::THROW },

    { "iterator", TokenType::ITERATOR },
    { "for", TokenType::FOR },
    { "while", TokenType::WHILE },
    { "break", TokenType::BREAK },
    { "continue", TokenType::CONTINUE },

    { "let", TokenType::LET },
    { "const", TokenType::CONST },

    { "string", TokenType::STRING },
    { "char", TokenType::CHAR },
    { "int", TokenType::INTEGER },
    { "long", TokenType::LONG },
    { "float", TokenType::FLOAT },
    { "double", TokenType::DOUBLE },
    { "boolean", TokenType::BOOLEAN },
    { "void", TokenType::VOID },
    { "unknown", TokenType::UNKNOWN },
    { "number", TokenType::NUMBER },

    { "import", TokenType::IMPORT },
    { "export", TokenType::EXPORT }
};