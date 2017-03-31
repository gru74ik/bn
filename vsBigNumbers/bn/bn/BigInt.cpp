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

BigInt::BigInt(const std::string& num) // #ctor(str)
	: BigNumber(num)
{
	/**/
	std::cout << "Ctor BigInt::BigInt(const std::string& num) has been called.\n\n";

	if (has_leading_zeros())
	{
		/**/
		// #ctor(str) 1
		std::cout
			<< "The number has leading zeros."
			<< "\nget_number(): " << get_number()
			<< "\nAssertion occured in BigInt.cpp, #ctor(str) 1.\n\n"
			;
		pop_front_extra_zeros();
		/**/
		// #ctor(str) 2
		std::cout
			<< "BigInt::pop_front_extra_zeros() has been called."
			<< "\nThe number after erasing extra zeros:"
			<< "\nget_number(): " << get_number()
			<< "\nAssertion occured in BigInt.cpp, #ctor(str) 2.\n\n"
			;
	}

	if (!is_correct(num))
	{
		/**/
		// #ctor(str) 3
		std::cout
			<< "BigInt::is_correct(num) has been called and the number is incorrect."
			<< "\nget_number(): " << get_number()
			<< "\nAssertion occured in BigInt.cpp, #ctor(str) 3.\n\n"
			;
		reset();
		/**/
		// #ctor(str) 4
		std::cout
			<< "reset() has been called and the number is incorrect."
			<< "\nget_number(): " << get_number()
			<< "\nAssertion occured in BigInt.cpp, #ctor(str) 4.\n\n"
			;
	}
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
BigInt BigInt::abs_value()
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
/**/
		// #setn(bi) 1
		std::cout
			<< "The BigInt is correct."
			<< "\nbi.get_number(): " << bi.get_number()
			<< "\nAssertion occured in BigInt.cpp, #setn(bi) 1.\n\n"
			;

		BigNumber::set_number(bi.get_number());
	}
	else
	{
/**/
		// #setn(bi) 2
		std::cout
			<< "The BigInt is incorrect."
			<< "\nbi.get_number(): " << bi.get_number()
			<< "\nAssertion occured in BigInt.cpp, #setn(bi) 2.\n\n"
			;
		reset();
	}
} // endof set_number(const std::string & num)

