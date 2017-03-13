#include "BigFloat.h"
#include "bn_functions.h"

#include <algorithm> // remove this header when all test will be completed

// #include <cmath> // можно использовать std::pow()

// constructors
BigFloat::BigFloat()
    : sign_( '+' ), number_( "0.0" ), tail_( " E+0" ), notation_( DEFAULT )
{
    //std::cout << "\nDefault constructor has been used.\n";
}

BigFloat::BigFloat( const std::string& number )
{
    number_ = number;
    sign_ = sign();
    discard_sign();
    tail_ = "";
    //std::cout
        //<< "In constructor before converting: "
        //<< sign_ << number_ << "\n";
    if ( is_correct( DECIMAL ) || is_correct( DEFAULT ) )
    {
        // do nothing

        //std::cout
            //<< "\nConstructor will try create object from string"
            //<< "\nthat represent number in decimal notation.\n";

    }
    else if ( is_correct( SCIENTIFIC ) )
    {
        convert_to( DECIMAL );
        //std::cout
            //<< "\nIn constructor after converting: "
            //<< sign_ << number_ << "\n";
        //std::cout
            //<< "\nConstructor will try create object from string"
            //<< "\nthat represent number in scientific notation.\n";
    }
    else
    {
        mark_as_wrong();
        //std::cout
            //<< "\nConstructor tried create object from string\n"
            //<< "but failed, because string is incorrect.\n";
    }
    std::cout << "After all number_ in ctor: " << number_ << "\n";
}

BigFloat::BigFloat( const BigInt& bigInteger )
{
    number_ = bigInteger.number() + ".0";
    sign_ = sign();
    discard_sign();
    tail_ = "";

    if ( is_correct( SCIENTIFIC ) )
    {
        convert_to( DECIMAL );
    }
    else if ( is_correct( DECIMAL ) || is_correct( DEFAULT ) )
    {
        // do nothing
    }
    else
    {
        //std::cout
            //<< "\nConstructor tried create object from BigInt type,\n"
            //<< "but failed, because source is incorrect.\n";
        mark_as_wrong();
    }
}

BigFloat::BigFloat( const BigFloat& bf )
{
    sign_ = bf.sign_;
    number_ = bf.number_;
    tail_ = bf.tail_;
    notation_ = bf.notation_;
}

//checkers
bool BigFloat::is_scientific() const
{
    return is_correct( SCIENTIFIC );
}

bool BigFloat::is_decimal() const
{
    return is_correct( DECIMAL );
}

