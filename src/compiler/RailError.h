#ifndef RAIL_ERROR_H
#define RAIL_ERROR_H
#include "CodeField.h"
#include "lexical_analyzer/TokenType.h"
#include <string>

[[noreturn]] void RailError(const std::string& code, const std::string& type, const std::string& message, int line, int column, const std::string& reason, const std::string& keyword, const std::string& fileName) {
	CodeField codeField(code, line, 10);
	codeField.build();
	std::cerr << type << ": " << message;
	if (!fileName.empty()) {
		std::cerr << " in file " << fileName << std::endl;
	}
	codeField.print();

	std::string underlineLine = "";
	for (int i = 0; i < column - 1 + codeField.lineStart; i++) {
		underlineLine.push_back(' ');
	}
	for (size_t i = 0; i < keyword.length(); i++) {
		underlineLine.push_back('^');
	}
	if (!reason.empty()) {
		underlineLine += " " + reason;
	}
	std::cerr << underlineLine << std::endl;
	std::exit(1);
}
#endif