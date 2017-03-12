#ifndef BIGFLOATTESTER_H
#define BIGFLOATTESTER_H

#include "BigInt.h"
#include "BigFloat.h"

class BigFloatTester : public BigFloat
{
public:
    enum SelectedFunctionGroup
    {
        CTORS = 1,
        CHECKERS,
        CHANGERS,
        GETTERS,
        SETTERS,
        COMPARISON_OPS,
        ASSIGNMENT_OPS,
        ARITHMETIC_OPS,
        INPUT_OUTPUT_OPS
    };

    enum Ctor
    {
        DEFAULT = 1,
        WITH_STRING_AS_PARAM,
        WITH_BIG_INT_AS_PARAM,
        COPY
    };

    enum Checker
    {
        IS_SCIENTIFIC = 5,
        IS_DECIMAL,
        IS_LESS_THAN_ZERO,
        IS_GREATER_THAN_ZERO,
        IS_CORRECT
    };

    enum Changer
    {
        DISCARD_SIGN = 10,
        MOVE_FLOATING_POINT,
        CONVERT_TO,
        PUSH_FRONT_ADDITIONAL_ZEROES,
        PUSH_BACK_ADDITIONAL_ZEROES,
        POP_FRONT_EXTRA_ZEROES,
        POP_BACK_EXTRA_ZEROES
    };

    enum Getter
    {
        DOT_POSITION,
        DIGITS_AFTER_DOT,
        DIGITS_BEFORE_DOT,
        E_POSITION,
        DIGITS_AFTER_E,
        E_VALUE_AS_NUMBER,
        E_VALUE_AS_STRING,
        LEAD_ZEROES,
        E_SIGN_POSITION,
        E_SIGN,
        LAST_DIGIT_POSITION,
        POSITION_AFTER,
        POSITION_BEFORE,
        SPACE_POSITION,
        SIGN,
        MANTISSA,
        NUMBER,
        NOTATION
    };

    enum Setter
    {
        SET_NUMBER,
        RESET,
        MARK_AS_WRONG
    };

    enum ComparisonOps
    {
        OP_LESS_THAN,
        OP_LESS_THAN_OR_EQUAL_TO,
        OP_GREATER_THAN,
        OP_GREATER_THAN_OR_EQUAL_TO,
        OP_EQUAL_TO
    };

    enum AssignmentOps
    {
        ASSIGNMENT_OP_WITH_BIG_FLOAT_AS_PARAM,
        ASSIGNMENT_OP_WITH_STRING_AS_PARAM
    };

    enum ArithmeticOps
    {
        ADDITION_WITH_BIG_FLOAT_AS_PARAM,
        SUBTRACTION_WITH_BIG_FLOAT_AS_PARAM,
        MULTIPLICATION_WITH_BIG_FLOAT_AS_PARAM,
        DIVISION_WITH_BIG_FLOAT_AS_PARAM,

        ADDITION_WITH_BIG_INT_AS_PARAM,
        SUBTRACTION_WITH_BIG_INT_AS_PARAM,
        MULTIPLICATION_WITH_BIG_INT_AS_PARAM,
        DIVISION_WITH_BIG_INT_AS_PARAM
    };

    enum InputOutputOps
    {
        INPUT_OP,
        OUTPUT_OP
    };

    void menu();
    void choose_group();

    // choosers
    void choose_ctor();
    void choose_checker();
    void choose_changer();
    void choose_getter();
    void choose_setter();
    void choose_comparison_ops();
    void choose_assignment_ops();
    void choose_arithmetic_ops();
    void choose_io_ops();

    // to test constructors:
    void big_float_default_ctor();
    void big_float_ctor_with_str_as_param();
    void big_float_ctor_with_bigint_as_param();
    void big_float_copy_ctor();

    // to test checkers:
    void is_scientific();
    void is_decimal();
    void is_less_than_zero();
    void is_greater_than_zero();

    // to test changers:
    void discard_sign();
    void move_floating_point();
    void convert_to();

    void push_front_additional_zeroes();
    void push_back_additional_zeroes();
    void pop_front_extra_zeroes();
    void pop_back_extra_zeroes();

    // to test getters:
    void dot_position();
    void digits_before_dot();
    void digits_after_dot();
    void last_digit_position();

    void space_position();

    void e_sign();
    void e_sign_position();
    void e_position();
    void digits_after_e();
    void e_value_as_number();
    void e_value_as_string();

    void position_before( size_t pos );
    void position_after( size_t pos );

    void sign();
    void lead_zeroes();
    void mantissa();
    void number();
    void notation();

    // to test setters:
    void set_number();
    void reset();
    void mark_as_wrong();

    // to test comparison operators:
    void op_less_than();
    void op_less_than_or_equal_to();
    void op_greater_than();
    void op_greater_than_or_equal_to();
    void op_equal_to();

    // to test assignment operators:
    void op_assign_to_big_float();
    void op_assign_to_string();

    // to test arithmetic operators:
    void addition_with_big_float_as_param();
    void subtraction_with_big_float_as_param();
    void multiplication_with_big_float_as_param();
    void division_with_big_float_as_param();

    void addition_with_big_int_as_param();
    void subtraction_with_big_int_as_param();
    void multiplication_with_big_int_as_param();
    void division_with_big_int_as_param();

    // to test input-output operators:
    void input_op();
    void output_op();
};

#endif // BIGFLOATTESTER_H