bool BigFloat::is_correct( Notation notation ) const
{
    bool result = true;

    switch ( notation )
    {
    case SCIENTIFIC:
    {
        //std::cout << "\nThe scientific number notation assertion.\n";
        size_t space_pos = space_position();
        size_t e_pos = e_position();
        size_t e_sign_pos = e_sign_position();

        // проверяем, что строка содержит пробел:
        if ( space_pos == number_.size() )
        {
            result = false;
            //std::cout <<
                //"\nThe scientific number notation is incorrect, because"
                //"\nthe number have to contain 1 space at least.\n";
        }
        // проверяем, что строка содержит букву 'e' или 'E':
        else if ( e_pos == number_.size() )
        {
            result = false;
            //std::cout <<
                //"\nThe scientific number notation is incorrect, because"
                //"\nthe number have to contain 1 letter 'e' or 'E'.\n";
        }
        // проверяем, что строка содержит точку и точка только одна:
        else if ( !contains_one_dot_only( number_ ) )
        {
            result = false;
            //std::cout <<
                //"\nThe scientific number notation is incorrect, because"
                //"\nthe number have to contain 1 dot (no more and no less).\n";
        }
        else
        {
            // проверяем, что до пробела все элементы строки - числа или точка:
            for ( size_t i = 0; i < space_pos; ++i )
            {
                if ( !is_digit( number_[i] ) && !is_dot( number_[i] ) )
                {
                    result = false;
                    //std::cout <<
                        //"\nThe scientific number notation is incorrect, because"
                        //"\nthe number contains forbidden characters before space.\n";
                    break;
                }
            }
            // проверяем, что буква 'e' или 'E' следует сразу за пробелом:
            if ( e_pos != position_after( space_pos ) )
            {
                result = false;
                //std::cout <<
                    //"\nThe scientific number notation is incorrect,"
                    //"\nbecause letter was not found after space.\n";
            }
            // проверяем что за буквой 'e' или 'E' следует знак плюс или минус:
            else if ( !is_sign( number_[e_sign_pos] ) )
            {
                result = false;
                //std::cout <<
                    //"\nThe scientific number notation is incorrect,"
                    //"\nbecause sign was not found after letter.\n";
            }
            else
            {
                // проверяем, что после знака следуют только числа:
                for ( size_t i = position_after( e_sign_pos ); i < number_.size(); ++i )
                {
                    if ( !is_digit( number_[i] ) )
                    {
                        result = false;
                        //std::cout <<
                            //"\nThe scientific number notation is incorrect,"
                            //"\nbecause was found forbidden characters after sign.\n";
                        break;
                    }
                }
            }
        }
        //std::cout
            //<< "\nis_correct( SCIENTIFIC ): "
            //<< std::boolalpha
            //<< result
            //<< std::noboolalpha
            //<< "\n";
        break;
    }

    case DECIMAL:
        //std::cout << "\nThe decimal number notation assertion.\n";
        // проверяем, что строка содержит точку и точка только одна:
        if ( contains_one_dot_only( number_ ) )
        {
            // проверяем, что все элементы строки - числа или точка:
            for ( size_t i = 0; i < number_.size(); ++i )
            {
                if ( !is_digit( number_[i] ) && !is_dot( number_[i] ) )
                {
                    result = false;
                    //std::cout <<
                        //"\nThe decimal notation of this number is incorrect,"
                        //"\nbecause it contains forbidden characters.\n";
                    break;
                }
            }
        }
        else
        {
            result = false;
            //std::cout <<
                //"\nThe decimal notation of this number is incorrect,"
                //"\nbecause it contains more than 1 dot.\n";
        }
        //std::cout
            //<< "\nis_correct( DECIMAL ): "
            //<< std::boolalpha
            //<< result
            //<< std::noboolalpha
            //<< "\n";
        break;

    case DEFAULT:
        if ( number_ != "0" )
        {
            result = false;
            //std::cout << "\nThis number is not equal to zero.\n"
        }
        break;

    default:
        std::cout << "\nError: incorrect function argument\n";
        break;

    } // endof switch ( notation )

    return result;
} // endof is_correct

// changers
void BigFloat::discard_sign()
{
    if ( is_sign( number_[0] ) )
    {
        erase_part_of( number_, 0, 0 );
    }
}

