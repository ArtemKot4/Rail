#include "SyntaxAnalyzer.h"
#include "compiler/lexical_analyzer/Token.h"
#include "compiler/RailError.h"

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

bool SyntaxAnalyzer::expect(TokenType type, int offset, const std::string& message, int line, int column,
	const std::string& keyword, const std::string& reason) {
	advance(offset);
	if(!match(type, 0)) {
		callError(message, line == -1 ? currentToken.line : line, column == -1 ? currentToken.column : column, keyword, reason);
	}
	return true;
}

[[noreturn]] void SyntaxAnalyzer::callError(const std::string& message, int line, int column, const std::string& keyword, const std::string& reason) {
	RailError(lexicalAnalyzer.code, "SyntaxError", message, line, column, reason, keyword, lexicalAnalyzer.fileName);
}