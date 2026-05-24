#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"
#include "compiler/syntax_analyzer/Node.h"

struct Expression : Node {
    using Node::Node;
};

#endif