void BigFloat::move_floating_point(Direction dir, size_t shiftSize )
{
    size_t dot_pos = dot_position();

    switch ( dir )
    {
    case RIGHT:
    {
        //std::cout << "\nBigFloat::move_floating_point( RIGHT ) works.\n";
        if ( digits_after_dot() > shiftSize )
        {
            //std::cout
                //<< "\ndigits_after_dot() > shiftSize"
                //<< "\ndigits_after_dot(): " << digits_after_dot()
                //<< "\nshiftSize: " << shiftSize << "\n";
            insert_to( number_ , ".", position_after( dot_pos ) + shiftSize );
        }
        else if ( digits_after_dot() == shiftSize )
        {
            //std::cout
                //<< "\ndigits_after_dot() == shiftSize\n"
                //<< "\ndigits_after_dot(): " << digits_after_dot()
                //<< "shiftSize: " << shiftSize << "\n";
            insert_to( number_ , ".0", position_after( last_digit_position() ) );
        }
        else
        {
            //std::cout
                //<< "\ndigits_after_dot() < shiftSize\n"
                //<< "\ndigits_after_dot(): " << digits_after_dot()
                //<< "\nshiftSize: " << shiftSize << "\n";
            size_t additional_zeroes = shiftSize - digits_after_dot();
            for ( size_t i = 0; i < additional_zeroes; ++i )
            {
                //std::cout
                    //<< "\nI insert zeroes, man!\n";
                insert_to( number_ , "0", position_after( last_digit_position() ) );
            }
            insert_to( number_ , ".0", position_after( last_digit_position() ) );
        }

        erase_part_of( number_, dot_pos, dot_pos );

        break;
    }
    case LEFT:
    {
        size_t digits_before = digits_before_dot();

        std::cout
            <<  "\nWe are in function BigFloat::move_floating_point in section\n"
                "of switch 'case LEFT' and current content of number_ is: "
            << number_
            << "\nand current value of dot_pos is: "
            << dot_pos << "\n\n";

        erase_part_of( number_, dot_pos, dot_pos );

        std::cout
            <<  "\nWe are in function BigFloat::move_floating_point in section\n"
                "of switch 'case LEFT' and current content of number_ after dot erasure is: "
            << number_
            << "\nand current value of dot_pos is: "
            << dot_pos << "\n\n";

        if ( digits_before > shiftSize )
        {
            insert_to( number_ , ".", dot_pos - shiftSize );
        }
        else if ( digits_before == shiftSize )
        {
            insert_to( number_ , "0.", 0 );
        }
        else if ( digits_before < shiftSize )
        {
            size_t additional_zeroes = shiftSize - digits_before;

            size_t i = 0;

            while ( i < additional_zeroes )
            {
                number_ = "0" + number_;
                ++i;
            }

            insert_to( number_ , "0.", 1 );
        }

        break;
    }
    default:
        break;
    }
}

void BigFloat::convert_to(Notation notation )
{
    switch ( notation )
    {
    case SCIENTIFIC:

        if ( dot_position() != 1 )
        {
            size_t shift = position_before( dot_position() );
            move_floating_point( LEFT, shift );
            number_ = number_ + " E+" + number_to_string( shift );

            std::cout <<
                "number_ after converting from decimal to scientific\n"
                "move_floating_point( LEFT ): " << number_ << "\n";
        }
        else
        {
            if ( lead_zeroes() )
            {
                move_floating_point( RIGHT, lead_zeroes() );
                number_ = number_ + " E-" + number_to_string( lead_zeroes() );
                erase_part_of( number_, 0, lead_zeroes() - 1 );
            }
            else
            {
                number_ = number_ + " E+0";
            }
            std::cout <<
                "number_ after converting from decimal to scientific\n"
                "move_floating_point( RIGHT ): " << number_ << "\n";
        }
        pop_back_extra_zeroes();
        notation_ = SCIENTIFIC;
        break;

    case DECIMAL:
    {
        if ( e_sign() == '+' )
        {
            move_floating_point( RIGHT, e_value_as_number() );

            //std::cout
                //<< "\nconvert_to(DECIMAL) works (floating point moved right): "
                //<< number_
                //<< "\n";

            erase_part_of( number_, position_before( e_position() ), number_.size() - 1 );

            //std::cout
                //<< "\nconvert_to(DECIMAL) works (after exponent tail erasure): "
                //<< number_
                //<< "\n";
        }
        else if ( e_sign() == '-' )
        {
            move_floating_point( LEFT, e_value_as_number() );

            //std::cout
                //<< "\nconvert_to(DECIMAL) works (floating point moved left): "
                //<< number_
                //<< "\n";

            erase_part_of( number_, position_before( e_position() ), number_.size() - 1 );

            //std::cout
                //<< "\nconvert_to(DECIMAL) works (after exponent tail erasure): "
                //<< number_
                //<< "\n";
        }
        else
        {
            std::cout
                << "\nError: incorrect character instead the sign."
                << "\nCurrent content of number_ is: " << number_
                << "\nAnd character is: " << number_[ e_sign() ] << "\n";
        }
        notation_ = DECIMAL;
        break;
    }

    case DEFAULT:
        reset();

    default:
        std::cout << "\nError: incorrect function argument.\n";
        break;
    }

} // endof convert_to()
/*
void BigFloat::reverse() // or std::string function member reverse()
{
    size_t initial_dot_pos = dot_position();
    size_t  final_dot_pos = last_digit_position() - dot_position();

    //std::cout << "initial_dot_pos: " << initial_dot_pos << "\n";
    //std::cout << "final_dot_pos: " << final_dot_pos << "\n";

    erase_part_of( number_, initial_dot_pos, initial_dot_pos );

    for ( size_t i = 0, j = last_digit_position(); i < position_after( last_digit_position() ) / 2; ++i, --j )
    {
        //std::cout << i + 1 << " pair: " << number_[i] << " and " << number_[j] << "\n";

        // or standard library algorithm std:swap( number_[i], number_[j] );
        char temp;
        temp = number_[i];
        number_[i] = number_[j];
        number_[j] = temp;
    }
    //std::cout << "current number after swapping and before dot coming back: " << number_ << "\n";
    insert_to( number_, ".", final_dot_pos );
    //std::cout << "current number after swapping and after dot coming back: " << number_ << "\n";
}

void BigFloat::push_front_additional_zeroes( const size_t quantity )
{
    std::string additional_zeroes( quantity, '0' );
    insert_to( number_, additional_zeroes, 0 );
}

void BigFloat::pop_front_extra_zeroes()
{
    erase_part_of( number_, 0, position_before( dot_position() ) - 1 );
}

void BigFloat::push_back_additional_zeroes( const size_t quantity )
{
    std::string additional_zeroes( quantity, '0' );
    insert_to( number_, additional_zeroes, position_after( last_digit_position() ) );
}
*/
void BigFloat::pop_back_extra_zeroes()
{
    while ( number_[last_digit_position()] == '0' &&
            last_digit_position() > position_after( dot_position() ) )
    {
        erase_part_of( number_, last_digit_position(), last_digit_position() );
    }
}

