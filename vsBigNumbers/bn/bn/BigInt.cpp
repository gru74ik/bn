#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"
#include "bn_functions.h"


// ctors =======================================================================
BigInt::BigInt() : BigNumber()
{
}

BigInt::BigInt(const std::string& num) : BigNumber(num)
{
	if (is_correct(num))
	{
		set_number(num);		
	}
	else
	{
		reset();
	}
}

BigInt::BigInt(const BigInt& bi)
{
	if (bi.is_correct())
	{
		set_number(bi.number());
	}
	else
	{
		reset();
	}
}

// checkers ====================================================================
bool BigInt::is_correct(const std::string& num) const
{
	bool correct = true;

	if (num.size() == 0) // if(number.empty())
	{
		correct = false;
	}
	else
	{
		if (is_one_char(num))
		{
			if (!is_digit(num[0])) // bi.number().at(0)
			{
				correct = false;
			}
		}
		else
		{
			if (!is_digit(num[0]))
			{
				correct = false;
			}

			for (size_t i = 1; i < num.size(); ++i)
			{
				if (!is_digit(num[i]))
				{
					correct = false;
					break;
				}
			}

		}
	}

	return correct;
} //endof is_correct(const std::string& number) const

bool BigInt::is_correct() const
{
	return is_correct(number());
} //endof is_correct() const

bool BigInt::is_greater_than_zero() const
{
	return has_leading_zeros() ? last_digit_value : sign() == '+' && first_digit_value() > 0;
} //endof is_greater_than_zero()

bool BigInt::is_less_than_zero() const
{
	return sign() == '-';
} // endof is_less_than_zero()

bool BigInt::is_zero() const
{
	return has_leading_zeros() ? last_digit_value : number() == "0";
} // endof is_zero()

// getters =====================================================================
size_t BigInt::last_digit_position() const
{
	return number().size() - 1;
} // endof last_digit_position()

size_t BigInt::last_digit_value() const
{
	return number()[last_digit_position()];
} // endof last_digit_value()

// setters =====================================================================
void BigInt::set_number(const std::string & num)
{
	if (is_correct(num))
	{
		BigNumber::set_number(num);
	}
	else
	{
		reset();
	}
} // endof set_number(const std::string & num)

// assignment operators ========================================================
BigInt BigInt::operator=(const BigInt& bi)
{
	if (this != &bi)
	{
		set_number(bi.number());
	}
	return *this;
} //endof operator=(const BigInt& bi)

BigInt BigInt::operator=(const std::string& num)
{
	if (number() != &num[0]) // &str.front()
	{
		set_number(num);
	}
	return *this;
} //endof operator=(const std::string& num)

// comparison operators ========================================================
bool BigInt::operator<(const BigInt& bi) const
{	
	bool result = true;

	BigInt a(*this);
	BigInt b(bi);

	if (!a.is_correct())
	{
		std::cout << "\nFirst operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	if (b.number().size() < a.number().size()) // #op<(bi) 1
	{
		result = false;
	}
	else if (a.number().size() < b.number().size()) // #op<(bi) 2
	{
		// do nothing (object a indeed less than b and result is true already)
	}
	else
	{
		bool bothNumbersAreTheSame = true;

		for (size_t i = 0; i < a.number().size(); ++i)
		{
			if (a.number()[i] < b.number()[i])
			{
				bothNumbersAreTheSame = false;
				result = true;
				continue;
			}
			else if (a.number()[i] == b.number()[i])
			{
				continue;
			}
			else
			{
				bothNumbersAreTheSame = false;
				result = false;
				break;
			}
		}

		if (bothNumbersAreTheSame)
		{
			result = false;
		}
	}

	return result;
} //endof operator<(const BigInt& bi) const

bool BigInt::operator<=(const BigInt& bi) const
{	// TODO: implement it right!
	BigInt a = *this;
	BigInt b = bi;

	return !(a > b);
} //endof operator<=(const BigInt& bi) const

bool BigInt::operator>(const BigInt& bi) const
{
	bool result = true;

	BigInt a(*this);
	BigInt b(bi);

	if (!a.is_correct())
	{
		std::cout << "\nFirst operand is incorrect. Comparison is impossible.\n";
		a.reset();
	}

	if (!b.is_correct())
	{
		std::cout << "\nSecond operand is incorrect. Comparison is impossible.\n";
		b.reset();
	}

	if (b.number().size() > a.number().size()) // #op<(bi) 1
	{
		result = false;
	}
	else if (a.number().size() > b.number().size()) // #op<(bi) 2
	{
		// do nothing (object a indeed greater than b and result is true already)
	}
	else
	{
		bool bothNumbersAreTheSame = true;

		for (size_t i = 0; i < a.number().size(); ++i)
		{
			if (a.number()[i] > b.number()[i])
			{
				bothNumbersAreTheSame = false;
				result = true;
				continue;
			}
			else if (a.number()[i] == b.number()[i])
			{
				continue;
			}
			else
			{
				bothNumbersAreTheSame = false;
				result = false;
				break;
			}
		}

		if (bothNumbersAreTheSame)
		{
			result = false;
		}
	}

	return result;
}	// endof operator>(const BigInt& bi) const

bool BigInt::operator>=(const BigInt& bi) const
{	// TODO: implement it right!
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b);
} // endof operator>=(const BigInt& bi) const

