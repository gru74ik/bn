#ifndef BN_TESTS_H
#define BN_TESTS_H

#include <string>
#include "BigInt.h"
#include "BigFloat.h"

void menu();
void set_test( std::string choice );

void test_default_ctor();

void test1_ctor_arg_exp_notation_str();
void test2_ctor_arg_exp_notation_str();
void test1_ctor_arg_dec_notation_str();
void test2_ctor_arg_dec_notation_str();

void test_input_operator();

// Yes, templates help us to avoid duplicating
// code, but we can't use templates, right?

// arithmetic operators
void test_subtraction_of_two_numbers( BigInt & a, BigInt & b );
void test_subtraction_of_two_numbers( BigFloat & a, BigFloat & b );
void test_subtraction_of_two_numbers( BigInt & a, BigFloat & b );
void test_subtraction_of_two_numbers( BigFloat & a, BigInt & b );

// comparison operators for class BigInt
void test1_comparison_operators( BigInt &a, BigInt &b );
void test2_comparison_operators( BigInt & a, BigInt & b );
void test3_comparison_operators( BigInt & a, BigInt & b );

// comparison operators for class BigFloat
void test1_comparison_operators( BigFloat &a, BigFloat &b );
void test2_comparison_operators( BigFloat & a, BigFloat & b );
void test3_comparison_operators( BigFloat &a, BigFloat &b );

// function members of class BigFloat
void test_checkers();
void test_changers();
void test_getters();
void test_setters();

#endif // BN_TESTS_H
