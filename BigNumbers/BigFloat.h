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
    std::string number_;
    MODE mode_;

public:

    enum MODE { DECIMAL, SCIENTIFIC };

    BigFloat();

    BigFloat(const std::string& number_in_scientific_notation );

    BigFloat( const BigInt& bigInteger );

    void convert_to( MODE mode );

    BigFloat operator/( const BigFloat& divider );

    friend std::ostream& operator<<
        (
            std::ostream& os,
            const BigFloat& bf
        );

    friend std::istream& operator>>
        (
            std::istream& is,
            BigFloat& bf
        );
};

#endif // BIGFLOAT_H
