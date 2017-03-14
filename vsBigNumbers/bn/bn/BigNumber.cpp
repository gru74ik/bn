#include "stdafx.h"
#include "BigNumber.h"
#include "bn_functions.h"


// constructors:
BigNumber::BigNumber()
{
	number_ = "0";
	sign_ = sign();
	discard_sign();
	tail_ = "";
}

BigNumber::BigNumber(const std::string& number)
{
	number_ = number;
	sign_ = sign();
	discard_sign();
	tail_ = "";
}


// changers:
void BigNumber::discard_sign()
{
	if (is_sign(number_[0]))
	{
		erase_part_of(number_, 0, 0);
	}
}

void BigNumber::pop_front_extra_zeros()
{

}

void BigNumber::push_front_additional_zeros(const size_t quantity)
{

}


// getters:
size_t BigNumber::first_digit_position() const
{
	size_t first_digit_pos = number_.size();

	if (is_digit(number_[0]))
	{
		first_digit_pos = number_[0];
	}
	else
	{
		for (size_t i = 0; i < number_.size(); ++i)
		{
			if (is_digit(number_[0]))
			{
				first_digit_pos = i;
				break;
			}
		}
	}

	return first_digit_pos;
}


size_t BigNumber::first_digit() const
{
	return char_to_digit(number_[first_digit_position()]);
}


size_t BigNumber::position_before(size_t pos) const
{
	size_t pos_before_pos = number_.size();
	if (pos > 0)
	{
		pos_before_pos = pos - 1;
	}

	return pos_before_pos;
}

size_t BigNumber::position_after(size_t pos) const
{
	size_t pos_after_pos = number_.size();
	if (pos + 1 < number_.size())
	{
		pos_after_pos = pos + 1;
	}

	return pos_after_pos;
}

size_t BigNumber::sign() const
{
	return number_[0] == '-' ? '-' : '+';
}


std::string BigNumber::number() const
{
	return number_;
}

// setters:
void BigNumber::set_number(const std::string & number)
{
	number_ = number;
	sign_ = sign();
	discard_sign();
	tail_ = "";
}

void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
	tail_ = "";
}

