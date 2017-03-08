#include "BigFloat.h"
#include "bn_functions.h"
// #include <cmath> // можно использовать std::pow()

// constructors
BigFloat::BigFloat() : sign_( '+' ), number_( "0.0" ), mode_( DECIMAL )
{}

BigFloat::BigFloat(const std::string& number )
{
    number_ = number;
    if ( is_correct() )
    {
        sign_ = get_sign();
        discard_sign();
        if ( is_scientific() )
            convert_to( DECIMAL );
        mode_ = DECIMAL;
    }
    else
    {
        std::cout
            << "\nConstructor tried create object from string but failed, "
            << "because string is incorrect.\n";
        number_ = "0.0";
        sign_ = '+';
        mode_ = DECIMAL;
    }
}

BigFloat::BigFloat( BigInt& bigInteger )
{
    number_ = bigInteger.number() + ".0";
    if ( is_correct() )
    {
        sign_ = get_sign();
        discard_sign();
        if ( is_scientific() )
            convert_to( DECIMAL );
        mode_ = DECIMAL;
    }
    else
    {
        std::cout
            << "\nConstructor tried create object from string but failed, "
            << "because string is incorrect.\n";
        number_ = "0.0";
        sign_ = '+';
        mode_ = DECIMAL;
    }
}

BigFloat::BigFloat( const BigFloat& bf )
{
    number_ = bf.number_;
}

//checkers
bool BigFloat::is_scientific()
{
    return e_position() != number_.size();
}

bool BigFloat::is_decimal()
{
    return e_position() == number_.size();
}

bool BigFloat::is_correct()
{
    bool result = true;
    if( number_.size() < 3 )    // every decimal number must have
    {                           // integer part, dot and fractional part
        result = false;         // for example: 1.5
    }                           // and this is 3 characters at least
    else
    {
        if ( is_scientific() )
        {
            // TODO:
            // проверить, что строка содержит пробел
            // проверить, что до пробела все элементы строки - числа
            // проверить, что после пробела стоит буква 'e' или 'E'
            // проверить, что после буквы 'e' или 'E' стоят только числа
        }
        else if ( is_decimal() )
        {
            // TODO
        }
    }

    return result;
}

// getters
size_t BigFloat::dot_position()
{
    size_t dot_pos = 0;
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( number_[i] == '.' )
        {
            dot_pos = i;
            break;
        }
    }

    return dot_pos;
}

size_t BigFloat::digits_after_dot()
{
    return number_.size() - dot_position() - 1;
}

size_t BigFloat::digits_before_dot()
{
    size_t result = 0;
    if ( is_digit( number_[0] ) )
        result = dot_position();
    else if ( is_sign( number_[0] ) )
        result = dot_position() - 1;
    return result;
}

size_t BigFloat::e_position()
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

size_t BigFloat::digits_after_e()
{
    return number_.size() - e_position() - 2;
}

size_t BigFloat::e_value_as_number()
{
    return string_to_number( e_value_as_string() );
}

std::string BigFloat::e_value_as_string()
{
    std::string e_val = "";
    for ( size_t i = e_position() + 2; i < number_.size(); ++i )
    {
        e_val = e_val + number_[i];
    }
    return e_val;
}

size_t BigFloat::lead_zeroes()
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

char BigFloat::get_sign()
{
    return number_[0] == '-' ? '-' : '+';
}

std::string BigFloat::get_mantissa()
{
    std::string mantissa = "";

    if ( is_scientific() )
    {
        std::cout <<
            "\nI AM INSIDE IN FUNCTION get_mantissa() and "
            "is_scientific() is TRUE!\n";
        size_t space_pos = e_position() - 1;
        if ( number_[ space_pos ] == ' ' )
        {
            erase_part_of( number_, space_pos, space_pos );
        }
        erase_part_of( number_, e_position(), number_.size()-1 );
    }

    return mantissa;
}

std::string BigFloat::number()
{
    return number_;
}

BigFloat::MODE BigFloat::mode()
{
    return mode_;
}

// setters
void BigFloat::set_number( const std::string & message )
{
    std::cout << message;
    std::string temp = number_;
    std::getline( std::cin, number_ );
    if ( !is_correct() )
    {
        number_ = temp;         // Лишнее копирование.
        sign_ = get_sign();     // Сделать функцию is_correct() глобальной?
        if ( is_scientific() )
        {
            convert_to( DECIMAL );
        mode_ = DECIMAL;
        }
    }
}

// changers
void BigFloat::discard_sign()
{
    if ( is_sign( number_[0] ) )
    {
        erase_part_of( number_, 0, 0 );
    }
}

