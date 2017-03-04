#include "BigInt.h"
#include "bn_functions.h"

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

BigInt::BigInt(const BigInt& bi )
{
    number_ = bi.number_;
}

bool BigInt::is_correct( const BigInt& bi )
{
    bool result = true;
    // TODO
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

void BigInt::set_number_by_user( const std::string & message )
{
    std::cout << message;
    std::cin >> number_;
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
