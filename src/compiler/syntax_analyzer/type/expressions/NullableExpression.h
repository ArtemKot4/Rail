#ifndef NULLABLE_EXPRESSION
#define NULLABLE_EXPRESSION

#include <memory>
#include "TypeExpression.h"
#include "UnionExpression.h"
#include "LiteralExpression.h"
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"

struct NullableExpression : TypeExpression {
    static std::optional<Types> parse(SyntaxAnalyzer& analyzer, std::optional<Types> expression) {
        analyzer.advance();
        if(!expression.has_value()) {
            analyzer.callError("Unknown type for nullable", analyzer.currentToken.line, analyzer.currentToken.column, "?", "Need to use like `type?`");
        }
        return std::make_unique<UnionExpression>(
            std::make_unique<Types>(std::move(expression.value())),
            std::make_unique<Types>(std::make_unique<LiteralExpression>("null"))
        );
    }
    
    static bool find(SyntaxAnalyzer& analyzer) {
        return analyzer.match(TokenType::QUESTION_MARK);
    }
};

#endif