bool BigFloat::is_less_than_zero() const
{
    bool has_digits_greater_than_zero_after_dot = true;

    for ( size_t i = position_after( dot_position() );
          i < position_after( last_digit_position() );
          ++i )
    {
        if ( char_to_digit( number_[i] ) > 0 )
        {
            has_digits_greater_than_zero_after_dot = false;
            break;
        }
    }

    return
        digits_before_dot() == 1 &&
        number_[0] == '0' &&
        has_digits_greater_than_zero_after_dot;

}

bool BigFloat::is_greater_than_zero() const
{
    return char_to_digit( number_[0] ) >= 1;
}

// getters
size_t BigFloat::dot_position() const
{
    return char_position( number_, '.' );
}

size_t BigFloat::digits_after_dot() const
{   // TODO: implement count() function?
    return last_digit_position() - dot_position();
}

size_t BigFloat::digits_before_dot() const
{
    return dot_position();
}

size_t BigFloat::e_position() const
{
    size_t e_pos = number_.size();
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( number_[i] == 'e' || number_[i] == 'E' )
        {
            e_pos = i;
            break;
        }
    }

    return e_pos;
}

size_t BigFloat::digits_after_e() const
{   // TODO: implement count() function?
    return number_.size() - position_before( space_position() );
}

size_t BigFloat::e_value_as_number() const
{
    return string_to_number( e_value_as_string() );
}

std::string BigFloat::e_value_as_string() const
{
    std::string e_val = "";
    for ( size_t i = position_after( e_sign_position() ); i < number_.size(); ++i )
    {
        e_val = e_val + number_[i];
    }
    return e_val;
}

size_t BigFloat::lead_zeroes() const
{
    size_t result = 0;
    {
        for ( size_t i = 0; i < number_.size(); ++i )
        {
            if ( number_[i] == '0' )
                ++result;
            else if ( number_[i] == '.' )
                continue;
            else
                break;
        }
    }
    return result;
}

