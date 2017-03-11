#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <string>
#include "BigInt.h"

class BigFloat
{
public:
    enum NOTATION { DECIMAL, SCIENTIFIC, DEFAULT, WRONG };
    enum DIRECTION { LEFT, RIGHT }; //private

private:
    char sign_;
    std::string number_;
    std::string tail_;
    NOTATION notation_;

public:
    BigFloat();
    BigFloat( const std::string& number );
    BigFloat( const BigInt &bigInteger );
    BigFloat( const BigFloat& bf );

private: // checkers:
    bool is_scientific() const;
    bool is_decimal() const;
public:
    bool is_correct( NOTATION notation ) const; //private

public: // getters:
    size_t dot_position() const; // private (remove to private section after tests)
    size_t digits_after_dot() const;              // private
    size_t digits_before_dot() const;             // private
    size_t e_position() const;                    // private
    size_t digits_after_e() const;                // private
    size_t e_value_as_number() const;             // private
    std::string e_value_as_string() const;        // private
    size_t lead_zeroes() const;                   // private
    size_t e_sign_position() const;               // private
    char e_sign() const;                          // private
    size_t last_digit_position() const;           // private
    size_t position_after( size_t pos ) const;    // private
    size_t position_before( size_t pos ) const;   // private
    size_t space_position() const;                // private

private:
    char sign() const;
    std::string mantissa() const;


public:
    std::string number() const;
    NOTATION notation() const;

    // setters:
    void set_number( const std::string& number );
    void mark_as_wrong();
    void reset();

    // changers:
    void discard_sign(); // private
    void move_floating_point( DIRECTION dir, size_t shiftSize ); // private
    void convert_to( NOTATION notation );


    // operators:
    bool operator<( BigFloat& b );
    BigFloat operator=( const BigFloat& bf );
    BigFloat operator=( const std::string& obj );
\
    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    BigFloat operator/( const BigFloat& divider ) const;

    BigFloat operator+( const BigInt& addendum ) const;
    BigFloat operator-( const BigInt& subtrahend ) const;
    BigFloat operator*( const BigInt& multiplier ) const;
    BigFloat operator/( const BigInt& divider ) const;

    // input-output operators:
    friend std::istream& operator>>( std::istream& is, BigFloat& bf );
    friend std::ostream& operator<<( std::ostream& os, BigFloat& bf );

};

#endif // BIGFLOAT_H
