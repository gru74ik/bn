// 6.022E23 or 6.022e23 is equivalent to 6.022 × 10^23,
// 1.234 × 10^3 = 12.34 × 10^2 = 123.4 × 10^1 = 1234
// 1.234E3 = 12.34E2 = 123.4E1 = 1234
// 0 × 10^0 = 0E0 = 0 × 1 = 0

#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <string>
#include "BigInt.h"

class ParsedBigFloat
{
    std::string mantissa_sign_;
    std::string integer_part_;
    std::string fractional_part_;
    std::string exponent_sign_;
    std::string exponent_;

    std::string decimal_form_;

public:
    ParsedBigFloat::BigFloat();
    ParsedBigFloat( const BigInt& bigInteger );
    ParsedBigFloat::BigFloat( const std::string& number );

    void to_decimal_form()
    {
        // TODO
    }
    std::string get_decimal_form()
    {
        // TODO
    }
};

class BigFloat
{
    std::string number_;

public:
    BigFloat();

    explicit BigFloat( const std::string& number );

    BigFloat( const ParsedBigFloat& pbf);

    BigFloat operator/( const BigFloat& divider );

    friend std::ostream& operator<<
        (
            std::ostream& os,
            const BigFloat& number
        );
};

#endif // BIGFLOAT_H