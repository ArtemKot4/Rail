#ifndef TYPE_VISITOR_H
#define TYPE_VISITOR_H

#include <memory>
#include <vector>
#include <optional>
#include "compiler/syntax_analyzer/type/TypesForward.h"

class SyntaxAnalyzer;

struct TypeVisitor {
    bool (*find)(SyntaxAnalyzer&);
    std::optional<Types> (*parse)(SyntaxAnalyzer&, std::optional<Types>);
    
    TypeVisitor(bool (*f)(SyntaxAnalyzer&), 
                std::optional<Types> (*p)(SyntaxAnalyzer&, std::optional<Types>))
        : find(f), parse(p) {}
};

extern std::vector<TypeVisitor> visitors;

#endif