size_t BigFloat::e_sign_position() const
{
    size_t e_sign_pos = number_.size();
    for ( size_t i = e_position(); i < number_.size(); ++i )
    {
        if ( is_sign ( number_[i] ) )
        {
            e_sign_pos = i;
            break;
        }
    }

    return e_sign_pos;
}

char BigFloat::e_sign() const
{
    return number_[ e_sign_position() ];
}

size_t BigFloat::last_digit_position() const
{
    size_t last_digit_pos = number_.size();
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( is_digit( number_[i] ) || is_dot( number_[i] ) )
        {
            last_digit_pos = i;
        }
        else
        {
            break;
        }
    }

    return last_digit_pos;
}

size_t BigFloat::position_after( size_t pos ) const
{
    size_t pos_after_pos = number_.size();
    if ( pos + 1 < number_.size() )
    {
        pos_after_pos = pos + 1;
    }

    return pos_after_pos;
}

size_t BigFloat::position_before( size_t pos ) const
{
    size_t pos_before_pos = number_.size();
    if ( pos > 0 )
    {
        pos_before_pos = pos - 1;
    }

    return pos_before_pos;
}

size_t BigFloat::space_position() const
{
    return char_position( number_, ' ' );
}

char BigFloat::sign() const
{
    return number_[0] == '-' ? '-' : '+';
}

std::string BigFloat::mantissa() const
{
    std::string mantissa = number_;

    if ( is_scientific() )
    {
        //std::cout <<
            //"\nI AM INSIDE IN FUNCTION mantissa() and "
            //"is_scientific() is TRUE!\n";
        size_t space_pos = space_position();
        if ( mantissa[ space_pos ] == ' ' )
        {
            erase_part_of( mantissa, space_pos, space_pos );
        }
        erase_part_of( mantissa, e_position(), mantissa.size() - 1 );
    }

    return mantissa;
}

std::string BigFloat::number() const
{
    return number_;
}

BigFloat::Notation BigFloat::notation() const
{
    return notation_;
}

// setters
void BigFloat::set_number( const std::string& number )
{
    BigFloat temp = *this; // Лишнее копирование (вынужденное).
    number_ = number;
    sign_ = sign();
    discard_sign();
    tail_ = "";

    // Сделать функцию is_correct() глобальной?
    if ( is_correct( SCIENTIFIC ) )
    {
        convert_to( DECIMAL );
    }
    else if ( is_correct( DECIMAL ) )
    {
        // do nothing
    }
    else if ( is_correct( DEFAULT ) )
    {
        reset();
    }
    else
    {
        *this = temp; // Лишнее копирование (вынужденное).
    }
}

void BigFloat::mark_as_wrong()
{
    sign_ = '+';
    number_ = "0.0";
    tail_ = "\b\b\b\bincorrect number";
    notation_ = WRONG;
}

void BigFloat::reset()
{    
    sign_ = '+';
    number_ = "0";
    tail_ = ".0 E+0";
    notation_ = DEFAULT;
}

// comparison operators
bool BigFloat::operator<( const BigFloat& bf ) const
{
    BigFloat a = *this;
    BigFloat b = bf;

    bool result = true;

    if ( a.sign_ == '+' && b.sign_ == '-' )
    {
        result = false;
    }
    else if ( a.notation_ == DEFAULT && b.notation_ == DEFAULT )
    {
        result = false;
    }
    else if ( a.is_greater_than_zero() && b.notation_ == DEFAULT )
    {
        result = false;
    }
    else if ( a.notation_ == DEFAULT && b.is_less_than_zero() )
    {
        result = false;
    }

    if ( !a.is_decimal() )
    {
        a.convert_to( DECIMAL );
    }

    if ( !b.is_decimal() )
    {
        b.convert_to( DECIMAL );
    }

    // TODO: сравнивать поразрядно

    return result;
}

bool BigFloat::operator<=( const BigFloat& bf ) const
{
    BigFloat a = *this;
    BigFloat b = bf;

    return a < b || a == b;
}

