#ifndef BN_TESTS_H
#define BN_TESTS_H

#include <string>

enum ChosenTest
{
    TEST_DEFAULT_CTOR = 1,
    TEST_CTOR1_ARG_EXP_NOTATION_STR,
    TEST_CTOR2_ARG_EXP_NOTATION_STR,
    TEST_CTOR1_ARG_DEC_NOTATION_STR,
    TEST_CTOR2_ARG_DEC_NOTATION_STR,
    TEST_INPUT_ITERATOR
};

void set_test( std::string choice );

void test1_default_ctor();
void test1_ctor_arg_exp_notation_str();
void test2_ctor_arg_exp_notation_str();
void test1_ctor_arg_dec_notation_str();
void test2_ctor_arg_dec_notation_str();

void test1_input_operator();

#endif // BN_TESTS_H
