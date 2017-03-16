#include "stdafx.h"
#include "BigNumber.h"
#include "bn_functions.h"


// ctors =======================================================================
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

// checkers ====================================================================
bool BigNumber::has_leading_zeros() const
{
	bool result = false;
	if (number_.size() > 1 && first_digit_value == 0 )
	{
		result = true;
	}

	return result;
}

// changers ====================================================================
// ��������� ����
void BigNumber::discard_sign()
{
	if (is_sign(number_[0]))
	{
		erase_part_of(number_, 0, 0);
	}
}

// ���������� ������� (���������) ������ ����
void BigNumber::pop_front_extra_zeros()
{	// TODO: implement for BigFloat his own version
	if (has_leading_zeros)
	{	// TODO: ��� BigFloat �������� ���������� ������� ��������� �����
		for (size_t i = 0; i < leading_zeros(); ++i)
		{
				pop_front(number_);
		}
	}
}

// ��������� ����� ���������� ����
void BigNumber::push_front_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_front(number_, '0');
	}
}




// getters =====================================================================
// ����� ���������� ���������� �����
size_t BigNumber::leading_zeros() const
{	// TODO: implement for BigFloat his own version
	size_t quantity_of_leading_zeros = 0;
	for (size_t i = 0; i < last_digit_position(); ++i)
	{	// TODO: ��� BigFloat �������� ���������� ������� ��������� �����
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

// ����� ������� ������ ����� �����
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

// ����� �������� ������ ����� �����
size_t BigNumber::first_digit_value() const
{
	return char_to_digit(number_[first_digit_position()]);
}

// ����� ������� ����� �������� ��������
size_t BigNumber::position_before(size_t pos) const
{
	size_t pos_before_pos = number_.size();
	if (pos > 0)
	{
		pos_before_pos = pos - 1;
	}

	return pos_before_pos;
}

// ����� ������� ����� �������� ��������
size_t BigNumber::position_after(size_t pos) const
{
	size_t pos_after_pos = number_.size();
	if (pos + 1 < number_.size())
	{
		pos_after_pos = pos + 1;
	}

	return pos_after_pos;
}

// ���������� ���� �����
size_t BigNumber::sign() const
{
	return number_[0] == '-' ? '-' : '+';
}

// ������� (to get) ���������� ���� number_
std::string BigNumber::number() const
{
	return number_;
}

// setters =====================================================================
// �������� �������� ����� � �������� �� ��������� (��������)
void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
	tail_ = "";
}

// ���������� �������� ����� � ������������ � ���������� ����������
void BigNumber::set_number(const std::string & number)
{
	number_ = number;
	sign_ = sign();
	discard_sign();
	tail_ = "";
}