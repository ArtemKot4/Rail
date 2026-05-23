#include <iostream>
#include "compiler/lexical_analyzer/LexicalAnalyzer.h"
#include "compiler/lexical_analyzer/TokenTypeUtils.h"

int main() {
    std::string text = R"(
1000.0
        "hello\"world\"\n"
        // Пример кода на Rail для тестирования лексера
        // Комментарий
        let name: string = "Rail";
        const version: int = 1;

        // Функция с условием
        function isEven(n: int): boolean {
            return n % 2 == 0;
        }

        // Процедура с циклом
        procedure main() {
            for (let i = 0; i < 10; i++) {
                if (isEven(i)) {
                    console.log(i, " is even");
                } else {
                    console.log(i, " is odd");
                }
            }
    
            const arr: int[] = [1, 2, 3, 4, 5];
            const sum = arr.reduce((acc, x) => acc + x, 0);
            console.log("Sum:", sum);
        }
        main();
    )"; //thank you deep seek for example of code

    std::cout << "Hello, rail!" << std::endl;

    std::unique_ptr<LexicalAnalyzer> analyzer = std::make_unique<LexicalAnalyzer>(text, "aboba.rail");
    analyzer.get()->tokenize();

    //TokenTypeUtils::printTokens(analyzer.get()->getTokensCopy());
    return 0;
}