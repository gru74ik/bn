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



// string ins will be inserted before position pos:
void insert_to( std::string& str, const std::string& ins, const size_t pos );

// part of string str will be erased from
// position first to position last inclusive:
void erase_part_of( std::string& str, const size_t first, const size_t last );

#endif // BN_FUNCTIONS_H
