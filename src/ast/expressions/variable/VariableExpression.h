#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H

#include "../Expression.h"

class VariableExpression : public Expression {
public:
	std::string name;
	std::unique_ptr<Node> value;
	bool isConst;
	bool find(SyntaxAnalyzer& parser) override;
	std::unique_ptr<Node> parse(SyntaxAnalyzer& parser) override;
};

#endif