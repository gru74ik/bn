#include "bn_functions.h"

bool is_sign( const char ch )
{
    return ch == '+' || ch == '-';
}

bool is_digit( const char ch )
{
    return
        ch == '0' ||
        ch == '1' ||
        ch == '2' ||
        ch == '3' ||
        ch == '4' ||
        ch == '5' ||
        ch == '6' ||
        ch == '7' ||
        ch == '8' ||
        ch == '9';
}

bool is_one_digit( const std::string& number )
{
    return number.size() == 1 && is_digit( number.at(0) );
}

bool is_correct( const BigInt& bi )
{
    // TODO
}

bool is_correct( const BigFloat& bf )
{
    // TODO
}
