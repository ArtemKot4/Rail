#ifndef OBJECT_EXPRESSION_H
#define OBJECT_EXPRESSION_H

#include "TypeExpression.h"
#include "compiler/syntax_analyzer/type/TypeSyntaxAnalyzer.h"
#include "compiler/RailError.h"
#include <unordered_map>

struct ObjectExpression : TypeExpression {
	std::unordered_map<std::string, std::unique_ptr<Types>> structure;

	static std::optional<Types> parse(SyntaxAnalyzer& analyzer, std::optional<Types> expression) {
		auto object = std::make_unique<ObjectExpression>();
		analyzer.advance();
		std::unordered_map<std::string, std::unique_ptr<Types>> structure;
		
		while(true) {
			std::optional<Token> key = analyzer.expect(TokenType::IDENTIFIER);
			analyzer.expect(TokenType::COLON);
			structure[key.value().text] = std::make_unique<Types>(std::move(TypeSyntaxAnalyzer::analyze(analyzer).value()));
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