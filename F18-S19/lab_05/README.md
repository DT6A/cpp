## Лабораторная №5 (`WW_C_io`)

0. Для выполнения задания понадобится реализацию intrusive list для точек.
Можно использовать либо свою, либо предоставленную реализацию. Замечание: порядок вывода/записи точек в файл должен быть _прямым_ (см. примеры).

1. В задании 03 была реализована "база данных", хранящая точки в памяти. В задании 05 предлагается реализовать возможность хранить точки на диске в двух форматах: текстовом и двоичном.

    * Интерфейс
        `./main (loadtext | loadbin) <infile> <action>`

        * `(loadtext | loadbin)` определяет вид `<infile>`: текстовый или двоичный, соответственно;
        * `<infile>` — имя файла, который хранит точки;
        * `<action>` — операция, которую нужно выполнить над точками.

    * Actions. Предлагается реализовать следующие операции (`<action>`):
        * `(savetext | savebin) <outfile>` -- сохранение считанных точек в файл `<outfile>` в текстовом или бинарном формате;
        * `print <fmt>` — вывод точек на экран в формате `<fmt>` (printf-like);
        * `count` — вывод на экран количества точек.

    * Формат файлов
        * текстовый: каждый элемент в отдельной строке; `x` и `y` разделены пробелом;
        * бинарный: элементы `x` и `y` записаны подряд `(x_1y_1x_2y_2...)`; каждое значение занимает _3_ байта.

        Числа `x` и `y` -- целые неотрицательные. Формат тестовых входных файлов всегда правильный.

    * БОНУС 2 балла за поддержку отрицательных чисел.

2. Реализация `print` и `count`

Операции `print` и `count` требуется реализовать, используя функцию `apply` (`get_length` использовать непосредственно в коде `count` нельзя).

Функция `apply` выполняет унарную операцию на каждом элементе списка и должна быть написана так, чтобы ее можно было использовать для списка, хранящего другие элементы (помимо точек), на которых определены собственные операции.

Сигнатура:
    ```c
    void apply(intrusive_list_t *lst, void (*op)(???), ???);
    ```

Hint: один из параметров `op` может использоваться как доп. аргумент для операции либо как способ хранения промежуточного результата операции.

3. Общие требования к решению аналогичны предыдущим заданиям: структура проекта, работа с памятью, code style.

4. Примеры
```
> cat test
1 1
2 2
3 3
>./main loadtext test savetext out_text
> cat out_text
1 1
2 2
3 3
>./main loadtext test count
3
> ./main loadtext test print "[%d, %d] "
[1, 1] [2, 2] [3, 3] 
> ./main loadtext test savebin out_bin
> hexdump out_bin
0000000 01 00 00 01 00 00 02 00 00 02 00 00 03 00 00 03
0000010 00 00
0000012
> ./main loadbin out_bin print "%d %d "
1 1 2 2 3 3
```