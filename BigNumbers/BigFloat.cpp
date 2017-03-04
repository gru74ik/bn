#include "BigFloat.h"
#include "bn_functions.h"

BigFloat::BigFloat() : number_( "0" ), mode_( DECIMAL )
{}

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
        /*
        // TODO: convert to decimal
        // example 1:
        // +123451234512345123451234512345 E-5 to
        // 1234512345123451234512345.12345
        // example 2:
        // +12345123451234512345.1234512345 E+5 to
        // 1234512345123451234512345.12345
        */

        break;

    case SCIENTIFIC:
        /*
        // TODO: convert to scientific
        // example 1:
        // 1234512345123451234512345.12345 to
        // +123451234512345123451234512345 E-5
        // example 2:
        // 1234512345123451234512345.12345 to
        // +12345123451234512345.1234512345 E+5
        */

        break;

    default:
        std::cout << "Error: incorrect function argument.";
    }

}

void BigFloat::set_number( const std::string & message )
{
    std::cout << message;
    std::getline( std::cin, number_ );
    if ( !is_correct( *this ) )
    {
        number_ = "0";
    }
}

BigFloat::MODE BigFloat::mode()
{
    return mode_;
}

bool BigFloat::operator<( BigFloat& b )
{
    BigFloat & a = *this;

    if ( a.mode() == SCIENTIFIC )
    {
        a.convert_to( DECIMAL );
    }

    if ( b.mode() == SCIENTIFIC )
    {
        b.convert_to( DECIMAL );
    }
    return a.number_ < b.number_;
}

std::string BigFloat::number()
{
    return number_;
}

BigFloat BigFloat::operator/( BigFloat& divisor )
{  
    BigFloat result;
    BigFloat & dividend = *this;

    if ( dividend.mode() == SCIENTIFIC )
    {
        dividend.convert_to( DECIMAL );
    }

    if ( divisor.mode() == SCIENTIFIC )
    {
        divisor.convert_to( DECIMAL );
    }

    if ( dividend.number_ == "0" )
    {
        result.number_ = "0";
    }
    else if ( divisor.number_ == "0" )
    {
        result.number_ = "1";
        std::cout <<
            "\nYou can not divide by zero! The result is "
            "equated to 1, but it is a wrong result.\n";
    }
    else
    {
        // TODO
    }

    // TODO:
    // реализовать деление одного числа типа BigFloat
    // на другое число типа BigFloat
/*
Цикл Х:
1)  Проверить, действительно ли делимое больше, чем делитель.
2)  Если да, начинаем делить.
3)  Если нет, добавляем разряд (или ноль, если разрядов в числе больше нет)
    к делимому и ноль с точкой в ответ.
4)  Проверить, действительно ли делимое больше, чем делитель.
5)	Если да, начинаем делить.
6)  Если нет, добавляем разряд (или ноль, если разрядов в числе больше нет)
    к делимому и ноль после точки в ответ.
7)  Выполнять цикл X, пока делимое не станет больше, чем делитель или пока
    количество разрядов в ответе не превысит 30.
8)  Делим делимое на делитель, частное записываем в ответ, остаток записываем
    в остаток (сносим вниз).
9)  Теперь остаток – это делимое.
10)	Выполнять цикл X, пока делимое не станет больше, чем делитель или пока
    количество разрядов в ответе не превысит 30.
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

size_t BigFloat::find_dot_position()
{
    size_t dot_position = 0;
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( number_[i] == '.' )
        {
            dot_position = i;
            std::cout << "dot_position: " << dot_position << "\n";
            break;
        }
    }

    return dot_position;
}

size_t BigFloat::digits_after_dot()
{
    return number_.size() - find_dot_position() - 1;
}

size_t BigFloat::digits_before_dot()
{
    size_t result = 0;
    if ( is_digit( number_[0] ) )
        result = find_dot_position();
    else if ( is_sign( number_[0] ) )
        result = find_dot_position() - 1;
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
