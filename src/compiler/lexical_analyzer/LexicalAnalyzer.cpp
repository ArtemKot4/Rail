#include "LexicalAnalyzer.h"
#include "compiler/RailError.h"
#include <string>
#include <unordered_map>
#include <optional>

LexicalAnalyzer::LexicalAnalyzer(const std::string& code, const std::string& fileName) : code(code), fileName(fileName) {};

char LexicalAnalyzer::peek(int offset) {
    int pos = position + offset;
    return pos < (int)code.length() ? code[pos] : '\0';
}

char LexicalAnalyzer::advance(int count) {
    char result = '\0';
    for(int i = 0; i < count; i++) {
        if(currentChar == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        position++;
        result = currentChar = position < (int)code.length() ? code[position] : '\0';
    }
    return result;
}

void LexicalAnalyzer::skipWhitespace() {
    while (isWhitespace(currentChar)) {
        advance();
    }
}

void LexicalAnalyzer::callError(const std::string& message, int line, int column, const std::string& reason, const std::string& keyword = " ") {
    RailError(code, "LexicalError", message, line, column, reason, keyword, fileName);
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
            if(!hasDot) {
                number += ".";
                hasDot = true;
            } else {
                callError("Invalid not an integer number", startLine, column, "number cannot have greater than one dot");
            }
        }
        current = advance();
    } while (isDigit(current) || current == ' ' || current == '.' || (current == '_' && isDigit(peek(1))));
    return Token(startLine, startColumn, TokenType::NUMBER_LITERAL, number);
}

Token LexicalAnalyzer::tokenizeString() {
    int startLine = line;
    int startColumn = column;
    std::string string;
    advance();

    while(isValidCurrentChar() && currentChar != '"') {
        if(currentChar == '\\') {
            char nextChar = peek(1);
            char add = nextChar;
            if(nextChar == '\\') {
                add = '\\';
            }
            else if(nextChar == 'n') {
                add = '\n';
            }
            else if(nextChar == 't') {
                add = '\t';
            }
            else if(nextChar == 'r') {
                add = '\r';
            }
            string.push_back(add);
            advance(2);
            continue;
        }
        string.push_back(currentChar);
        advance();
    }
    advance();
    return Token(startLine, startColumn, TokenType::STRING_LITERAL, string);
}

Token LexicalAnalyzer::tokenizeIdentifier() {
    return Token(line, column, TokenType::IDENTIFIER, "");
}

Token LexicalAnalyzer::newToken(TokenType type, std::string text) {
    return Token(line, column, type, text);
}

std::string LexicalAnalyzer::buildIdentifier() {
    std::string identifier;
    char letter = currentChar;

    while(std::isalpha(static_cast<unsigned char>(letter)) || isDigit(letter) || letter == '_') {
        identifier += letter;
        letter = advance();
    }
    return identifier;
}

