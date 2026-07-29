#ifndef TYPES_FORWARD_H
#define TYPES_FORWARD_H

#include <variant>
#include <memory>

struct ArrayExpression;
struct IntersectionExpression;
struct LiteralExpression;
struct NullableExpression;
struct ObjectExpression;
struct TupleExpression;
struct TypeofWrapper;
struct UnionExpression;

using Types = std::variant<
    std::unique_ptr<ArrayExpression>,
    std::unique_ptr<IntersectionExpression>,
    std::unique_ptr<LiteralExpression>,
    std::unique_ptr<NullableExpression>,
    std::unique_ptr<ObjectExpression>,
    std::unique_ptr<TupleExpression>,
    std::unique_ptr<TypeofWrapper>,
    std::unique_ptr<UnionExpression>
>;

#endif