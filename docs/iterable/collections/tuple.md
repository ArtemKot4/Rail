# Кортежи
Кортежи - неизменяемые коллекции, которые могут содержать в себе различные типы данных.

## Синтаксис
```rail
(тип_данных1, тип_данных2, ...);

//или
тип_данных1, тип_данных2, ...;
```

## Типизация
Типизировать кортежи очень просто:
Для этого нужно просто написать в круглых скобках типы данных, которые нужно использовать.
```rail
const names: (string, string) = ("Maks", "Petya");
// или
const names: (string, string) = "Maks", "Petya";  //без скобок при создании
```
**Важно**! Если в круглых скобках будет лишь один тип данных, это не будет считаться кортежем, это будет считаться написанным типом данных. Удобно для операций типизации.
```rail
const x: (int) = 5;            //это просто int в скобках
const y: (int, int) = (1, 2);  //это кортеж
```

## Работа с индексами
Поскольку кортежи - неизменяемые коллекции, то их индексы тоже неизменяемые. Мы можем лишь обращаться к значениям, но не перезаписывать их.
```rail
console.log(names[0]); //Maks
console.log(names[1]); //Petya

names[0] = "Vasya";    //ошибка
```
Обращение к индексам работает так же, как и в массивах.

## Размер кортежа
Для получения размера кортежа нужно использовать свойство length.
```rail
console.log(names.length); //2
```

## Распаковка кортежа
Распаковать кортежи в Rail легче, чем массивы в JavaScript.
```rail
const first, second = names;
console.log(first); //Maks
console.log(second); //Petya
```

### Распаковываем в циклах
```rail
const namesList = (typeof names)[names];

for(let first, second in namesList) {
    console.log(first); //Maks
    console.log(second); //Petya
}
```

## Примеры
```rail
type tupleExample = (int, string, boolean);

let tuple1: tupleExample = (1, "hello", true);
let tuple2: tupleExample = 2, "world", false;
```