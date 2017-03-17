#include "stdafx.h"
#include "BigNumber.h"
#include "bn_functions.h"


// ctors =======================================================================
BigNumber::BigNumber()
{
	number_ = "0";
	sign_ = define_sign();
	discard_sign();
	tail_ = "";
/*
	std::cout << "Ctor BigNumber::BigNumber() has been called.\n";
*/
}

BigNumber::BigNumber(const std::string& num)
{
	number_ = num;
	sign_ = define_sign();
	discard_sign();
	tail_ = "";
/*
	std::cout
		<< "The object has_leading_zeros(). "
		<< "Assertion occured in BigNumber.cpp, #ctor(arg)\n"
		;
*/
	pop_front_extra_zeros();
/*
	std::cout << "Ctor BigNumber::BigNumber(const std::string& num) has been called.\n";
*/
}

// checkers ====================================================================
bool BigNumber::has_leading_zeros() const
{
	bool result = false;
	if (number_.size() > 1 && first_digit_value() == 0 )
	{
		result = true;
	}

	return result;
}

// changers ====================================================================
// отбросить знак
void BigNumber::discard_sign()
{
	if (is_sign(number_[0]))
	{
		erase_part_of(number_, 0, 0);
	}
}

// вытолкнуть спереди (отбросить) лишние нули
void BigNumber::pop_front_extra_zeros() // #pfez
{	// TODO: implement for BigFloat his own version
	for (size_t i = 0; i < number_.size() - 1; ++i)
	{
		if (number_[i] == '0')
		{
			pop_front(number_);
		}
		else
		{
			break;
		}
	}
}

// затолкать вперёд добавочные нули
void BigNumber::push_front_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_front(number_, '0');
	}
}

void BigNumber::reverse_number()
{
	reverse(number_);
}

// getters =====================================================================

// найти количество лидирующих нулей
size_t BigNumber::leading_zeros() const
{	// TODO: implement for BigFloat his own version
	size_t quantity_of_leading_zeros = 0;
	for (size_t i = 0; i < number_.size(); ++i)
	{	// TODO: для BigFloat заменить граничащее условие окончания цикла
		if (number_[i] == '0')
		{
			++quantity_of_leading_zeros;
		}
		else
		{
			break;
		}
	}
/*
	std::cout
		<< "The quantity of leading zeros is: "
		<< quantity_of_leading_zeros
		<< ". Assertion occured in BigNumber.cpp, "
		<< "in function leading_zeros().\n"
		;
*/
	return quantity_of_leading_zeros;
}

// найти позицию первой цифры числа
size_t BigNumber::first_digit_position() const
{
	size_t first_digit_pos = number_.size();

	for (size_t i = 0; i < number_.size(); ++i)
	{
		if (is_digit(number_[0]))
		{
			first_digit_pos = i;
			break;
		}
	}

	return first_digit_pos;
}

// найти значение первой цифры числа
size_t BigNumber::first_digit_value() const
{
	return char_to_digit(number_[first_digit_position()]);
	//return char_to_digit(number_[0]);
}

// найти позицию перед заданной позицией
size_t BigNumber::position_before(size_t pos) const
{
	size_t posBeforePos = number_.size();
	if (pos > 0)
	{
		posBeforePos = pos - 1;
	}

	return posBeforePos;
}

// найти позицию после заданной позицией
size_t BigNumber::position_after(size_t pos) const
{
	size_t numSize = number_.size();
	size_t posAfterPos = numSize;

	if (pos + 1 < numSize)
	{
		posAfterPos = pos + 1;
	}

	return posAfterPos;
}

// определить знак числа
char BigNumber::define_sign() const
{
	return number_[0] == '-' ? '-' : '+';
}

// получить знак числа
char BigNumber::get_sign() const
{
	return sign_;
}

// получить "хвост"
std::string BigNumber::get_tail() const
{
	return tail_;
}

// достать (to get) содержимое поля number_
std::string BigNumber::get_number() const
{
	return number_;
}

// setters =====================================================================
// сбросить значения полей в значения по умолчанию (обнулить)
void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
	tail_ = "";
}

// установить значения полей в соответствии с переданным аргументом
void BigNumber::set_number(const std::string & num)
{
	number_ = num;
	sign_ = define_sign();
	discard_sign();
	tail_ = "";
}

void BigNumber::set_tail(const std::string & num)
{
	tail_ = num;
}