#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

class TokenTypeUtils {
public:
	static std::string getTokenTypeName(TokenType type) {
        switch(type) {
            case TokenType::FUNCTION: return "FUNCTION";
            case TokenType::PROCEDURE: return "PROCEDURE";

            case TokenType::RETURN: return "RETURN";
            case TokenType::THROWS: return "THROWS";
            case TokenType::DEFER: return "DEFER";

            case TokenType::THREAD: return "THREAD";
            case TokenType::TRAIN: return "TRAIN";
            case TokenType::YIELD: return "YIELD";

            case TokenType::NEW: return "NEW";
            case TokenType::DELETE: return "DELETE";
            case TokenType::STRUCTURE: return "STRUCTURE";
            case TokenType::CLASS: return "CLASS";
            case TokenType::INTERFACE: return "INTERFACE";
            case TokenType::ENUMERATION: return "ENUMERATION";
            case TokenType::UNIT: return "UNIT";

            case TokenType::PUBLIC: return "PUBLIC";
            case TokenType::PRIVATE: return "PRIVATE";
            case TokenType::PROTECTED: return "PROTECTED";
            case TokenType::ABSTRACT: return "ABSTRACT";
            case TokenType::STATIC: return "STATIC";
            case TokenType::NATIVE: return "NATIVE";

            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::KEYWORD: return "KEYWORD";

            case TokenType::SATISFIES: return "SATISFIES";
            case TokenType::EXTENDS: return "EXTENDS";
            case TokenType::IMPLEMENTS: return "IMPLEMENTS";
            case TokenType::TYPEOF: return "TYPEOF";

            case TokenType::OF: return "OF";
            case TokenType::IN: return "IN";
            case TokenType::AS: return "AS";

            case TokenType::NAMESPACE: return "NAMESPACE";

            case TokenType::IF: return "IF";
            case TokenType::ELSE: return "ELSE";
            case TokenType::MATCH: return "MATCH";
            case TokenType::CASE: return "CASE";

            case TokenType::TRY: return "TRY";
            case TokenType::CATCH: return "CATCH";
            case TokenType::FINALLY: return "FINALLY";
            case TokenType::THROW: return "THROW";

            case TokenType::ITERATOR: return "ITERATOR";
            case TokenType::FOR: return "FOR";
            case TokenType::WHILE: return "WHILE";

            case TokenType::BREAK: return "BREAK";
            case TokenType::CONTINUE: return "CONTINUE";

            case TokenType::LET: return "LET";
            case TokenType::CONST: return "CONST";

            case TokenType::LEFT_PARENTHESIS: return "LEFT_PARENTHESIS";
            case TokenType::RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";
            case TokenType::LEFT_BRACE: return "LEFT_BRACE";
            case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
            case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
            case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
            case TokenType::LEFT_ANGLE_BRACKET: return "LEFT_ANGLE_BRACKET";
            case TokenType::RIGHT_ANGLE_BRACKET: return "RIGHT_ANGLE_BRACKET";

            case TokenType::SEMICOLON: return "SEMICOLON";
            case TokenType::COLON: return "COLON";
            case TokenType::COMMA: return "COMMA";
            case TokenType::POINT: return "POINT";

            case TokenType::DOG: return "DOG";
            case TokenType::HASHTAG: return "HASHTAG";

            case TokenType::ASSIGN: return "ASSIGN";
            case TokenType::ASSIGN_NULLABLE: return "ASSIGN_NULLABLE";
            case TokenType::PLUS: return "PLUS";
            case TokenType::MINUS: return "MINUS";
            case TokenType::STAR: return "STAR";
            case TokenType::SLASH: return "SLASH";
            case TokenType::AMPERSAND: return "AMPERSAND";
            case TokenType::PIPE: return "PIPE";
            case TokenType::CARET: return "CARET";
            case TokenType::TILDE: return "TILDE";
            case TokenType::DOLLAR: return "DOLLAR";
            case TokenType::PERCENT: return "PERCENT";

            case TokenType::PLUS_ASSIGN: return "PLUS_ASSIGN";
            case TokenType::MINUS_ASSIGN: return "MINUS_ASSIGN";
            case TokenType::STAR_ASSIGN: return "STAR_ASSIGN";
            case TokenType::SLASH_ASSIGN: return "SLASH_ASSIGN";
            case TokenType::PERCENT_ASSIGN: return "PERCENT_ASSIGN";

            case TokenType::PLUS_PLUS: return "PLUS_PLUS";
            case TokenType::MINUS_MINUS: return "MINUS_MINUS";

            case TokenType::QUESTION_MARK: return "QUESTION_MARK";
            case TokenType::EXCLAMATION_MARK: return "EXCLAMATION_MARK";
            case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
            case TokenType::NOT_EQUAL: return "NOT_EQUAL";
            case TokenType::LESS_EQUAL: return "LESS_EQUAL";
            case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";

            case TokenType::AND: return "AND";
            case TokenType::OR: return "OR";

            case TokenType::ELLIPSIS: return "ELLIPSIS";
            case TokenType::ARROW: return "ARROW";
            case TokenType::FAT_ARROW: return "FAT_ARROW";

            case TokenType::STRING_LITERAL: return "STRING_LITERAL";
            case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
            case TokenType::NUMBER_LITERAL: return "NUMBER_LITERAL";
            case TokenType::TRUE_LITERAL: return "TRUE_LITERAL";
            case TokenType::FALSE_LITERAL: return "FALSE_LITERAL";
            //case TokenType::NULL_LITERAL: return "NULL_LITERAL";

            case TokenType::IDENTIFIER: return "IDENTIFIER";
            // case TokenType::STRING: return "STRING";
            // case TokenType::CHAR: return "CHAR";
            // case TokenType::INTEGER: return "INTEGER";
            // case TokenType::LONG: return "LONG";
            // case TokenType::FLOAT: return "FLOAT";
            // case TokenType::DOUBLE: return "DOUBLE";
            // case TokenType::BOOLEAN: return "BOOLEAN";
            // case TokenType::VOID: return "VOID";
            // case TokenType::UNKNOWN: return "UNKNOWN";
            // case TokenType::NUMBER: return "NUMBER";

            case TokenType::IMPORT: return "IMPORT";
            case TokenType::EXPORT: return "EXPORT";
        }
        return "UNKNOWN";
	}

    static void printToken(const Token& token) {
        std::cout << "Token: { type: " << getTokenTypeName(token.type)
            << ", text: \"" << token.text << "\""
            << ", line: " << token.line
            << ", col: " << token.column << " }" << std::endl;
    }

    static void printTokens(const std::vector<Token>& tokens) {
        std::cout << "out tokens:" << std::endl;
        for(const auto& token : tokens) {
            printToken(token);
        }
    }
};