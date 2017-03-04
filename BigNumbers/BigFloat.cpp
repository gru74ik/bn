#include "BigFloat.h"
#include "bn_functions.h"

BigFloat::BigFloat()
{
    number_ = "0";
    mode_ = DECIMAL;
}

BigFloat::BigFloat(const std::string& number )
{
    number_ = number;
    convert_to( DECIMAL );
}

BigFloat::BigFloat( BigInt& bigInteger )
{
    convert_to( DECIMAL );
    number_ = bigInteger.number() + ".0";
}

void BigFloat::convert_to( MODE mode )
{
    switch ( mode )
    {
    case DECIMAL:
        // TODO: convert to decimal
        break;

    case SCIENTIFIC:
        // TODO: convert to scientific
        break;

    default:
        std::cout << "Error: incorrect function argument.";
    }

}

void BigFloat::set_number( const std::string & message )
{
    std::cout << message;
    std::cin >> number_;
}

BigFloat::MODE BigFloat::mode()
{
    return mode_;
}

std::string BigFloat::number()
{
    return number_;
}

BigFloat BigFloat::operator/( BigFloat& divider )
{
    BigFloat result;
    divider.convert_to( BigFloat::DECIMAL );
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
123456789.123456789123456789 / 9 == 13717421013717421013717421
*/

    return result;
}

bool BigFloat::is_correct( BigFloat& bf )
{
    bool result = true;
    if( bf.number_.empty() )
    {
        result = false;
    }
    else
    {
        if ( is_one_char( bf.number() ) )
        {
            if ( !is_digit( bf.number_[0] ) )
            {
                result = false;
            }
        }
        else
        {
            bf.convert_to( BigFloat::DECIMAL );
            if ( contains_one_dot_only( bf.number() ) )
            {
                // TODO: проверить, что число записано
                // в правильной экспоненциальной или
                // десятичной форме
            }
            else
            {
                result = false;
            }
        }
    }

    return result;
}

std::ostream& operator<<( std::ostream& os, BigFloat& bf )
{
    bf.convert_to( BigFloat::SCIENTIFIC );
    os << bf.number_;
    return os;
}

std::istream& operator>>( std::istream& is, BigFloat& bf )
{
    is >> bf.number_;
    bf.convert_to( BigFloat::DECIMAL );
    return is;
}
