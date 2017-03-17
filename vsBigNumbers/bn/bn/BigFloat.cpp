#include "stdafx.h"
#include "BigFloat.h"
#include "bn_functions.h"
// #include <cmath> // можно использовать std::pow()

// ctors =======================================================================
BigFloat::BigFloat()
	: BigNumber()
{
	//std::cout << "\nDefault constructor has been used.\n";
	notation_ = DEFAULT;
	set_number("0.0");
	set_tail(" E+0");
}

BigFloat::BigFloat(const std::string& num)
	: BigNumber(num)
{
	set_number(num);
	notation_ = DEFAULT;
/*
	std::cout
		<< "In constructor before converting: "
		<< sign_ << number() << "\n";
*/
	if (is_correct(DECIMAL) || is_correct(DEFAULT))
	{
		// do nothing
/*
		std::cout
			<< "\nConstructor will try create object from string"
			<< "\nthat represent number in decimal notation.\n";
*/
	}
	else if (is_correct(SCIENTIFIC))
	{
		convert_to(DECIMAL);
/*
		std::cout
			<< "\nIn constructor after converting: "
			<< sign_ << number() << "\n";
*/
/*
		std::cout
			<< "\nConstructor will try create object from string"
			<< "\nthat represent number in scientific notation.\n";
*/
	}
	else
	{
		reset();
		std::cout
			<< "\nConstructor tried create object from string\n"
			<< "but failed, because string is incorrect.\n"
			<< "The number you have entered set to zero.\n";
	}
/*
	std::cout << "After all number() in ctor: " << number() << "\n";
*/
}

BigFloat::BigFloat(const BigInt& bi)
{
	BigNumber::set_number(bi.get_number() + ".0");
}

BigFloat::BigFloat(const BigFloat& bf)
{
	set_number(bf.get_number());
}

// checkers ====================================================================
bool BigFloat::is_correct(Notation notation) const
{
	bool result = true;
	size_t spacePos = space_position();
	size_t ePos = e_position();
	size_t eSignPos = e_sign_position();
	size_t numSize = get_number().size();

	switch (notation)
	{
	case SCIENTIFIC:
	{
/*
		std::cout << "\nThe scientific number notation assertion.\n";
*/


		// проверяем, что строка содержит пробел:
		if (spacePos == numSize)
		{
			result = false;
/*
			std::cout <<
				"\nThe scientific number notation is incorrect, because"
				"\nthe number have to contain 1 space at least.\n";
*/
		}
		// проверяем, что строка содержит букву 'e' или 'E':
		else if (ePos == numSize)
		{
			result = false;
/*
			std::cout <<
				"\nThe scientific number notation is incorrect, because"
				"\nthe number have to contain 1 letter 'e' or 'E'.\n";
*/
		}
		// проверяем, что строка содержит точку и точка только одна:
		else if (!contains_one_dot_only(get_number()))
		{
			result = false;
/*
			std::cout <<
				"\nThe scientific number notation is incorrect, because"
				"\nthe number have to contain 1 dot (no more and no less).\n";
*/
		}
		else
		{
			// проверяем, что до пробела все элементы строки - числа или точка:
			for (size_t i = 0; i < spacePos; ++i)
			{
				if (!is_digit(get_number()[i]) && !is_dot(get_number()[i]))
				{
					result = false;
/*
					std::cout <<
						"\nThe scientific number notation is incorrect, because"
						"\nthe number contains forbidden characters before space.\n";
*/
					break;
				}
			}
			// проверяем, что буква 'e' или 'E' следует сразу за пробелом:
			if (ePos != position_after(spacePos))
			{
				result = false;
/*
				std::cout <<
					"\nThe scientific number notation is incorrect,"
					"\nbecause letter was not found after space.\n";
*/
			}
			// проверяем что за буквой 'e' или 'E' следует знак плюс или минус:
			else if (!is_sign(get_number()[eSignPos]))
			{
				result = false;
/*
				std::cout <<
					"\nThe scientific number notation is incorrect,"
					"\nbecause sign was not found after letter.\n";
*/
			}
			else
			{
				// проверяем, что после знака следуют только числа:
				for (size_t i = position_after(eSignPos); i < numSize; ++i)
				{
					if (!is_digit(get_number()[i]))
					{
						result = false;
/*
						std::cout <<
							"\nThe scientific number notation is incorrect,"
							"\nbecause was found forbidden characters after sign.\n";
*/
						break;
					}
				}
			}
		}
/*
		std::cout
			<< "\nis_correct( SCIENTIFIC ): "
			<< std::boolalpha
			<< result
			<< std::noboolalpha
			<< "\n";
*/
		break;
	}

	case DECIMAL:
/*
		std::cout << "\nThe decimal number notation assertion.\n";
*/
		// проверяем, что строка содержит точку и точка только одна:
		if (contains_one_dot_only(get_number()))
		{
			// проверяем, что все элементы строки - числа или точка:
			for (size_t i = 0; i < numSize; ++i)
			{
				if (!is_digit(get_number()[i]) && !is_dot(get_number()[i]))
				{
					result = false;
/*
					std::cout <<
						"\nThe decimal notation of this number is incorrect,"
						"\nbecause it contains forbidden characters.\n";
*/
					break;
				}
			}
		}
		else
		{
			result = false;
/*
			std::cout <<
				"\nThe decimal notation of this number is incorrect,"
				"\nbecause it contains more than 1 dot.\n";
*/
		}
/*
		std::cout
			<< "\nis_correct( DECIMAL ): "
			<< std::boolalpha
			<< result
			<< std::noboolalpha
			<< "\n";
*/
		break;

	case DEFAULT:
		if (!is_zero())
		{
			result = false;
/*
			std::cout << "\nThis number is not equal to zero.\n"
*/
		}
		break;

	default:
		std::cout << "\nError: incorrect function argument\n";
		break;

	} // endof switch ( notation )

	return result;
} // endof is_correct()

