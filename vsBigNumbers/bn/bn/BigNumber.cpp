#include "stdafx.h"
#include "BigNumber.h"
#include "bn_functions.h"


// ctors =======================================================================
BigNumber::BigNumber()
{
	number_ = "0";
	sign_ = '+';
/*
	std::cout << "Ctor BigNumber::BigNumber() has been called.\n";
*/
}

BigNumber::BigNumber(const std::string& num)
{
	if (num.size() == 0)
	{
		reset();
	}	
	else
	{ 
		number_ = num;
		sign_ = define_sign();
		discard_sign();	
	}
	

/*
	std::cout << "Ctor BigNumber::BigNumber(const std::string& num) has been called.\n";
*/
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

// затолкать вперёд добавочные нули
void BigNumber::push_front_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_front(number_, '0');
	}
}

// "перевернуть" число (поменять местами старшие разряды и младшие)
void BigNumber::reverse_number()
{
	reverse(number_);
}

void BigNumber::erase_elem(const size_t pos)
{
	erase_part_of(number_, pos, pos);
}

void BigNumber::erase_elem(const size_t first, const size_t last)
{
	erase_part_of(number_, first, last);
}

void BigNumber::insert_elem(const char ch, const size_t pos)
{
	insert_to(number_, ch, pos);
}

void BigNumber::insert_elem(const std::string & str, const size_t pos)
{
	insert_to(number_, str, pos);
}

void BigNumber::push_back_elem(const char ch)
{
	push_back(number_, ch);
}

void BigNumber::push_back_elem(const std::string & str)
{
	push_back(number_, str);
}

void BigNumber::push_front_elem(const char ch)
{
	push_front(number_, ch);
}

void BigNumber::push_front_elem(const std::string & str)
{
	push_front(number_, str);
}

void BigNumber::pop_back_elem()
{
	pop_back(number_);
}

void BigNumber::pop_back_elem(const size_t quantity)
{
	erase_part_of(number_, number_.size() - quantity, number_.size() - 1);
}

void BigNumber::pop_front_elem()
{
	pop_front(number_);
}

void BigNumber::pop_front_elem(const size_t quantity)
{
	erase_part_of(number_, 0, quantity - 1);
}

void BigNumber::clear_number()
{
	//number_.clear();
	erase_elem(0, number_.size() - 1);
}

// getters =====================================================================

// найти количество лидирующих нулей
size_t BigNumber::leading_zeros() const
{
	size_t quantity_of_leading_zeros = 0;
	for (size_t i = 0; i < number_.size(); ++i)
	{
		if (number_[i] == '0')
		{
			++quantity_of_leading_zeros;
		}
		else
		{
			break;
		}
	}
/**/
	std::cout
		<< "The quantity of leading zeros is: "
		<< quantity_of_leading_zeros
		<< ". Assertion occured in BigNumber.cpp, leading_zeros().\n\n"
		;

	return quantity_of_leading_zeros;
}

size_t BigNumber::elem_value_as_digit(size_t index) const
{
	return char_to_digit(number_[index]);
}

char BigNumber::elem_value_as_char(size_t index) const
{
	return number_[index];
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

// достать (to get) содержимое поля number_
std::string BigNumber::get_number() const
{
/*
	std::cout
		<< "get_number() function has been called. The number is: "
		<< number_
		<< "\nAssertion occured in BigNumber.cpp, get_number().\n\n"
		;
*/
	return number_;
}



// setters =====================================================================

// сбросить значения полей в значения по умолчанию (обнулить)
void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
}

// установить знак
void BigNumber::set_sign(const char sign)
{
	sign_ = sign;
}

// установить значение полей в соответствии с переданным аргументом
void BigNumber::set_number(const std::string & num)
{
	number_ = num;
	sign_ = define_sign();
	discard_sign();
}


