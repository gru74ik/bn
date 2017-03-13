#include "BigFloatTester.h"
#include "bn_functions.h"

void BigFloatTester::menu()
{
    std::string choice = "y";
    for( size_t i = 1; choice[0] == 'y' || choice[0] == 'Y'; ++i )
    {
        choose_group();
        std::cout << "Do you want proceed work with the program? (y /n) ";
        std::cin >> choice;
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
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the constructor you want to test:\n"

            << " 1 - default constructors;\n"
            << " 2 - constructor with string as parameter;\n"
            << " 3 - constructor with big integer as parameter;\n"
            << " 4 - copy constructor;\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_checker()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the checker you want to test:\n"

            << " 1 - is_scientific;\n"
            << " 2 - is_decimal;\n"
            << " 3 - is_less_than_zero;\n"
            << " 4 - is_greater_than_zero;\n"
            << " 5 - is_correct;\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_changer()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_getter()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_setter()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the setter you want to test:\n"

            << " 1 - set_number;\n"
            << " 2 - reset;\n"
            << " 3 - mark_as_wrong;\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_comparison_ops()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the comparison operator you want to test:\n"

            << " 1 - operator< (less than);\n"
            << " 2 - operator<= (less than or equal to);\n"
            << " 3 - operator> (greater than);\n"
            << " 4 - operator>= (greater than or equal to);\n"
            << " 5 - operator== (equal to);\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_assignment_ops()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the assignment operator you want to test:\n"

            << " 1 - operator that assings big float to big float;\n"
            << " 2 - operator that assings string to big float;\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_arithmetic_ops()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
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

        std::cout << "Do you want continue testing arithmetic operators? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
}

void BigFloatTester::choose_io_ops()
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the input-output operator you want to test:\n"

            << " 1 - input operator;\n"
            << " 2 - output operator;\n"
               ;

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

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
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
    BigFloat a ( "+1.234 E-5" );
    BigFloat b ( "-1.234 E-5" );
    BigFloat c ( "1.234 E-5" );

    BigFloat d ( "+1.234 E+5" );
    BigFloat e ( "-1.234 E+5" );
    BigFloat f ( "1.234 E+5" );

    BigFloat g ( "+0.234 E-5" );
    BigFloat h ( "-0.234 E-5" );
    BigFloat i ( "0.234 E-5" );

    BigFloat j ( "+0.234 E+5" );
    BigFloat k ( "-0.234 E+5" );
    BigFloat l ( "0.234 E+5" );

    BigFloat m ( "+1.234 e-5" );
    BigFloat n ( "-1.234 e-5" );
    BigFloat o ( "1.234 e-5" );

    BigFloat p ( "+1.234 e+5" );
    BigFloat q ( "-1.234 e+5" );
    BigFloat r ( "1.234 e+5" );

    BigFloat s ( "+0.234 e-5" );
    BigFloat t ( "-0.234 e-5" );
    BigFloat u ( "0.234 e-5" );

    BigFloat v ( "+0.234 e+5" );
    BigFloat w ( "-0.234 e+5" );
    BigFloat x ( "0.234 e+5" );

    BigFloat y ( "0" );
    BigFloat z ( "deliberate_error" );

    std::cout
        << "BigFloat a ( \"+1.234 E-5\" ): " << a << "\n"
        << "BigFloat b ( \"-1.234 E-5\" ): " << b << "\n"
        << "BigFloat c ( \"1.234 E-5\" ): " << c << "\n\n"

        << "BigFloat d ( \"+1.234 E+5\" ): " << d << "\n"
        << "BigFloat e ( \"-1.234 E+5\" ): " << e << "\n"
        << "BigFloat f ( \"1.234 E+5\" ): " << f << "\n\n"

        << "BigFloat g ( \"+0.234 E-5\" ): " << g << "\n"
        << "BigFloat h ( \"-0.234 E-5\" ): " << h << "\n"
        << "BigFloat i ( \"0.234 E-5\" ): " << i << "\n\n"

        << "BigFloat j ( \"+0.234 E+5\" ): " << j << "\n"
        << "BigFloat k ( \"-0.234 E+5\" ): " << k << "\n"
        << "BigFloat l ( \"0.234 E+5\" ): " << l << "\n\n"

        << "BigFloat m ( \"+1.234 e-5\" ): " << m << "\n"
        << "BigFloat n ( \"-1.234 e-5\" ): " << n << "\n"
        << "BigFloat o ( \"1.234 e-5\" ): " << o << "\n\n"

        << "BigFloat p ( \"+1.234 e+5\" ): " << p << "\n"
        << "BigFloat q ( \"-1.234 e+5\" ): " << q << "\n"
        << "BigFloat r ( \"1.234 e+5\" ): " << r << "\n\n"

        << "BigFloat s ( \"+0.234 e-5\" ): " << s << "\n"
        << "BigFloat t ( \"-0.234 e-5\" ): " << t << "\n"
        << "BigFloat u ( \"0.234 e-5\" ): " << u << "\n\n"

        << "BigFloat v ( \"+0.234 e+5\" ): " << v << "\n"
        << "BigFloat w ( \"-0.234 e+5\" ): " << w << "\n"
        << "BigFloat x ( \"0.234 e+5\" ): " << x << "\n\n"

        << "BigFloat y ( \"0\" ): " << y << "\n"
        << "BigFloat z ( \"deliberate_error\" ): " << z << "\n"
           ;
}

