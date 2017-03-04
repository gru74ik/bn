#include "BigInt.h"
#include "bn_functions.h"

BigInt::BigInt() : number_( "0" )
{}

BigInt::BigInt( const std::string& number )
{
    number_ = number;
    if ( !is_correct( *this ) )
    {
        number_ = "0";
    }
}

BigInt::BigInt( const BigInt& bi )
{
    number_ = bi.number_;
}

bool BigInt::is_correct( const BigInt& bi )
{
    bool result = true;
    if( bi.number_.empty() )
    {
        result = false;
    }
    else
    {
        if ( is_one_char( bi.number_ ) )
        {
            if ( !is_digit( bi.number_[0] ) )
            {
                result = false;
            }
        }
        else
        {
            if ( !is_sign( bi.number_[0] ) && !is_digit( bi.number_[0] ) )
            {
                result = false;
            }

            for ( size_t i = 1; i < bi.number_.size(); ++i )
            {
                if ( !is_digit( bi.number_[i] ) )
                {
                    result = false;
                    break;
                }
            }

        }
    }

    return result;
}

BigInt BigInt::operator=( const BigInt& bi )
{
    if ( this != &bi )
    {
        number_ = bi.number_;
    }
    return *this;
}

BigInt BigInt::operator=( const std::string& obj )
{
    if ( this->number_ != &obj.front() )
    {
        number_ = obj;
    }
    return *this;
}

void BigInt::set_number( const std::string & message )
{
    std::cout << message;
    std::getline( std::cin, number_ );
    if ( !is_correct( *this ) )
    {
        number_ = "0";
    }
}

std::string BigInt::number()
{
    return number_;
}

std::ostream& operator<<( std::ostream& os, const BigInt& bi )
{
    os << bi.number_;

    return os;
}

std::istream& operator>>( std::istream& is, BigInt& bi )
{
    is >> bi.number_;
    return is;
}
