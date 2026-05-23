#ifndef OBJECT_EXPRESSION_H
#define OBJECT_EXPRESSION_H

#include "TypeExpression.h"
#include <unordered_map>

struct ObjectExpression : TypeExpression {
	std::unordered_map<std::string, TypeExpression> structure;

	//virtual ObjectExpression parse() {

	//}
};

#endif