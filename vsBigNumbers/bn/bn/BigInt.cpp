#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"
#include "BigFloat.h"
#include "bn_functions.h"

// ctors =======================================================================
BigInt::BigInt()
	: BigNumber()
{
}

BigInt::BigInt(const char num)
	: BigNumber(num)
{
	std::string numAsStr = "";
	numAsStr = numAsStr + num;
	if (!is_correct(numAsStr))
	{
		reset();
	}
}

BigInt::BigInt(const std::string& num)
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
}

BigInt::BigInt(const BigInt& bi) // #copy ctor
	: BigNumber(bi.get_sign() + bi.get_number())
{
}



// checkers ====================================================================
bool BigInt::has_leading_zeros() const
{
	// for example: the number 0001234 has three leading zeros
	return get_number().size() > 1 && first_digit_value() == 0;
}

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
			if (!is_digit(num[0]))
			{
				std::cout
					<<
					"BigInt is incorrect because arg size is 1 "
					"and the character is not a digit."
					<< "\nThe character is: " << num[0] << "\n\n";
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
}

bool BigInt::is_greater_than_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}
	return num.get_sign() == '+' && num.first_digit_value() != 0;
}

bool BigInt::is_less_than_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}
	return num.get_sign() == '-' && num.first_digit_value() != 0;
}

bool BigInt::is_zero() const
{
	BigInt num(*this);

	if (has_leading_zeros())
	{
		num.pop_front_extra_zeros();
	}

	return num.get_number() == "0";
}



// changers ====================================================================

void BigInt::pop_front_extra_zeros()
{
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
BigInt BigInt::abs_value() const
{
	return get_number();
}

size_t BigInt::quantity_of_digits() const
{
	return get_number().size();
}

size_t BigInt::last_digit_position() const
{
	return get_number().size() - 1;
}

size_t BigInt::last_digit_value() const
{
	return elem_value_as_digit(last_digit_position());
}



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
}

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
}



// assignment operators ========================================================
BigInt BigInt::operator=(const BigInt& bi)
{
	if (this != &bi)
	{
		set_number(bi.get_number());
	}
	return *this;
}

BigInt BigInt::operator=(const std::string& num)
{
	if (get_number() != &num[0]) // &str.front()
	{
		set_number(num);
	}
	return *this;
}



