#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"
#include "bn_functions.h"


// ctors =======================================================================
BigInt::BigInt() : BigNumber()
{
}

BigInt::BigInt(const std::string& number) : BigNumber(number)
{
	if (!is_correct())
	{
		reset();
	}
}


// checkers ====================================================================
bool BigInt::is_correct(const std::string& number) const
{
	bool correct = true;

	if (number.size() == 0) // if(bi.number().empty())
	{
		correct = false;
	}
	else
	{
		if (is_one_char(number))
		{
			if (!is_digit(number[0])) // bi.number().at(0)
			{
				correct = false;
			}
		}
		else
		{
			if (!is_digit(number[0]))
			{
				correct = false;
			}

			for (size_t i = 1; i < number.size(); ++i)
			{
				if (!is_digit(number[i]))
				{
					correct = false;
					break;
				}
			}

		}
	}

	return correct;
} //endof is_correct()

bool BigInt::is_correct() const
{
	return is_correct(number());
}

bool BigInt::is_greater_than_zero() const
{
	//TODO: проверить, что нет лидирующих нулей
	return sign() == '+' && first_digit() > 0;
} //endof is_greater_than_zero()

bool BigInt::is_less_than_zero() const
{
	return sign() == '-';
}

bool BigInt::is_zero() const
{
	//TODO: проверить, что нет лидирующих нулей
	return number() == "0";
}


// getters =====================================================================
size_t BigInt::last_digit_position() const
{
	return number().size() - 1;
}

size_t BigInt::last_digit() const
{
	return number()[last_digit_position()];
}

void BigInt::set_number(const std::string & str)
{
	if (is_correct(str))
	{
		BigNumber::set_number(str);
	}
}


// assignment operators:
BigInt BigInt::operator=(const BigInt& bi)
{
	if (this != &bi)
	{
		number() = bi.number();
	}
	return *this;
}

BigInt BigInt::operator=(const std::string& str)
{
	if (number() != &str[0]) // &str.front()
	{
		number() = str;
	}
	return *this;
}

// comparison operators:
bool BigInt::operator<(const BigInt& bi) const
{
	BigInt a(*this);
	BigInt b(bi);

	if (!a.is_correct())
	{
		std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	return string_to_number(a.number()) < string_to_number(b.number());
}

bool BigInt::operator<=(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	if (!a.is_correct())
	{
		std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	return
		string_to_number(a.number_) < string_to_number(b.number_) ||
		string_to_number(a.number_) == string_to_number(b.number_);
}

bool BigInt::operator>(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	if (!a.is_correct())
	{
		std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	return string_to_number(a.number_) > string_to_number(b.number_);
}

bool BigInt::operator>=(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	if (!a.is_correct())
	{
		std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	return
		string_to_number(a.number_) > string_to_number(b.number_) ||
		string_to_number(a.number_) == string_to_number(b.number_);
}

bool BigInt::operator==(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	if (!a.is_correct())
	{
		std::cout << "\nFrist operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	return string_to_number(a.number_) == string_to_number(b.number_);
}

// arithmetic operators:
BigInt BigInt::operator+(const BigInt& addendum) const
{
	BigInt sum;
	BigInt a(*this);
	BigInt b(addendum);

	if (a < b)
	{
		a.add_lead_zeroes(b.number_.size() - a.number_.size()); // implement this function member
	}
	else if (a > b)
	{
		b.add_lead_zeroes(a.number_.size() - b.number_.size()); // implement this function member
	}

	// будем складывать, начиная с млаших разрядов, для этого перевернём числа:
	reverse(a.number_);
	reverse(b.number_);

	// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
	size_t extra = 0;
	// промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
	size_t subtotal = 0;

	for (size_t i = 0; i < a.number_.size(); ++i)
	{
		subtotal = char_to_digit(a.number_[i]) + char_to_digit(b.number_[i]) + extra;

		if (subtotal > MAX_DIGIT) // десятичная система, поэтому последняя цифра в разряде 9
		{
			extra = subtotal / BASE;
			subtotal = subtotal % BASE;
		}
		else
		{
			extra = 0;
		}

		push_back(sum.number_, digit_to_char(subtotal));
	}

	if (extra)
	{
		push_back(sum.number_, digit_to_char(extra));
	}

	return sum;
}

BigInt BigInt::operator-(const BigInt& subtrahend) const
{
	BigInt diff(subtrahend); // temporary solution to avoid compiler warning
							 // TODO
	return diff;
}

BigInt BigInt::operator*(const BigInt& multiplier) const
{
	BigInt product(multiplier); // temporary solution to avoid compiler warning
								// TODO
	return product;
}

BigInt BigInt::operator/(const BigInt& divider) const
{
	BigInt result(divider); // temporary solution to avoid compiler warning
							// TODO
	return result;
}

BigFloat BigInt::operator+(const BigFloat& addendum) const
{
	BigFloat sum(addendum);
	// TODO
	return sum;
}

BigFloat BigInt::operator-(const BigFloat& subtrahend) const
{
	BigFloat diff(subtrahend); // temporary solution to avoid compiler warning
							   // TODO
	return diff;
}

BigFloat BigInt::operator*(const BigFloat& multiplier) const
{
	BigFloat product(multiplier); // temporary solution to avoid compiler warning
								  // TODO
	return product;
}

BigFloat BigInt::operator/(const BigFloat& divider) const
{
	BigFloat result(divider); // temporary solution to avoid compiler warning
							  // TODO
	return result;
}

//префиксная версия возвращает значение после инкремента
const BigInt& operator++(BigInt& bi)
{
	BigInt one("1");
	bi = bi + one;
	return bi;
}

//постфиксная версия возвращает значение до инкремента
const BigInt operator++(BigInt& bi, int fakeArg)
{
	BigInt one("1");
	BigInt oldValue(bi);

	bi = bi + one;
	return oldValue;
}

// input-output operators:
std::istream& operator >> (std::istream& is, BigInt& bi)
{
	is >> bi.number_;
	return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
	os << bi.number_;

	return os;
}