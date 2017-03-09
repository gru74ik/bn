#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <string>
#include "BigInt.h"

class BigFloat
{
public:
    enum NOTATION { DECIMAL, SCIENTIFIC };
    enum DIRECTION { LEFT, RIGHT }; //private

private:
    char sign_;
    std::string number_;
    NOTATION notation_;

public:
    BigFloat();
    BigFloat( const std::string& number );
    BigFloat( BigInt &bigInteger );
    BigFloat( const BigFloat& bf );

private: // checkers:
    bool is_scientific();
    bool is_decimal();
    bool is_correct( NOTATION notation );

public: // getters:
    size_t dot_position(); // private (remove to private section after tests)
    size_t digits_after_dot();              // private
    size_t digits_before_dot();             // private
    size_t e_position();                    // private
    size_t digits_after_e();                // private
    size_t e_value_as_number();             // private
    std::string e_value_as_string();        // private
    size_t lead_zeroes();                   // private
    size_t e_sign_position();               // private
    char e_sign();                          // private
    size_t last_digit_position();           // private
    size_t position_after( size_t pos );    // private
    size_t position_before( size_t pos );   // private
    size_t space_position();                // private

private:
    char get_sign();
    std::string get_mantissa();


public:
    std::string number();
    NOTATION notation();

    // setters:
    void set_number( const std::string& message );
    void reset();

    // changers:
    void discard_sign(); // private
    void move_floating_point( DIRECTION dir, size_t shiftSize ); // private
    void convert_to( NOTATION notation );


    // operators:
    bool operator<( BigFloat& b );
    BigFloat operator=( const BigFloat& bf );
    BigFloat operator=( const std::string& obj );
    /*
    BigFloat operator+( const BigFloat& addendum ) const;
    BigFloat operator-( const BigFloat& subtrahend ) const;
    BigFloat operator*( const BigFloat& multiplier ) const;
    */
    BigFloat operator/( const BigFloat& divider ) const;

    // input-output operators:
    friend std::istream& operator>>( std::istream& is, BigFloat& bf );
    friend std::ostream& operator<<( std::ostream& os, BigFloat& bf );

};

#endif // BIGFLOAT_H