bool BigFloat::is_decimal() const
{
	return is_correct(DECIMAL);
}

bool BigFloat::is_scientific() const
{
	return is_correct(SCIENTIFIC);
}

bool BigFloat::is_greater_than_zero() const
{
	bool result = true;
	BigFloat num(*this);
	if (get_sign() == '-')
	{
		result = false;
	}
	else
	{
		if (num.has_leading_zeros())
		{
			num.pop_front_extra_zeros();
			if (first_digit_value() >= 1)
			{
				result = true;
			}
			else
			{
				result = false;
			}
		}
	}

	return result;
}

bool BigFloat::is_less_than_zero() const
{
	bool hasDigitsGreaterThanZeroAfterDot = true;

	for
		(
			size_t i = position_after(dot_position());
			i < position_after(last_digit_position());
			++i
			)
	{
		if (char_to_digit(number()[i]) > 0)
		{
			hasDigitsGreaterThanZeroAfterDot = false;
			break;
		}
	}

	return
		digits_before_dot() == 1 &&
		first_digit_value() == 0 &&
		hasDigitsGreaterThanZeroAfterDot;
}

bool BigFloat::is_zero() const
{
	return get_number() == "0" || get_number() == "0.0";
}

// changers ====================================================================
void BigFloat::move_floating_point(Direction dir, size_t shiftSize)
{
	size_t dotPos = dot_position();

	switch (dir)
	{
	case RIGHT:
	{
		//std::cout << "\nBigFloat::move_floating_point( RIGHT ) works.\n";
		if (digits_after_dot() > shiftSize)
		{
			/*
			std::cout
			<< "\ndigits_after_dot() > shiftSize"
			<< "\ndigits_after_dot(): " << digits_after_dot()
			<< "\nshiftSize: " << shiftSize << "\n";
			*/
			insert_to(number(), ".", position_after(dotPos) + shiftSize);
		}
		else if (digits_after_dot() == shiftSize)
		{
			/*
			std::cout
			<< "\ndigits_after_dot() == shiftSize\n"
			<< "\ndigits_after_dot(): " << digits_after_dot()
			<< "shiftSize: " << shiftSize << "\n";
			*/
			insert_to(number(), ".0", position_after(last_digit_position()));
		}
		else
		{
			/*
			std::cout
			<< "\ndigits_after_dot() < shiftSize\n"
			<< "\ndigits_after_dot(): " << digits_after_dot()
			<< "\nshiftSize: " << shiftSize << "\n";
			*/
			size_t additionalzeros = shiftSize - digits_after_dot();
			for (size_t i = 0; i < additionalzeros; ++i)
			{
				//std::cout << "\nI insert zeros, man!\n";
				insert_to(number(), "0", position_after(last_digit_position()));
			}
			insert_to(number(), ".0", position_after(last_digit_position()));
		}

		erase_part_of(number(), dotPos, dotPos);

		break;
	}
	case LEFT:
	{
		size_t digitsBefore = digits_before_dot();
		/*
		std::cout
		<<  "\nWe are in function BigFloat::move_floating_point in section\n"
		"of switch 'case LEFT' and current content of number() is: "
		<< number()
		<< "\nand current value of dot_pos is: "
		<< dot_pos << "\n\n";
		*/
		erase_part_of(number(), dotPos, dotPos);
		/*
		std::cout
		<<  "\nWe are in function BigFloat::move_floating_point in section\n"
		"of switch 'case LEFT' and current content of number() after dot erasure is: "
		<< number()
		<< "\nand current value of dot_pos is: "
		<< dot_pos << "\n\n";
		*/
		if (digitsBefore > shiftSize)
		{
			insert_to(number(), ".", dotPos - shiftSize);
		}
		else if (digitsBefore == shiftSize)
		{
			insert_to(number(), "0.", 0);
		}
		else if (digitsBefore < shiftSize)
		{
			size_t additionalzeros = shiftSize - digitsBefore;

			size_t i = 0;

			while (i < additionalzeros)
			{
				number() = "0" + number();
				++i;
			}

			insert_to(number(), "0.", 1);
		}

		break;
	}
	default:
		break;
	}
} // endof move_floating_point()

