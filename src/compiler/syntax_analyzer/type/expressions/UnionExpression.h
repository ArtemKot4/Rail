#ifndef UNION_EXPRESSION_H
#define UNION_EXPRESSION_H

#include "TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"

struct UnionExpression : TypeExpression {
    std::unique_ptr<Types> left;
    std::unique_ptr<Types> right;

    UnionExpression() {};
    UnionExpression(std::unique_ptr<Types> left, std::unique_ptr<Types> right): left(std::move(left)), right(std::move(right)) {};

    static std::optional<Types> parse(SyntaxAnalyzer& analyzer, std::optional<Types> expression) {
        auto unionExpression = std::make_unique<UnionExpression>();
        if(!expression.has_value()) {
            analyzer.callError("Unexpected empty left part", analyzer.currentToken.line, analyzer.currentToken.column, "|", "Missing left expression");
        }
        unionExpression->left = std::make_unique<Types>(std::move(expression.value()));
        analyzer.advance();
        auto rightExpression = TypeSyntaxAnalyzer::analyze(analyzer);
        if(!rightExpression.has_value()) {
            analyzer.callError("Unexpected empty right part", analyzer.currentToken.line, analyzer.currentToken.column, "|", "Missing right expression");
        }
        unionExpression->right = std::make_unique<Types>(std::move(rightExpression.value()));
        return unionExpression;
    }

    static bool find(SyntaxAnalyzer& analyzer) {
   	 	return analyzer.match(TokenType::PIPE);
    }
};

#endif