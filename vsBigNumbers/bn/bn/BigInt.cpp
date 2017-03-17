#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"
#include "bn_functions.h"

// ctors =======================================================================
BigInt::BigInt()
	: BigNumber()
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
		set_number(bi.get_number());
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
	return is_correct(get_number());
} //endof is_correct() const

bool BigInt::is_greater_than_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}
	return num.get_sign() == '+' && num.first_digit_value() != 0;
} //endof is_greater_than_zero()

bool BigInt::is_less_than_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}
	return num.get_sign() == '-' && num.first_digit_value() != 0;
} // endof is_less_than_zero()

bool BigInt::is_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}

	return num.get_number() == "0";
} // endof is_zero()

// getters =====================================================================
size_t BigInt::last_digit_position() const
{
	return get_number().size() - 1;
} // endof last_digit_position()

size_t BigInt::last_digit_value() const
{
	return get_number()[last_digit_position()];
} // endof last_digit_value()

// setters =====================================================================
void BigInt::set_number(const BigInt& bi)
{
	if (is_correct(bi.get_number()))
	{
		BigNumber::set_number(bi.get_number());
	}
	else
	{
		reset();
	}
} // endof set_number(const std::string & num)

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
		set_number(bi.get_number());
	}
	return *this;
} //endof operator=(const BigInt& bi)

BigInt BigInt::operator=(const std::string& num)
{
	if (get_number() != &num[0]) // &str.front()
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

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (bNumSize < aNumSize) // #op<(bi) 1
	{
		result = false;
	}
	else if (aNumSize < bNumSize) // #op<(bi) 2
	{
		// do nothing (object a indeed less than b and result is true already)
	}
	else
	{
		bool bothNumbersAreTheSame = true;

		for (size_t i = 0; i < aNumSize; ++i)
		{
			if (a.get_number()[i] < b.get_number()[i])
			{
				bothNumbersAreTheSame = false;
				result = true;
				continue;
			}
			else if (a.get_number()[i] == b.get_number()[i])
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

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (bNumSize > aNumSize) // #op>(bi) 1
	{
		result = false;
	}
	else if (aNumSize > bNumSize) // #op>(bi) 2
	{
		// do nothing (object a indeed greater than b and result is true already)
	}
	else
	{
		bool bothNumbersAreTheSame = true;

		for (size_t i = 0; i < aNumSize; ++i)
		{
			if (a.get_number()[i] > b.get_number()[i])
			{
				bothNumbersAreTheSame = false;
				result = true;
				continue;
			}
			else if (a.get_number()[i] == b.get_number()[i])
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

// arithmetic operators =========================================================
// (both operands are same type)
BigInt BigInt::operator+(const BigInt& addendum) const
{
	BigInt sum;
	BigInt a(*this);
	BigInt b(addendum);

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (a < b)
	{
		a.push_front_additional_zeros(bNumSize - aNumSize);
	}
	else if (a > b)
	{
		b.push_front_additional_zeros(aNumSize - bNumSize);
	}

	// будем складывать, начина€ с млаших разр€дов, дл€ этого перевернЄм числа:
	reverse(a.get_number());
	reverse(b.get_number());

	// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
	size_t extra = 0;
	// промежуточный итог сложени€ двух цифр одинакового разр€да будем складывать в переменную subtotal:
	size_t subtotal = 0;

	for (size_t i = 0; i < aNumSize; ++i)
	{
		subtotal = char_to_digit(a.get_number()[i]) + char_to_digit(b.get_number()[i]) + extra;

		if (subtotal > MAX_DIGIT) // дес€тична€ система, поэтому последн€€ цифра в разр€де 9
		{
			extra = subtotal / BASE;
			subtotal = subtotal % BASE;
		}
		else
		{
			extra = 0;
		}

		push_back(sum.get_number(), digit_to_char(subtotal));
	}

	if (extra)
	{
		push_back(sum.get_number(), digit_to_char(extra));
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

// arithmetic operators ========================================================
// (each operand is different type)
/*
BigFloat BigInt::operator+(const BigInt& a, const BigFloat& b)
{
	BigFloat x(a);
	BigFloat y(b);

	return x + y;
} // endof operator+(const BigFloat& addendum) const

BigFloat BigInt::operator-(const BigInt& a, const BigFloat& b)
{
	BigFloat x(a);
	BigFloat y(b);

	return x - y;
} // endof operator-(const BigFloat& subtrahend) const

BigFloat BigInt::operator*(const BigInt& a, const BigFloat& b)
{
	BigFloat x(a);
	BigFloat y(b);

	return x * y;
} // endof operator*(const BigFloat& multiplier) const

BigFloat BigInt::operator/(const BigInt& a, const BigFloat& b)
{
	BigFloat x(a);
	BigFloat y(b);

	return x / y;
} // endof operator/(const BigFloat& divider) const
*/
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
	is >> bi.get_number();
	return is;
} // endof operator>>(std::istream& is, BigInt& bi)

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
	os << bi.get_sign() << bi.get_number();

	return os;
} // endof operator<<(std::ostream& os, const BigInt& bi)