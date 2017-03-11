#include "bn_tests.h"
#include "bn_functions.h"
#include "BigInt.h"
#include "BigFloat.h"

enum ChosenTest
{
    TEST1_DEFAULT_CTOR = 1,

    TEST2_CTOR1_ARG_EXP_NOTATION_STR,
    TEST3_CTOR2_ARG_EXP_NOTATION_STR,
    TEST4_CTOR1_ARG_DEC_NOTATION_STR,
    TEST5_CTOR2_ARG_DEC_NOTATION_STR,

    TEST6_INPUT_BY_USER,

    TEST7_SUBTRACTION_OF_TWO_BIG_INTEGERS,
    TEST8_SUBTRACTION_OF_TWO_BIG_FLOATS,
    TEST9_SUBTRACTION_OF_BIG_INTEGER_AND_BIG_FLOAT,
    TEST10_SUBTRACTION_OF_BIG_FLOAT_AND_BIG_INTEGER,

    TEST11_COMPARE_TWO_BIG_INTEGERS,
    TEST12_COMPARE_TWO_BIG_INTEGERS,
    TEST13_COMPARE_TWO_BIG_INTEGERS,

    TEST14_COMPARE_TWO_BIG_FLOATS,
    TEST15_COMPARE_TWO_BIG_FLOATS,
    TEST16_COMPARE_TWO_BIG_FLOATS,

    TEST17_CHECKERS_OF_BIG_FLOAT_CLASS,
    TEST18_CHANGERS_OF_BIG_FLOAT_CLASS,
    TEST19_GETTERS_OF_BIG_FLOAT_CLASS,
    TEST20_SETTERS_OF_BIG_FLOAT_CLASS
};

void menu()
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

void set_test( std::string choice )
{
    std::cout
        << "Choose the number of the test you want to run:\n"
        << " 1 - to test default constructor;\n\n"

        << " 2 - to test constructor with 1 parameter - string that represent number in exponent notation (test 1);\n"
        << " 3 - to test constructor with 1 parameter - string that represent number in exponent notation (test 2);\n"
        << " 4 - to test constructor with 1 parameter - string that represent number in decimal notation (test 1);\n"
        << " 5 - to test constructor with 1 parameter - string that represent number in decimal notation (test 2);\n\n"

        << " 6 - to test overloaded << operator (input number by user).\n\n"

        << " 7 - to test overloaded operator- (subtraction of two big integers).\n"
        << " 8 - to test overloaded operator- (subtraction of two big floats).\n"
        << " 9 - to test overloaded operator- (subtraction of big integer and big float).\n"
        << "10 - to test overloaded operator- (subtraction of big float and big integer).\n\n"

        << "11 - to test overloaded comparison operators ( BigInt::operator<, BigInt::operator>, BigInt::operator==).\n"
        << "12 - to test overloaded comparison operators ( BigInt::operator<=, BigInt::operator>).\n"
        << "13 - to test overloaded comparison operators ( BigInt::operator>=, BigInt::operator<).\n\n"

        << "14 - to test overloaded comparison operators ( BigFloat::operator<, BigFloat::operator>, BigFloat::operator==).\n"
        << "15 - to test overloaded comparison operators ( BigFloat::operator<=, BigFloat::operator>).\n"
        << "16 - to test overloaded comparison operators ( BigFloat::operator>=, BigFloat::operator<).\n\n"

        << "17 - to test function members of class BigFloat (checkers).\n"
        << "18 - to test function members of class BigFloat (changers).\n"
        << "19 - to test function members of class BigFloat (getters).\n"
        << "20 - to test function members of class BigFloat (setters).\n\n"
           ;

    BigInt bi1;
    BigInt bi2;
    BigFloat bf1;
    BigFloat bf2;

    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case TEST1_DEFAULT_CTOR:
        test_default_ctor();
        break;

    case TEST2_CTOR1_ARG_EXP_NOTATION_STR:
        test1_ctor_arg_exp_notation_str();
        break;

    case TEST3_CTOR2_ARG_EXP_NOTATION_STR:
        test2_ctor_arg_exp_notation_str();
        break;

    case TEST4_CTOR1_ARG_DEC_NOTATION_STR:
        test1_ctor_arg_dec_notation_str();
        break;

    case TEST5_CTOR2_ARG_DEC_NOTATION_STR:
        test2_ctor_arg_dec_notation_str();
        break;

    case TEST6_INPUT_BY_USER:
        test_input_operator();
        break;

    case TEST7_SUBTRACTION_OF_TWO_BIG_INTEGERS:
        test_subtraction_of_two_numbers( bi1, bi2 );
        break;


    case TEST8_SUBTRACTION_OF_TWO_BIG_FLOATS:
        test_subtraction_of_two_numbers( bf1, bf2 );
        break;

    case TEST9_SUBTRACTION_OF_BIG_INTEGER_AND_BIG_FLOAT:
        test_subtraction_of_two_numbers( bi1, bf1 );
        break;

    case TEST10_SUBTRACTION_OF_BIG_FLOAT_AND_BIG_INTEGER:
        test_subtraction_of_two_numbers( bf1, bi1 );
        break;

    case TEST11_COMPARE_TWO_BIG_INTEGERS:
        test1_comparison_operators( bi1, bi2 );
        break;

    case TEST12_COMPARE_TWO_BIG_INTEGERS:
        test2_comparison_operators( bi1, bi2 );
        break;

    case TEST13_COMPARE_TWO_BIG_INTEGERS:
        test3_comparison_operators( bi1, bi2 );
        break;

    case TEST14_COMPARE_TWO_BIG_FLOATS:
        test1_comparison_operators( bf1, bf2 );
        break;

    case TEST15_COMPARE_TWO_BIG_FLOATS:
        test2_comparison_operators( bf1, bf2 );
        break;

    case TEST16_COMPARE_TWO_BIG_FLOATS:
        test3_comparison_operators( bf1, bf2 );
        break;

    case TEST17_CHECKERS_OF_BIG_FLOAT_CLASS:
        test_checkers();
        break;

    case TEST18_CHANGERS_OF_BIG_FLOAT_CLASS:
        test_changers();
        break;

    case TEST19_GETTERS_OF_BIG_FLOAT_CLASS:
        test_getters();
        break;

    case TEST20_SETTERS_OF_BIG_FLOAT_CLASS:
        test_setters();
        break;

    default:
        std::cout << "Incorrect input.\n";
        break;

    } // endof switch
}

