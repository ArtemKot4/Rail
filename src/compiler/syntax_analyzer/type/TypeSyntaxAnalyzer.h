#ifndef TYPE_SYNTAX_ANALYZER_H
#define TYPE_SYNTAX_ANALYZER_H

#include "compiler/syntax_analyzer/type/expressions/TypeExpression.h"
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"
#include "compiler/syntax_analyzer/type/expressions/TypeVisitor.h"

namespace TypeSyntaxAnalyzer {
    inline std::unique_ptr<TypeExpression> analyze(SyntaxAnalyzer& analyzer) {
        std::unique_ptr<TypeExpression> expression = nullptr; //rewrite to std::variant

		while(true) {
			bool foundExpression = false;

			for(const auto& visitor : visitors) {
				if(visitor.find(analyzer)) {
					expression = visitor.parse(analyzer, std::move(expression));
					foundExpression = true;
				}
			}
			if(!foundExpression) {
				return expression;
			}
		} 
    }
}
#endif