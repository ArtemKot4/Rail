#include <iostream>
#include "compiler/lexical_analyzer/LexicalAnalyzer.h"
#include "compiler/lexical_analyzer/TokenTypeUtils.h"

int main() {
    std::string text =
    "10 000.0 const appleCount: int = 10;                                ";

    std::unique_ptr<LexicalAnalyzer> analyzer = std::make_unique<LexicalAnalyzer>(text);
    analyzer.get()->tokenize();

    TokenTypeUtils::printTokens(analyzer.get()->getTokensCopy());

    return 0;
}