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
#include "bn_functions.h"

int main()
{
/*
    BigInt a;
    a.set_number( "Enter an integer a: " );

    BigFloat b;
    b.set_number( "Enter a float b: " );

    BigFloat c(a);
    std::cout << a << "\n" << b << "\n" << c << "\n";

    BigFloat result = c / b;

    std::cout << "a divided by b: " << result << "\n\n";
*/


    BigFloat d ( "-0.00123456789" );
    std::cout << "The number: " << d ;
    std::cout << "\nLetter E position: " << d.e_position();
    std::cout << "\nDigits after letter E: " << d.digits_after_e();
    std::cout << "\nExponent value: " << d.e_value_as_number();
    std::cout << "\nLead zeroes: " << d.count_lead_zeroes();

/*
    for ( size_t shiftSize = 0; shiftSize < 7; ++shiftSize )
    {
        d = "-1234.5678 E-5";
        std::cout << "\n=======================\n" << d << "\n";
        d.move_floating_point( BigFloat::LEFT, shiftSize );
        std::cout << "shiftSize: " << shiftSize << "\n" << d ;
    }

    for ( size_t shiftSize = 0; shiftSize < 7; ++shiftSize )
    {
        d = "-1234.5678 E-5";
        std::cout << "\n-----------------------\n" << d << "\n";
        d.move_floating_point( BigFloat::RIGHT, shiftSize );
        std::cout << "shiftSize: " << shiftSize << "\n" << d ;
    }
*/
    return 0;
}