bool BigFloat::operator>( const BigFloat& bf ) const
{
    BigFloat a = *this;
    BigFloat b = bf;

    bool result = true;

    if ( a.sign_ == '-' && b.sign_ == '+' )
    {
        result = false;
    }
    else if ( a.notation_ == DEFAULT && b.notation_ == DEFAULT )
    {
        result = false;
    }
    else if ( a.is_less_than_zero() && b.notation_ == DEFAULT )
    {
        result = false;
    }
    else if ( a.notation_ == DEFAULT && b.is_greater_than_zero() )
    {
        result = false;
    }

    if ( !a.is_decimal() )
    {
        a.convert_to( DECIMAL );
    }

    if ( !b.is_decimal() )
    {
        b.convert_to( DECIMAL );
    }

    // TODO: сравнивать поразрядно

    return result;
}

bool BigFloat::operator>=( const BigFloat& bf ) const
{
    BigFloat a = *this;
    BigFloat b = bf;

    return a > b || a == b;
}

bool BigFloat::operator==( const BigFloat& bf ) const
{
    BigFloat a = *this;
    BigFloat b = bf;

    return !(a < b) && !(a > b);
}

// assignment operators:
BigFloat BigFloat::operator=( const BigFloat& bf )
{
    if ( this != &bf )
    {
        sign_ = bf.sign_;
        number_ = bf.number_;
        tail_ = bf.tail_;
        notation_ = bf.notation_;
    }
    return *this;
}

BigFloat BigFloat::operator=( const std::string& obj )
{
    if ( this->number_ != &obj[0] ) // &obj.front()
    {
        BigFloat temp = *this;
        number_ = obj;
        sign_ = sign();
        discard_sign();

        if ( is_correct( SCIENTIFIC ) )
        {
            convert_to( DECIMAL );
            notation_ = DECIMAL;
        }
        else if ( is_correct( DECIMAL ) )
        {
            // do nothing
        }
        else if ( is_correct( DEFAULT ) )
        {
            reset();
        }
        else
        {
            *this = temp;
        }
    }
    return *this;
}

