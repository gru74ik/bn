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

bool is_one_char( const std::string& number )
{
    return number.size() == 1;
}

bool is_dot( const char ch )
{
    return ch == '.';
}

bool contains_one_dot_only( const std::string& number )
{
    int counter = 0;
    for ( const auto & elem : number )
    {
        if ( is_dot( elem ) )
            ++counter;
        if ( counter > 1)
            break;
    }
    return counter == 1;
}
