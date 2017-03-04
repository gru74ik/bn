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
#include "BigInt.h"
#include "BigFloat.h"

BigInt get_number( const std::string & message )
{
    std::cout << message;
    BigInt number;
    std::cin >> number;
    return number;
}

BigFloat get_number( const std::string & message )
{
    std::cout << message;
    BigFloat number;
    std::cin >> number;
    return number;
}

int main()
{
    BigInt x = get_number( "Enter an integer: " );
    BigFloat y = get_number( "Enter a float: " );
    std::cout << "Result of division of x and y: " << x / y;
}
