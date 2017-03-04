#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

class BigInt
{
private:
    std::string number_;

    bool is_correct(const BigInt& bi );

public:
    BigInt();
    BigInt( const std::string& number );
    BigInt( const BigInt& bi );

    BigInt operator=( const BigInt& bi );
    BigInt operator=( const std::string& obj );

    void set_number( const std::string & message );
    std::string number();

    friend std::ostream& operator<<
        (
            std::ostream& os,
            const BigInt& bi
        );
    friend std::istream& operator>>
        (
            std::istream& is,
            BigInt& bi
        );
};

#endif // BIGINT_H
