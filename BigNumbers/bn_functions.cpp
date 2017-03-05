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

bool is_dot( const char ch )
{
    return ch == '.';
}

size_t char_to_digit( const char ch )
{
    size_t result = 0;
    switch ( ch )
    {
    case '0':
        result = 0;
        break;
    case '1':
        result = 1;
        break;
    case '2':
        result = 2;
        break;
    case '3':
        result = 3;
        break;
    case '4':
        result = 4;
        break;
    case '5':
        result = 5;
        break;
    case '6':
        result = 6;
        break;
    case '7':
        result = 7;
        break;
    case '8':
        result = 8;
        break;
    case '9':
        result = 9;
        break;
    default:
        break;
    }
    return result;
}

char digit_to_char( const size_t )
{
    char result = '0';
    switch ( result )
    {
    case 0:
        result = '0';
        break;
    case 1:
        result = '1';
        break;
    case 2:
        result = '2';
        break;
    case 3:
        result = '3';
        break;
    case 4:
        result = '4';
        break;
    case 5:
        result = '5';
        break;
    case 6:
        result = '6';
        break;
    case 7:
        result = '7';
        break;
    case 8:
        result = '8';
        break;
    case 9:
        result = '9';
        break;
    default:
        break;
    }
    return result;
}

bool is_one_char( const std::string& number )
{
    return number.size() == 1;
}

bool contains_one_dot_only( const std::string& number )
{
    int counter = 0;
    for ( size_t i = 0; i < number.size(); ++i )
    {
        if ( is_dot( number[i] ) )
            ++counter;
        if ( counter > 1)
            break;
    }
    return counter == 1;
}

// string ins will be inserted before position pos:
void insert_to( std::string& str, const std::string& ins, const size_t pos )
{
    std::string part_before = "";
    for ( size_t i = 0; i < pos; ++i )
        part_before = part_before + str[i];

    std::string part_after = "";
    std::string result;

    if ( pos < str.size() )
    {
        for ( size_t i = pos; i < str.size(); ++i )
            part_after = part_after + str[i];

        result = part_before + ins + part_after;
    }
    else
    {
        result = part_before + ins;
    }

    str = result;
}

// part of string str will be erased from
// position first to position last inclusive:
void erase_part_of( std::string& str, const size_t first, const size_t last )
{
    if ( first < last )
    {
        std::string part_before = "";
        for ( size_t i = 0; i < first; ++i )
        {
            part_before = part_before + str[i];
        }

        if ( last < str.size()-2 )
        {
            std::string part_after = "";
            for ( size_t i = last+1; i < str.size(); ++i )
            {
                part_after = part_after + str[i];
            }
            str = part_before + part_after;
        }
        else
        {
            str = part_before;
        }
    }
}