bool BigInt::operator==(const BigInt& bi) const
{	// TODO: implement it right!
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b) && !(a > b);
} // endof operator==(const BigInt& bi) const

// arithmetic operators ========================================================
BigInt BigInt::operator+(const BigInt& addendum) const
{	// TODO: implement it right!
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

	// будем складывать, начина€ с млаших разр€дов, дл€ этого перевернЄм числа:
	reverse(a.number_);
	reverse(b.number_);

	// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
	size_t extra = 0;
	// промежуточный итог сложени€ двух цифр одинакового разр€да будем складывать в переменную subtotal:
	size_t subtotal = 0;

	for (size_t i = 0; i < a.number_.size(); ++i)
	{
		subtotal = char_to_digit(a.number_[i]) + char_to_digit(b.number_[i]) + extra;

		if (subtotal > MAX_DIGIT) // дес€тична€ система, поэтому последн€€ цифра в разр€де 9
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
} // endof operator+(const BigInt& addendum) const

BigInt BigInt::operator-(const BigInt& subtrahend) const
{	// TODO: implement this function member!
	BigInt diff(subtrahend); // temporary solution to avoid compiler warning

	return diff;
} // endof operator-(const BigInt& subtrahend) const

BigInt BigInt::operator*(const BigInt& multiplier) const
{	// TODO: implement this function member!
	BigInt product(multiplier); // temporary solution to avoid compiler warning

	return product;
} // endof operator*(const BigInt& multiplier) const

BigInt BigInt::operator/(const BigInt& divider) const
{	// TODO: implement this function member!
	BigInt result(divider); // temporary solution to avoid compiler warning

	return result;
} // endof operator/(const BigInt& divider) const

BigFloat BigInt::operator+(const BigFloat& addendum) const
{	// TODO: implement this function member!
	BigFloat sum(addendum);

	return sum;
} // endof operator+(const BigFloat& addendum) const

BigFloat BigInt::operator-(const BigFloat& subtrahend) const
{	// TODO: implement this function member!
	BigFloat diff(subtrahend); // temporary solution to avoid compiler warning

	return diff;
} // endof operator-(const BigFloat& subtrahend) const

BigFloat BigInt::operator*(const BigFloat& multiplier) const
{	// TODO: implement this function member!
	BigFloat product(multiplier); // temporary solution to avoid compiler warning

	return product;
} // endof operator*(const BigFloat& multiplier) const

BigFloat BigInt::operator/(const BigFloat& divider) const
{	// TODO: implement this function member!
	BigFloat result(divider); // temporary solution to avoid compiler warning

	return result;
} // endof operator/(const BigFloat& divider) const

//префиксна€ верси€ возвращает значение после инкремента
const BigInt& operator++(BigInt& bi)
{
	BigInt one("1");
	bi = bi + one;
	return bi;
} // endof operator++(BigInt& bi)

//постфиксна€ верси€ возвращает значение до инкремента
const BigInt operator++(BigInt& bi, int fakeArg)
{
	BigInt one("1");
	BigInt oldValue(bi);

	bi = bi + one;
	return oldValue;
} // endof BigInt operator++(BigInt& bi, int fakeArg)

// input-output operators ======================================================
std::istream& operator>>(std::istream& is, BigInt& bi)
{
	is >> bi.number();
	return is;
} // endof operator>>(std::istream& is, BigInt& bi)

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
	os << bi.sign << bi.number();

	return os;
} // endof operator<<(std::ostream& os, const BigInt& bi)