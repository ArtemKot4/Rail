#ifndef TYPE_DECLARATION_EXPRESSION
#define TYPE_DECLARATION_EXPRESSION

#include <string>
#include <memory>
#include "ast/expressions/Expression.h"
#include "compiler/syntax_analyzer/type/expressions/TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"
#include "ast/NodesForward.h"
#include "compiler/syntax_analyzer/type/TypesForward.h"

struct TypeDeclarationExpression : Expression {
    using Expression::Expression;

    std::string name;
    Types type;

    static Nodes parse(SyntaxAnalyzer& analyzer) {
        TypeDeclarationExpression expression = TypeDeclarationExpression(analyzer.currentToken.line, analyzer.currentToken.column);
        expression.name = analyzer.expect(TokenType::IDENTIFIER).value().text;
        analyzer.expect(TokenType::ASSIGN);
        analyzer.advance();
        expression.type = TypeSyntaxAnalyzer::analyze(analyzer).value();
        analyzer.expect(TokenType::SEMICOLON, 0);
        analyzer.advance();

        return std::move(expression);
    }

    static bool find(SyntaxAnalyzer& analyzer) {
        return analyzer.match(TokenType::TYPE);
    }
};

#endif