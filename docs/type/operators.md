# Операторы типов
Rail предлагает несколько нестандартных операторов для работы с типами данных.

## Логические операторы
Здесь вы познакомитесь с новыми способами работы с типами, которых нет в Java.

### is-проверки
Такие проверки строго проверяют, является ли объект экземпляром конкретного класса.

Синтаксис:
```rail
объект is класс
```

Например:
```rail
class A {}
class B extends A {}

const b = new B();
console.log(b is B); //true
console.log(b is A); //false
```

### extends-проверки
Такие проверки проверяют, что объект является наследником или самим экземпляром.

Синтаксис:
```rail
объект extends класс
```

Примеры использования:
1. Проверяем, что объект наследник:
    ```rail
    class User {
        public constructor(
            public name: string;
            public age: int;
        ) {}
    }

    const john: User = new User(name="John", age=30); 

    console.log(john extends User); //true

    class Admin extends User {}

    console.log(new Admin(name="Mark", age=25) extends User); //true
    ```

2. Проверяем, что класс наследник:
    ```rail
        class User {
            public constructor(
                public name: string;
                public age: int;
            ) {}
        }

        class Admin extends User {
            public constructor(public protectionLevel: string, name: string, age: int) {
                super(name, age);
            }
        }

    const john: User = new User(name="John", age=30); 

    console.log(Admin extends User); //true
    ```

### super-проверки
Проверяет, является ли один класс прямым родителем другого. В таких проверках сравнение объектов недопустимо.

```rail
class Animal { }
class Mammal extends Animal { }
class Dog extends Mammal { }

console.log(Dog super Mammal);   // true
console.log(Dog super Animal);   // false

### implements-проверки
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

Если сравнение происходит с другими объектами как в примере выше, а не с типами, satisfies автоматически узнает тип и проведёт по нему сравнение.

## Остальные операторы

### Преобразование типов через as
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
typeof <значение>
```

Примеры использования:
```rail
type MyType = typeof 1; // int
```

Работает и с переменными, применим в примере с `keyof`.

Важно! Извлекает типы с учётом ссылок, например:
```rail
const num1: int& = 10;
const num2: typeof num1 = num1; //тип данных стал int&

//так же рассмотрим пример, где мы пытаемся взять ссылку в такой же ситуации
const num3: (typeof num1)& = num2; //Ошибка! Архитектурное ограничение, нельзя брать ссылки на ссылки. 

```

#### typeof static
Если мы работаем с typeof, то когда мы применим на объектах, мы получим следующее:

```rail
const obj = { hello: "world" }
type typeOfObj = typeof obj; // { hello: string }
```

Но что, если мы хотим, чтобы "world" стал литеральным типом данных? А именно типом, который является им, но имеет конкретное ограничение. `"world"` вместо `string` в нашем случае.  

На помощь приходит `static`! Он делает ключи литеральными типами, в случае таких примитивов как числа и строки.

```rail
type typeOfObj = typeof static obj; // { "hello": "world" }
```

С массивами история похожая:

```rail
const array = [1, 2, 3, 4, 5];

type arrayType = typeof array; // [int, int, int, int, int]
type arrayTypeConst = typeof static array; // [1, 2, 3, 4, 5]
```

## keyof
`keyof` - оператор, который позволяет получить названия ключей объекта в виде литеральных строковых типов.

### Получаем литеральные типы данных ключей

```rail
const materials = { "wood": "Дерево", "stone": "Камень" }

const anyKeyName: keyof (typeof static materials) = "wood"; // тип данных становится "wood" | "stone"
```

Давайте рассмотрим пример, когда мы можем использовать только значения ключей объекта.

### Получаем литеральные типа данных значений

```rail
const anyKeyName: (typeof static materials)[keyof (typeof static materials)] = "wood"; // тип данных становится "Дерево" | "Камень"
```

Сложно, могли вы подумать. Но давайте разберёмся в том, почему это проще, чем вы думаете!

Рассмотрим все действия:
1. `(typeof static materials)` - получаем `materials` как тип данных, где ключи - [литеральные значения](#typeof-static). Это нужно для того, чтобы мы могли работать с ним как с типом объекта, где ключи и значения представлены литеральными строковыми типами: типами, которые могут хранить в себе текст, а не быть абстрактными `string`.
2. `[keyof (typeof static materials)]` - тут точно так же. Мы получили тип данных, а это объект, и обращаемся к его ключу через `union` тип, который нам даёт `keyof`.
В данном случае `union` тип от `keyof` это `"wood" | "stone"`