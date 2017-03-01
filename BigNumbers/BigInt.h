#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include "BigFloat.h"

class BigInt
{
    std::string number_;

public:
    BigInt();

    explicit BigInt( const std::string& number );

    BigInt( const BigInt& obj );

    BigInt operator=( const BigInt& obj );
    BigInt operator=( const std::string& obj );
/*
    BigInt operator/( const BigInt& number ) const;

    BigInt operator/( const BigFloat& number ) const;
*/
    friend std::ostream& operator<<
        (
            std::ostream& os,
            const BigInt& number
        );
};

#endif // BIGINT_H
