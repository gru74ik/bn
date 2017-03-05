#include "BigFloat.h"
#include "bn_functions.h"

BigFloat::BigFloat() : number_( "0" ), mode_( DECIMAL )
{}

BigFloat::BigFloat(const std::string& number )
{
    number_ = number;
    if ( is_scientific() )
        convert_to( DECIMAL );
}

BigFloat::BigFloat( BigInt& bigInteger )
{
    number_ = bigInteger.number() + ".0";
}

void BigFloat::convert_to( MODE mode )
{
    switch ( mode )
    {
    case SCIENTIFIC:

        if ( number_[0] == '+' || is_digit( number_[0] ) )
        {
            number_ = "+" + number_ + " E+0";
        }
        else if ( number_[0] == '-' )
        {
            number_ = "-" + number_ + " E+0";
        }
        else
        {
            number_ = "0";
            std::cout << "Incorrect number notation. The number equated to 0.";
        }
        mode_ = SCIENTIFIC;
        break;

    case DECIMAL:        
    {
        char sign_of_exp = number_[number_.size()-3];
        char value_of_exp = number_[number_.size()-2];
        if ( sign_of_exp == '+' )
            move_floating_point( RIGHT, char_to_digit( value_of_exp ) );
        else if ( sign_of_exp == '-' )
            move_floating_point( LEFT, char_to_digit( value_of_exp ) );
        mode_ = DECIMAL;
        break;
    }
    default:
        std::cout << "Error: incorrect function argument.";
        break;
    }

}

void BigFloat::set_number( const std::string & message )
{
    std::cout << message;
    std::getline( std::cin, number_ );
    if ( !is_correct() )
    {
        number_ = "0";
    }
}

BigFloat::MODE BigFloat::mode()
{
    return mode_;
}

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

std::string BigFloat::number()
{
    return number_;
}

BigFloat BigFloat::operator/( const BigFloat& divider ) const
{  
    BigFloat result;
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
        // TODO:
        // реализовать деление одного числа типа BigFloat
        // на другое число типа BigFloat
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

bool BigFloat::is_correct()
{
    bool result = true;
    if( number_.empty() )
    {
        result = false;
    }
    else
    {
        if ( is_one_char( number() ) )
        {
            if ( !is_digit( number_[0] ) )
            {
                result = false;
            }
        }
        else
        {
            if ( contains_one_dot_only( number_ ) )
            {
                // TODO: проверить, что число записано
                // в правильной экспоненциальной или
                // десятичной форме
            }
            else
            {
                result = false;
            }
        }
    }

    return result;
}

size_t BigFloat::find_dot_position()
{
    size_t dot_position = 0;
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( number_[i] == '.' )
        {
            dot_position = i;
            break;
        }
    }

    return dot_position;
}

size_t BigFloat::digits_after_dot()
{
    return number_.size() - find_dot_position() - 1;
}

size_t BigFloat::digits_before_dot()
{
    size_t result = 0;
    if ( is_digit( number_[0] ) )
        result = find_dot_position();
    else if ( is_sign( number_[0] ) )
        result = find_dot_position() - 1;
    return result;
}

void BigFloat::move_floating_point( DIRECTION dir, size_t shiftSize )
{
    BigFloat temp( get_mantissa() );
    std::string result;
    switch ( dir )
    {
    case RIGHT:
        if ( temp.digits_after_dot() == 0 )
        {
            result = temp.number_;
            result = result + '0';
        }
        else
        {
            for ( size_t i = 0; i < temp.digits_before_dot(); ++i )
            {
                result = result + temp.number_[i];
            }

            if ( temp.digits_after_dot() > shiftSize )
            {
                size_t i = temp.find_dot_position() + 1;
                for ( ; i < temp.find_dot_position() + shiftSize; ++i )
                    result = result + temp.number_[i];
                result = result + '.';
                for ( ; i < temp.number_.size(); ++i )
                    result = result + temp.number_[i];
            }
            else if ( temp.digits_after_dot() == shiftSize )
            {
                for ( size_t i = temp.find_dot_position() + 1;
                      i < temp.find_dot_position() + shiftSize;
                      ++i
                    )
                {
                    result = result + temp.number_[i];
                }
                result = result + ".0";
            }
            else
            {
                size_t i = temp.find_dot_position() + 1;
                for ( ; i < temp.number_.size(); ++i )
                    result = result + temp.number_[i];

                for ( size_t i = 0; i < shiftSize - temp.digits_after_dot(); ++i )
                {
                    result = result + '0';
                }
                result = result + ".0";
            }
        }


        break;

    case LEFT:
        //TODO
        break;

    default:
        break;
    }
}

std::string BigFloat::get_mantissa()
{
    std::string mantissa;
    for ( size_t i = 1; number_[i] != ' ' || i < number_.size(); ++i )
        mantissa = mantissa + number_[i];
    return mantissa;
}

bool BigFloat::is_scientific()
{
    bool result = false;
    for ( size_t i = 0; i < number_.size(); ++i )
    {
        if ( number_[i] == 'E' )
        {
            result = true;
            break;
        }
    }
    return result;
}

bool BigFloat::is_decimal()
{
    return !is_scientific();
}

std::ostream& operator<<( std::ostream& os, BigFloat& bf )
{
    if ( bf.is_decimal() )
        bf.convert_to( BigFloat::SCIENTIFIC );
    os << bf.number_;
    return os;
}

std::istream& operator>>( std::istream& is, BigFloat& bf )
{
    is >> bf.number_;
    if ( bf.is_scientific() )
        bf.convert_to( BigFloat::DECIMAL );
    return is;
}
