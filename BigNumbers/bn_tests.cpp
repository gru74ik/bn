#include "bn_tests.h"
#include "bn_functions.h"
#include "BigInt.h"
#include "BigFloat.h"

enum ChosenTest
{
    TEST_DEFAULT_CTOR = 1,
    TEST_CTOR1_ARG_EXP_NOTATION_STR,
    TEST_CTOR2_ARG_EXP_NOTATION_STR,
    TEST_CTOR1_ARG_DEC_NOTATION_STR,
    TEST_CTOR2_ARG_DEC_NOTATION_STR,
    TEST_INPUT_OPERATOR,
    TEST_SUBTRACTION_OF_TWO_BIG_INTEGERS,
    TEST_SUBTRACTION_OF_TWO_BIG_FLOATS,
    TEST_SUBTRACTION_OF_BIG_INTEGER_AND_BIG_FLOAT,
    TEST_SUBTRACTION_OF_BIG_FLOAT_AND_BIG_INTEGER
};

void set_test( std::string choice )
{
    std::cout
        << "Choose the number of the test you want to run:\n"
        << " 1 - to test default constructor;\n"
        << " 2 - to test constructor with 1 parameter - string that represent number in exponent notation (test 1);\n"
        << " 3 - to test constructor with 1 parameter - string that represent number in exponent notation (test 2);\n"
        << " 4 - to test constructor with 1 parameter - string that represent number in decimal notation (test 1);\n"
        << " 5 - to test constructor with 1 parameter - string that represent number in decimal notation (test 2);\n"
        << " 6 - to test overloaded << operator (input number by user).\n"
        << " 7 - to test overloaded - operator (subtraction of two big integers).\n"
        << " 8 - to test overloaded - operator (subtraction of two big floats).\n"
        << " 9 - to test overloaded - operator (subtraction of big integer and big float).\n"
        << "10 - to test overloaded - operator (subtraction of big float and big integer).\n"
           ;

    BigInt bi1;
    BigInt bi2;
    BigFloat bf1;
    BigFloat bf2;

    std::cin >> choice;
    switch ( string_to_number( choice ) )
    {
    case TEST_DEFAULT_CTOR:
        test_default_ctor();
        break;

    case TEST_CTOR1_ARG_EXP_NOTATION_STR:
        test1_ctor_arg_exp_notation_str();
        break;

    case TEST_CTOR2_ARG_EXP_NOTATION_STR:
        test2_ctor_arg_exp_notation_str();
        break;

    case TEST_CTOR1_ARG_DEC_NOTATION_STR:
        test1_ctor_arg_dec_notation_str();
        break;

    case TEST_CTOR2_ARG_DEC_NOTATION_STR:
        test2_ctor_arg_dec_notation_str();
        break;

    case TEST_INPUT_OPERATOR:
        test_input_operator();
        break;

    case TEST_SUBTRACTION_OF_TWO_BIG_INTEGERS:
        test_subtraction_of_two_numbers( bi1, bi2 );
        break;


    case TEST_SUBTRACTION_OF_TWO_BIG_FLOATS:
        test_subtraction_of_two_numbers( bf1, bf2 );
        break;

    case TEST_SUBTRACTION_OF_BIG_INTEGER_AND_BIG_FLOAT:
        test_subtraction_of_two_numbers( bi1, bf1 );
        break;

    case TEST_SUBTRACTION_OF_BIG_FLOAT_AND_BIG_INTEGER:
        test_subtraction_of_two_numbers( bf1, bi1 );
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