// arithmetic operators (both operand are same type):
BigFloat BigFloat::operator+(const BigFloat& addendum) const
{
    BigFloat a = *this;
    BigFloat b = addendum;

    std::string aStr = this->number_;
    std::string bStr = addendum.number_;

    size_t diff; // разница между количеством разрядов

    // уравниваем количество разрядов обоих чисел до плавающей точки:
    if (a.digits_before_dot() < b.digits_before_dot()) // #1
    {
        std::cout << "\n#1\n";
        std::cout << "we are here because a.digits_before_dot() < b.digits_before_dot():\n";
        std::cout << "a.digits_before_dot(): " << a.digits_before_dot() << "\n";
        std::cout << "b.digits_before_dot(): " << b.digits_before_dot() << "\n";
        std::cout << "current content of number a: " << a.number_ << "\n";
        std::cout << "current content of number b: " << b.number_ << "\n";
        std::cout << "current content of string aStr: " << aStr << "\n";
        std::cout << "current content of number bStr: " << bStr << "\n\n";

        diff = b.digits_before_dot() - a.digits_before_dot();
        for (size_t i = 0; i < diff; ++i)
        {
            push_front(aStr, "0");
        }
        std::cout << "string aStr after pushing front zeroes: " << aStr << "\n";
    }
    else if (b.digits_before_dot() < a.digits_before_dot()) // #2
    {
        std::cout << "\n#2\n";
        std::cout << "we are here because b.digits_before_dot() < a.digits_before_dot():\n";
        std::cout << "a.digits_before_dot(): " << a.digits_before_dot() << "\n";
        std::cout << "b.digits_before_dot(): " << b.digits_before_dot() << "\n";
        std::cout << "current content of number a: " << a.number_ << "\n";
        std::cout << "current content of number b: " << b.number_ << "\n";
        std::cout << "current content of string aStr: " << aStr << "\n";
        std::cout << "current content of number bStr: " << bStr << "\n\n";

        diff = a.digits_before_dot() - b.digits_before_dot();
        for (size_t i = 0; i < diff; ++i)
        {
            push_front(bStr, "0");
        }
        std::cout << "string bStr after pushing front zeroes: " << bStr << "\n";
    }

    // уравниваем количество разрядов обоих чисел после плавающей точки:
    if (a.digits_after_dot() < b.digits_after_dot()) // #3
    {
        std::cout << "\n#3\n";
        std::cout << "we are here because a.digits_after_dot() < b.digits_after_dot():\n";
        std::cout << "a.digits_after_dot(): " << a.digits_after_dot() << "\n";
        std::cout << "b.digits_after_dot(): " << b.digits_after_dot() << "\n\n";
        std::cout << "current content of number a: " << a.number_ << "\n";
        std::cout << "current content of number b: " << b.number_ << "\n";
        std::cout << "current content of string aStr: " << aStr << "\n";
        std::cout << "current content of number bStr: " << bStr << "\n\n";

        diff = b.digits_after_dot() - a.digits_after_dot();
        for (size_t i = 0; i < diff; ++i)
        {
            push_back(aStr, "0");
        }
        std::cout << "string aStr after pushing back zeroes: " << aStr << "\n";
    }
    else if (b.digits_after_dot() < a.digits_after_dot()) // #4
    {
        auto a_it = std::find(a.number_.begin(), a.number_.end(), '.');
        auto a_dad = std::distance(a_it + 1, a.number_.end());

        auto b_it = std::find(b.number_.begin(), b.number_.end(), '.');
        auto b_dad = std::distance(b_it + 1, b.number_.end());

        std::cout << "\n#4\n";
        std::cout << "we are here because b.digits_after_dot() < a.digits_after_dot():\n";

        std::cout << "a.digits_after_dot(): " << a.digits_after_dot() << "\n";
        std::cout << "b.digits_after_dot(): " << b.digits_after_dot() << "\n";

        std::cout << "real quantity digits after dot in number a: " << a_dad << "\n";
        std::cout << "real quantity digits after dot in number b: " << b_dad << "\n";

        std::cout << "current content of number a: " << a.number_ << "\n";
        std::cout << "current content of number b: " << b.number_ << "\n";

        std::cout << "current content of string aStr: " << aStr << "\n";
        std::cout << "current content of string bStr: " << bStr << "\n\n";

        diff = a.digits_after_dot() - b.digits_after_dot();
        for (size_t i = 0; i < diff; ++i)
        {
            push_back(bStr, "0");
        }
        std::cout << "string bStr after pushing back zeroes: " << bStr << "\n";
    }

    // запомним позицию плавающей точки:
    size_t dot_pos_a = char_position(aStr, '.');
    size_t dot_pos_b = char_position(bStr, '.');

    // уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
    erase_part_of(aStr, dot_pos_a, dot_pos_a);
    erase_part_of(bStr, dot_pos_b, dot_pos_b);

    // будем складывать, начиная с млаших разрядов, для этого перевернём числа:
    reverse(aStr);
    reverse(bStr);

    // излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
    size_t extra = 0;
    // промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
    size_t subtotal = 0;

    std::string sumStr;
    std::string curRes;
    for (size_t i = 0; i < aStr.size(); ++i)
    {
        subtotal = char_to_digit(aStr[i]) + char_to_digit(bStr[i]) + extra;

        std::cout
            << "\n"
            << char_to_digit(aStr[i])
            << " + "
            << char_to_digit(bStr[i])
            << " + number, that we keep in mind ("
            << extra
            << ") = "
            << subtotal;

        if (subtotal > MAX_DIGIT) // десятичная система, поэтому последняя цифра в разряде 9
        {
            extra = subtotal / BASE;
            subtotal = subtotal % BASE;
        }
        else
        {
            extra = 0;
        }

        std::cout << "\n" << subtotal << " we write, and " << extra << " we keep in mind.\n";
        push_back(sumStr, digit_to_char(subtotal));
        curRes = sumStr;
        reverse(curRes);
        std::cout << "current result is " << curRes << "\n";
    }

    if (extra)
    {
        push_back(sumStr, digit_to_char(extra));
        std::cout
            << "\nwe add the number, that we keep in mind ("
            << extra
            << ") to out result and ";
        curRes = sumStr;
        reverse(curRes);
    }


    reverse(sumStr);
    insert_to(sumStr, ".", dot_pos_a );

    std::cout << "final result is " << sumStr << "\n";

    BigFloat sum(sumStr);

    std::cout << "And in exponent notation final result is\n";

    return sum;
}

