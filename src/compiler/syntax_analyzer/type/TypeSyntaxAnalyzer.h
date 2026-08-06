#ifndef TYPE_SYNTAX_ANALYZER_H
#define TYPE_SYNTAX_ANALYZER_H

#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"
#include "compiler/syntax_analyzer/type/expressions/TypeVisitor.h"
#include "compiler/syntax_analyzer/type/TypesForward.h"

namespace TypeSyntaxAnalyzer {
    inline std::optional<Types> analyze(SyntaxAnalyzer& analyzer) {
        std::optional<Types> expression = std::nullopt; //rewrite to std::variant

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