void BigFloat::convert_to(Notation notation)
{
	size_t numSize = number().size();
	size_t dotPos = dot_position();
	size_t ePos = e_position();
	size_t eValAsNum = e_value_as_number();

	switch (notation)
	{
	case SCIENTIFIC:

		if (dotPos != 1)
		{
			size_t shift = position_before(dotPos);
			move_floating_point(LEFT, shift);
			number() = number() + " E+" + number_to_string(shift);
			/*
			std::cout <<
			"number() after converting from decimal to scientific\n"
			"move_floating_point( LEFT ): " << number() << "\n";
			*/
		}
		else
		{
			if (leading_zeros())
			{
				move_floating_point(RIGHT, leading_zeros());
				number() = number() + " E-" + number_to_string(leading_zeros());
				erase_part_of(number(), 0, leading_zeros());
			}
			else
			{
				number() = number() + " E+0";
			}
			/*
			std::cout <<
			"number() after converting from decimal to scientific\n"
			"move_floating_point( RIGHT ): " << number() << "\n";
			*/
		}
		pop_back_extra_zeros();
		notation_ = SCIENTIFIC;
		break;

	case DECIMAL:
	{
		if (e_sign() == '+')
		{
			move_floating_point(RIGHT, eValAsNum);
			/*
			std::cout
			<< "\nconvert_to(DECIMAL) works (floating point moved right): "
			<< number()
			<< "\n";
			*/
			erase_part_of(number(), position_before(ePos), numSize - 1);
			/*
			std::cout
			<< "\nconvert_to(DECIMAL) works (after exponent tail erasure): "
			<< number()
			<< "\n";
			*/
		}
		else if (e_sign() == '-')
		{
			move_floating_point(LEFT, eValAsNum);
			/*
			std::cout
			<< "\nconvert_to(DECIMAL) works (floating point moved left): "
			<< number()
			<< "\n";
			*/
			erase_part_of(number(), position_before(ePos), numSize - 1);
			/*
			std::cout
			<< "\nconvert_to(DECIMAL) works (after exponent tail erasure): "
			<< number()
			<< "\n";
			*/
		}
		else
		{
			std::cout
				<< "\nError: incorrect character instead the sign."
				<< "\nCurrent content of number() is: " << number()
				<< "\nAnd character is: " << e_sign() << "\n";
		}
		notation_ = DECIMAL;
		break;
	}

	case DEFAULT:
		reset();

	default:
		std::cout << "\nError: incorrect function argument.\n";
		break;
	}

} // endof convert_to()

void BigFloat::push_back_additional_zeros(const size_t quantity)
{
	std::string additionalZeros(quantity, '0');
	insert_to(number(), additionalZeros, position_after(last_digit_position()));
}

void BigFloat::pop_back_extra_zeros()
{
	size_t lastDigitPos = last_digit_position();

	while
		(
			number()[lastDigitPos] == '0' &&
			lastDigitPos > position_after(dot_position())
		)
	{
		erase_part_of(number(), last_digit_position(), last_digit_position());
	}
}

