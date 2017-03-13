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

#include <random>
#include <ctime>
#include <algorithm>

template <typename T>
T getRandNumber( const T & begin, const T & end )
{
    static std::mt19937 generator( time( 0 ) );
    std::uniform_int_distribution<size_t> distribution( begin, end );
    return distribution( generator ) ;
}

int main()
{
    BigFloatTester tester;
    tester.menu();
/*
    std::string str;
    BigFloat x;
    bool errorsIsNotFound = true;

    for ( int i = 0; i < 10000000; ++i )
    {
        str =
            number_to_string(getRandNumber(1, 111)) +
            '.' +
            number_to_string(getRandNumber(1, 111111));

            x.set_number(str);

        auto it = std::find(str.begin(), str.end(), '.');





        if (x.dot_position() != std::distance(str.begin(), it))
        {
            errorsIsNotFound = false;
            std::cout
                << "\n========================================================\n"
                << "x.dot_position() is wrong in test #: "
                << i + 1
                << "\n";

            std::cout << "x.number(): " << x.number() << "\n";
            std::cout << "x.dot_position(): " << x.dot_position() << "\n";
            std::cout
                << "real dot position: " << std::distance(str.begin(), it)
                << "\n========================================================\n\n";
            break;
        }
    }

    if (errorsIsNotFound)
        std::cout << "Errors is not found.";
*/
}
