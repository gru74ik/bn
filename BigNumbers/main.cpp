/*
Смоделировать операцию деления целого числа длиной до 30 десятичных цифр на
действительное число в форме (zn)m.n Е N, где суммарная длина мантиссы (m+n)
– до 30 значащих цифр, а величина порядка N – до 5 цифр.

Результат выдать в форме (zn)0.m1 Е N1.

Условные обозначения (zn) – знак числа N, N1 – величина порядка E – основание
числа. Запись числа (zn)0.m Е N соответствует следующей записи числа
N mzn 10 *. 0) ( . Например, число 2.5 можно записать в виде: +0.25 E+1.

Порядок выполнения работы:
1.  Определить структуру данных для хранения длинного числа.
2.  Предусмотреть ввод и вывод чисел обязательно в том формате, который указан
    в задании.
3.  Разбивать число на составляющие при вводе нельзя (т.е. число должно
    считываться сразу полностью).
4.  STL не пользоваться.
*/

#include <iostream>
#include <string>
#include "BigFloatTester.h"
#include "bn_functions.h"

int main()
{
    //BigFloatTester tester;
    //tester.menu();

    str::string str = "1.0";

    BigFloat init( str );

    BigFloat one( init );

    for (size_t i = 0; i < 11; ++i)
    {
        init = init + one;
        std::cout << "Step #" << i + 1 << ": " << init << "\n";

    }

}