// getters =====================================================================
size_t BigFloat::dot_position() const
{
	return char_position(number(), '.');
}

size_t BigFloat::digits_after_dot() const
{   // TODO: implement count() function?
	return last_digit_position() - dot_position();
}

size_t BigFloat::digits_before_dot() const
{
	return dot_position();
}

size_t BigFloat::e_position() const
{
	size_t numSize = number().size();
	size_t ePos = numSize;

	for (size_t i = 0; i < numSize; ++i)
	{
		if (number()[i] == 'e' || number()[i] == 'E')
		{
			ePos = i;
			break;
		}
	}

	return ePos;
}

size_t BigFloat::digits_after_e() const
{   // TODO: implement count() function?
	return number().size() - position_before(space_position());
}

size_t BigFloat::e_value_as_number() const
{
	return string_to_number(e_value_as_string());
}

std::string BigFloat::e_value_as_string() const
{
	std::string eVal = "";
	for (size_t i = position_after(e_sign_position()); i < number().size(); ++i)
	{
		eVal = eVal + number()[i];
	}
	return eVal;
}

size_t BigFloat::e_sign_position() const
{
	size_t eSignPos = number().size();
	for (size_t i = e_position(); i < number().size(); ++i)
	{
		if (is_sign(number()[i]))
		{
			eSignPos = i;
			break;
		}
	}

	return eSignPos;
}

char BigFloat::e_sign() const
{
	return number()[e_sign_position()];
}

size_t BigFloat::last_digit_position() const
{
	size_t lastDigitPos = number().size();
	for (size_t i = 0; i < number().size(); ++i)
	{
		if (is_digit(number()[i]) || is_dot(number()[i]))
		{
			lastDigitPos = i;
		}
		else
		{
			break;
		}
	}

	return lastDigitPos;
}

size_t BigFloat::last_digit_value() const
{
	return number()[last_digit_position()];
}

size_t BigFloat::space_position() const
{
	return char_position(number(), ' ');
}

std::string BigFloat::mantissa() const
{
	std::string mantissa = number();

	if (is_scientific())
	{
		/*
		std::cout <<
		"\nI AM INSIDE IN FUNCTION mantissa() and "
		"is_scientific() is TRUE!\n";
		*/
		size_t spacePos = space_position();
		if (mantissa[space_pos] == ' ')
		{
			erase_part_of(mantissa, space_pos, space_pos);
		}
		erase_part_of(mantissa, e_position(), mantissa.size() - 1);
	}

	return mantissa;
}

BigFloat::Notation BigFloat::notation() const
{
	return notation_;
}

// setters =====================================================================
void BigFloat::set_number(const BigFloat& bf)
{
	BigNumber::set_number(bf.get_number());

	if (is_correct(SCIENTIFIC))
	{
		convert_to(DECIMAL);
	}
	else if (is_correct(DECIMAL))
	{
		// do nothing
	}
	else
	{
		reset();
	}
}

void BigFloat::set_number(const std::string& num)
{	
	BigNumber::set_number(num);

	if (is_correct(SCIENTIFIC))
	{
		convert_to(DECIMAL);
	}
	else if (is_correct(DECIMAL))
	{
		// do nothing
	}
	else
	{
		reset();
	}
}

void BigFloat::reset()
{
	set_number("0.0");
	set_tail(" E+0");
	notation_ = DEFAULT;
}

// comparison operators ========================================================
bool BigFloat::operator<(const BigFloat& bf) const // #op<
{
	BigFloat a(*this);
	BigFloat b(bf);

	bool result = true;

	if (a.get_sign() == '+' && b.get_sign() == '-')
	{
		result = false;
	}
	else if (a.notation_ == DEFAULT && b.notation_ == DEFAULT)
	{
		result = false;
	}
	else if (a.is_greater_than_zero() && b.notation_ == DEFAULT)
	{
		result = false;
	}
	else if (a.notation_ == DEFAULT && b.is_less_than_zero())
	{
		result = false;
	}

	if (!a.is_decimal())
	{
		a.convert_to(DECIMAL);
	}

	if (!b.is_decimal())
	{
		b.convert_to(DECIMAL);
	}

	// TODO: сравнивать поразрядно

	return result;
}

bool BigFloat::operator<=(const BigFloat& bf) const // #op<=
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a > b);
}

