#ifndef BN_FUNCTIONS_H
#define BN_FUNCTIONS_H

bool is_sign( const char ch );

bool is_digit( const char ch );

bool is_one_digit( const std::string& number );

bool is_correct( const BigInt& bi );

bool is_correct( const BigFloat& bf );


#endif // BN_FUNCTIONS_H
