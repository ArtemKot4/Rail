#ifndef TYPEOF_WRAPPER_H
#define TYPEOF_WRAPPER_H

#include <string>
#include "TypeExpression.h"

struct TypeofWrapper : TypeExpression {
	std::vector<std::string> path;
};

#endif