bool BigFloat::operator>(const BigFloat& bf) const // #op>
{
	BigFloat a = *this;
	BigFloat b = bf;

	bool result = true;

	if (a.get_sign() == '-' && b.get_sign() == '+')
	{
		result = false;
	}
	else if (a.notation_ == DEFAULT && b.notation_ == DEFAULT)
	{
		result = false;
	}
	else if (a.is_less_than_zero() && b.notation_ == DEFAULT)
	{
		result = false;
	}
	else if (a.notation_ == DEFAULT && b.is_greater_than_zero())
	{
		result = false;
	}

	if (!a.is_decimal())
	{
		a.convert_to(DECIMAL);
	}

	if (!b.is_decimal())
	{
		b.convert_to(DECIMAL);
	}

	// TODO: сравнивать поразрядно

	return result;
} // endof operator>

bool BigFloat::operator>=(const BigFloat& bf) const // #op>=
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a < b);
} // endof operator>=

bool BigFloat::operator==(const BigFloat& bf) const // #op==
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a < b) && !(a > b);
} // endof operator==

// assignment operators ========================================================
BigFloat BigFloat::operator=(const BigFloat& bf) // #op=
{
	if (this != &bf)
	{
		set_number(bf);
	}
	return *this;
} // endof operator=

BigFloat BigFloat::operator=(const std::string& obj) // #op=
{
	if (this->number() != &obj[0]) // &obj.front()
	{
		BigFloat temp = *this;
		number() = obj;
		sign_ = sign();
		discard_sign();

		if (is_correct(SCIENTIFIC))
		{
			convert_to(DECIMAL);
			notation_ = DECIMAL;
		}
		else if (is_correct(DECIMAL))
		{
			// do nothing
		}
		else if (is_correct(DEFAULT))
		{
			reset();
		}
		else
		{
			*this = temp;
		}
	}
	return *this;
} // endof operator=