void test_default_ctor()
{
    BigFloat x;

    std::cout
        << "The number x constructed by default ctor:\n"
        << x
        << "\n";
}

void test1_ctor_arg_exp_notation_str()
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

    std::cout
        << "The number a: " << a << "\n"
        << "The number b: " << b << "\n"
        << "The number c: " << c << "\n"
        << "The number d: " << d << "\n"
        << "The number e: " << e << "\n"
        << "The number f: " << f << "\n"
        << "The number g: " << g << "\n"
        << "The number h: " << h << "\n"
        << "The number i: " << i << "\n"
        << "The number j: " << j << "\n"
        << "The number k: " << k << "\n"
        << "The number l: " << l << "\n"
           ;
}

void test2_ctor_arg_exp_notation_str()
{
    BigFloat a ( "+1.234 e-5" );
    BigFloat b ( "-1.234 e-5" );
    BigFloat c ( "1.234 e-5" );

    BigFloat d ( "+1.234 e+5" );
    BigFloat e ( "-1.234 e+5" );
    BigFloat f ( "1.234 e+5" );

    BigFloat g ( "+0.234 e-5" );
    BigFloat h ( "-0.234 e-5" );
    BigFloat i ( "0.234 e-5" );

    BigFloat j ( "+0.234 e+5" );
    BigFloat k ( "-0.234 e+5" );
    BigFloat l ( "0.234 e+5" );

    std::cout
        << "The number a: " << a << "\n"
        << "The number b: " << b << "\n"
        << "The number c: " << c << "\n\n"

        << "The number d: " << d << "\n"
        << "The number e: " << e << "\n"
        << "The number f: " << f << "\n\n"

        << "The number g: " << g << "\n"
        << "The number h: " << h << "\n"
        << "The number i: " << i << "\n\n"

        << "The number j: " << j << "\n"
        << "The number k: " << k << "\n"
        << "The number l: " << l << "\n"
           ;
}

void test1_ctor_arg_dec_notation_str()
{
    BigFloat a ( "+1.2" );
    BigFloat b ( "-1.2" );
    BigFloat c ( "1.2" );

    BigFloat d ( "+0.123456789" );
    BigFloat e ( "-0.123456789" );
    BigFloat f ( "0.123456789" );

    BigFloat g ( "+12345678.9" );
    BigFloat h ( "-12345678.9" );
    BigFloat i ( "12345678.9" );

    BigFloat j ( "+12345.6789" );
    BigFloat k ( "-12345.6789" );
    BigFloat l ( "12345.6789" );

    std::cout
        << "The number a: " << a << "\n"
        << "The number b: " << b << "\n"
        << "The number c: " << c << "\n\n"

        << "The number d: " << d << "\n"
        << "The number e: " << e << "\n"
        << "The number f: " << f << "\n\n"

        << "The number g: " << g << "\n"
        << "The number h: " << h << "\n"
        << "The number i: " << i << "\n\n"

        << "The number j: " << j << "\n"
        << "The number k: " << k << "\n"
        << "The number l: " << l << "\n"
           ;
}

