#ifndef TYPE_EXPRESSION
#define TYPE_EXPRESSION

#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"

struct TypeExpression {
	virtual ~TypeExpression() = default;
	virtual TypeExpression parse(SyntaxAnalyzer& syntaxAnalyzer);
};

#endif
