/*
Смоделировать операцию деления целого числа длиной до 30 десятичных цифр на
действительное число в форме (zn)m.n Е N, где суммарная длина мантиссы (m+n)
– до 30 значащих цифр, а величина порядка N – до 5 цифр.

Результат выдать в форме (zn)0.m1 Е N1.

Условные обозначения (zn) – знак числа N, N1 – величина порядка E – основание
числа. Запись числа (zn)0.m Е N соответствует следующей записи числа
N mzn 10 *. 0) ( . Например, число 2.5 можно записать в виде: +0.25 E+1.

Порядок выполнения работы:
1.  Определить структуру данных для хранения длинного числа.
2.  Предусмотреть ввод и вывод чисел обязательно в том формате, который указан
    в задании.
3.  Разбивать число на составляющие при вводе нельзя (т.е. число должно
    считываться сразу полностью).
4.  STL не пользоваться.
*/

#include <string>
#include <iostream>
#include "bn_tests.h"
#include "bn_functions.h"

int main()
{
    enum ChosenTest
    {
        TEST_DEFAULT_CTOR = 1,
        TEST_CTOR1_ARG_EXP_NOTATION_STR,
        TEST_CTOR2_ARG_EXP_NOTATION_STR,
        TEST_CTOR1_ARG_DEC_NOTATION_STR,
        TEST_CTOR2_ARG_DEC_NOTATION_STR,
        TEST_INPUT_ITERATOR
    };

    std::string choice = "y";
    while( choice[0] == 'y' || choice[0] == 'Y' )
    {
        std::cout
            << "Choose the number of the test you want to run:\n"
            << "1 - to test default constructor;\n"
            << "2 - to test constructor with 1 parameter - string that represent number in exponent notation (test 1);\n"
            << "3 - to test constructor with 1 parameter - string that represent number in exponent notation (test 2);\n"
            << "4 - to test constructor with 1 parameter - string that represent number in decimal notation (test 1);\n"
            << "5 - to test constructor with 1 parameter - string that represent number in decimal notation (test 2);\n"
            << "6 - to test overloaded << operator.\n"
               ;

        std::cin >> choice;
        switch ( string_to_number( choice ) )
        {
        case TEST_DEFAULT_CTOR:
            test1_default_ctor();
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

        case TEST_INPUT_ITERATOR:
            test1_input_operator();
            break;

        default:
            std::cout << "Incorrect input.\n";
            break;

        } // endof switch

        std::cout << "\nDo you want proceed work with the program? (y /n) ";
        std::cin >> choice;
        std::cout << "\n";

    } // endof while( choice[0] == 'y' || choice[0] == 'Y' )

    return 0;
}
