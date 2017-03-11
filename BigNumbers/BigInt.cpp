#include "BigInt.h"
#include "bn_functions.h"

BigInt::BigInt()
    : sign_( '+' ), number_( "0" )
{}

BigInt::BigInt( const std::string& number )
{
    number_ = number;
    sign_ = sign();
    discard_sign();
    if ( !is_correct() )
    {
        reset();
    }
}

BigInt::BigInt( const BigInt& bi )
{
    sign_ = bi.sign_;
    number_ = bi.number_;
}

bool BigInt::is_correct() const
{
    bool correct = true;

    if( number_.size() == 0 ) // if( bi.number_.empty() )
    {
        correct = false;
    }
    else
    {
        if ( is_one_char( number_ ) )
        {
            if ( !is_digit( number_[0] ) ) // bi.number_.at(0)
            {
                correct = false;
            }
        }
        else
        {
            if ( !is_digit( number_[0] ) )
            {
                correct = false;
            }

            for ( size_t i = 1; i < number_.size(); ++i )
            {
                if ( !is_digit( number_[i] ) )
                {
                    correct = false;
                    break;
                }
            }

        }
    }

    return correct;
}

void BigInt::discard_sign()
{
    if ( is_sign( number_[0] ) )
    {
        erase_part_of( number_, 0, 0 );
    }
}

// setters:
void BigInt::set_number( const std::string & number )
{
    BigInt temp = *this; // Лишнее копирование (вынужденное).
    if ( is_correct() )
    {
        number_ = number;
        sign_ = sign();
        discard_sign();
    }
    else
    {
        *this = temp; // Лишнее копирование (вынужденное).
    }
}

void BigInt::reset()
{
    number_ = "0";
}

// getters:
char BigInt::sign() const
{
    return number_[0] == '-' ? '-' : '+';
}

std::string BigInt::number() const
{
    return number_;
}

// assignment operators:
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
    if ( this->number_ != &obj[0] ) // &obj.front()
    {
        number_ = obj;
    }
    return *this;
}

// comparison operators:
bool BigInt::operator<( const BigInt& bi ) const
{
    BigInt a = *this;
    BigInt b = bi;

    if ( !a.is_correct() )
    {
        std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
        a.reset();
    }

    if ( !b.is_correct() )
    {
        std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
        b.reset();
    }

    return string_to_number( a.number_ ) < string_to_number( b.number_ );
}

bool BigInt::operator<=( const BigInt& bi ) const
{
    BigInt a = *this;
    BigInt b = bi;

    if ( !a.is_correct() )
    {
        std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
        a.reset();
    }

    if ( !b.is_correct() )
    {
        std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
        b.reset();
    }

    return
        string_to_number( a.number_ ) < string_to_number( b.number_ ) ||
        string_to_number( a.number_ ) == string_to_number( b.number_ );
}

bool BigInt::operator>( const BigInt& bi ) const
{
    BigInt a = *this;
    BigInt b = bi;

    if ( !a.is_correct() )
    {
        std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
        a.reset();
    }

    if ( !b.is_correct() )
    {
        std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
        b.reset();
    }

    return string_to_number( a.number_ ) > string_to_number( b.number_ );
}

bool BigInt::operator>=( const BigInt& bi ) const
{
    BigInt a = *this;
    BigInt b = bi;

    if ( !a.is_correct() )
    {
        std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
        a.reset();
    }

    if ( !b.is_correct() )
    {
        std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
        b.reset();
    }

    return
        string_to_number( a.number_ ) > string_to_number( b.number_ ) ||
        string_to_number( a.number_ ) == string_to_number( b.number_ );
}

bool BigInt::operator==( const BigInt& bi ) const
{
    BigInt a = *this;
    BigInt b = bi;

    if ( !a.is_correct() )
    {
        std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
        a.reset();
    }

    if ( !b.is_correct() )
    {
        std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
        b.reset();
    }

    return string_to_number( a.number_ ) == string_to_number( b.number_ );
}

// arithmetic operators:
BigInt BigInt::operator+( const BigInt& addendum ) const
{
    BigInt sum( addendum ); // temporary solution to avoid compiler warning
    // TODO
    return sum;
}

BigInt BigInt::operator-( const BigInt& subtrahend ) const
{
    BigInt diff( subtrahend ); // temporary solution to avoid compiler warning
    // TODO
    return diff;
}

BigInt BigInt::operator*( const BigInt& multiplier ) const
{
    BigInt product( multiplier ); // temporary solution to avoid compiler warning
    // TODO
    return product;
}

BigInt BigInt::operator/( const BigInt& divider ) const
{
    BigInt result( divider ); // temporary solution to avoid compiler warning
    // TODO
    return result;
}

BigFloat BigInt::operator+( const BigFloat& addendum ) const
{
    BigFloat sum( addendum ); // temporary solution to avoid compiler warning
    // TODO
    return sum;
}

BigFloat BigInt::operator-( const BigFloat& subtrahend ) const
{
    BigFloat diff( subtrahend ); // temporary solution to avoid compiler warning
    // TODO
    return diff;
}

BigFloat BigInt::operator*( const BigFloat& multiplier ) const
{
    BigFloat product( multiplier ); // temporary solution to avoid compiler warning
    // TODO
    return product;
}

BigFloat BigInt::operator/( const BigFloat& divider ) const
{
    BigFloat result( divider ); // temporary solution to avoid compiler warning
    // TODO
    return result;
}

// input-output operators:
std::istream& operator>>( std::istream& is, BigInt& bi )
{
    is >> bi.number_;
    return is;
}

std::ostream& operator<<( std::ostream& os, const BigInt& bi )
{
    os << bi.number_;

    return os;
}