std::optional<Token> LexicalAnalyzer::getOperatorToken() {
    char letter = currentChar;
    char nextLetter = peek();

    switch(letter) {
        case ';': {
            advance();
            return newToken(TokenType::SEMICOLON);
        }
        case ':': {
            advance();
            return newToken(TokenType::COLON);
        }
        case ',': {
            advance();
            return newToken(TokenType::COMMA);
        }
        case '.': {
            advance();
            return newToken(TokenType::POINT);
        }

        case '=': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::EQUAL_EQUAL);
            }
            if(nextLetter == '>') {
                advance();
                return newToken(TokenType::FAT_ARROW);
            }
            return newToken(TokenType::ASSIGN);
        }
        case '+': {
            advance();
            if(nextLetter == '+') {
                advance();
                return newToken(TokenType::PLUS_PLUS);
            }
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::PLUS_ASSIGN);
            }
            return newToken(TokenType::PLUS);
        }
        case '-': {
            advance();
            if(nextLetter == '-') {
                advance();
                return newToken(TokenType::MINUS_MINUS);
            }
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::MINUS_ASSIGN);
            }
            if(nextLetter == '>') {
                advance();
                return newToken(TokenType::ARROW);
            }
            return newToken(TokenType::MINUS);
        }
        case '/': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::SLASH_ASSIGN);
            }
            return newToken(TokenType::SLASH);
        }
        case '*': {
            advance();
            if(nextLetter == '*') {
                advance();
                return newToken(TokenType::STAR_STAR);
            }
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::STAR_ASSIGN);
            }
            return newToken(TokenType::STAR);
        }
        case '%': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::PERCENT_ASSIGN);
            }
            return newToken(TokenType::PERCENT);
        }
        case '&': {
            advance();
            if(nextLetter == '&') {
                advance();
                return newToken(TokenType::AND);
            }
            return newToken(TokenType::AMPERSAND);
        }
        case '|': {
            advance();
            if(nextLetter == '|') {
                advance();
                return newToken(TokenType::OR);
            }
            return newToken(TokenType::PIPE);
        }
        case '!': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::NOT_EQUAL);
            }
            return newToken(TokenType::EXCLAMATION_MARK);
        }
        case '?': {
            advance();
            if(nextLetter == '?' && peek(2) == '=') {
                advance(2);
                return newToken(TokenType::ASSIGN_NULLABLE);
            }
            return newToken(TokenType::QUESTION_MARK);
        }

        case '(': {
            advance();
            return newToken(TokenType::LEFT_PARENTHESIS);
        }
        case ')': {
            advance();
            return newToken(TokenType::RIGHT_PARENTHESIS);
        }
        case '[': {
            advance();
            return newToken(TokenType::LEFT_BRACKET);
        }
        case ']': {
            advance();
            return newToken(TokenType::RIGHT_BRACKET);
        }
        case '{': {
            advance();
            return newToken(TokenType::LEFT_BRACE);
        }
        case '}': {
            advance();
            return newToken(TokenType::RIGHT_BRACE);
        }
        case '<': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::LESS_EQUAL);
            }
            return newToken(TokenType::LEFT_ANGLE_BRACKET);
        }
        case '>': {
            advance();
            if(nextLetter == '=') {
                advance();
                return newToken(TokenType::GREATER_EQUAL);
            }
            return newToken(TokenType::RIGHT_ANGLE_BRACKET);
        }

        case '^': {
            advance();
            return newToken(TokenType::CARET);
        }
        case '~': {
            advance();
            return newToken(TokenType::TILDE);
        }

        case '$': {
            advance();
            return newToken(TokenType::DOLLAR);
        }
        case '@': {
            advance();
            return newToken(TokenType::DOG);
        }
        case '#': {
            advance();
            return newToken(TokenType::HASHTAG);
        }
    }
    return std::nullopt;
}

std::optional<Token> LexicalAnalyzer::next() {
    skipWhitespace();

    if(!isValidCurrentChar()) {
        return std::nullopt;
    }

    if(currentChar == '/') {
        char charNext = peek();
        if(charNext == '/') {
            skipComment();
            return next();
        }
        if(charNext == '*') {
            skipMultilineComment();
            return next();
        }
    }
    if(isDigit(currentChar)) {
        return tokenizeNumber();
    }
    if(currentChar == '"') {
        return tokenizeString();
    }

    if(std::isalnum(static_cast<unsigned char>(currentChar))) {
        int startLine = line;
        int startColumn = column;
        std::string identifier = buildIdentifier();
        std::optional<Token> token = getKeywordToken(identifier, line, column);
        
        if(token.has_value()) {
            return token.value();
        }
        return newToken(TokenType::IDENTIFIER, identifier);
    }
    std::optional<Token> operatorToken = getOperatorToken();

    if(operatorToken.has_value()) {
        return operatorToken.value();
    }
    callError("Unexpected token", line, column, "is unknown", std::string(1, currentChar));
}

std::vector<Token> LexicalAnalyzer::tokenize() {
    if(code.length() == 0) {
        return tokens;
    }
    currentChar = code[0];

    do {
        std::optional<Token> token = next();
        if(!token.has_value()) {
            break;
        }
        tokens.push_back(token.value());
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

    { "structure", TokenType::STRUCTURE },
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

std::optional<Token> LexicalAnalyzer::getKeywordToken(const std::string& word, int line, int column) {
    auto it = keywords.find(word);
    if(it != keywords.end()) {
        return Token(line, column, it->second, "");
    }
    return std::nullopt;
}