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
