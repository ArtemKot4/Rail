#include <iostream>
#include "compiler/lexical_analyzer/LexicalAnalyzer.h"

int main() {
    std::string text =
    " const appleCount: int = 10;                                ";

    std::unique_ptr<LexicalAnalyzer> analyzer = std::make_unique<LexicalAnalyzer>(text);

    std::cout << "hello train station from rails!";
}