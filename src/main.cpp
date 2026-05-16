#include <iostream>
#include "compiler/lexical_analyzer/LexicalAnalyzer.h"
#include "compiler/lexical_analyzer/TokenTypeUtils.h"
#include "compiler/CodeField.h"

int main() {
    std::string text = R"(
        // Пример кода на языке Rail
    
        // Юниты для измерений
        unit km extends int;
        unit hour extends int;
        unit kg extends float;
    
        // Структура для точки
        struct Point {
            x: int;
            y: int;
        
            function distanceTo(other: Point): int {
                return sqrt((x - other.x) ^ 2 + (y - other.y) ^ 2);
            }
        }
    
        // Класс с наследованием
        class Animal {
            name: string;
        
            constructor(name: string) {
                this.name = name;
            }
        
            procedure speak(): void {
                console.log(name + " makes a sound");
            }
        }
    
        class Dog extends Animal {
            constructor(name: string) {
                super(name);
            }
        
            override procedure speak(): void {
                console.log(name + " says Woof!");
            }
        }
    
        // Функции с контрактами
        function divide(a: int, b: int where b != 0): int {
            return a / b;
        }
    
        function sqrt(x: double where x >= 0): double {
            return math.sqrt(x);
        }
    
        // Процедура с defer
        procedure readFile(path: string) {
            const file = open(path);
            defer close(file);
        
            const content = file.read();
            if (content == null) {
                return;
            }
            console.log(content);
        }
    
        // Итератор
        iterator range(start: int, end: int, step: int = 1): int {
            for (let i = start; i < end; i += step) {
                yield i;
            }
        }
    
        // Поток
        thread processData(data: int[]): int[] {
            const result = [];
            for (let x of data) {
                if (x % 2 == 0) {
                    result.push(x * 2);
                }
            }
            return result;
        }
    
        // Поезд (композиция потоков)
        train readData, processData, saveResult;
    
        // Главный код
        procedure main() {
            // Переменные
            let name: string = "Rail";
            const version: int = 1;
            var counter: int? = null;
        
            // Nullable с проверкой
            if (counter != null) {
                console.log("Counter: " + counter);
            }
        
            // Optional chaining
            const value = counter ?? 0;
        
            // Массивы с размерами
            let numbers: int[5] = [1, 2, 3, 4, 5];
            let dynamic: int[] = [10, 20, 30];
            let flexible: int[3-] = [1, 2];  // максимум 3 элемента
        
            // Списковое включение
            const squares = [x * x for x in range(0, 10) if x % 2 == 0];
        
            // Match выражение
            const status = match httpCode {
                case 200: "OK"
                case 404: "Not Found"
                case >= 500: "Server Error"
                case _: "Unknown"
            };
        
            // Try-catch
            try {
                const result = divide(10, 0);
            } catch (e) {
                console.log("Error: " + e.message);
            }
        
            // Циклы
            for (let i of range(0, 5)) {
                console.log(i);
            }
        
            while (counter < 10) {
                counter++;
            }
        
            // Использование юнитов
            const distance: km = 100 km;
            const time: hour = 2 hour;
            const speed = distance / time;  // km/hour
        
            // Проверка типа
            if (value extends int) {
                console.log("Integer");
            }
        
            // Typeof
            type PointType = typeof Point;
        
            // Структура с распаковкой
            const point = Point(10, 20);
            const (x, y) = point;
        
            // Multiple inheritance (последний побеждает)
            class SmartDevice extends Device, Networkable, Configurable {
                constructor() {
                    super();
                }
            }
        
            // Деструктуризация массива
            const [first, second, ...rest] = numbers;
        
            // Spread оператор
            const merged = [...numbers, ...dynamic];
        
            // Модули
            import "math.rail" as math;
            export function helper(): void {}
        }
    
        // Запуск
        main();
    )"; //thank you deep seek for example of code

    std::unique_ptr<LexicalAnalyzer> analyzer = std::make_unique<LexicalAnalyzer>(text);
    analyzer.get()->tokenize();

    TokenTypeUtils::printTokens(analyzer.get()->getTokensCopy());

    std::unique_ptr<CodeField> field = std::make_unique<CodeField>(text, 15, 9);
    field.get()->build();
    field.get()->print();

    return 0;
}