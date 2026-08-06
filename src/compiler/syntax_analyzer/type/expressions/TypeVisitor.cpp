#include "TypeVisitor.h"
#include "LiteralExpression.h"
#include "NullableExpression.h"
#include "UnionExpression.h"
#include "ObjectExpression.h"

static std::vector<TypeVisitor> visitors = {
    { LiteralExpression::find, LiteralExpression::parse },
    { NullableExpression::find, NullableExpression::parse },
    { ObjectExpression::find, ObjectExpression::parse },
    { UnionExpression::find, UnionExpression::parse }
    //{ ArrayExpression::find, ArrayExpression::parse },
};