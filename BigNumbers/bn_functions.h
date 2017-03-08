#ifndef BN_FUNCTIONS_H
#define BN_FUNCTIONS_H

#include "BigInt.h"
#include "BigFloat.h"

bool is_sign( const char ch );
bool is_digit( const char ch );
bool is_dot( const char ch );
bool is_one_char( const std::string& number );
bool contains_one_dot_only( const std::string& number );

size_t char_to_digit( const char ch );
char digit_to_char(const size_t num);
size_t string_to_number( const std::string& str );
std::string number_to_string( size_t number );

// string ins will be inserted before position pos:
void insert_to( std::string& str, const std::string& ins, const size_t pos );

// part of string str will be erased from
// position first to position last inclusive:
void erase_part_of( std::string& str, const size_t first, const size_t last );

size_t pow( size_t base, size_t exp );

#endif // BN_FUNCTIONS_H
