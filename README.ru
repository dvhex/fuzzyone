FuzzyOne

Fast fuzzy library

Библиотека нечёткой логики, основанная на использовании встроенных функций c++,
таких, как +-*&|=, которые переопределены для нечётких операций.

Использование:

В простейшем случае формируется входные и выходные переменные типа LVar
(нечёткие переменные).  Каждой переменной задаются термы используя метод
setTerm. Обращение к термам осуществляется посредством индексного оператора
через целое число. Потом выполняются операции, основанные на нечётких правилах,
записываются они на языке си++, а не на языке нечётких множеств. Например,
есть две входные переменные - first и second, и одна выходная - result. Всем
переменным заданы по 3 терма: LOW = 0, MEDIUM = 1, HIGH = 2. Тогда, чтоб
записать выражение типа

"If first is LOW and second is MEDIUM, then result is LOW",

следует записать:

result[LOW] |= first[LOW] & second[MEDIUM].

Названия термов могут быть сформированы, например, через enum {LOW, MEDIUM,
HIGH}.  Вместо оператора & (определён, как минимум) может быть оператор *
(определён, как умножение).  Оператор + определён как нечёткая сумма, а | -
как максимум, т.е. |= используется для добавления значения в логическую
переменную, поэтому перед использованием следует обнулить выходную переменную
через вызов метода zero(). Дефуззификация осуществляется через метод
defuzzify(int), принимающий значение - количество интервалов для вычисления
центра тяжести. Получение числа осуществляется через поле класса value, задаётся
значение (осуществляется фуззификация) через оператор =.