void BigFloatTester::big_float_ctor_with_bigint_as_param()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::big_float_copy_ctor()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

// to test checkers:
void BigFloatTester::is_scientific()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::is_decimal()
{
    BigFloat x( "0.0001" );
    if ( x.is_decimal() )
    {
        std::cout <<
            "\nBigFloat x( \"0.0001\" ) is decimal.\n"
            "Function member is_decimal works properly.\n";
    }
    else
    {
        std::cout <<
            "Function member is_decimal works with errors.\n";
    }
}

void BigFloatTester::is_less_than_zero()
{
    BigFloat x( "0.00000000000000000000000000001" );
    if ( x.is_less_than_zero() )
    {
        std::cout <<
            "\nBigFloat x( \"0.0001\" ) is less than zero.\n"
            "Function member is_less_than_zero() works properly.\n";
    }
    else
    {
        std::cout <<
            "Function member is_decimal works with errors.\n";
    }
}

void BigFloatTester::is_greater_than_zero()
{
    BigFloat x( "1.00000000000000000000000000001" );
    if ( x.is_greater_than_zero() )
    {
        std::cout <<
            "\nBigFloat x( \"0.0001\" ) is greater than zero.\n"
            "Function member is_less_than_zero() works properly.\n";
    }
    else
    {
        std::cout <<
            "Function member is_decimal works with errors.\n";
    }
}

void BigFloatTester::is_correct()
{
    BigFloat x( "1.00000000000000000000000000001" );
    if ( x.is_correct( DECIMAL ) )
    {
        std::cout <<
            "\nBigFloat x( \"0.0001\" ) is correct number written in decimal notation.\n"
            "Function member is_less_than_zero() works properly.\n";
    }
    else
    {
        std::cout <<
            "Function member is_decimal works with errors.\n";
    }
}

// to test changers:
void BigFloatTester::discard_sign()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::move_floating_point()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::convert_to()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}


void BigFloatTester::push_front_additional_zeroes()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::push_back_additional_zeroes()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::pop_front_extra_zeroes()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::pop_back_extra_zeroes()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}


// to test getters:
void BigFloatTester::dot_position()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::digits_before_dot()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::digits_after_dot()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::last_digit_position()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::space_position()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::e_sign()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::e_sign_position()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::e_position()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::digits_after_e()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::e_value_as_number()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}
void BigFloatTester::e_value_as_string()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::position_before()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::position_after()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::sign()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::lead_zeroes()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::mantissa()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::number()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::notation()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}


// to test setters:
void BigFloatTester::set_number()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::reset()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::mark_as_wrong()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}


// to test comparison operators:
void BigFloatTester::op_less_than()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::op_less_than_or_equal_to()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::op_greater_than()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::op_greater_than_or_equal_to()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::op_equal_to()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

// to test assignment operators:
void BigFloatTester::op_assign_big_float_to_big_float()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}

void BigFloatTester::op_assign_string_to_big_float()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}