// arithmetic operators (both operand are same type) ===========================
BigFloat BigFloat::operator+(const BigFloat& addendum) const // #op+(bf)
{
	BigFloat a = *this;
	BigFloat b = addendum;

	std::string aStr = this->number();
	std::string bStr = addendum.number();

	size_t diff; // разница между количеством разрядов

				 // уравниваем количество разрядов обоих чисел до плавающей точки:
	if (a.digits_before_dot() < b.digits_before_dot()) // #op+1
	{
		/*
		std::cout << "\n#1\n";
		std::cout << "we are here because a.digits_before_dot() < b.digits_before_dot():\n";
		std::cout << "a.digits_before_dot(): " << a.digits_before_dot() << "\n";
		std::cout << "b.digits_before_dot(): " << b.digits_before_dot() << "\n";
		std::cout << "current content of number a: " << a.number() << "\n";
		std::cout << "current content of number b: " << b.number() << "\n";
		std::cout << "current content of string aStr: " << aStr << "\n";
		std::cout << "current content of number bStr: " << bStr << "\n\n";
		*/
		diff = b.digits_before_dot() - a.digits_before_dot();
		for (size_t i = 0; i < diff; ++i)
		{
			push_front(aStr, "0");
		}
		//std::cout << "string aStr after pushing front zeros: " << aStr << "\n";
	}
	else if (b.digits_before_dot() < a.digits_before_dot()) // #op+2
	{
		/*
		std::cout << "\n#2\n";
		std::cout << "we are here because b.digits_before_dot() < a.digits_before_dot():\n";
		std::cout << "a.digits_before_dot(): " << a.digits_before_dot() << "\n";
		std::cout << "b.digits_before_dot(): " << b.digits_before_dot() << "\n";
		std::cout << "current content of number a: " << a.number() << "\n";
		std::cout << "current content of number b: " << b.number() << "\n";
		std::cout << "current content of string aStr: " << aStr << "\n";
		std::cout << "current content of number bStr: " << bStr << "\n\n";
		*/
		diff = a.digits_before_dot() - b.digits_before_dot();
		for (size_t i = 0; i < diff; ++i)
		{
			push_front(bStr, "0");
		}
		//std::cout << "string bStr after pushing front zeros: " << bStr << "\n";
	}

	// уравниваем количество разрядов обоих чисел после плавающей точки:
	if (a.digits_after_dot() < b.digits_after_dot()) // #op+3
	{
		/*
		std::cout << "\n#3\n";
		std::cout << "we are here because a.digits_after_dot() < b.digits_after_dot():\n";
		std::cout << "a.digits_after_dot(): " << a.digits_after_dot() << "\n";
		std::cout << "b.digits_after_dot(): " << b.digits_after_dot() << "\n\n";
		std::cout << "current content of number a: " << a.number() << "\n";
		std::cout << "current content of number b: " << b.number() << "\n";
		std::cout << "current content of string aStr: " << aStr << "\n";
		std::cout << "current content of number bStr: " << bStr << "\n\n";
		*/
		diff = b.digits_after_dot() - a.digits_after_dot();
		for (size_t i = 0; i < diff; ++i)
		{
			push_back(aStr, "0");
		}
		//std::cout << "string aStr after pushing back zeros: " << aStr << "\n";
	}
	else if (b.digits_after_dot() < a.digits_after_dot()) // #op+4
	{
		/*
		auto a_it = std::find(a.number().begin(), a.number().end(), '.');
		auto a_dad = std::distance(a_it + 1, a.number().end());

		auto b_it = std::find(b.number().begin(), b.number().end(), '.');
		auto b_dad = std::distance(b_it + 1, b.number().end());

		std::cout << "\n#4\n";
		std::cout << "we are here because b.digits_after_dot() < a.digits_after_dot():\n";

		std::cout << "a.digits_after_dot(): " << a.digits_after_dot() << "\n";
		std::cout << "b.digits_after_dot(): " << b.digits_after_dot() << "\n";

		std::cout << "real quantity digits after dot in number a: " << a_dad << "\n";
		std::cout << "real quantity digits after dot in number b: " << b_dad << "\n";

		std::cout << "current content of number a: " << a.number() << "\n";
		std::cout << "current content of number b: " << b.number() << "\n";

		std::cout << "current content of string aStr: " << aStr << "\n";
		std::cout << "current content of string bStr: " << bStr << "\n\n";
		*/
		diff = a.digits_after_dot() - b.digits_after_dot();
		for (size_t i = 0; i < diff; ++i)
		{
			push_back(bStr, "0");
		}
		//std::cout << "string bStr after pushing back zeros: " << bStr << "\n";
	}

	// запомним позицию плавающей точки:
	size_t dot_pos_a = char_position(aStr, '.');
	size_t dot_pos_b = char_position(bStr, '.');

	// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
	erase_part_of(aStr, dot_pos_a, dot_pos_a);
	erase_part_of(bStr, dot_pos_b, dot_pos_b);

	// будем складывать, начиная с млаших разрядов, для этого перевернём числа:
	reverse(aStr);
	reverse(bStr);

	// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
	size_t extra = 0;
	// промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
	size_t subtotal = 0;

	std::string sumStr;
	std::string curRes;
	for (size_t i = 0; i < aStr.size(); ++i)
	{
		subtotal = char_to_digit(aStr[i]) + char_to_digit(bStr[i]) + extra;
		/*
		std::cout
		<< "\n"
		<< char_to_digit(aStr[i])
		<< " + "
		<< char_to_digit(bStr[i])
		<< " + number we keep in mind (it's "
		<< extra
		<< ") = "
		<< subtotal;
		*/
		if (subtotal > BigInt::MAX_DIGIT) // десятичная система, поэтому последняя цифра в разряде 9
		{
			extra = subtotal / BigInt::BASE;
			subtotal = subtotal % BigInt::BASE;
		}
		else
		{
			extra = 0;
		}

		//std::cout << "\n" << subtotal << " we write, and " << extra << " we keep in mind.\n";
		push_back(sumStr, digit_to_char(subtotal));
		curRes = sumStr;
		reverse(curRes);
		//std::cout << "current result (without floating point ofc) is " << curRes << "\n";
	}

	size_t extra_dot_shift = 0;
	if (extra)
	{
		push_back(sumStr, digit_to_char(extra));
		/*
		std::cout
		<< "\nwe add the number we keep in mind (it's "
		<< extra
		<< ") to out result and ";
		*/
		curRes = sumStr;
		reverse(curRes);
		extra_dot_shift = 1;
	}

	reverse(sumStr);
	insert_to(sumStr, ".", dot_pos_a + extra_dot_shift);

	//std::cout << "\nfinal result in decimal notation: " << sumStr << "\n";

	BigFloat sum(sumStr);

	//std::cout << "And in exponent notation final result is\n";

	return sum;
} // endof #op+(bf)

