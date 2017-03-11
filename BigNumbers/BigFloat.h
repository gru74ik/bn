#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <string>
#include "BigInt.h"

class BigFloat
{
private:
    enum NOTATION { DECIMAL, SCIENTIFIC, DEFAULT, WRONG };
    enum DIRECTION { LEFT, RIGHT };

    char sign_;
    std::string number_;
    std::string tail_;
    NOTATION notation_;

public:
    // constructors:
    BigFloat();
    BigFloat( const std::string& number );
    BigFloat( const BigInt &bigInteger );
    BigFloat( const BigFloat& bf );

    // checkers:
    bool is_scientific() const;
    bool is_decimal() const;
    bool is_less_than_zero() const;
    bool is_greater_than_zero() const;

private:
    bool is_correct( NOTATION notation ) const;

    // changers:
    void discard_sign();
    void move_floating_point( DIRECTION dir, size_t shiftSize );
    void convert_to( NOTATION notation );
    void push_front_additional_zeroes( size_t numberOfZeroes );
    void pop_front_additional_zeroes( size_t numberOfZeroes );
    void push_back_additional_zeroes( size_t numberOfZeroes );
    void pop_back_additional_zeroes( size_t numberOfZeroes );

    // getters:
    size_t dot_position() const;
    size_t digits_after_dot() const;
    size_t digits_before_dot() const;
    size_t e_position() const;
    size_t digits_after_e() const;
    size_t e_value_as_number() const;
    std::string e_value_as_string() const;
    size_t lead_zeroes() const;
    size_t e_sign_position() const;
    char e_sign() const;
    size_t last_digit_position() const;
    size_t position_after( size_t pos ) const;
    size_t position_before( size_t pos ) const;
    size_t space_position() const;

    char sign() const;
    std::string mantissa() const;


public:
    std::string number() const;
    NOTATION notation() const;

    // setters:
    void set_number( const std::string& number );   
    void reset();

private:
    void mark_as_wrong();

public:
    // comparison operators:
    bool operator<( const BigFloat& bf ) const;
    bool operator<=( const BigFloat& bf ) const;
    bool operator>( const BigFloat& bf ) const;
    bool operator>=( const BigFloat& bf ) const;
    bool operator==( const BigFloat& bf ) const;

    // assignment operators:
    BigFloat operator=( const BigFloat& bf );
    BigFloat operator=( const std::string& obj );

    // arithmetic operators (both operand are same type):
    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    BigFloat operator/( const BigFloat& divider ) const;

    // arithmetic operators (each operand are different type):
    BigFloat operator+( const BigInt& addendum ) const;
    BigFloat operator-( const BigInt& subtrahend ) const;
    BigFloat operator*( const BigInt& multiplier ) const;
    BigFloat operator/( const BigInt& divider ) const;

    // input-output operators:
    friend std::istream& operator>>( std::istream& is, BigFloat& bf );
    friend std::ostream& operator<<( std::ostream& os, BigFloat& bf );

};

#endif // BIGFLOAT_H