// to test arithmetic operators:
void BigFloatTester::addition_with_big_float_as_param()
{
    /*
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st big float operand: ";
        BigFloat x;
        std::cin >> x;
        std::cout << "Enter 2st big float operand: ";
        BigFloat y;
        std::cin >> y;

        std::cout << "x + y = " << x + y << "\n";

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while
    */

    std::string str;
    BigFloat x;
    BigFloat y;

    for ( int i = 0; i < 10; ++i )
    {
        for ( int i = 0; i < getRandNumber( 1, 30 ); ++i )
        {
           str.push_back( digit_to_char( getRandNumber( 0, 9 ) ) );
        }

        str = str + '.';

        for ( int i = 0; i < getRandNumber( 1, 30 ); ++i )
        {
           str.push_back( digit_to_char( getRandNumber( 0, 9 ) ) );
        }

        x.set_number( str );

        str.clear();

        for ( int i = 0; i < getRandNumber( 1, 30 ); ++i )
        {
           str.push_back( digit_to_char( getRandNumber( 0, 9 ) ) );
        }

        str = str + '.';

        for ( int i = 0; i < getRandNumber( 1, 30 ); ++i )
        {
           str.push_back( digit_to_char( getRandNumber( 0, 9 ) ) );
        }

        y.set_number( str );

        str.clear();

        std::cout << "\nTest #" << i + 1 << "\n";
        std::cout << "x: " << x.number() << "\n";
        std::cout << "y: " << y.number() << "\n";
        std::cout << "x + y = " << x + y << "\n";
    }
}

void BigFloatTester::subtraction_with_big_float_as_param()
{
    BigFloat x( "+6.66666666666666666666666666664 E+5" );
    BigFloat y( "+2.22222222222222222222222222221 E+5" );
    BigFloat result = x - y;
    BigFloat rightAnswer( "4.44444444444444444444444444443 E+5" );
    std::cout << "Function member subtraction_with_big_float_as_param() works ";

    if ( result == rightAnswer )
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}

void BigFloatTester::multiplication_with_big_float_as_param()
{
    BigFloat x( "+4.44444444444444444444444444443 E+5" );
    BigFloat y( "+2.22222222222222222222222222222 E+5" );
    BigFloat result = x * y;
    BigFloat rightAnswer( "98765432098.7654320987654320985" );

    std::cout << "Function member multiplication_with_big_float_as_param() works ";

    if ( result == rightAnswer )
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}

void BigFloatTester::division_with_big_float_as_param()
{
    BigFloat x( "+7.77777777777777777777777777777 E+5" );
    BigFloat y( "+0.12345678901234567890123456789 E+5" );
    BigFloat result = x / y;
    BigFloat rightAnswer( "6300000.05670000051597000469532" );

    std::cout << "Function member division_with_big_float_as_param() works ";

    if ( result == rightAnswer )
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}


void BigFloatTester::addition_with_big_int_as_param()
{
    BigFloat x( "666666.666666666666666666666663" ); // 6.66666666666666666666666666663 E+5
    BigInt y( "222222222222222222222222211111" );
    BigFloat result = x + y;
    BigFloat rightAnswer( "+22222222222222222222222887777.0 E+0" );

    std::cout << "Function member addition_with_big_int_as_param() works ";

    if ( result == rightAnswer ) // 22222222222222222222222887777
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}

void BigFloatTester::subtraction_with_big_int_as_param()
{
    BigFloat x( "666666.666666666666666666666667" ); // 6.66666666666666666666666666667 E+5
    BigInt y( "222222222222222222222222211111" );
    BigFloat result = x - y;
    BigFloat rightAnswer( "-22222222222222222222222887777.0 E+0" );

    std::cout << "Function member subtraction_with_big_int_as_param() works ";

    if ( result == rightAnswer ) // 22222222222222222222222887777
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}

void BigFloatTester::multiplication_with_big_int_as_param()
{
    BigFloat x( "+4.44444444444444444444444444443 E+5" );
    BigInt y( "2.22222222222222222222222222222" );
    BigFloat result = x * y;
    BigFloat rightAnswer( "+8.88888888888888888888888888886  E+5" );

    std::cout << "Function member multiplication_with_big_int_as_param() works ";

    if ( result == rightAnswer )
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}

void BigFloatTester::division_with_big_int_as_param()
{
    BigFloat x( "+7.77777777777777777777777777777 E+5" );
    BigInt y( "123456789012345678901234567890" );
    BigFloat result = x / y;
    BigFloat rightAnswer( "+6.30000005670000051597000469532 E-24" );

    std::cout << "Function member division_with_big_float_as_param() works ";

    if ( result == rightAnswer )
    {
        std::cout << "properly.\n";
    }
    else
    {
        std::cout << "with errors.\n";
    }
}


// to test input-output operators:
void BigFloatTester::input_op()
{
    BigFloat number;

    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter a big float: ";
        number.reset();
        std::cin >> number;
        std::cout << "The number you have entered is " << number;
        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void BigFloatTester::output_op()
{
    // TODO: implement this function
    std::cout <<
        "\nThis test is temporarily unavailable. "
        "Try again later or call to support team.\n";
}
