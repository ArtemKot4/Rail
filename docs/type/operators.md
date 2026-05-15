# Операторы типов
Rail предлагает несколько нестандартных операторов для работы с типами данных.

## Логические операторы
Здесь вы познакомитесь с новыми способами работы с типами, которых нет в Java.

### extends-проверки
Это аналог instanceof из Java, но работающий только с [классами](..\object-oriented/class/intro.md), [юнитами](..\object-oriented/unit/intro.md) и [перечислениями](..\object-oriented/enum/intro.md)

Синтаксис:
```rail
значение extends классы, юниты
```

Примеры использования:
```rail
class User {
    public constructor(
        public name: string;
        public age: int;
    )
}

const john: User = new User(name="John", age=30); 

console.log(john extends User); //true
```

### implements-проверки
То же самое, что и extends, но **только для интерфейсов**.

Работает только с теми значениями, которые являются реализацией интерфейсов.

Синтаксис:
```rail
значение implements интерфейсы
```

Примеры использования:
```rail
interface User {
    public name: string;
    public age: int;
}

const john: User = {
    name: "John",
    age: 30
};

const mark = {
    name: "Mark",
    age: 25
};

console.log(john implements User); //true
console.log(mark implements User); //false
```

### satisfies-проверки
Реализация satisfies из TypeScript для проверок.

Позволяет проверять объекты на соответствие структуре типа, вне зависимости от того, класс это, объект, интерфейс или что-то ещё.

Проверяет конкретно по наличию полей и совпадению типов данных.

Синтаксис:
```rail
значение satisfies значения_или_типы
```

Примеры использования:
```rail
const john = {
    name: "John",
    age: 30
};

const mark = {
    name: "Mark",
    age: 25
};

console.log(mark satisfies john); //true, потому что mark соответствует структуре john в плане типов данных у полей
```

## Остальные операторы

### преобразование типов через as
Если в TypeScript оператор as использовался в качестве абстракции, здесь он действительно позволяет преобразовывать типы, если это возможно.

### typeof
#### Вне типа
Возвращает строковое название типа данных.

Синтаксис:
```rail
typeof значение
```

Примеры использования:
```rail
console.log(typeof 1); //int
console.log(typeof "1"); //string
console.log(typeof true); //boolean
```

#### В объявлении типа
Возвращает тип данных от значения.

Синтаксис:
```rail
typeof <тип_данных>
```

Примеры использования:
```rail
type MyType = typeof 1;

console.log(MyType); //int
```