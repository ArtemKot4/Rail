#ifndef NULLABLE_EXPRESSION
#define NULLABLE_EXPRESSION

#include <memory>
#include "TypeExpression.h"
#include "UnionExpression.h"
#include "LiteralExpression.h"
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"

struct NullableExpression : TypeExpression {
    static std::unique_ptr<TypeExpression> parse(SyntaxAnalyzer& analyzer, std::unique_ptr<TypeExpression> expression) {
        analyzer.advance();
        return std::make_unique<UnionExpression>(UnionExpression(std::move(expression), std::make_unique<LiteralExpression>(LiteralExpression("null"))));
    }
    
    static bool find(SyntaxAnalyzer& analyzer) {
        return analyzer.match(TokenType::QUESTION_MARK);
    }
};

#endif