BigFloat BigFloat::operator-( const BigFloat& subtrahend ) const
{
    BigFloat diff( subtrahend ); // temporary solution to avoid compiler warning
    // TODO
    return diff;
}

BigFloat BigFloat::operator*( const BigFloat& multiplier ) const
{
    BigFloat product( multiplier ); // temporary solution to avoid compiler warning
    // TODO
    return product;
}

BigFloat BigFloat::operator/( const BigFloat& divider ) const
{  
    BigFloat result;
    BigFloat dividend ( *this );
    BigFloat divisor ( divider );
    if ( dividend.notation() == SCIENTIFIC )
    {
        dividend.convert_to( DECIMAL );
    }

    if ( divisor.notation() == SCIENTIFIC )
    {
        divisor.convert_to( DECIMAL );
    }

    if ( dividend.is_correct( DEFAULT ) )
    {
        // do nothing (result already equal to zero)
    }
    else if ( divisor.is_correct( DEFAULT ) )
    {
        result.number_ = "1.0";
        std::cout <<
            "\nYou can not divide by zero! The result is "
            "equated to 1, but it is a wrong result.\n";
    }
    else
    {
        size_t digitsAfterDot = divisor.digits_after_dot();
        for ( size_t  i = digitsAfterDot; i > 0; --i )
        {
            divisor.move_floating_point( RIGHT, 1 );
            dividend.move_floating_point( RIGHT, 1 );
        }

        // TODO: закончить
    }

    return result;
}

// arithmetic operators (each operand are different type):
BigFloat BigFloat::operator+( const BigInt& addendum ) const
{
    BigFloat sum( addendum ); // temporary solution to avoid compiler warning
    // TODO
    return sum;
}

BigFloat BigFloat::operator-( const BigInt& subtrahend ) const
{
    BigFloat diff( subtrahend ); // temporary solution to avoid compiler warning
    // TODO
    return diff;
}

BigFloat BigFloat::operator*( const BigInt& multiplier ) const
{
    BigFloat product( multiplier ); // temporary solution to avoid compiler warning
    // TODO
    return product;
}

BigFloat BigFloat::operator/( const BigInt& divider ) const
{
    BigFloat result( divider ); // temporary solution to avoid compiler warning
    // TODO
    return result;
}

// input-output operators
std::istream& operator>>( std::istream& is, BigFloat& bf )
{
    std::string num;
    std::cin.sync();
    std::getline( std::cin, num );

    bf.set_number( num );

    if ( bf.is_correct( BigFloat::SCIENTIFIC ) )
    {
        bf.convert_to( BigFloat::DECIMAL );
    }
    else if ( bf.is_correct( BigFloat::DECIMAL ) )
    {
        // do nothing
    }
    else if ( bf.is_correct( BigFloat::DEFAULT ) )
    {
        bf.reset();
    }
    else
    {
        bf.mark_as_wrong();
    }

    return is;
}

std::ostream& operator<<( std::ostream& os, const BigFloat& bf )
{
    BigFloat temp = bf;
    if ( temp.is_correct( BigFloat::DECIMAL ) )
    {
        temp.convert_to( BigFloat::SCIENTIFIC );
    }
    else if ( temp.is_correct( BigFloat::SCIENTIFIC ) )
    {
        // do nothing
    }
    else if ( temp.is_correct( BigFloat::DEFAULT ) )
    {
        temp.tail_ = ".0 E+0";
    }
    else
    {
        temp.mark_as_wrong();
    }

    os << temp.sign_ << temp.number_ << temp.tail_;

    return os;
}
