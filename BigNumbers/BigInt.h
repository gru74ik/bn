#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

class BigFloat; // forward declaration

class BigInt
{
private:
    char sign_;
    std::string number_;

public:
    // constructors:
    BigInt();
    BigInt( const std::string& number );
    BigInt( const BigInt& bi );

private:
    // checkers:
    bool is_correct() const;

    // changers:
    void discard_sign();

    // setters:
    void set_number( const std::string & number );
    void reset();

private:
    // getters:
    char sign() const;

public:
    std::string number() const ;

    // assignment operators:
    BigInt operator=( const BigInt& bi );
    BigInt operator=( const std::string& obj );

    // comparison operators:
    bool operator<( const BigInt& bi ) const;
    bool operator<=( const BigInt& bi ) const;
    bool operator>( const BigInt& bi ) const;
    bool operator>=( const BigInt& bi ) const;
    bool operator==( const BigInt& bi ) const;

    // arithmetic operators:
    BigInt operator+( const BigInt& addendum ) const;
    BigInt operator-( const BigInt& subtrahend ) const;
    BigInt operator*( const BigInt& multiplier ) const;
    BigInt operator/( const BigInt& divider ) const;

    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    BigFloat operator/( const BigFloat& divider ) const;

    // input-output operators:
    friend std::ostream& operator<<( std::ostream& os, const BigInt& bi );
    friend std::istream& operator>>( std::istream& is, BigInt& bi );
};

#endif // BIGINT_H
