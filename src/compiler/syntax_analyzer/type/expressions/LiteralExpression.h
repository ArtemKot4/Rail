#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include <string>
#include <memory>
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"
#include "TypeExpression.h"
#include "UnionExpression.h"

struct LiteralExpression : TypeExpression {
    std::string value;
    LiteralExpression(const std::string& value) : value(value) {}
    
    static std::optional<Types> parse(SyntaxAnalyzer& analyzer, std::optional<Types> expression) {
        std::string value = analyzer.currentToken.text;
        analyzer.advance();
        return std::make_unique<LiteralExpression>(value);
    }

	static bool find(SyntaxAnalyzer& analyzer) {
		return analyzer.match(TokenType::IDENTIFIER, 0);
	}
};

#endif