BigFloat BigFloat::operator-(const BigFloat& subtrahend) const // #op-(bf)
{
	BigFloat diff(subtrahend); // temporary solution to avoid compiler warning
							   // TODO
	return diff;
} // endof // #op-(bf)

BigFloat BigFloat::operator*(const BigFloat& multiplier) const // #op*(bf)
{
	BigFloat product(*this);
	BigFloat addition(*this);
	BigFloat mult(multiplier);

	size_t cur_mult_dot_pos = mult.dot_position();
	size_t cur_prod_dot_pos = product.digits_after_dot();
	size_t fin_prod_dot_pos = product.digits_after_dot() + mult.digits_after_dot();

	// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
	erase_part_of(product.number(), cur_prod_dot_pos, cur_prod_dot_pos);
	erase_part_of(mult.number(), cur_mult_dot_pos, cur_mult_dot_pos);

	BigInt limit(mult.number());
	for (BigInt i("0"); i < limit; ++i)
	{
		product = product + addition;
	}

	insert_to(product.number(), ".", fin_prod_dot_pos);

	return product;
} // endof // #op*(bf)

BigFloat BigFloat::operator/(const BigFloat& divider) const // #op/(bf)
{
	BigFloat result;
	BigFloat dividend(*this);
	BigFloat divisor(divider);
	if (dividend.notation() == SCIENTIFIC)
	{
		dividend.convert_to(DECIMAL);
	}

	if (divisor.notation() == SCIENTIFIC)
	{
		divisor.convert_to(DECIMAL);
	}

	if (dividend.is_correct(DEFAULT))
	{
		// do nothing (result already equal to zero)
	}
	else if (divisor.is_correct(DEFAULT))
	{
		result.number() = "1.0";
		std::cout <<
			"\nYou can not divide by zero! The result is "
			"equated to 1, but it is a wrong result.\n";
	}
	else
	{
		size_t digitsAfterDot = divisor.digits_after_dot();
		for (size_t i = digitsAfterDot; i > 0; --i)
		{
			divisor.move_floating_point(RIGHT, 1);
			dividend.move_floating_point(RIGHT, 1);
		}

		// TODO: закончить
	}

	return result;
} // endof #op/(bf)

// arithmetic operators (each operand are different type) ======================
BigFloat BigFloat::operator+(const BigInt& addendum) const // #op+(bi)
{
	BigFloat sum(addendum); // temporary solution to avoid compiler warning
							// TODO
	return sum;
} // endof #op+(bi)

BigFloat BigFloat::operator-(const BigInt& subtrahend) const // #op-(bi)
{
	BigFloat diff(subtrahend); // temporary solution to avoid compiler warning
							   // TODO
	return diff;
} // endof #op-(bi)

BigFloat BigFloat::operator*(const BigInt& multiplier) const // #op*(bi)
{
	BigFloat product(multiplier); // temporary solution to avoid compiler warning
								  // TODO
	return product;
} // endof #op*(bi)

BigFloat BigFloat::operator/(const BigInt& divider) const // #op/(bi)
{
	BigFloat result(divider); // temporary solution to avoid compiler warning
							  // TODO
	return result;
} // endof #op/(bi)


// input-output operators ======================================================
std::istream& operator >> (std::istream& is, BigFloat& bf)
{
	std::string num;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::getline(std::cin, num);

	bf.set_number(num);

	if (bf.is_correct(BigFloat::SCIENTIFIC))
	{
		bf.convert_to(BigFloat::DECIMAL);
	}
	else if (bf.is_correct(BigFloat::DECIMAL))
	{
		// do nothing
	}
	else
	{
		bf.reset();
	}

	return is;
} // endof // #op>>(bf)


std::ostream& operator<<(std::ostream& os, const BigFloat& bf) // #op<<(bf)
{
	BigFloat temp = bf;
	if (temp.is_correct(BigFloat::DECIMAL))
	{
		temp.convert_to(BigFloat::SCIENTIFIC);
	}
	else if (temp.is_correct(BigFloat::SCIENTIFIC))
	{
		// do nothing
	}
	else
	{
		temp.reset();
	}

	temp.pop_front_extra_zeros();

	os << temp.get_sign() << temp.get_number() << temp.get_tail();

	return os;
} // endof // #op<<(bf)