void test2_ctor_arg_dec_notation_str()
{
    BigFloat a ( "+0.0001" );
    BigFloat b ( "-0.0001" );
    BigFloat c ( "0.0001" );

    BigFloat d ( "+0.000000002" );
    BigFloat e ( "-0.000000002" );
    BigFloat f ( "0.000000002" );

    BigFloat g ( "+0.000000000000000000000000000003" );
    BigFloat h ( "-0.000000000000000000000000000003" );
    BigFloat i ( "0.000000000000000000000000000003" );

    BigFloat j ( "+0.012345678901234567890123456789" );
    BigFloat k ( "-0.012345678901234567890123456789" );
    BigFloat l ( "0.012345678901234567890123456789" );

    std::cout
        << "The number a: " << a << "\n"
        << "The number b: " << b << "\n"
        << "The number c: " << c << "\n\n"

        << "The number d: " << d << "\n"
        << "The number e: " << e << "\n"
        << "The number f: " << f << "\n\n"

        << "The number g: " << g << "\n"
        << "The number h: " << h << "\n"
        << "The number i: " << i << "\n\n"

        << "The number j: " << j << "\n"
        << "The number k: " << k << "\n"
        << "The number l: " << l << "\n"
           ;
}

void test_input_operator()
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

// Yes, templates help us to avoid duplicating
// code, but we can't use templates, right?

// arithmetic operators
void test_subtraction_of_two_numbers( BigInt & a, BigInt & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter a minuend: ";
        std::cin >> a;
        std::cout << "Enter a subtrahend: ";
        std::cin >> b;
        BigInt difference = a - b;
        std::cout << "a - b = " << difference;
        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test_subtraction_of_two_numbers( BigFloat & a, BigFloat & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter a minuend: ";
        std::cin >> a;
        std::cout << "Enter a subtrahend: ";
        std::cin >> b;
        BigFloat difference = a - b;
        std::cout << "a - b = " << difference;
        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test_subtraction_of_two_numbers( BigInt & a, BigFloat & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter a minuend: ";
        std::cin >> a;
        std::cout << "Enter a subtrahend: ";
        std::cin >> b;
        BigFloat difference = a - b;
        std::cout << "a - b = " << difference;
        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test_subtraction_of_two_numbers( BigFloat & a, BigInt & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter a minuend: ";
        std::cin >> a;
        std::cout << "Enter a subtrahend: ";
        std::cin >> b;
        BigFloat difference = a - b;
        std::cout << "a - b = " << difference;
        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

// comparison operators for class BigInt
void test1_comparison_operators( BigInt & a, BigInt & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a == b )
        {
            std::cout << "a == b\n";
        }
        else if ( a < b )
        {
            std::cout << "a < b\n";
        }
        else if ( a > b )
        {
            std::cout << "a > b\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test2_comparison_operators( BigInt & a, BigInt & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a <= b )
        {
            std::cout << "a <= b\n";
        }
        else
        {
            std::cout << "a > b\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test3_comparison_operators(BigInt &a, BigInt &b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a >= b )
        {
            std::cout << "a >= b\n";
        }
        else
        {
            std::cout << "a < b\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

// comparison operators for class BigFloat
void test1_comparison_operators( BigFloat & a, BigFloat & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a == b )
        {
            std::cout << "a == b\n";
        }
        else if ( a < b )
        {
            std::cout << "a < b\n";
        }
        else if ( a > b )
        {
            std::cout << "a > b\n";
        }
        else
        {
            std::cout << "Some strange error is here.\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test2_comparison_operators( BigFloat &a, BigFloat &b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a <= b )
        {
            std::cout << "a <= b\n";
        }
        else
        {
            std::cout << "a > b\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

void test3_comparison_operators( BigFloat & a, BigFloat & b )
{
    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout << "Enter 1st operand: ";
        std::cin >> a;
        std::cout << "Enter 2nd operand: ";
        std::cin >> b;

        if ( a >= b )
        {
            std::cout << "a >= b\n";
        }
        else
        {
            std::cout << "a < b\n";
        }

        std::cout << "\nDo you want proceed this test? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";
    }
}

// function members of class BigFloat
void test_checkers()
{
    // TODO
}

void test_changers()
{
    // TODO
}

void test_getters()
{
    // TODO
}

void test_setters()
{
    // TODO
}
