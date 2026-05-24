#ifndef TYPE_VISITOR_H
#define TYPE_VISITOR_H

#include <memory>
#include <vector>
#include "TypeExpression.h"

class SyntaxAnalyzer;

struct TypeVisitor {
    bool (*find)(SyntaxAnalyzer&);
    std::unique_ptr<TypeExpression> (*parse)(SyntaxAnalyzer&, std::unique_ptr<TypeExpression>);
    
    TypeVisitor(bool (*f)(SyntaxAnalyzer&), 
                std::unique_ptr<TypeExpression> (*p)(SyntaxAnalyzer&, std::unique_ptr<TypeExpression>))
        : find(f), parse(p) {}
};

extern std::vector<TypeVisitor> visitors;

#endif