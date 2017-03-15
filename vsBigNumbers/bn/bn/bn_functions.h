#ifndef BN_FUNCTIONS_H
#define BN_FUNCTIONS_H

#include "stdafx.h"
//#include "BigInt.h"
//#include "BigFloat.h"

// Or use standard functions from cctype header.

// checkers ====================================================================
bool contains_one_dot_only(const std::string& number);
bool is_digit(const char ch);
bool is_dot(const char ch);
bool is_one_char(const std::string& number);
bool is_sign(const char ch);
bool is_space(const char ch);


// finders =====================================================================
// Returns position of character if it has been found
// in string str or size of string otherwise:
size_t char_position(const std::string& str, const char ch);


// changers ====================================================================
// Erases part of string str from position first to position last inclusive:
void erase_part_of(std::string& str, const size_t first, const size_t last);

// Inserts string ins before position pos
void insert_to(std::string& str, const std::string& ins, const size_t pos);

void pop_back(std::string &str);
void pop_front(std::string &str);

void push_back(std::string& str, const std::string& substr);
void push_back(std::string& str, const char ch);

void push_front(std::string& str, const std::string& substr);
void push_front(std::string& str, const char ch);

// Reverse elements of string:
void reverse(std::string& str);


// converters ==================================================================
size_t char_to_digit(const char ch);
char digit_to_char(const size_t num);
std::string number_to_string(size_t number);
size_t string_to_number(const std::string& str);


// math functions ==============================================================
// Because we can't use STL. Otherwise we can use std::pow() from cmath header.
size_t pow(size_t base, size_t exp);

#endif // BN_FUNCTIONS_H