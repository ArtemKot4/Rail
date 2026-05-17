#ifndef CODE_FIELD_H
#define CODE_FIELD_H
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <minmax.h>

class CodeField {
public:	
	std::vector<std::string> field;
	int lineStart;

	CodeField(const std::string& code, int lineIndex, int lineCount = 1) : code(code), lineIndex(lineIndex + 1), lineCount(lineCount) {
		int startIndex = this->lineIndex - lineCount;
		start = max(startIndex, 0);
	};

	void build() {
		std::vector<std::string> lines = getLines();
		int lineIndex = start + 1;
		int width = std::to_string(start + lines.size()).length();

		for(const std::string& line : lines) {
			std::string lineIndexString = std::to_string(lineIndex);
			std::string padding = std::string(width - lineIndexString.length(), ' ');
			std::string sidePart = lineIndexString + padding + " | ";
			lineStart = sidePart.length();
			field.push_back(sidePart + line);
			lineIndex++;
		}
	}

	void print() {
		for(const std::string& line : field) {
			std::cerr << line << std::endl;
		}
	}

private:
	std::string code;
	int lineCount;
	int lineIndex;
	int start;

	std::vector<std::string> getLines() {
		std::vector<std::string> lines;
		std::string line;
		std::string currentLineText;
		int currentLineIndex = 0;
		bool hasEmpty = true;

		for(const char& letter : code + "\n") {
			if(letter == '\n') {
				if(currentLineIndex + 1 > lineIndex) {
					break;
				}
				if(currentLineIndex >= start && !hasEmpty) {
					lines.push_back(currentLineText);
				}
				currentLineText.clear();
				currentLineIndex++;
				continue;
			}
			if(currentLineIndex < start) {
				continue;
			}
			if(letter != ' ') {
				hasEmpty = false;
			}
			currentLineText.push_back(letter);
		}
		return lines;
	}
};

#endif