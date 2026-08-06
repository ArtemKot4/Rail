#include <iostream>
#include "compiler/lexical_analyzer/LexicalAnalyzer.cpp"
#include "compiler/syntax_analyzer/SyntaxAnalyzer.cpp"
#include "compiler/lexical_analyzer/TokenTypeUtils.h"

void testTypeParsing() {
    std::string text = "type testing = { hello: string, rail: string }?";
    
    std::unique_ptr<LexicalAnalyzer> lexicalAnalyzer = std::make_unique<LexicalAnalyzer>(text, "type_declaration.rail");
    lexicalAnalyzer.get()->tokenize();
    std::unique_ptr<SyntaxAnalyzer> syntaxAnalyzer = std::make_unique<SyntaxAnalyzer>(SyntaxAnalyzer(*lexicalAnalyzer));
    std::unique_ptr<BlockStatement> ast = syntaxAnalyzer->analyze();
}

int main() {
    std::cout << "Hello, rail! after 2 months!" << std::endl;

    //TokenTypeUtils::printTokens(analyzer.get()->getTokensCopy());
    return 0;
}