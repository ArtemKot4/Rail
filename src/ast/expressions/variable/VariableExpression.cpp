#include "VariableExpression.h"

bool VariableExpression::find(SyntaxAnalyzer& parser) {
    return parser.match(TokenType::LET) || parser.match(TokenType::CONST);
}

//std::unique_ptr<Node> VariableExpression::parse(SyntaxAnalyzer& parser) {
//    isConst = parser.match(TokenType::CONST);
//    parser.expect(TokenType::IDENTIFIER);
//    name = parser.currentToken.text;
//    parser.advance();
//
//    if(parser.match(TokenType::COLON)) {
//        parser.advance();
//        
//    }
//
//    while(parser.hasToken() && !parser.match(TokenType::SEMICOLON)) {
//        //временно просто пропускаем, потому что я не написал реализацию выражений
//        parser.advance();
//    }
//    parser.advance();
//}