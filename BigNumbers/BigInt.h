#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

class BigFloat;

class BigInt
{
private:
    std::string number_;

    bool is_correct(const BigInt& bi );

public:
    BigInt();
    BigInt( const std::string& number );
    BigInt( const BigInt& bi );

    bool operator<( BigInt& bi );
    BigInt operator=( const BigInt& bi );
    BigInt operator=( const std::string& obj );

    BigInt operator+( const BigInt& addendum ) const;
    BigInt operator-( const BigInt& subtrahend ) const;
    BigInt operator*( const BigInt& multiplier ) const;
    BigInt operator/( const BigInt& divider ) const;

    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    BigFloat operator/( const BigFloat& divider ) const;

    void set_number( const std::string & message );
    std::string number() const ;

    friend std::ostream& operator<<( std::ostream& os, const BigInt& bi );
    friend std::istream& operator>>( std::istream& is, BigInt& bi );
};

#endif // BIGINT_H
