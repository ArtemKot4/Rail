#ifndef NODES_FORWARD_H
#define NODES_FORWARD_H

#include <variant>
#include <memory>

struct TypeDeclarationExpression;

using Nodes = std::variant<
    TypeDeclarationExpression
>;

#endif