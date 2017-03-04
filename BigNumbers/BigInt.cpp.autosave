#include "BigInt.h"
#include "bn_functions.h"

bool is_permitted_character( const char ch )
{
    return is_sign( ch ) || is_digit( ch );
}

bool is_one_digit( const std::string& number )
{
    return number.size() == 1 && is_digit( number.at(0) );
}

bool is_correct( const std::string& number )
{
    bool result = false;
    if ( !number.empty() )
    {
        if ( is_one_digit( number ) )
        {
                result = true;
        }
        else if ( number.size() > 1 )
        {
            if ( is_permitted_character( number[0] ) )
            {
                result = true;
                for ( size_t i = 1; i < number.size(); ++i )
                {
                    if ( !is_digit( number[i] ) )
                    {
                        result = false;
                        break;
                    }
                }
            }
        }
    }

    return result;
}

BigInt::BigInt()
    : number_( "0" )
{}

BigInt::BigInt( const std::string& number )
{
    if ( !is_correct( number ) )
    {
        number_ = "0";
    }
    else
    {
        number_ = number;
    }
}

BigInt::BigInt( const BigInt& obj )
{
    number_ = obj.number_;
}

BigInt BigInt::operator=( const BigInt& obj )
{
    if ( this != &obj )
    {
        number_ = obj.number_;
    }
    return *this;
}

/*
BigInt BigInt::operator/( const BigInt& number ) const
{
    BigInt result;
    // TODO:
    // реализовать деление числа типа BigInt
    // на число типа BigInt
    return result;
}

BigFloat BigInt::operator/( const BigFloat& number ) const
{
    BigFloat result;
    // TODO:
    // реализовать деление числа типа BigInt
    // на число типа BigFloat
    return result;
}
*/
std::ostream& operator<<( std::ostream& os, const BigInt& num )
{
    os << num.number_;

    return os;
}
