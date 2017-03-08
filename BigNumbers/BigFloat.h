// 6.022E23 or 6.022e23 is equivalent to 6.022 × 10^23,
// 1.234 × 10^3 = 12.34 × 10^2 = 123.4 × 10^1 = 1234
// 1.234E3 = 12.34E2 = 123.4E1 = 1234
// 0 × 10^0 = +0 E+0 = 0 × 1 = 0

#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <string>
#include "BigInt.h"

class BigFloat
{
public:
    enum MODE { DECIMAL, SCIENTIFIC };
    enum DIRECTION { LEFT, RIGHT }; //private

private:
    char sign_;
    std::string number_;
    MODE mode_;

public:
    BigFloat();
    BigFloat( const std::string& number );
    BigFloat( BigInt &bigInteger );
    BigFloat( const BigFloat& bf );

private: // checkers:
    bool is_scientific();
    bool is_decimal();
    bool is_correct();

public:
    size_t dot_position();      // private (remove to private section after tests)
    size_t digits_after_dot();  // private
    size_t digits_before_dot(); // private
    size_t e_position();        // private

private: // getters:
    char get_sign();
    std::string get_mantissa();

public:
    std::string number();
    MODE mode();

    // setter:
    void set_number( const std::string & message );

    // changers:
    void discard_sign(); // private
    void move_floating_point( DIRECTION dir, size_t shiftSize ); // private
    void convert_to( MODE mode );


    // operators:
    bool operator<( BigFloat& b );
    BigFloat operator=( const BigFloat& bf );
    BigFloat operator=( const std::string& obj );
    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    BigFloat operator/( const BigFloat& divider ) const;

    // input-output operators:
    friend std::istream& operator>>( std::istream& is, BigFloat& bf );
    friend std::ostream& operator<<( std::ostream& os, BigFloat& bf );

};

#endif // BIGFLOAT_H
