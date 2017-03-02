#include "BigFloat.h"

BigFloat::BigFloat()
    :
        mantissa_sign_( "+" ),
        integer_part_( "0" ),
        fractional_part_( "0" ),
        exponent_sign_( "+" ),
        exponent_( "0" )
{}

BigFloat::BigFloat( const std::string& number )
{
    if ( number.empty() || !is_correct( number ) )
    {
        mantissa_sign_ = "+";
        integer_part_ = "0";
        fractional_part_ = "0";
        exponent_sign_ = "+";
        exponent_ = "0";
    }

    // TODO:
    // организовать парсинг строки и разбивку на части

}

bool BigFloat::is_correct( const std::string& number )
{
    bool result = true;
    if ( number[0] != '+' && number[0] != '-' )
        result = false;
    // TODO:
    // организовать парсинг строки и проверку её корректности
    // для использования её (строки) в качестве основы
    // для конструирования объекта BigFloat

    return result;
}

BigFloat BigFloat::operator/( const BigFloat& divider )
{
    BigFloat result;
    // TODO:
    // реализовать деление одного числа типа BigFloat
    // на другое число типа BigFloat
/*
Цикл Х:
1)  Проверить, действительно ли делимое больше, чем делитель.
2)  Если да, начинаем делить.
3)  Если нет, добавляем разряд (или ноль, если разрядов в числе больше нет) к делимому и ноль с точкой в ответ.
4)  Проверить, действительно ли делимое больше, чем делитель.
5)	Если да, начинаем делить.
6)  Если нет, добавляем разряд (или ноль, если разрядов в числе больше нет) к делимому и ноль после точки в ответ.
7)  Выполнять цикл X, пока делимое не станет больше, чем делитель или пока количество разрядов в ответе не превысит 30.
8)  Делим делимое на делитель, частное записываем в ответ, остаток записываем в остаток (сносим вниз).
9)  Теперь остаток – это делимое.
10)	Выполнять цикл X, пока делимое не станет больше, чем делитель или пока количество разрядов в ответе не превысит 30.

Три теста:
1 / 2000 == 0.0005
123456789123456789123456789 / 9 == 13717421013717421013717421
*/
    divider;
    return result;
}

std::ostream& operator<<( std::ostream& os, const BigFloat& num )
{
    os
        << num.mantissa_sign_
        << num.integer_part_
        << '.'
        << num.fractional_part_
        << " E"
        << num.exponent_sign_
        << num.exponent_;
    return os;
}
