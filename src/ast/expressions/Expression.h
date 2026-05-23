#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include "compiler/syntax_analyzer/SyntaxAnalyzer.h"

class Expression {
public:
    virtual ~Expression() = default;
    virtual bool find(SyntaxAnalyzer& parser);
    virtual std::unique_ptr<Node> parse(SyntaxAnalyzer& parser);
};

#endif