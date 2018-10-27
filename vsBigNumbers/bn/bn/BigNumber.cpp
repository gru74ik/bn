#include "stdafx.h"

#include "BigNumber.h"
#include "bn_functions.h"


// ctors =======================================================================
BigNumber::BigNumber()
	:
		number_("0"),
		sign_('+')
{
}

BigNumber::BigNumber(const char num)
{
	if (num == '0')
	{
		reset();
	}
	else
	{
		number_ = "";
		number_ = number_ + num;
		sign_ = define_sign();
		discard_sign();
	}
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
}

BigNumber::BigNumber(const BigNumber &)
{
}



// changers ====================================================================

void BigNumber::discard_sign()
{
	if (is_sign(number_[0]))
	{
		erase_elem(0);
	}
}

void BigNumber::push_front_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_front(number_, '0');
	}
}

void BigNumber::push_back_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_back(number_, '0');
	}
}

void BigNumber::reverse_number() // swaps left-hand digits with right-hand digits
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

size_t BigNumber::leading_zeros() const // finds quantity of leading zeros
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

size_t BigNumber::first_digit_value() const
{
	return char_to_digit(number_[first_digit_position()]);
}

size_t BigNumber::position_before(size_t pos) const // finds position before given position pos
{
	size_t posBeforePos = number_.size();
	if (pos > 0)
	{
		posBeforePos = pos - 1;
	}

	return posBeforePos;
}

size_t BigNumber::position_after(size_t pos) const // finds position after given position pos
{
	size_t numSize = number_.size();
	size_t posAfterPos = numSize;

	if (pos + 1 < numSize)
	{
		posAfterPos = pos + 1;
	}

	return posAfterPos;
}

char BigNumber::define_sign() const
{
	return number_[0] == '-' ? '-' : '+';
}

char BigNumber::get_sign() const
{
	return sign_;
}

std::string BigNumber::get_number() const // gets content of number_ data member
{
	return number_;
}



// setters =====================================================================

void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
}

void BigNumber::set_sign(const char sign)
{
	sign_ = sign;
}

void BigNumber::set_number(const std::string & num)
{
	number_ = num;
	sign_ = define_sign();
	discard_sign();
}