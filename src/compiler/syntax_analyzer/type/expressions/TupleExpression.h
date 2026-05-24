#ifndef TUPLE_EXPRESSION_H
#define TUPLE_EXPRESSION_H

#include <vector>
#include <memory>
#include "TypeExpression.h"

struct TupleExpression : TypeExpression {
	std::vector<std::unique_ptr<TypeExpression>> types;
	TupleExpression(std::vector<std::unique_ptr<TypeExpression>> types) : types(std::move(types)) {}
};

#endif