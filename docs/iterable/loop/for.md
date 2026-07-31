# Цикл for
Цикл for используется для повторения операций определенное количество раз.

Он будет работать, пока указанное условие не будет выполнено. Это похоже на цикл [while](while.md), но в отличие от него, переменные можно создать внутри цикла.
## Синтаксис
```rail
for(переменные; условие; операции) {
    //тело цикла
}
```

### Пропуск этапов:
Этапы можно пропускать, тогда нужно их просто не писать, но всё равно ставить ставить `;`.

Делаем бесконечный цикл: если условие не указано, оно всегда true.
```rail
for(;;) {
    //тело цикла
}
```

## Пишем простой счётчик
```rail
for(let i = 0; i < 10; i++) {
    console.log(i);
}
```

Или при помощи `range`:
```rail
for(const i of range(10)) {
    console.log(i);
}
```

## Используйте `&` для переменных
Это позволит не копировать значения ключей. Используйте, если это нужно.

```rail
const nums10 = range(10);

for(const num& of nums10) {
    console.log(num);
}
```

## Композиция циклических конструкций
Циклы могут совмещать неограниченное количество конструкций. Выглядит как их перечисление через запятую.

Всё разложится на итераторы в случае `for i` и `for of` и на условие в остальных случаях, псевдокод чего мы разберём далее, а сейчас давайте посмотрим как это работает.

```rail
const books = ["rail language", "java", "c++"];
const descriptions = ["like a TypeScript", "is legend", "is hard"];

for(const book& of books, const description& of descriptions, let index = 1; index <= books.length; index++) {
    console.log(index + ". " + book + " " + descriptions);
}
// 1. rail language like a TypeScript
// 2. java is legend
// 3. c++ is hard
```

Посмотрим на то, как это может выглядеть после компиляции.

```rail
const books: string[3] = ["rail language", "java", "c++"];
const descriptions: string[3] = ["like a TypeScript", "is legend", "is hard"];

{
    const books_iterator = books.iterator();
    const descriptions_iterator = descriptions.iterator();

    let book: string&?, description: string&?, index?: int = 1;
    let bookEnd: boolean = false, descriptionEnd: boolean = false, indexEnd: boolean = false;

    while(true) {    
        if(books_iterator.hasNext()) {
            book = books_iterator.next();
        } else if (!bookEnd){
            bookEnd = true;
            book = null;
        }

        if(descriptions_iterator.hasNext()) {
            description = descriptions_iterator.next();
        } else if(!descriptionEnd) {
            descriptionEnd = true;
            description = null;
        }

        if(index <= books.length) {
            index++;
        } else if(!indexEnd) {
            indexEnd = true;
            index = null;
        }

        if(bookEnd && descriptionEnd && indexEnd) {
            break;
        }

        console.log(index + ". " + book + " " + descriptions);
    }
}
```

Таким образом если какие-то итераторы были полностью перебраны, но не все, цикл не закончится, а переменные, связанные с перебранными итераторами станут `null`.