#ifndef OBJECT_EXPRESSION_H
#define OBJECT_EXPRESSION_H

#include "TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"
#include "compiler/RailError.h"
#include <unordered_map>

struct ObjectExpression : TypeExpression {
	std::unordered_map<std::string, std::unique_ptr<TypeExpression>> structure;

	static std::unique_ptr<TypeExpression> parse(SyntaxAnalyzer& analyzer, std::unique_ptr<TypeExpression> expression) {
		auto object = std::make_unique<ObjectExpression>();
		analyzer.advance();

		std::unordered_map<std::string, std::unique_ptr<TypeExpression>> structure;
		
		while(true) {
			Token key = analyzer.expect(TokenType::IDENTIFIER);
			analyzer.expect(TokenType::COLON);
			structure[key.text] = TypeSyntaxAnalyzer::analyze(analyzer);
			if(analyzer.match(TokenType::RIGHT_BRACE, 0)) {
				break;
			}
			analyzer.advance();
		}
		analyzer.advance();
		object->structure = std::move(structure);
		return object;
	}

	static bool find(SyntaxAnalyzer& analyzer) {
   	 	return analyzer.match(TokenType::LEFT_BRACE, 0);
	}
};

#endif