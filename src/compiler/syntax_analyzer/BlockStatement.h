#ifndef BLOCK_STATEMENT_H
#define BLOCK_STATEMENT_H

#include <vector>
#include <memory>
#include "Node.h"
#include "Import.h"

struct BlockStatement : public Node {
    std::vector<Import> imports;
    std::vector<std::unique_ptr<Node>> nodes;

    BlockStatement(int line, int column) : Node(line, column) {}

    void addNode(std::unique_ptr<Node> node) {
        nodes.push_back(std::move(node));
    }
};

#endif