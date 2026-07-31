# Map
Map - это коллекция, которая содержит пары ключ-значение, при этом ключ может быть чем угодно.

Обычный конструктор принимает дженерик `K`, `V`, где первый отвечает за то, каким типом данных сможет быть ключ, а каким значение.

## Пример использования
```rail
let map = new Map<string, string>();
map.set('key', 'value');
console.log(map.get('key')); // value
```

## Конструкторы

```rail
Map<K, V>
Map<const O& extends static Object, const K = keyof O, V = O[keyof O]>(object: O);
```

## Методы
* `set(key, value)` - добавляет пару ключ-значение в map
* `get(key)` - получает значение по ключу
* `has(key)` - проверяет, есть ли ключ в map
* `delete(key)` - удаляет пару ключ-значение из map

