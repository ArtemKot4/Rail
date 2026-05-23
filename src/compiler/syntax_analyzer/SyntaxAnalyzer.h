#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include "compiler/lexical_analyzer/Token.h"
#include "BlockStatement.h"
#include "Node.h"
#include "compiler/lexical_analyzer/LexicalAnalyzer.h"

class SyntaxAnalyzer {
public:
    SyntaxAnalyzer(LexicalAnalyzer& lexicalAnalyzer);
    int position = 0;
    Token currentToken;

    bool hasToken();
    std::optional<Token> advance(int count = 1);
    std::optional<Token> peek(int offset = 1);
    bool match(TokenType type, int offset = 1);
    bool expect(TokenType type, int offset = 1, const std::string& message = "Missed token", int line = -1, int column = -1,
        const std::string& keyword = " ", const std::string& reason = "");
    [[noreturn]] void callError(const std::string& message, int line, int column,
        const std::string& keyword = "", const std::string& reason = "");
    std::unique_ptr<BlockStatement> buildAST();

private:
    LexicalAnalyzer& lexicalAnalyzer;
    std::vector<Token> tokens;
};

#endif