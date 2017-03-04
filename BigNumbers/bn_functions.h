#ifndef BN_FUNCTIONS_H
#define BN_FUNCTIONS_H

#include "BigInt.h"
#include "BigFloat.h"

bool is_sign( const char ch );

bool is_digit( const char ch );

bool is_one_char( const std::string& number );

bool contains_one_dot_only( const std::string& number );

#endif // BN_FUNCTIONS_H
