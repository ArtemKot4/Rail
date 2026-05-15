# Цикл for of

Цикл for of позволяет перебирать значения коллекций, в которых индексы представлены только числами. Часто это [массивы](../iterable/collections/array.md) и [кортежи](../iterable/collections/tuple.md).

Синтаксис: `for(переменная of коллекция)`.

```rail
const array = [1, 2, 3];

for(const value of array) {
    console.log(value);
}
//1
//2
//3
```