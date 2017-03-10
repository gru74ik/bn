#include "bn_tests.h"
#include "bn_functions.h"
#include "BigInt.h"
#include "BigFloat.h"

void test1_default_ctor()
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