void BigFloat::move_floating_point( DIRECTION dir, size_t shiftSize )
{
    // we work with numbers in decimal notation!
    size_t dot_pos = dot_position();
    switch ( dir )
    {
    case RIGHT:
        if ( digits_after_dot() > shiftSize )
        {
            insert_to( number_ , ".", dot_pos + shiftSize + 1 );
        }
        else if ( digits_after_dot() == shiftSize )
        {
            insert_to( number_ , ".0", dot_pos + shiftSize + 1 );
        }
        else
        {
            size_t additional_zeroes = shiftSize - digits_after_dot();
            for ( size_t i = 0; i < additional_zeroes; ++i )
                number_ = number_ + "0";
            number_ = number_ + ".0";
        }

        erase_part_of( number_, dot_pos, dot_pos );

        break;

    case LEFT:
    {
        size_t digits_before = digits_before_dot();
        erase_part_of( number_, dot_pos, dot_pos );

        if ( digits_before > shiftSize )
        {
            insert_to( number_ , ".", dot_pos - shiftSize );
        }
        else if ( digits_before == shiftSize )
        {
            insert_to( number_ , "0.", 0 );
        }
        else
        {
            size_t additional_zeroes = shiftSize - digits_before;
            for ( size_t i = 0; i < additional_zeroes; ++i )
                number_ = "0" + number_;
            insert_to( number_ , "0.", 0 );
        }

        break;
    }
    default:
        break;
    }
}

void BigFloat::convert_to( MODE mode )
{
    switch ( mode )
    {
    case SCIENTIFIC:

        if ( dot_position() != 1 )
        {
            size_t shift = dot_position() - 1;
            move_floating_point( LEFT, shift );
            number_ = number_ + " E+" + number_to_string( shift );
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
        }
        mode_ = SCIENTIFIC;
        break;

    case DECIMAL:        
    {
        char sign_of_exp = number_[number_.size()-3];

        if ( sign_of_exp == '+' )
            move_floating_point( RIGHT, string_to_number( e_value_as_string() ) );
        else if ( sign_of_exp == '-' )
            move_floating_point( LEFT, string_to_number( e_value_as_string() ) );
        mode_ = DECIMAL;
        break;
    }
    default:
        std::cout << "Error: incorrect function argument.";
        break;
    }

}

// operators
bool BigFloat::operator<( BigFloat& b )
{
    BigFloat & a = *this;

    if ( a.mode() == SCIENTIFIC )
    {
        a.convert_to( DECIMAL );
    }

    if ( b.mode() == SCIENTIFIC )
    {
        b.convert_to( DECIMAL );
    }
    return a.number_ < b.number_;
}

BigFloat BigFloat::operator=( const BigFloat& bf )
{
    if ( this != &bf )
    {
        number_ = bf.number_;
        mode_ = bf.mode_;
    }
    return *this;
}

BigFloat BigFloat::operator=( const std::string& obj )
{
    if ( this->number_ != &obj[0] ) // &obj.front()
    {
        std::string temp = number_;
        number_ = obj;
        if ( is_correct() )
        {
            sign_ = get_sign();
            discard_sign();
            if ( is_scientific() )
                convert_to( DECIMAL );
            mode_ = DECIMAL;
        }
        else
        {
            number_ = temp;
        }
    }
    return *this;
}

/*
BigFloat BigFloat::operator+( const BigFloat& addendum ) const
{
    BigFloat sum( "0" );
    // TODO
    return sum;
}

BigFloat BigFloat::operator-( const BigFloat& subtrahend ) const
{
    BigFloat diff( "0" );
    // TODO
    return diff;
}

BigFloat BigFloat::operator*( const BigFloat& multiplier ) const
{
    BigFloat product( "0" );
    // TODO
    return product;
}
*/

BigFloat BigFloat::operator/( const BigFloat& divider ) const
{  
    BigFloat result( "0" );
    BigFloat dividend ( *this );
    BigFloat divisor ( divider );
    if ( dividend.mode() == SCIENTIFIC )
    {
        dividend.convert_to( DECIMAL );
    }

    if ( divisor.mode() == SCIENTIFIC )
    {
        divisor.convert_to( DECIMAL );
    }

    if ( dividend.number_ == "0" )
    {
        result.number_ = "0";
    }
    else if ( divisor.number_ == "0" )
    {
        result.number_ = "1";
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


/*
Цикл Х:
1)  Проверить, действительно ли делимое больше, чем делитель.
2)  Если да, начинаем делить.
3)  Если нет, сдвигаем вправо плавающую точку в делимом и
    добавляем ноль с точкой в ответ.
4)  Проверить, действительно ли делимое больше, чем делитель.
5)	Если да, начинаем делить.
6)  Если нет, сдвигаем вправо плавающую точку в делимом
    и добавляем ноль после точки в ответ.
7)  Выполнять цикл X, пока делимое не станет больше, чем делитель или пока
    количество разрядов в ответе не превысит 30.
8)  Делим делимое на делитель, частное записываем в ответ, остаток записываем
    в остаток (сносим вниз).
9)  Теперь остаток – это делимое.
10)	Выполнять цикл X, пока делимое не станет больше, чем делитель или пока
    количество разрядов в ответе не превысит 30.
*/

    return result;
}

// input-output operators
std::istream& operator>>( std::istream& is, BigFloat& bf )
{
    is >> bf.number_;
    if ( bf.is_scientific() )
        bf.convert_to( BigFloat::DECIMAL );
    return is;
}

std::ostream& operator<<( std::ostream& os, BigFloat& bf )
{
    if ( bf.is_decimal() )
        bf.convert_to( BigFloat::SCIENTIFIC );
    os << bf.sign_ << bf.number_;
    return os;
}