// comparison operators ========================================================
bool BigInt::operator<(const BigInt& bi) const
{	
	bool result = true;

	BigInt a(*this);
	BigInt b(bi);

	a.pop_front_extra_zeros();
	b.pop_front_extra_zeros();

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (a.get_sign() == '+' && b.get_sign() == '-')
	{
		result = false;
	}
	else if (a.get_sign() == '-' && b.get_sign() == '+')
	{
		result = true;
	}
	else if (a.get_sign() == '+' && b.get_sign() == '+')
	{
		if (b.quantity_of_digits() < a.quantity_of_digits())
		{
			result = false;
		}
		else if (a.quantity_of_digits() < b.quantity_of_digits())
		{
			result = true;
		}
		else
		{
			bool bothNumbersAreTheSame = true;

			for (size_t i = 0; i < aNumSize; ++i)
			{
				if (a.elem_value_as_digit(i) < b.elem_value_as_digit(i))
				{
					bothNumbersAreTheSame = false;
					result = true;
					break;
				}
				else if (a.elem_value_as_digit(i) == b.elem_value_as_digit(i))
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
	} // endof else if (a.get_sign() == b.get_sign())
	else
	{
		if (b.quantity_of_digits() < a.quantity_of_digits())
		{
			result = true;
		}
		else if (a.quantity_of_digits() < b.quantity_of_digits())
		{
			result = false;
		}
		else
		{
			bool bothNumbersAreTheSame = true;

			for (size_t i = 0; i < aNumSize; ++i)
			{
				if (a.elem_value_as_digit(i) < b.elem_value_as_digit(i))
				{
					bothNumbersAreTheSame = false;
					result = false;
					break;
				}
				else if (a.elem_value_as_digit(i) == b.elem_value_as_digit(i))
				{
					continue;
				}
				else
				{
					bothNumbersAreTheSame = false;
					result = true;
					break;
				}
			}

			if (bothNumbersAreTheSame)
			{
				result = false;
			}
		}
	}

	return result;
} //endof operator<(const BigInt& bi) const

bool BigInt::operator<=(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	return !(a > b);
}

bool BigInt::operator>(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	return b < a;
}

bool BigInt::operator>=(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b);
}

bool BigInt::operator==(const BigInt& bi) const
{
	BigInt a = *this;
	BigInt b = bi;

	return !(a < b) && !(a > b);
}

bool BigInt::operator!=(const BigInt & bi) const
{
	BigInt a(*this);
	BigInt b(bi);

	return (a < b) || (a > b);
}



// arithmetic operators (both operands are same type) ===========================
BigInt BigInt::operator+(const BigInt& addendum) const
{
	BigInt sum;
	BigInt a(*this);
	BigInt b(addendum);

	size_t aNumSize = a.get_number().size();
	size_t bNumSize = b.get_number().size();

	if (aNumSize < bNumSize)
	{
		a.push_front_additional_zeros(bNumSize - aNumSize);
	}
	else if (aNumSize > bNumSize)
	{
		b.push_front_additional_zeros(aNumSize - bNumSize);
	}
	else
	{
		// do nothing (both numbers have same quantity of digits)
	}

	a.reverse_number();
	b.reverse_number();

	size_t extra = 0;
	size_t subtotal = 0;
	bool hasBeenCalledBeforeYet = false;
	size_t limit = aNumSize > bNumSize ? aNumSize : bNumSize;
	for (size_t i = 0; i < limit; ++i)
	{
		subtotal = char_to_digit(a.get_number()[i]) + char_to_digit(b.get_number()[i]) + extra;

		if (subtotal > MAX_DIGIT)
		{
			extra = subtotal / BASE;
			subtotal = subtotal % BASE;
		}
		else
		{
			extra = 0;
		}

		sum.push_back_elem(digit_to_char(subtotal));
		if (!hasBeenCalledBeforeYet)
		{
			sum.pop_front_extra_zeros();
			hasBeenCalledBeforeYet = true;
		}
	}

	if (extra)
	{
		sum.push_back_elem(digit_to_char(extra));
	}

	sum.reverse_number();
	return sum;
} // endof operator+(const BigInt& addendum) const

BigInt BigInt::operator-(const BigInt& subtrahend) const
{
	BigInt diff;
	diff.clear_number();
	BigInt a(*this);
	BigInt b(subtrahend);
	size_t quantity = 0;
	if (a.quantity_of_digits() > b.quantity_of_digits())
	{
		quantity = a.quantity_of_digits() - b.quantity_of_digits();
		b.push_front_additional_zeros(quantity);
	}
	else if (b.quantity_of_digits() > a.quantity_of_digits())
	{
		quantity = b.quantity_of_digits() - a.quantity_of_digits();
		a.push_front_additional_zeros(quantity);
	}

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

	if (a.get_sign() == b.get_sign())
	{
		BigInt minuendNonReversed(a);
		BigInt subtrahendNonReversed(b);

		a.reverse_number();
		b.reverse_number();

		size_t subtotal = 0;
		size_t minuendDigit = 0;
		size_t subtrahendDigit = 0;
		size_t borrowed = 0;
		size_t prevBorrowed = 0;

		if (minuendNonReversed > subtrahendNonReversed)
		{
			for (size_t i = 0; i < aSize; ++i)
			{
				minuendDigit = a.elem_value_as_digit(i);
				subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed;
				if (minuendDigit < subtrahendDigit)
				{
					borrowed = 1;
				}
				else
				{
					borrowed = 0;
				}
				minuendDigit = minuendDigit + borrowed * 10;
				subtotal = minuendDigit - subtrahendDigit;
				diff.push_back_elem(digit_to_char(subtotal));
				prevBorrowed = borrowed;
			} // endof for (size_t i = 0; i < aSize; ++i)
			diff.set_sign('+');
		} // endof if (a > b)
		else if (subtrahendNonReversed > minuendNonReversed)
		{
			for (size_t i = 0; i < aSize; ++i)
			{
				minuendDigit = b.elem_value_as_digit(i);
				subtrahendDigit = a.elem_value_as_digit(i) + prevBorrowed;
				if (minuendDigit < subtrahendDigit)
				{
					borrowed = 1;
				}
				else
				{
					borrowed = 0;
				}
				minuendDigit = minuendDigit + borrowed * 10;
				subtotal = minuendDigit - subtrahendDigit;
				diff.push_back_elem(digit_to_char(subtotal));
				prevBorrowed = borrowed;
			} // endof for (size_t i = 0; i < aSize; ++i)
			diff.set_sign('-');		
		} // endof else if (b > a)
		else
		{
			diff.reset();
			diff.set_sign('+');
		}
		diff.reverse_number();
	} // endof if (a.get_sign() == b.get_sign())
	else
	{
		if (a.abs_value() < b.abs_value())
		{
			diff = a + b;
			diff.set_sign('+');
		}
		else if (b.abs_value() < a.abs_value())
		{
			diff = a + b;
			diff.set_sign('-');
		}
		else
		{
			diff.reset();
			diff.set_sign('+');
		}		
	}
	
	diff.pop_front_extra_zeros();

	return diff;
} // endof operator-(const BigInt& subtrahend) const

BigInt BigInt::operator*(const BigInt& multiplier) const
{
	BigInt product;
	product.clear_number();
	BigInt a(*this);
	BigInt b(multiplier);

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

	a.reverse_number();
	b.reverse_number();

	size_t extra = 0;
	size_t digitsProd = 0;
	BigInt subtotalProd;
	subtotalProd.clear_number();

	BigInt sumOfSubtotals;
	sumOfSubtotals.clear_number();

	for (size_t i = 0; i < bSize; ++i)
	{
		for (size_t j = 0; j < aSize; ++j)
		{
			digitsProd = b.elem_value_as_digit(i) * a.elem_value_as_digit(j) + extra;
			subtotalProd.push_back_elem(digit_to_char(digitsProd % BigNumber::BASE));
			extra = digitsProd / BigNumber::BASE;
		}

		if (i)
		{
			subtotalProd.push_front_additional_zeros(i);
		}

		if (extra)
		{
			subtotalProd.push_back_elem(digit_to_char(extra));
		}

		sumOfSubtotals.reverse_number();
		subtotalProd.reverse_number();

		sumOfSubtotals = sumOfSubtotals + subtotalProd;

		sumOfSubtotals.reverse_number();

		subtotalProd.clear_number();
		extra = 0;
	} // endof outer for

	sumOfSubtotals.reverse_number();
	product.set_number(sumOfSubtotals);

	if (a.get_sign() == b.get_sign())
	{
		if (a.get_sign() == '+')
		{
			product.set_sign('+');
		}
		else
		{
			product.set_sign('-');
		}
	}
	else
	{
		product.set_sign('-');
	}

	return product;
} // endof operator*(const BigInt& multiplier) const

BigInt BigInt::operator/(const BigInt& divider) const
{	// TODO: implement this function member!
	BigInt result(divider); // temporary solution to avoid compiler warning

	return result;
}



// arithmetic operators (each operand is different type) =======================
BigFloat BigInt::operator+(const BigFloat& b) const
{
	BigFloat x(*this);
	BigFloat y(b);

	return x + y;
}

BigFloat BigInt::operator-(const BigFloat& b) const
{
	BigFloat x(*this);
	BigFloat y(b);

	return x - y;
}

BigFloat BigInt::operator*(const BigFloat& b) const
{
	BigFloat x(*this);
	BigFloat y(b);

	return x * y;
}

BigFloat BigInt::operator/(const BigFloat& b) const
{
	BigFloat x(*this);
	BigFloat y(b);

	return x / y;
}



// increment operators =========================================================

const BigInt& operator++(BigInt& bi) // prefix version
{
	BigInt one("1");
	bi = bi + one;
	return bi;
}

const BigInt operator++(BigInt& bi, int fakeArg) // postfix version
{
	fakeArg++;  // In fact, we don't need this.
				// This is to avoid compiler warnings.
	BigInt one("1");
	BigInt oldValue(bi);

	bi = bi + one;
	return oldValue;
}



// input-output operators ======================================================
std::istream& operator>>(std::istream& is, BigInt& bi)
{
	std::string num;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::getline(std::cin, num);

	bi.set_number(num);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
	os << bi.get_sign() << bi.get_number();

	return os;
}