#include "SyntaxAnalyzer.h"
#include "compiler/lexical_analyzer/Token.h"
#include "compiler/RailError.h"

#include "ast/expressions/type/TypeDeclarationExpression.h"
#include "BlockStatement.h"

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer& lexicalAnalyzer) : lexicalAnalyzer(lexicalAnalyzer), tokens(lexicalAnalyzer.getTokensCopy()) {};

std::optional<Token> SyntaxAnalyzer::advance(int count) {
	position += count;
	auto token = peek(0);

	if(token.has_value()) {
		return currentToken = token.value();
	}
	return std::nullopt;
}

std::optional<Token> SyntaxAnalyzer::peek(int offset) {
	int index = position + offset;

	if(index < tokens.size()) {
		return tokens[index];
	}
	return std::nullopt;
}

bool SyntaxAnalyzer::match(TokenType type, int offset) {
	auto token = peek(offset);
	return token.has_value() && token.value().type == type;
}

std::optional<Token> SyntaxAnalyzer::expect(TokenType type, const std::string& message, int line, int column,
	const std::string& keyword, const std::string& reason) {
    
	if(!match(type, 0)) {
        callError(message, line == -1 ? currentToken.line : line, column == -1 ? currentToken.column : column, keyword, reason);
    }
	auto current = peek(0);
    advance(1);
	return current;
}

[[noreturn]] void SyntaxAnalyzer::callError(const std::string& message, int line, int column, const std::string& keyword, const std::string& reason) {
	RailError(lexicalAnalyzer.code, "SyntaxError", message, line, column, reason, keyword, lexicalAnalyzer.fileName);
}

bool SyntaxAnalyzer::hasToken() {
	return peek(0) != std::nullopt;
}

#include <iostream> //for debugging

std::unique_ptr<BlockStatement> SyntaxAnalyzer::analyze() {
	auto block = std::make_unique<BlockStatement>(0, 0);
	
	while(hasToken()) {
		if(TypeDeclarationExpression::find(*this)) { //while NodeVisitor is not done
			std::cout << "found type declaration" << std::endl;
			Nodes expression = TypeDeclarationExpression::parse(*this);
			block->addNode(std::move(expression));
			// if(const auto* type = std::get_if<TypeDeclarationExpression>(&expression)) {
			// 	std::cout << "name is: " << type->name << std::endl;
				// if(std::holds_alternative<UnionExpression>(type)) {
				// 	std::cout << "is union expression" << std::endl;
					
				// }
    		//} //debug
		} else {
			auto token = peek(0);
			callError("Unexpected token", token->line, token->column, token->text, "");
    	}
	}
	return block;
}