#include "BigFloatTester.h"
#include "bn_functions.h"

void BigFloatTester::menu()
{
    std::string choice = "y";
    for( size_t i = 1; choice[0] == 'y' || choice[0] == 'Y'; ++i )
    {
        std::cout << "Test #" << i << "\n\n";
        set_test( choice );
        std::cout << "\nDo you want proceed work with the program? (y /n) ";
        std::cin >> choice;
        std::cout <<
            "\n===================================================="
            "====================================================\n";
    }
}

void BigFloatTester::choose_group()
{
    std::cout
        << "Choose the group of function members you want to test:\n"

        << " 1 - constructors;\n"
        << " 2 - checkers;\n"
        << " 3 - changers;\n"
        << " 4 - getters;\n"
        << " 5 - setters;\n"
        << " 6 - comparison operators;\n"
        << " 7 - assignment operators;\n"
        << " 8 - arithmetic operators;\n"
        << " 9 - input-output operators;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case CTORS:
        choose_ctor();
        break;

    case CHECKERS:
        choose_checker();
        break;

    case CHANGERS:
        choose_changer();
        break;

    case GETTERS:
        choose_getter();
        break;

    case SETTERS:
        choose_setter();
        break;

    case COMPARISON_OPS:
        choose_comparison_ops();
        break;

    case ASSIGNMENT_OPS:
        choose_assignment_ops();
        break;

    case ARITHMETIC_OPS:
        choose_arithmetic_ops();
        break;

    case INPUT_OUTPUT_OPS:
        choose_io_ops();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

// to test constructors:
void BigFloatTester::big_float_default_ctor()
{
    BigFloat x;

    std::cout
        << "The number x constructed by default ctor:\n"
        << x
        << "\n";
}

void BigFloatTester::big_float_ctor_with_str_as_arg()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::big_float_ctor_with_bigint_as_arg()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::big_float_copy_ctor()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

// to test checkers:
void BigFloatTester::is_scientific()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::is_decimal()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::is_less_than_zero()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::is_greater_than_zero()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

// to test changers:
void discard_sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void move_floating_point()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void convert_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


void push_front_additional_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void push_back_additional_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void pop_front_extra_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void pop_back_extra_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test getters:
void dot_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void digits_before_dot()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void digits_after_dot()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void last_digit_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void space_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void e_sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void e_sign_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void e_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void digits_after_e()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void e_value_as_number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void e_value_as_string()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void position_before( size_t pos )
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void position_after( size_t pos )
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void lead_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void mantissa()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void notation()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test setters:
void set_number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void reset()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void mark_as_wrong()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test comparison operators:
void op_less_than()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void op_less_than_or_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void op_greater_than()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void op_greater_than_or_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void op_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test assignment operators:
void op_assign_to_big_float()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void op_assign_to_string()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test arithmetic operators:
void addition_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void subtraction_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void multiplication_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void division_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


void addition_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void subtraction_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void multiplication_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void division_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test input-output operators:
void input_op()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void output_op()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}