void BigInt::set_number(const std::string & num)
{
	if (is_correct(num))
	{
/*
		// #setn(str) 1
		std::cout
			<< "BigInt::is_correct() has been called and the number is correct."
			<< "\nnum: " << num
			<< "\nAssertion occured in BigInt.cpp, #setn(str) 1.\n\n"
			;
*/
		BigNumber::set_number(num);
	}
	else
	{
/*
		// #setn(str) 2
		std::cout
			<< "BigInt::is_correct() has been called and the number is incorrect."
			<< "\nnum: " << num
			<< "\nAssertion occured in BigInt.cpp, #setn(str) 2.\n\n"
			;
*/
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

	// будем складывать, начиная с млаших разрядов, для этого перевернём числа:
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
	// промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
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

		if (subtotal > MAX_DIGIT) // десятичная система, поэтому последняя цифра в разряде 9
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
{
	BigInt diff;

/*
	// #op-(bi) 1
	std::cout
		<< "diff in beginning: " << diff.get_number()
		<< "\nAssertion occured in BigInt.cpp, #op-(bi) 1.\n\n"
		;
*/
	diff.clear_number();
/*
	// #op-(bi) 2
	std::cout
		<< "diff after cleaning: " << diff.get_number()
		<< "\nAssertion occured in BigInt.cpp, #op-(bi) 2.\n\n"
		;
*/
	BigInt a(*this);
	BigInt b(subtrahend);

	// уравниваем количество разрядов обоих чисел:
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
/*
	// #op-(bi) 10
	std::cout
		<< "Data members after #op-(bf) finished align numbers:"
		<< "\na (without sign): " << a.get_number()
		<< "\nb (without sign): " << b.get_number()
		<< "\nAssertion occured in BigInt.cpp, #op-(bi) 10.\n\n"
		;
*/

	if (a.get_sign() == b.get_sign())
	{
		// считать будем с младших разрядов, поэтому "перевернём" оба числа:
		a.reverse_number();
		b.reverse_number();

/**/
		// #op-(bf) 11
		std::cout
			<< "Data members after #op-(bi) finished reverse numbers:"
			<< "\na (without sign): " << a.get_number()
			<< "\nb (without sign): " << b.get_number()
			<< "\nAssertion occured in BigInt.cpp, #op-(bi) 11.\n\n"
			;

		// промежуточный итог сложения двух цифр одинакового
		// разряда будем складывать в переменную subtotal:
		size_t subtotal = 0;

		// уменьшаемая цифра:
		size_t minuendDigit = 0;

		// вычитаемая цифра:
		size_t subtrahendDigit = 0;

		// занимать единичку из старшего разряда будем,
		// складывая её в переменную borrowed:
		size_t borrowed = 0;

		// "долги" с предыдущего витка цикла:
		size_t prevBorrowed = 0;
		if (a > b)
		{
			for (size_t i = 0; i < aSize; ++i)
			{
				minuendDigit = a.elem_value_as_digit(i);
				subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed;
				if (minuendDigit < subtrahendDigit)
				{	// если уменьшаемая цифра меньше, чем вычитаемая,
					// значит занимаем из старшего разряда единицу:
					borrowed = 1;
				}
				else
				{	// иначе, ничего не занимаем:
					borrowed = 0;
				}
				minuendDigit = minuendDigit + borrowed * 10;
				subtotal = minuendDigit - subtrahendDigit;
	/**/
				// #op-(bi) 20
				std::cout
					<< "Data on " << i + 1 << " step:"
					<< "\nminuendDigit: " << minuendDigit
					<< "\nsubtrahendDigit: " << subtrahendDigit
					<< "\nsubtotal: " << subtotal
					<< "\nAssertion occured in BigInt.cpp, #op-(bi) 20.\n\n"
					;

				diff.push_back_elem(digit_to_char(subtotal));
				prevBorrowed = borrowed;

	/**/
				// #op-(bi) 21
				std::cout
					<< "Diff on " << i + 1 << " step: " << diff.get_number()
					<< "\nAssertion occured in BigInt.cpp, #op-(bi) 21.\n\n"
					;

			} // endof for (size_t i = 0; i < aSize; ++i)
			diff.set_sign('+');
/**/
			// #op-(bi) 21a
			std::cout
				<< "\nDiff after all: " << diff.get_sign() << diff.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op-(bi) 21a.\n\n"
				;

		} // endof if (a > b)
		else if (b > a)
		{
			for (size_t i = 0; i < aSize; ++i)
			{
				minuendDigit = b.elem_value_as_digit(i);
				subtrahendDigit = a.elem_value_as_digit(i) + prevBorrowed;
				if (minuendDigit < subtrahendDigit)
				{	// если уменьшаемая цифра меньше, чем вычитаемая,
					// значит занимаем из старшего разряда единицу:
					borrowed = 1;
				}
				else
				{	// иначе, ничего не занимаем:
					borrowed = 0;
				}
				minuendDigit = minuendDigit + borrowed * 10;
				subtotal = minuendDigit - subtrahendDigit;
				/**/
				// #op-(bi) 22
				std::cout
					<< "Data on " << i + 1 << " step:"
					<< "\nminuendDigit: " << minuendDigit
					<< "\nsubtrahendDigit: " << subtrahendDigit
					<< "\nsubtotal: " << subtotal
					<< "\nAssertion occured in BigInt.cpp, #op-(bi) 22.\n\n"
					;

				diff.push_back_elem(digit_to_char(subtotal));
				prevBorrowed = borrowed;

				/**/
				// #op-(bi) 23
				std::cout
					<< "Diff on " << i + 1 << " step: " << diff.get_number()
					<< "\nAssertion occured in BigInt.cpp, #op-(bi) 23.\n\n"
					;

			} // endof for (size_t i = 0; i < aSize; ++i)
			diff.set_sign('-');
/**/
			// #op-(bi) 23a
			std::cout
				<< "\nDiff after all: " << diff.get_sign() << diff.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op-(bi) 23a.\n\n"
				;
			
		} // endof else if (b > a)
		else
		{
			diff.reset();
			diff.set_sign('+');
/**/
			// #op-(bi) 24
			std::cout
				<< "a.abs_value() == b.abs_value()"
				<< "\nDiff equals to zero:"
				<< "\ndiff.get_number(): " << diff.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op-(bi) 24.\n\n"
				;
		}


/*
		// #op-(bi) 26
		std::cout
			<< "Diff before reversing: " << diff.get_number()
			<< "\nAssertion occured in BigInt.cpp, #op-(bi) 26.\n\n"
			;
*/
		diff.reverse_number();
/*
		// #op-(bi) 27
		std::cout
			<< "Diff after reversing: " << diff.get_number()
			<< "\nAssertion occured in BigInt.cpp, #op-(bi) 27.\n\n"
			;
*/
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

	return diff;
} // endof operator-(const BigInt& subtrahend) const

BigInt BigInt::operator*(const BigInt& multiplier) const
{
	BigInt product;
/*
	// #op*(bi) 1
	std::cout
		<< "product in beginning: " << product.get_number()
		<< "\nAssertion occured in BigInt.cpp, #op*(bi) 1.\n\n"
		;
*/
	product.clear_number();
	/*
	// #op*(bi) 2
	std::cout
	<< "sproduct after cleaning: " << product.clear_number()
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 2.\n\n"
	;
	*/
	BigInt a(*this);
	BigInt b(multiplier);

	/*
	// #op*(bi) 3
	std::cout
	<< "Data of temporary objects a and b in beginning: "
	<< "\na.get_sign() and a.get_number(): " << a.get_sign() << a.get_number()
	<< "\na itself: " << a
	<< "\nb.get_sign() and b.get_number(): " << b.get_sign() << b.get_number()
	<< "\nb itself: " << b
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 3.\n\n"
	;
	*/

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();
	/*
	// #op*(bi) 4
	std::cout
	<< "Size of temporary objects a and b in beginning: "
	<< "\naSize: " << aSize
	<< "\nbSize: " << bSize
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 4.\n\n"
	;
	*/

	// будем умножать, начиная с млаших разрядов, для этого перевернём числа:
	a.reverse_number();
	b.reverse_number();
	/*
	// #op*(bi) 12
	std::cout
	<< "The numbers after reversing: "
	<< "\na.get_number(): " << a.get_number()
	<< "\nb.get_number(): " << b.get_number()
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 12.\n\n"
	;
	*/

	// излишки (то, что обычно при умножении в столбик "пишем в уме")
	// будем складывать в переменную extra;
	size_t extra = 0;

	// итог умножения двух цифр одинакового разряда
	// будем складывать в переменную digitsProd:
	size_t digitsProd = 0;

	// итог умножения цифры текущего разряда на число
	// будем складывать в переменную subtotalProd:
	BigInt subtotalProd;
	subtotalProd.clear_number();
	/*
	// #op*(bi) 13
	std::cout
	<< "The number named subtotalProd of type BigInt has been created."
	<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 13.\n\n"
	;
	*/

	// сумму промежуточных результатов умножения
	// будем складывать в переменную sumOfSubtotals:
	BigInt sumOfSubtotals;
	sumOfSubtotals.clear_number();
	/*
	// #op*(bi) 14
	std::cout
	<< "The number named sumOfSubtotals of type BigInt has been created."
	<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
	<< "\nAssertion occured in BigInt.cpp, #op*(bi) 14.\n\n"
	;
	*/
	for (size_t i = 0; i < bSize; ++i)
	{
		/*
		// #op*(bi) 15
		std::cout
		<< "Outer for loop: iteration " << i + 1
		<< "\nAssertion occured in BigInt.cpp, #op*(bi) 15.\n\n"
		;
		*/
		for (size_t j = 0; j < aSize; ++j)
		{
			/*
			// #op*(bi) 16
			std::cout
			<< "Inner for loop: iteration " << j + 1
			<< "\nAssertion occured in BigInt.cpp, #op*(bi) 16.\n\n"
			;
			*/
			/*
			// #op*(bi) 17
			std::cout
			<< "digitsProd before assignment: " << digitsProd
			<< "\nAssertion occured in BigInt.cpp, #op*(bi) 17.\n\n"
			;
			*/
			/*
			// #op*(bi) 18
			std::cout
			<< "b.get_number(): " << b.get_number()
			<< "\nb.elem_value_as_digit(i): " << b.elem_value_as_digit(i)
			<< "\nindex i: " << i
			<< "\nbSize: " << bSize
			<< "\nAssertion occured in BigInt.cpp, #op*(bi) 18.\n\n"
			;
			*/
			/*
			// #op*(bi) 19
			std::cout
			<< "a.get_number(): " << a.get_number()
			<< "\na.elem_value_as_digit(j): " << a.elem_value_as_digit(j)
			<< "\nindex j: " << j
			<< "\naSize: " << aSize
			<< "\nAssertion occured in BigInt.cpp, #op*(bi) 19.\n\n"
			;
			*/
			/**/
			// #op*(bi) 20
			std::cout
				<< "extra: " << extra
				<< "\nAssertion occured in BigInt.cpp, #op*(bi) 20.\n\n"
				;

			digitsProd = b.elem_value_as_digit(i) * a.elem_value_as_digit(j) + extra;
			/**/
			// #op*(bi) 21
			std::cout
				<< "digitsProd after assignment: " << digitsProd
				<< "\nAssertion occured in BigInt.cpp, #op*(bi) 21.\n\n"
				;

			subtotalProd.push_back_elem(digit_to_char(digitsProd % BigNumber::BASE));
			/**/
			// #op*(bi) 22
			std::cout
				<< "subtotalProd after calling push_back_elem: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op*(bi) 27.\n\n"
				;

			extra = digitsProd / BigNumber::BASE;
		} // endof inner for

		if (i)
		{
			subtotalProd.push_front_additional_zeros(i);
			/**/
			// #op*(bi) 28
			std::cout
				<< "subtotalProd after pushing back additional zeros: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op*(bi) 28.\n\n"
				;

		}

		if (extra)
		{
			subtotalProd.push_back_elem(digit_to_char(extra));
			/**/
			// #op*(bi) 29
			std::cout
				<< "subtotalProd after pushing back remaining extra: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigInt.cpp, #op*(bi) 29.\n\n"
				;

		}

		sumOfSubtotals.reverse_number();
		subtotalProd.reverse_number();

		sumOfSubtotals = sumOfSubtotals + subtotalProd;

		sumOfSubtotals.reverse_number();

		subtotalProd.clear_number();
		extra = 0;
		/**/
		// #op*(bi) 30
		std::cout
			<< "sumOfSubtotals at " << i + 1 << " iteration: "
			<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
			<< " ======================================"
			<< "\nAssertion occured in BigInt.cpp, #op*(bi) 30.\n\n"
			;

	} // endof outer for

	sumOfSubtotals.reverse_number();

	/**/
	// #op*(bi) 31
	std::cout
		<< "sumOfSubtotals at the end: "
		<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigInt.cpp, #op*(bi) 31.\n\n"
		;

	product.set_number(sumOfSubtotals);

	/**/
	// #op*(bi) 32
	std::cout
		<< "Product after product.set_number(sumOfSubtotals.get_number()): "
		<< "\nproduct.get_number(): " << product.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigInt.cpp, #op*(bi) 32.\n\n"
		;

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
//префиксная версия возвращает значение после инкремента
const BigInt& operator++(BigInt& bi)
{
	BigInt one("1");
	bi = bi + one;
	return bi;
} // endof operator++(BigInt& bi)

//постфиксная версия возвращает значение до инкремента
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