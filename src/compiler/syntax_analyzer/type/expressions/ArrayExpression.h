#ifndef ARRAY_EXPRESSION_H
#define ARRAY_EXPRESSION_H

#include <memory>
#include "TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"
#include "compiler/RailError.h"
#include <memory>

struct ArrayExpression : TypeExpression {
    std::unique_ptr<TypeExpression> type;
    int from = 0;
    int to = 0;
    bool limited = false;

    //is []
    ArrayExpression(std::unique_ptr<TypeExpression> t) : type(std::move(t)), limited(false) {}

    //from = 0, to = n is [n-]; from = n1, to = n2 is [n1-n2]
    ArrayExpression(std::unique_ptr<TypeExpression> t, int from, int to) : type(std::move(t)), from(from), to(to), limited(true) {}

    //size = n, unlimited = true is [n+]; size = n, unlimied = false is [n]
    ArrayExpression(std::unique_ptr<TypeExpression> t, int size, bool limited = true): type(std::move(t)), from(size), to(size), limited(limited) {}

    static std::unique_ptr<TypeExpression> parse(SyntaxAnalyzer& analyzer, std::unique_ptr<TypeExpression> expression) {
        return nullptr;
    }

	static bool find(SyntaxAnalyzer& analyzer) {
		return analyzer.currentToken.type == TokenType::LEFT_BRACKET;
	}
};

#endif