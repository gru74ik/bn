#ifndef BN_TESTS_H
#define BN_TESTS_H

#include <string>
#include "BigInt.h"
#include "BigFloat.h"

void set_test( std::string choice );

void test_default_ctor();

void test1_ctor_arg_exp_notation_str();
void test2_ctor_arg_exp_notation_str();
void test1_ctor_arg_dec_notation_str();
void test2_ctor_arg_dec_notation_str();

void test_input_operator();

// Yes, templates help us to avoid duplicating
// code, but we can't use templates, right?
void test_subtraction_of_two_numbers( BigInt & a, BigInt & b );
void test_subtraction_of_two_numbers( BigFloat & a, BigFloat & b );
void test_subtraction_of_two_numbers( BigInt & a, BigFloat & b );
void test_subtraction_of_two_numbers( BigFloat & a, BigInt & b );

#endif // BN_TESTS_H
