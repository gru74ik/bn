#include "BigFloatTester.h"
#include "bn_functions.h"

void BigFloatTester::menu()
{
    std::string choice = "y";
    for( size_t i = 1; choice[0] == 'y' || choice[0] == 'Y'; ++i )
    {
        choose_group();
        std::cout << "\nDo you want proceed work with the program? (y /n) ";
        std::cin >> choice;
        std::cout << "\n===================================================\n";
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

// choosers
void BigFloatTester::choose_ctor()
{
    std::cout
        << "Choose the constructor you want to test:\n"

        << " 1 - default constructors;\n"
        << " 2 - constructor with string as parameter;\n"
        << " 3 - constructor with big integer as parameter;\n"
        << " 4 - copy constructor;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case DEFAULT:
        big_float_default_ctor();
        break;

    case WITH_STRING_AS_PARAM:
        big_float_ctor_with_str_as_param();
        break;

    case WITH_BIG_INT_AS_PARAM:
        big_float_ctor_with_bigint_as_param();
        break;

    case COPY:
        big_float_copy_ctor();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_checker()
{
    std::cout
        << "Choose the checker you want to test:\n"

        << " 1 - is_scientific;\n"
        << " 2 - is_decimal;\n"
        << " 3 - is_less_than_zero;\n"
        << " 4 - is_greater_than_zero;\n"
        << " 5 - is_correct;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case IS_SCIENTIFIC:
        is_scientific();
        break;

    case IS_DECIMAL:
        is_decimal();
        break;

    case IS_LESS_THAN_ZERO:
        is_less_than_zero();
        break;

    case IS_GREATER_THAN_ZERO:
        is_greater_than_zero();
        break;

    case IS_CORRECT:
        is_correct();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_changer()
{
    std::cout
        << "Choose the changer you want to test:\n"

        << " 1 - discard_sign;\n"
        << " 2 - move_floating_point;\n"
        << " 3 - convert_to;\n"
        << " 4 - push_front_additional_zeroes;\n"
        << " 5 - push_back_additional_zeroes;\n"
        << " 6 - pop_front_extra_zeroes;\n"
        << " 7 - pop_back_extra_zeroes;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case DISCARD_SIGN:
        discard_sign();
        break;

    case MOVE_FLOATING_POINT:
        move_floating_point();
        break;

    case CONVERT_TO:
        convert_to();
        break;

    case PUSH_FRONT_ADDITIONAL_ZEROES:
        push_front_additional_zeroes();
        break;

    case PUSH_BACK_ADDITIONAL_ZEROES:
        push_back_additional_zeroes();
        break;

    case POP_FRONT_EXTRA_ZEROES:
        pop_front_extra_zeroes();
        break;

    case POP_BACK_EXTRA_ZEROES:
        pop_back_extra_zeroes();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_getter()
{
    std::cout
        << "Choose the getter you want to test:\n"

        << " 1 - dot_position;\n"
        << " 2 - digits_before_dot;\n"
        << " 3 - digits_after_dot;\n"
        << " 4 - last_digit_position;\n"
        << " 5 - space_position;\n"
        << " 6 - e_sign;\n"
        << " 7 - e_sign_position;\n"
        << " 8 - e_position;\n"
        << " 9 - digits_after_e;\n"
        << "10 - e_value_as_number;\n"
        << "11 - e_value_as_string;\n"
        << "12 - position_before;\n"
        << "13 - position_after;\n"
        << "14 - sign;\n"
        << "15 - lead_zeroes;\n"
        << "16 - number;\n"
        << "17 - notation;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case DOT_POSITION:
        dot_position();
        break;

    case DIGITS_BEFORE_DOT:
        digits_before_dot();
        break;

    case DIGITS_AFTER_DOT:
        digits_after_dot();
        break;

    case LAST_DIGIT_POSITION:
        last_digit_position();
        break;

    case SPACE_POSITION:
        space_position();
        break;

    case E_SIGN:
        e_sign();
        break;

    case E_SIGN_POSITION:
        e_sign_position();
        break;

    case E_POSITION:
        e_position();
        break;

    case DIGITS_AFTER_E:
        digits_after_e();
        break;

    case E_VALUE_AS_NUMBER:
        e_value_as_number();
        break;

    case E_VALUE_AS_STRING:
        e_value_as_string();
        break;

    case POSITION_BEFORE:
        position_before();
        break;

    case POSITION_AFTER:
        position_after();
        break;

    case SIGN:
        sign();
        break;

    case LEAD_ZEROES:
        lead_zeroes();
        break;

    case MANTISSA:
        mantissa();
        break;

    case NUMBER:
        number();
        break;

    case NOTATION:
        notation();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_setter()
{
    std::cout
        << "Choose the setter you want to test:\n"

        << " 1 - set_number;\n"
        << " 2 - reset;\n"
        << " 3 - mark_as_wrong;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case SET_NUMBER:
        set_number();
        break;

    case RESET:
        reset();
        break;

    case MARK_AS_WRONG:
        mark_as_wrong();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_comparison_ops()
{
    std::cout
        << "Choose the comparison operator you want to test:\n"

        << " 1 - operator< (less than);\n"
        << " 2 - operator<= (less than or equal to);\n"
        << " 3 - operator> (greater than);\n"
        << " 4 - operator>= (greater than or equal to);\n"
        << " 5 - operator== (equal to);\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case OP_LESS_THAN:
        op_less_than();
        break;

    case OP_LESS_THAN_OR_EQUAL_TO:
        op_less_than_or_equal_to();
        break;

    case OP_GREATER_THAN:
        op_greater_than();
        break;

    case OP_GREATER_THAN_OR_EQUAL_TO:
        op_greater_than_or_equal_to();
        break;

    case OP_EQUAL_TO:
        op_equal_to();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_assignment_ops()
{
    std::cout
        << "Choose the assignment operator you want to test:\n"

        << " 1 - operator that assings big float to big float;\n"
        << " 2 - operator that assings string to big float;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case ASSIGNMENT_OP_WITH_BIG_FLOAT_AS_PARAM:
        op_assign_big_float_to_big_float();
        break;

    case ASSIGNMENT_OP_WITH_STRING_AS_PARAM:
        op_assign_string_to_big_float();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_arithmetic_ops()
{
    std::cout
        << "Choose the arithmetic operator you want to test:\n"

        << " 1 - addition_with_big_float_as_param;\n"
        << " 2 - subtraction_with_big_float_as_param;\n"
        << " 3 - multiplication_with_big_float_as_param;\n"
        << " 4 - division_with_big_float_as_param;\n"

        << " 5 - addition_with_big_int_as_param;\n"
        << " 6 - subtraction_with_big_int_as_param;\n"
        << " 7 - multiplication_with_big_int_as_param;\n"
        << " 8 - division_with_big_int_as_param;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case ADDITION_WITH_BIG_FLOAT_AS_PARAM:
        addition_with_big_float_as_param();
        break;

    case SUBTRACTION_WITH_BIG_FLOAT_AS_PARAM:
        subtraction_with_big_float_as_param();
        break;

    case MULTIPLICATION_WITH_BIG_FLOAT_AS_PARAM:
        multiplication_with_big_float_as_param();
        break;

    case DIVISION_WITH_BIG_FLOAT_AS_PARAM:
        division_with_big_float_as_param();
        break;

    case ADDITION_WITH_BIG_INT_AS_PARAM:
        addition_with_big_int_as_param();
        break;

    case SUBTRACTION_WITH_BIG_INT_AS_PARAM:
        subtraction_with_big_int_as_param();
        break;

    case MULTIPLICATION_WITH_BIG_INT_AS_PARAM:
        multiplication_with_big_int_as_param();
        break;

    case DIVISION_WITH_BIG_INT_AS_PARAM:
        division_with_big_int_as_param();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void BigFloatTester::choose_io_ops()
{
    std::cout
        << "Choose the input-output operator you want to test:\n"

        << " 1 - input operator;\n"
        << " 2 - output operator;\n"
           ;
    std::string choice;
    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case INPUT_OP:
        input_op();
        break;

    case OUTPUT_OP:
        output_op();
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

void BigFloatTester::big_float_ctor_with_str_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::big_float_ctor_with_bigint_as_param()
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

void BigFloatTester::is_correct()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

// to test changers:
void BigFloatTester::discard_sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::move_floating_point()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::convert_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


void BigFloatTester::push_front_additional_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::push_back_additional_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::pop_front_extra_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::pop_back_extra_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test getters:
void BigFloatTester::dot_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::digits_before_dot()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::digits_after_dot()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::last_digit_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::space_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::e_sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::e_sign_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::e_position()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::digits_after_e()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::e_value_as_number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::e_value_as_string()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::position_before()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::position_after()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::sign()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::lead_zeroes()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::mantissa()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::notation()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test setters:
void BigFloatTester::set_number()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::reset()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::mark_as_wrong()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test comparison operators:
void BigFloatTester::op_less_than()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::op_less_than_or_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::op_greater_than()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::op_greater_than_or_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::op_equal_to()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test assignment operators:
void BigFloatTester::op_assign_big_float_to_big_float()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::op_assign_string_to_big_float()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test arithmetic operators:
void BigFloatTester::addition_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::subtraction_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::multiplication_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::division_with_big_float_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


void BigFloatTester::addition_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::subtraction_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::multiplication_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::division_with_big_int_as_param()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}


// to test input-output operators:
void BigFloatTester::input_op()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}

void BigFloatTester::output_op()
{
    // TODO
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again a little bit later.\n";
}
