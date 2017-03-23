#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"
#include "bn_functions.h"

// ctors =======================================================================
BigInt::BigInt()
	: BigNumber()
{
/*
	std::cout << "Ctor BigInt::BigInt() has been called.\n";
*/
}

BigInt::BigInt(const std::string& num) // #ctor(arg)
	: BigNumber(num)
{
	if (has_leading_zeros())
	{
		pop_front_extra_zeros();
	}

	if (!is_correct(num))
	{
		reset();
	}
/*
	std::cout << "Ctor BigInt::BigInt(const std::string& num) has been called.\n";
*/
/*
	std::cout << "Num after all: " << get_number() << "\n";
*/
}

BigInt::BigInt(const BigInt& bi) // #copy ctor
	: BigNumber(bi.get_sign() + bi.get_number())
{
/*
	std::cout << "Ctor BigInt::BigInt(const BigInt& bi) has been called.\n";
*/
}



// checkers ====================================================================
bool BigInt::has_leading_zeros() const
{
	// for example: the number 0001234 has three leading zeros

	return get_number().size() > 1 && first_digit_value() == 0;
} //endof has_leading_zeros() const

bool BigInt::is_correct(const std::string& num) const
{
	bool correct = true;

	if (num.size() == 0)
	{
		std::cout << "BigInt is incorrect because arg size is 0.\n";
		correct = false;
	}
	else
	{
		if (is_one_char(num))
		{
			if (!is_digit(num[0])) // bi.number().at(0)
			{
				std::cout <<
					"BigInt is incorrect because arg size is 1 "
					"and the character is not a digit.\n";
				correct = false;
			}
		}
		else
		{
			for (size_t i = 0; i < num.size(); ++i)
			{
				if (!is_digit(num[i]) && !is_sign(num[i]))
				{
					std::cout
						<<
						"BigInt is incorrect because first character "
						"of the number is not a digit nor a sign.\n"
						<< "The character is : "
						<< num[0]
						<< "\n";
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



  // changers ====================================================================

  // вытолкнуть спереди (отбросить) лишние нули
void BigInt::pop_front_extra_zeros() // #pfez
{
	/*
	std::cout << "Function member BigNumber::pop_front_extra_zeros() has been called.\n\n";
	*/
	size_t fromPos = 0, toPos = 0;
	for (size_t i = 0; i < last_digit_position(); ++i)
	{
		if (elem_value_as_digit(i) == 0)
		{
			++toPos;
		}
		else
		{
			break;
		}
	}
	if (has_leading_zeros())
	{
		erase_elem(fromPos, toPos - 1);
	}
}



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

	if (bNumSize < aNumSize) // #op<(bi) 3
	{
/*
		std::cout
			<< "(bNumSize < aNumSize) is true. "
			<< "Assertion occured in BigInt.cpp, #op<(bi), branch 3\n"
			;
*/
		result = false;
	}
	else if (aNumSize < bNumSize) // #op<(bi) 4
	{
/*
		std::cout
			<< "(aNumSize < bNumSize) is true. "
			<< "Assertion occured in BigInt.cpp, #op<(bi), branch 4\n"
			;
*/
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
{
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
/*
		std::cout << 
			"\nbNumSize > aNumSize\n"
			"occured in #op>(bi) in branch 1\n";
*/
		result = false;
	}
	else if (aNumSize > bNumSize) // #op>(bi) 2
	{
/*
		std::cout <<
			"\naNumSize > bNumSize\n"
			"occured in #op>(bi) in branch 2\n";
*/
		// do nothing (object a indeed greater than b and result is true already)
	}
	else if (aNumSize == bNumSize) // #op>(bi) 3
	{
/*
		std::cout <<
			"\naNumSize == bNumSize\n"
			"occured in #op>(bi) in branch 3\n";
*/
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
{
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b);
} // endof operator>=(const BigInt& bi) const

bool BigInt::operator==(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b) && !(a > b);
} // endof operator==(const BigInt& bi) const



// arithmetic operators (both operands are same type) ===========================
BigInt BigInt::operator+(const BigInt& addendum) const
{
	BigInt sum;
	// #op+(bi) 1
/*
	std::cout
		<< "Sum is: "
		<< sum
		<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 1\n\n"
		;
*/
	BigInt a(*this);
	BigInt b(addendum);

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (aNumSize < bNumSize) // #op+(bi) 2
	{
/*
		std::cout
			<< "The object a have less digits than b. "
			<< "Object a before adding zeros: "
			<< a
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 2\n"
			;
*/
		a.push_front_additional_zeros(bNumSize - aNumSize);
/*
		std::cout
			<< "Object a after adding zeros: "
			<< a
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 2\n"
			;
*/
	}
	else if (aNumSize > bNumSize) // #op+(bi) 3
	{
/*
		std::cout
			<< "The object a have more digits than b. "
			<< "Object b before adding zeros: "
			<< b
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 3\n"
			;
*/
		b.push_front_additional_zeros(aNumSize - bNumSize);
/*
		std::cout
			<< "Object b after adding zeros: "
			<< b
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 3\n"
			;
*/
	}
	else // #op+(bi) 4
	{
/*
		std::cout
			<< "The objects a and b have same quantity of digits. "
			<< "Assertion occured in BigInt.cpp, #op+(bi), section 4\n"
			;
*/
		// do nothing (both numbers have same quantity of digits)
	}

	// будем складывать, начина€ с млаших разр€дов, дл€ этого перевернЄм числа:
	a.reverse_number();
	b.reverse_number();
	// #op+(bi) 5
/*
	std::cout
		<< "The objects a after reverse is: "
		<< a
		<< "\nThe objects b after reverse is: "
		<< b
		<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 5\n\n"
		;
*/
	// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
	size_t extra = 0;
	// промежуточный итог сложени€ двух цифр одинакового разр€да будем складывать в переменную subtotal:
	size_t subtotal = 0;

	// #op+(bi) 6
/*
	std::cout
		<< "aNumSize is: "
		<< aNumSize
		<< "\nbNumSize is: "
		<< bNumSize
		<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 6\n\n"
		;
*/
	bool hasBeenCalledBeforeYet = false;
	size_t limit = aNumSize > bNumSize ? aNumSize : bNumSize;
	for (size_t i = 0; i < limit; ++i)
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
		// #op+(bi) 7
/*
		std::cout
			<< i + 1 << " digit of number a is: "
			<< a.get_number()[i]
			<< "\n"
			<< i + 1 << " digit of number b is: "
			<< b.get_number()[i]
			<< "\nsubtotal is: "
			<< subtotal
			<< "\nextra is: "
			<< extra
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 7\n\n"
			;
*/
		sum.push_back_elem(digit_to_char(subtotal));
		if (!hasBeenCalledBeforeYet)
		{
			sum.pop_front_extra_zeros();
			hasBeenCalledBeforeYet = true;
		}

		// #op+(bi) 8
/*
		std::cout
			<< "Sum is: "
			<< sum
			<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 8\n\n"
			;
*/
	}

	if (extra)
	{
		sum.push_back_elem(digit_to_char(extra));
	}

	// #op+(bi) 9
/*
	std::cout
		<< "Sum is: "
		<< sum
		<< "\nAssertion occured in BigInt.cpp, #op+(bi), section 9\n\n"
		;
*/
	sum.reverse_number();
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



// arithmetic operators (each operand is different type) =======================
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
	fakeArg++;  // In fact, we don't need this.
				// This is to avoid compiler warnings.

	BigInt one("1");
	BigInt oldValue(bi);

	bi = bi + one;
	return oldValue;
} // endof BigInt operator++(BigInt& bi, int fakeArg)



// input-output operators ======================================================
std::istream& operator>>(std::istream& is, BigInt& bi)
{
	std::string num;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::getline(std::cin, num);

	bi.set_number(num);

	return is;
} // endof operator>>(std::istream& is, BigInt& bi)

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
	os << bi.get_sign() << bi.get_number();

	return os;
} // endof operator<<(std::ostream& os, const BigInt& bi)