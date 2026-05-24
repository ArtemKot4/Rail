#ifndef UNION_EXPRESSION_H
#define UNION_EXPRESSION_H

#include "TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"

struct UnionExpression : TypeExpression {
    std::unique_ptr<TypeExpression> left;
    std::unique_ptr<TypeExpression> right;

    UnionExpression() {};
    UnionExpression(std::unique_ptr<TypeExpression> left, std::unique_ptr<TypeExpression> right): left(std::move(left)), right(std::move(right)) {};

    static std::unique_ptr<TypeExpression> parse(SyntaxAnalyzer& analyzer, std::unique_ptr<TypeExpression> expression) {
        auto unionExpression = std::make_unique<UnionExpression>();
        unionExpression->left = std::move(expression);
        analyzer.advance();
        unionExpression->right = TypeSyntaxAnalyzer::analyze(analyzer);
        return unionExpression;
    }

    static bool find(SyntaxAnalyzer& analyzer) {
   	 	return analyzer.match(TokenType::PIPE);
    }
};

#endif