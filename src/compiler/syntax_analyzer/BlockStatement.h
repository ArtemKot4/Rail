#ifndef BLOCK_STATEMENT_H
#define BLOCK_STATEMENT_H

#include <vector>
#include <memory>
#include <variant>
#include "Node.h"
#include "Import.h"
#include "ast/expressions/type/TypeDeclarationExpression.h"
#include "ast/Nodes.h"

struct BlockStatement : public Node {
    std::vector<Import> imports;
    std::vector<Nodes> nodes;

    BlockStatement(int line, int column) : Node(line, column) {}

    void addNode(Nodes node) {
        nodes.push_back(std::move(node));
    }
};

#endif