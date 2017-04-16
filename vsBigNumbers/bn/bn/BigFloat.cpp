#include "stdafx.h"
#include "BigFloat.h"
#include "bn_functions.h"
// #include <cmath> // можно использовать std::pow()

const size_t PRECISION = 30;

// ctors =======================================================================
BigFloat::BigFloat()
	:
		BigNumber("0.0"),
		notation_(DEFAULT),
		eSign_('+'),
		eValueAsString_("0")
{
/*
	std::cout
		<< "Default ctor BigFloat::BigFloat() has been called.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;
*/
}

BigFloat::BigFloat(const std::string& num)
	:
		BigNumber(num)
{
	char temporaryCrutch = get_sign();
/*
	std::cout
		<< "Ctor BigFloat::BigFloat(const std::string& num) has been called.\n"
		;
*/
	set_number(num);
/*
	std::cout
		<< "Ctor BigFloat::set_number(get_number()) has been called.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;
*/
	set_sign(temporaryCrutch);
}

BigFloat::BigFloat(const BigInt& bi)
	:
		BigNumber(bi.get_sign() + bi.get_number())
{
	char temporaryCrutch = bi.get_sign();
/*
	std::cout
		<< "Ctor BigFloat::BigFloat(const BigInt& bi) has been used.\n"
		;
*/
	std::string tempNumber(bi.get_number());
	tempNumber = tempNumber + ".0";

	set_number(tempNumber);
/*
	std::cout
		<< "Ctor BigFloat::set_number(bi.get_number()) has been used.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;
*/
	set_sign(temporaryCrutch);
}

BigFloat::BigFloat(const BigFloat& bf)
	: 
		BigNumber(bf.get_sign() + bf.get_number()),
		notation_(bf.notation_),
		eSign_(bf.eSign_),
		eValueAsString_(bf.eValueAsString_)
{
/*
	std::cout
		<< "Copy ctor BigFloat::BigFloat(const BigFloat& bf) has been used.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n";
		;
*/	
}



// checkers ====================================================================
bool BigFloat::has_extra_leading_zeros() const
{	
	// for example: the number 0000.01234 has three extra leading zeros

	return
		elem_value_as_char(0) == '0' &&
		is_digit(elem_value_as_char(1));
}

bool BigFloat::has_leading_zeros() const
{
	// for example: the number 0.01234 has two leading zeros

/*
		std::cout
			<< "The object has leading zeros.\n"
			<< "Assertion occured in BigFloat.cpp, has_leading_zeros().\n\n"
			;
*/
	return first_digit_value() == 0 ? true : false;
}

bool BigFloat::has_trailing_zeros() const
{
	// for example: the number 0.012340000 has four trailing zeros
	return
		digits_after_dot() > 1 &&
		last_digit_value() == 0;
}

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
// #iscor(sci) 1
		std::cout
			<< "\nThe scientific number notation assertion.\n"
			<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 1.\n\n"
			;
*/
		// проверяем, что строка содержит пробел:
		if (spacePos == numSize)
		{
			result = false;
/*
// #iscor(sci) 2
			std::cout
				<<
				"The scientific number notation is incorrect, because "
				"the number have to contain 1 space at least.\n"
				<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 2.\n\n"
				;
*/
		}
		// проверяем, что строка содержит букву 'e' или 'E':
		else if (ePos == numSize)
		{
			result = false;
/*
// #iscor(sci) 3
			std::cout <<
				"The scientific number notation is incorrect, because "
				"the number have to contain 1 letter 'e' or 'E'.\n"
				"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 3.\n\n"
				;
*/
		}
		// проверяем, что строка содержит точку и точка только одна:
		else if (!contains_one_dot_only(get_number()))
		{
			result = false;
/*
// #iscor(sci) 4
			std::cout <<
				"The scientific number notation is incorrect, because "
				"the number have to contain 1 dot (no more and no less).\n"
				"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 4.\n\n"
				;
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
// #iscor(sci) 5
					std::cout <<
						"The scientific number notation is incorrect, because "
						"the number contains forbidden characters before space.\n"
						"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 5.\n\n"
						;
*/
					break;
				}
			}
			// проверяем, что буква 'e' или 'E' следует сразу за пробелом:
			if (ePos != position_after(spacePos))
			{
				result = false;
/*
// #iscor(sci) 6
				std::cout <<
					"The scientific number notation is incorrect, "
					"because letter was not found after space.\n"
					"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 6.\n\n"
					;
*/
			}
			// проверяем что за буквой 'e' или 'E' следует знак плюс или минус:
			else if (!is_sign(get_number()[eSignPos]))
			{
				result = false;
/*
// #iscor(sci) 7
				std::cout <<
					"The scientific number notation is incorrect, "
					"because sign was not found after letter.\n"
					"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 7.\n\n"
					;
*/
			}
			else
			{
				// проверяем, что после знака следуют только цифры:
				for (size_t i = position_after(eSignPos); i < numSize; ++i)
				{
					if (!is_digit(get_number()[i]))
					{
						result = false;
/*
// #iscor(sci) 8
						std::cout <<
							"The scientific number notation is incorrect, "
							"because was found forbidden characters after sign.\n"
							"Assertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 8.\n\n"
							;
*/
						break;
					}
				}
			}
		}
/*
// #iscor(sci) 9
		std::cout
			<< "is_correct(SCIENTIFIC): " << std::boolalpha << result << std::noboolalpha
			<< "\nAssertion occured in BigFloat.cpp, is_correct(), #iscor(sci) 9.\n\n"
			;
*/
		break;
	}

	case DECIMAL:
/*
// #iscor(dec) 1
		std::cout
			<< "\nThe decimal number notation assertion.\n"
			<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(dec) 1.\n\n"
			;
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
// #iscor(dec) 2
					std::cout <<
						"\nThe decimal notation of this number is incorrect, "
						"because it contains forbidden characters.\n"
						"Assertion occured in BigFloat.cpp, is_correct(), #iscor(dec) 2.\n\n"
						;
*/
					break;
				}
			}
		}
		else
		{
			result = false;
/*
// #iscor(dec) 3
			std::cout <<
				"\nThe decimal notation of this number is incorrect, "
				"because it contains more than 1 dot.\n"
				"Assertion occured in BigFloat.cpp, is_correct(), #iscor(dec) 3.\n\n"
				;
*/
		}
/*
// #iscor(dec) 4
		std::cout
			<< "\nis_correct(DECIMAL): " << std::boolalpha << result << std::noboolalpha
			<< "\nAssertion occured in BigFloat.cpp, is_correct(), #iscor(dec) 4.\n\n"
			;
*/
		break;

	case DEFAULT:
/*
// #iscor(dft) 1
		std::cout
			<< "\nThe default number notation assertion.\n"
			<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(dft) 1.\n\n"
			;
*/
		if (!is_zero())
		{
			result = false;
/*
// #iscor(dft) 2
			std::cout <<
				"\nThe default notation of this number is incorrect, "
				"because the number is not equal to zero.\n"
				"Assertion occured in BigFloat.cpp, is_correct(), #iscor(dft) 2.\n\n"
				;
*/
		}
		break;
/*
// #iscor(dft) 3
		std::cout
			<< "\nis_correct(DEFAULT): " << std::boolalpha << result << std::noboolalpha
			<< "\nAssertion occured in BigFloat.cpp, is_correct(), #iscor(dft) 3.\n\n"
			;
*/
	default:
		std::cout << "\nError: incorrect function argument\n";
		break;


	} // endof switch ( notation )

	return result;
} // endof is_correct()

bool BigFloat::is_decimal() const
{
	return notation_ == DECIMAL;
}

bool BigFloat::is_scientific() const
{
	return notation_ == SCIENTIFIC;
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
			num.pop_front_leading_zeros();
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
		if (char_to_digit(get_number()[i]) > 0)
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
	return
		mantissa() == "0" ||
		mantissa() == "0.0";
}




// changers ====================================================================
void BigFloat::discard_e_tail()
{
	set_number(mantissa());
}

void BigFloat::move_floating_point(Direction dir, size_t shiftSize)
{
/**/
	if (is_zero())
	{
/*
		// #mfp(r) 0
		std::cout
			<< "BigFloat::move_floating_point(args) has been called."
			<< "\nThe number is zero: "
			<< get_number()
			<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 0.\n\n"
			;
*/
		return;	
	}

	size_t dotPos = dot_position();
	size_t digitsAfterDot = digits_after_dot();
	size_t lastDigitPos = last_digit_position();

	switch (dir)
	{
	case RIGHT:
	{
		//std::cout << "\nBigFloat::move_floating_point( RIGHT ) works.\n";
		if (digitsAfterDot > shiftSize)
		{
/*
			std::cout
				<< "\ndigits_after_dot() > shiftSize"
				<< "\ndigits_after_dot(): " << digits_after_dot()
				<< "\nshiftSize: " << shiftSize << "\n";
*/
			insert_elem('.', position_after(dotPos) + shiftSize);
/*
			// #mfp(r) 1
			std::cout
				<< "BigFloat::move_floating_point(args) has been called."
				<< "\nThe number after floating point was moved: "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 1.\n\n"
				;
*/
		}
		else if (digitsAfterDot == shiftSize)
		{
/*
			std::cout
				<< "\ndigits_after_dot() == shiftSize\n"
				<< "\ndigits_after_dot(): " << digits_after_dot()
				<< "shiftSize: " << shiftSize << "\n";
*/
			insert_elem(".0", position_after(lastDigitPos));
/*
			// #mfp(r) 2
			std::cout
				<< "BigFloat::move_floating_point(args) has been called."
				<< "\nThe number after new floating point was inserted: "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 2.\n\n"
				;
*/
		}
		else
		{
/*
			std::cout
				<< "\ndigits_after_dot() < shiftSize\n"
				<< "\ndigits_after_dot(): " << digits_after_dot()
				<< "\nshiftSize: " << shiftSize << "\n";
*/
			size_t additionalZeros = shiftSize - digitsAfterDot;
			size_t posToInsertAdditionalZeros = position_after(lastDigitPos);
			for (size_t i = 0; i < additionalZeros; ++i)
			{				
				insert_elem('0', posToInsertAdditionalZeros);
/*
				std::cout << "\nI insert zeros, man!\n\n";
*/
			}

			insert_elem
				(
					".0",
					position_after(last_digit_position())	 
				);	// This is so on purpose! Do not change the 2nd
					// arg of function insert_elem() in this case.

/*
			// #mfp(r) 3
			std::cout
				<< "BigFloat::move_floating_point(args) has been called."
				<< "\nThe number after new floating point was inserted: "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 3.\n\n"
				;
*/
		}

		erase_elem(dotPos);
/*
		// #mfp(r) 4
		std::cout
			<< "BigFloat::move_floating_point(args) has been called."
			<< "\nThe number after floating point was moved: "
			<< get_number()
			<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 4.\n\n"
			;
*/
		break;
	}
	case LEFT:
	{
		size_t digitsBeforeDot = digits_before_dot();
/*
		std::cout
			<<  "\nWe are in function BigFloat::move_floating_point in section\n"
				"of switch 'case LEFT' and current content of number() is: "
			<< number()
			<< "\nand current value of dot_pos is: "
			<< dot_pos << "\n\n";
*/
		erase_elem(dotPos);
/*
		std::cout
			<<  "\nWe are in function BigFloat::move_floating_point in section\n"
				"of switch 'case LEFT' and current content of number() after dot erasure is: "
			<< number()
			<< "\nand current value of dot_pos is: "
			<< dot_pos << "\n\n";
*/
		if (digitsBeforeDot > shiftSize)
		{
			insert_elem('.', dotPos - shiftSize);
		}
		else if (digitsBeforeDot == shiftSize)
		{
			insert_elem("0.", 0);
		}
		else if (digitsBeforeDot < shiftSize)
		{			
			//push_front_additional_zeros(shiftSize - digitsBeforeDot); bugged arg
			push_front_additional_zeros(shiftSize);

/*
			//Old version:

			size_t additionalZeros = shiftSize - digitsBefore;
			size_t i = 0;

			while (i < additionalZeros)
			{
				set_number("0" + get_number());
				++i;
			}
*/
			insert_elem("0.", 1);
		}

		break;
	}
	default:
		break;
	}
} // endof move_floating_point()

void BigFloat::convert_to(Notation notation)
{
/**/
	if (is_zero())
	{
/*
		// #conv(arg) 0
		std::cout
			<< "BigFloat::move_floating_point(args) has been called."
			<< "\nThe number is zero: "
			<< get_number()
			<< "\nAssertion occured in BigFloat.cpp, // #conv(arg) 0.\n\n"
			;
*/
		return;
	}

	size_t numSize = get_number().size();	
	size_t dotShift = 0;

	switch (notation)
	{
	case SCIENTIFIC:
	{
		size_t dotPos = dot_position();	
		size_t digitsBeforeDot = digits_before_dot();

		if (digitsBeforeDot > 1)
		{	
			dotShift = dotPos - 1;
/*
			// #conv(sci) 4
			std::cout
				<< "number before move_floating_point(LEFT, dotShift): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 4\n\n"
				;
*/			
			move_floating_point(LEFT, dotShift);
/*
			// #conv(sci) 5
			std::cout
				<< "number after move_floating_point(LEFT, dotShift): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 5\n\n"
				;
*/
			if (has_trailing_zeros())
			{
/*
				// #conv(sci) 5a
				std::cout
					<< "\nhas_trailing_zeros() has been called,"
					<< "\nbecause the number has trailing zeros: "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 5a\n\n"
					;
*/
				pop_back_trailing_zeros();

/*
				// #conv(sci) 5b
				std::cout
					<< "pop_back_trailing_zeros() has been called."
					<< "\nThe number after pop_back_trailing_zeros(): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 5b\n\n"
					;
*/
			}


			eSign_ = '+';
			eValueAsString_ = number_to_string(dotShift);
/*
			// #conv(sci) 6
			std::cout
				<< "number before push_back_elem(e_tail()): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 6\n\n"
				;
*/
			push_back_elem(e_tail());
/*
			// #conv(sci) 7
			std::cout
				<< "e_tail() has been called and it is: "
				<< e_tail()
				<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 7\n\n"
				;
*/
/*
			// #conv(sci) 8
			std::cout
				<< "number after push_back_elem(e_tail()): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 8\n\n"
				;
*/		
		}
		else
		{
			if (has_leading_zeros())
			{
/*
				// #conv(sci) 9
				std::cout
					<< "has_leading_zeros() has been called, "
					<< "because the number has leading zeros: "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 9\n\n"
					;
*/
				dotShift = leading_zeros();
/*
				// #conv(sci) 10
				std::cout
					<< "leading_zeros() has been called. "
					<< "The quantity of leading zeros is: "
					<< dotShift
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 10\n\n"
					;
*/
/*
				// #conv(sci) 11
				std::cout
					<< "number before move_floating_point(RIGHT, dotShift): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 11\n\n"
					;
*/
				move_floating_point(RIGHT, dotShift);
/*
				// #conv(sci) 12
				std::cout
					<< "number after move_floating_point(RIGHT, dotShift): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 12\n\n"
					;
*/
				if (has_extra_leading_zeros())
				{
/*
					// #conv(sci) 13
					std::cout
						<< "has_extra_leading_zeros() has been called, "
						<< "because the number has extra leading zeros: "
						<< get_number()
						<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 13\n\n"
						;
*/
					pop_front_extra_leading_zeros();
/*
					// #conv(sci) 14
					std::cout
						<< "pop_front_extra_leading_zeros() has been called."
						<< "\nThe number after extra leading zeros was erased: "
						<< get_number()
						<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 14\n\n"
						;
*/
				}
				else
				{
/*
					// #conv(sci) 15
					std::cout
						<< "has_extra_leading_zeros() wasn't called, "
						<< "because the number has not extra leading zeros: "
						<< get_number()
						<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 15\n\n"
						;
*/
				}

				eSign_ = '-';
				eValueAsString_ = number_to_string(dotShift);
/*
				// #conv(sci) 16
				std::cout
					<< "number before push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 16\n\n"
					;
*/
				push_back_elem(e_tail());
/*
				// #conv(sci) 17
				std::cout
					<< "e_tail() has been called and it is:"
					<< e_tail()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 17\n\n"
					;
*/
/*
				// #conv(sci) 18
				std::cout
					<< "number after push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 18\n\n"
					;
*/
			}
			else
			{
				eSign_ = '+';
				eValueAsString_ = "0";
/*
				// #conv(sci) 19
				std::cout
					<< "number before push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 19\n\n"
					;
*/
				push_back_elem(e_tail());
/*
				// #conv(sci) 20
				std::cout
					<< "number after push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 20\n\n"
					;
*/
			}
		}

		notation_ = SCIENTIFIC;
		break;
	}

	case DECIMAL:
	{
		size_t ePos = e_position();
		/*
		// #conv(dec) 1
		std::cout
		<< "BigFloat::e_position() has been called."
		<< "\nePos: " << ePos
		<< "\nAssertion occured in BigFloat.cpp, #conv(arg) 1\n\n"
		;
		*/
		size_t eValAsNum = e_value_as_number();

/*
		// #conv(dec) 2
		std::cout
			<< "BigFloat::e_value_as_number() has been called."
			<< "\neValAsNum: " << eValAsNum
			<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 2\n\n"
			;
*/
		if (e_sign() == '+')
		{
/*
		// #conv(dec) 3
		std::cout
			<< "e_sign() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #conv(dec) 3\n\n"
			;
*/
/*
			// #conv(dec) 4
			std::cout
				<< "number before move_floating_point(RIGHT, eValAsNum): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 4\n\n"
				;
*/
			move_floating_point(RIGHT, eValAsNum);
/*
			// #conv(dec) 5
			std::cout
				<< "number after move_floating_point(RIGHT, eValAsNum): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 5\n\n"
				;
*/
/*
			// #conv(dec) 6
			std::cout
				<< "number before discard_e_tail(): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 6\n\n"
				;
*/
			discard_e_tail();
/*
			// #conv(dec) 7
			std::cout
				<< "number after discard_e_tail(): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 7\n\n"
				;
*/
		}
		else if (e_sign() == '-')
		{
/*
			// #conv(dec) 8
			std::cout
				<< "e_sign() has been called.\n"
				<< "Assertion occured in BigFloat.cpp, #conv(dec) 8\n\n"
				;
*/
/*
			// #conv(dec) 9
			std::cout
				<< "number before move_floating_point(LEFT, eValAsNum): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 9\n\n"
				;
*/
			move_floating_point(LEFT, eValAsNum);
/*
			// #conv(dec) 10
			std::cout
				<< "number after move_floating_point(LEFT, eValAsNum): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 10\n\n"
				;
*/
/*
			// #conv(dec) 11
			std::cout
				<< "number before erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 11\n\n"
				;
*/
			//erase_elem(position_before(ePos), position_before(numSize));
			discard_e_tail();
/*
			// #conv(dec) 12
			std::cout
				<< "position_before(ePos): "
				<< position_before(ePos)
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 12\n\n"
				;
*/
/*
			// #conv(dec) 13
			std::cout
				<< "number after erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 13\n\n"
				;
*/
		}
		else
		{
			std::cout
				<< "\nError: incorrect character instead the sign."
				<< "\nCurrent content of number() is: " << get_number()
				<< "\nAnd character is: " << e_sign() << "\n";
		}
		notation_ = DECIMAL;
/*
		// #conv(dec) 14
		std::cout
		<< "BigFloat::convert_to(arg) has been called."
		<< "\nThe number after conversion to decimal notation: "
		<< get_number()
		<< "\nAssertion occured in BigFloat.cpp, #conv(dec) 14.\n\n"
		;
*/		
		break;
	}

	case DEFAULT:
/*
		// #conv(dft) 1
		std::cout
			<< "number before reset(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(dft) 1\n\n"
			;
*/
		reset();
/*
		// #conv(dft) 2
		std::cout
			<< "number after reset(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(dft) 2\n\n"
			;
*/
	default:
		std::cout << "\nError: incorrect function argument.\n";
		break;
	}

} // endof convert_to()

void BigFloat::pop_front_leading_zeros()
{
/* Old version:
	size_t limit = last_digit_position();

	for (size_t i = 0; i < limit; ++i)
	{
		if (get_number()[0] == '0')
		{
			erase_elem(0);
		}
		else if (get_number()[0] == '.')
		{
			continue;
		}
		else
		{
			break;
		}
	}
*/
	pop_front_elem(leading_zeros());
}

void BigFloat::pop_front_extra_leading_zeros()
{
	pop_front_elem(extra_leading_zeros());
}

void BigFloat::push_back_additional_zeros(const size_t quantity)
{
	std::string additionalZeros(quantity, '0');
	insert_elem(additionalZeros, space_position());
}

void BigFloat::pop_back_trailing_zeros()
{
/*
Old version:
	size_t lastDigitPos = last_digit_position();

	while
		(
			last_digit_value() == 0 &&
			lastDigitPos > position_after(dot_position())
		)
	{
		erase_elem(lastDigitPos, lastDigitPos);
	}
*/
	size_t lastDigitPos = last_digit_position();
	size_t from_pos_inclusive = position_after(lastDigitPos - trailing_zeros());
/*
	// #pbtz() 49
	std::cout
		<< "pop_back_trailing_zeros() compute from_pos_inclusive according to formula:"
		<< "\nfrom_pos_inclusive = position_after(lastDigitPos - trailing_zeros())"
		<< "\nAll elements of formula are:"
		<< "\nThe number itself: " << get_number()
		<< "\nlastDigitPos: " << lastDigitPos
		<< "\ntrailing_zeros(): " << trailing_zeros()
		<< "\nlastDigitPos - trailing_zeros(): " << lastDigitPos - trailing_zeros()
		<< "\nposition_after(lastDigitPos - trailing_zeros()): " << position_after(lastDigitPos - trailing_zeros())
		<< "\nAssertion occured in BigFloat.cpp, #pbtz() 49\n\n"
		;
*/
	size_t to_pos_inclusive = lastDigitPos;
/*
	// #pbtz() 50
	std::cout
		<< "pop_back_trailing_zeros() will erase elements"
		<< "\nfrom element with index " << from_pos_inclusive
		<< "\nto element with index " << to_pos_inclusive
		<< "\nin number: " << get_number()
		<< "\nAssertion occured in BigFloat.cpp, #pbtz() 50\n\n"
		;
*/
	erase_elem(from_pos_inclusive, to_pos_inclusive);
}



// getters =====================================================================
BigFloat BigFloat::abs_value()
{
	return get_number();
}

size_t BigFloat::extra_leading_zeros() const
{	
	// for example:
	// number 000012.345 has 4 extra leading zeros (normal view: 12.345)
	// number 0000.00666 has 3 extra leading zeros (normal view: 0.00666)

	size_t extraLeadingZeros = 0;
	size_t limit = position_before(dot_position());
	for (size_t i = 0; i < limit; ++i)
	{
		if (get_number()[i] == '0')
		{
			++extraLeadingZeros;
		}
		else
		{
			break;
		}

	}

	return extraLeadingZeros;
}

size_t BigFloat::leading_zeros() const
{
	// for example:
	// number 000012.345 has 4 leading zeros
	// number 0000.00666 has 6 leading zeros

	size_t LeadingZeros = 0;
	size_t limit = last_digit_position();
	if (has_leading_zeros())
	{
		for (size_t i = 0; i < limit; ++i)
		{
			if (get_number()[i] == '0')
			{
				++LeadingZeros;
			}
			else if (get_number()[i] == '.')
			{
				continue;
			}
			else
			{
				break;
			}
		}
	}

/*
	std::cout
		<< "The quantity of leading zeros is: "
		<< quantity_of_leading_zeros
		<< "\nAssertion occured in BigFloat.cpp, leading_zeros().\n\n"
		;
*/
	return LeadingZeros;
}

size_t BigFloat::trailing_zeros() const
{
	size_t trailingZeros = 0;
	size_t limit = position_after(dot_position());

	for (size_t i = last_digit_position(); i > limit; --i)
	{
		if (elem_value_as_digit(i) == 0)
		{
			++trailingZeros;
		}
		else
		{
			break;
		}
	}
	//std::cout << "\ntrailingZeros: " << trailingZeros << "\n";
	return trailingZeros;
}

size_t BigFloat::dot_position() const
{
/*
	std::cout
		<< "The dot position is: "
		<< char_position(get_number(), '.')
		<< "\nAssertion occured in BigFloat.cpp, dot_position().\n\n"
		;
*/
	return char_position(get_number(), '.');
}

size_t BigFloat::digits_after_dot() const
{   // TODO: implement count() function?
/*
	std::cout
		<< "The quantity of digits after dot is: "
		<< last_digit_position() - dot_position()
		<< "\nAssertion occured in BigFloat.cpp, digits_after_dot().\n\n"
		;
*/
	return last_digit_position() - dot_position();
}

size_t BigFloat::digits_before_dot() const
{
/*
	std::cout
		<< "The quantity of digits before dot is: "
		<< dot_position()
		<< "\nAssertion occured in BigFloat.cpp, digits_before_dot().\n\n"
		;
*/
	return dot_position();
}

size_t BigFloat::e_position() const
{
	size_t numSize = get_number().size();
	size_t ePos = numSize;

	for (size_t i = 0; i < numSize; ++i)
	{
		if (elem_value_as_char(i) == 'e' || elem_value_as_char(i) == 'E')
		{
			ePos = i;
			break;
		}
	}

	/*
	// #epos() 1
	std::cout
		<< "The E position is: "
		<< ePos
		<< "\nAssertion occured in BigFloat.cpp, e_position(), #epos() 1.\n\n"
		;
	*/
	/*
	// #epos() 2
	std::cout
		<< "The number: "
		<< get_number()
		<< "\nAssertion occured in BigFloat.cpp, e_position(), #epos() 2.\n\n"
		;
	*/	
	return ePos;
}

size_t BigFloat::digits_after_e() const
{   // TODO: implement count() function?
/*
	std::cout
		<< "The quantity of digits after E is: "
		<< get_number().size() - position_before(space_position())
		<< "\nAssertion occured in BigFloat.cpp, digits_after_e().\n\n"
		;
*/
	return get_number().size() - position_before(space_position());
}

size_t BigFloat::e_value_as_number() const
{
/*
	std::cout
		<< "The E value as number is: "
		<< string_to_number(e_value_as_string())
		<< "\nAssertion occured in BigFloat.cpp, digits_after_e().\n\n"
		;
*/
	return string_to_number(e_value_as_string());
}

std::string BigFloat::e_value_as_string() const
{
	std::string eVal = "";
	size_t numSize = get_number().size();
	size_t posAfterESignPos = position_after(e_sign_position());

	if (posAfterESignPos < numSize)
	{
		for (size_t i = posAfterESignPos; i < numSize; ++i)
		{
			eVal = eVal + elem_value_as_char(i);
		}
	}

/*
	// #evas() 77
	std::cout
		<< "The E value as string is: " << eVal
		<< "\nIn number: " << get_number()
		<< "\nAssertion occured in BigFloat.cpp, e_value_as_string(), #evas() 77.\n\n"
		;
*/
	return eVal;
}

size_t BigFloat::e_sign_position() const
{
	size_t numSize = get_number().size();
	size_t eSignPos = numSize;
	for (size_t i = e_position(); i < numSize; ++i)
	{
		if (is_sign(get_number()[i]))
		{
			eSignPos = i;
			break;
		}
	}
/*
	std::cout
		<< "The E sign position is: "
		<< eSignPos
		<< "\nAssertion occured in BigFloat.cpp, e_sign_position().\n\n"
		;
*/
	return eSignPos;
}

char BigFloat::e_sign() const
{
/*
	std::cout
		<< "The E sign is: "
		<< get_number()[e_sign_position()]
		<< "\nAssertion occured in BigFloat.cpp, e_sign().\n\n"
		;
*/
	return get_number()[e_sign_position()];
}

std::string BigFloat::e_tail() const
{
	std::string eTail;
	eTail = eTail + " E" + eSign_ + eValueAsString_;
	return eTail;
}

size_t BigFloat::last_digit_position() const
{
/*
	Old version:
	size_t numSize = get_number().size();
	size_t lastDigitPos = numSize;
	for (size_t i = 0; i < numSize; ++i)
	{
		if (is_digit(get_number()[i]) || is_dot(get_number()[i]))
		{
			lastDigitPos = i;
		}
		else
		{
			break;
		}
	}

	return lastDigitPos;
*/

/*
	std::cout
		<< "The last digit position is: "
		<< position_before(space_position())
		<< "\nAssertion occured in BigFloat.cpp, last_digit_position().\n\n"
		;
*/
	return position_before(space_position());
}

size_t BigFloat::last_digit_value() const
{
/*
	std::cout
		<< "The last digit value is: "
		<< get_number()[last_digit_position()]
		<< "\nAssertion occured in BigFloat.cpp, last_digit_value().\n\n"
		;
*/
	return elem_value_as_digit(last_digit_position());
}

size_t BigFloat::space_position() const
{
/*
	std::cout
		<< "The space position is: "
		<< char_position(get_number(), ' ')
		<< "\nAssertion occured in BigFloat.cpp, space_position().\n\n"
		;
*/
	return char_position(get_number(), ' ');
}

std::string BigFloat::mantissa() const
{
	std::string mantissa("");

	size_t spacePos = space_position();
	size_t numSize = get_number().size();

	if (spacePos != numSize)
	{
		mantissa = get_number();
		erase_part_of(mantissa, spacePos, numSize - 1);
	}

/*
	std::cout
		<< "The mantissa is: "
		<< mantissa
		<< "\nAssertion occured in BigFloat.cpp, mantissa().\n\n"
		;
*/
	return mantissa;
}

BigFloat::Notation BigFloat::notation() const
{
/*
	std::cout
		<< "The notation is: "
		<< ((notation_ == DECIMAL) ? "DECIMAL" : (notation_ == SCIENTIFIC ? "SCIENTIFIC" : "DEFAULT"))
		<< "\nAssertion occured in BigFloat.cpp, mantissa().\n\n"
		;
*/
	return notation_;
}



// setters =====================================================================
void BigFloat::set_number(const BigFloat& bf)
{
	BigNumber::set_number(bf.get_sign() + bf.get_number());
	notation_ = bf.notation_;
	eSign_ = bf.eSign_;
	eValueAsString_ = bf.eValueAsString_;
/*
	std::cout
		<< "Assertion occured in BigFloat.cpp, set_number(const BigFloat& bf)."
		<< "\nData members after setter finished his work:"
		<< "\nsign_: " << get_sign()
		<< "\nnumber_: " << get_number()
		<< "\neSign_: " << eSign_
		<< "\neValueAsString_" << eValueAsString_ << "\n\n"
		;
*/
}

void BigFloat::set_number(const std::string& num)
{	
/*
	// #setn(str) 1
	std::cout
		<< "BigFloat::set_number(const std::string& num) began his work."
		<< "\nAssertion occured in BigFloat.cpp, #setn(str) 1.\n\n"
		;
*/
	size_t numSize = get_number().size();

	if (num == "0.0" || num == "0" || numSize == 0)
	{
		reset();

/*
		// #setn(str) 2
		std::cout
			<< "BigFloat::reset() has been called, "
			<< "because the number is zero: "
			<< num
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 2.\n\n"
			;
*/
	}
	else if (contains_digits_only(num))
	{
/*
		// #setn(str) 3
		std::cout
			<< "Global function contains_digits_only(const std::string& num) has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 3.\n\n"
			;
*/
		if (numSize == 1)
		{

			BigNumber::set_number(num);
			notation_ = DECIMAL;
			eSign_ = '+';				
			eValueAsString_ = "0";
			insert_elem(".0", numSize);
				
/*
				// #setn(str) 6
				std::cout
					<< "BigNumber::insert_elem(const std::string & str, const size_t pos) has been called."
					<< "\nAssertion occured in BigFloat.cpp, #setn(str) 6.\n\n"
					;
*/

		}
		else
		{
			BigNumber::set_number(num);
/*
			// #setn(str) 7
			std::cout
				<< "BigNumber::set_number(num) has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 7.\n\n"
				;
*/
			if (has_extra_leading_zeros())
			{
/*
				// #setn(str) 8
				std::cout
					<< "BigFloat::has_extra_leading_zeros() has been called."
					<< "\nAssertion occured in BigFloat.cpp, #setn(str) 8.\n\n"
					;
*/
				pop_front_extra_leading_zeros();

/*
				// #setn(str) 9
				std::cout
					<< "BigFloat::pop_front_extra_leading_zeros() has been called."
					<< "\nAssertion occured in BigFloat.cpp, #setn(str) 9.\n\n"
					;
*/
			}

			notation_ = DECIMAL;
			eSign_ = '+';
			eValueAsString_ = number_to_string(numSize - 1);
			insert_elem('.', 1);
/*
			// #setn(str) 10
			std::cout
				<< "BigNumber::insert_elem(const char ch, const size_t pos) has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 10.\n\n"
				;
*/
		}		
	}
	else
	{
		BigNumber::set_number(num);
/*
		// #setn(str) 21
		std::cout
			<< "BigNumber::set_number(num) has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 21.\n\n"
			;
*/
		if (has_extra_leading_zeros())
		{
/*
			// #setn(str) 22
			std::cout
				<< "BigFloat::has_extra_leading_zeros() has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 22.\n\n"
				;
*/
			pop_front_extra_leading_zeros();
/*
			// #setn(str) 23
			std::cout
				<< "BigFloat::pop_front_extra_leading_zeros() has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 23.\n\n"
				;
*/
		}

		if (has_trailing_zeros())
		{
/*
			// #setn(str) 24
			std::cout
				<< "BigFloat::has_trailing_zeros() has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 24.\n\n"
				;
*/
			pop_back_trailing_zeros();
/*
			// #setn(str) 25
			std::cout
				<< "BigFloat::pop_back_trailing_zeros() has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 25.\n\n"
				;
*/
		}

		if (is_correct(SCIENTIFIC))
		{
			eSign_ = e_sign();
			eValueAsString_ = e_value_as_string();
/*
			// #setn(str) 26
			std::cout
				<< "is_correct(SCIENTIFIC) has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 26.\n\n"
				;
*/
			convert_to(DECIMAL);
/*
			// #setn(str) 27
			std::cout
				<< "convert_to(DECIMAL) has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 27.\n\n"
				;
*/
		}
		else if (is_correct(DECIMAL))
		{
			notation_ = DECIMAL;
			if (has_leading_zeros())
			{
				eSign_ = '-';
				eValueAsString_ = number_to_string(leading_zeros());
			}
			else
			{
				if (dot_position() != 1)
				{
					eSign_ = '+';
					eValueAsString_ = number_to_string(dot_position() - 1);
				}
				else
				{
					eSign_ = '+';
					eValueAsString_ = "0";
				}

			}
/*
			// #setn(str) 28
			std::cout
				<< "is_correct(DECIMAL) has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 28.\n\n"
				;
*/
			// do nothing
		}
		else
		{
			reset();
/*
			// #setn(str) 29
			std::cout
				<< "reset() has been called."
				<< "\nAssertion occured in BigFloat.cpp, #setn(str) 29.\n\n"
				;
*/
		}
	}

	if (has_extra_leading_zeros())
	{
/*
		// #setn(str) 30
		std::cout
			<< "BigFloat::has_extra_leading_zeros() has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 30.\n\n"
			;
*/
		pop_front_extra_leading_zeros();
/*
		// #setn(str) 31
		std::cout
			<< "BigFloat::pop_front_extra_leading_zeros() has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 31.\n\n"
			;
*/
	}

	if (has_trailing_zeros())
	{
/*
		// #setn(str) 32
		std::cout
			<< "BigFloat::has_trailing_zeros() has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 32.\n\n"
			;
*/
		pop_back_trailing_zeros();
/*
		// #setn(str) 33
		std::cout
			<< "BigFloat::pop_back_trailing_zeros() has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 33.\n\n"
			;
*/
	}

/*
	// #setn(str) 34
	std::cout
		<< "\nData members after setter finished his work:"
		<< "\nsign_: " << get_sign()
		<< "\nnumber_: " << get_number()
		<< "\neSign_: " << eSign_
		<< "\neValueAsString_: " << eValueAsString_
		<< "\nAssertion occured in BigFloat.cpp, set_number(const std::string& num), #setn(str) 34.\n\n"
		;
*/
}

void BigFloat::reset()
{
	//clear_number();
	BigNumber::set_number("0.0");
	notation_ = DEFAULT;
	eSign_ = '+';
	eValueAsString_ = "0";
/*
	std::cout
		<< "Assertion occured in BigFloat.cpp, reset().\n\n"
		;
*/
}



// division helpers ============================================================
static BigFloat::DivisionMembers dm;

char BigFloat::next_digit_of_quotient() const
{
	BigInt fitSubtrahend = dm.divisorInt;
/*	
	// #nxtdigqnt 1
	std::cout
		<< "fitSubtrahend.get_number(): " << fitSubtrahend.get_number()
		<< "\nAssertion occured in BigFloat.cpp, ##nxtdigqnt 1.\n\n"
		;
*/
	BigInt curSubtrahend = dm.divisorInt;
/*
	// #nxtdigqnt 2
	std::cout
		<< "curSubtrahend.get_number(): " << curSubtrahend.get_number()
		<< "\nAssertion occured in BigFloat.cpp, ##nxtdigqnt 2.\n\n"
		;
*/
	BigInt fitMultiplier('1');
/*
	// #nxtdigqnt 3
	std::cout
		<< "fitMultiplier.get_number(): " << fitMultiplier.get_number()
		<< "\nAssertion occured in BigFloat.cpp, ##nxtdigqnt 3.\n\n"
		;
*/
	BigInt curMultiplier('1');
/*
	// #nxtdigqnt 4
	std::cout
		<< "curMultiplier.get_number(): " << curMultiplier.get_number()
		<< "\nAssertion occured in BigFloat.cpp, ##nxtdigqnt 4.\n\n"
		;
*/
	
	size_t iteration = 1;
	while (curSubtrahend <= dm.subtotal)
	{
/*
		// #nxtdigqnt 5
		std::cout
			<< " iteration " << iteration << " ####################################"
			<< "\ncurSubtrahend: " << curSubtrahend.get_number()
			<< "\nsubtotal: " << dm.subtotal.get_number()
			<< "\n(curSubtrahend <= subtotal): " << std::boolalpha << (curSubtrahend <= dm.subtotal) << std::noboolalpha
			<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 5\n\n"
			;
*/		
		fitSubtrahend = curSubtrahend;
/*
		// #nxtdigqnt 6
		std::cout
			<< "fitSubtrahend.get_number(): " << fitSubtrahend.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 6.\n\n"
			;
*/
		fitMultiplier = curMultiplier;
/*
		// #nxtdigqnt 7
		std::cout
			<< "fitMultiplier.get_number(): " << fitMultiplier.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 7.\n\n"
			;
*/
		++curMultiplier;
/*
		// #nxtdigqnt 8
		std::cout
			<< "curMultiplier.get_number(): " << curMultiplier.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 8.\n\n"
			;
*/
		curSubtrahend = dm.divisorInt * curMultiplier;
/*
		// #nxtdigqnt 9
		std::cout
			<< "curSubtrahend in the end of " << iteration << " iteration: " << curSubtrahend.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 9.\n\n"
			;
*/
		iteration++;
	}
/**/
	// #nxtdigqnt 10
	std::cout
		<< "fitSubtrahend is " << fitSubtrahend.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #nxtdigqnt 10.\n\n"
		;

/**/
	// #nxtdigqnt 11
	std::cout
		<< "fitMultiplier (digit, that goes to dm.quotientInt) is " << fitMultiplier.get_number() << " *****************************"
		<< "\nAssertion occured in BigFloat.cpp, ##nxtdigqnt 11.\n\n"
		;

	return fitMultiplier.elem_value_as_char(0);
}

// для деления меньшего числа на большее:
void BigFloat::calc_subtotal_and_add_digits_to_quotient() const
{
	bool zeroWasPushedBackInSubtotalInPrevStep = false;

	dm.subtotal.pop_front_extra_zeros();

	size_t iteration = 1;
	while (dm.subtotal < dm.divisorInt)
	{
		/**/
		// #calcsubdig() 1
		std::cout
			<< " iteration " << iteration << " ====================================="
			<< "\nsubtotal: " << dm.subtotal.get_number()
			<< "\ndivisorInt: " << dm.divisorInt.get_number()
			<< "\n(subtotal < divisorInt): " << std::boolalpha << (dm.subtotal < dm.divisorInt) << std::noboolalpha
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 1\n\n"
			;
		dm.subtotal.push_back_elem('0');
/**/
		// #calcsubdig() 2
		std::cout
			<< "subtotal.push_back_elem('0') has been called."
			<< "\nsubtotal.get_number(): " << dm.subtotal.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 2.\n\n"
			;

		if (zeroWasPushedBackInSubtotalInPrevStep)
		{
			dm.quotientInt.push_back_elem('0');
/**/
			// #calcsubdig() 3
			std::cout
				<< "quotientInt.push_back_elem('0') has been called."
				<< "\nquotientInt.get_number(): " << dm.quotientInt.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 3."
				<< " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n"
				;

		}

		zeroWasPushedBackInSubtotalInPrevStep = true;
		/**/
		// #calcsubdig() 4
		std::cout
			<< "subtotal before subtotal.pop_front_extra_zeros():" << dm.subtotal.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 4.\n\n"
			;

		dm.subtotal.pop_front_extra_zeros();
		/**/
		// #calcsubdig() 5
		std::cout
			<< "subtotal after subtotal.pop_front_extra_zeros():" << dm.subtotal.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 5.\n\n"
			;

		++iteration;

	} // endof while (dm.subtotal < dm.divisorInt)

	/**/
	// #calcsubdig() 6
	std::cout
		<< "subtotal after all: " << dm.subtotal.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #calcsubdig() 6.\n\n"
		;

	dm.curIndexOfDigitOfDividend = dm.divisorInt.quantity_of_digits() + 1;
} // endof calc_subtotal_and_add_digits_to_quotient(args)

  // для деления большего числа на меньшее:
void BigFloat::calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) const
{
/**/
	// #calcsubdig(bi) 1
	std::cout
		<< "prevSubtotal is " << prevSubtotal.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 1\n\n"
		;

	dm.subtotal = prevSubtotal;
	dm.subtotal.pop_front_extra_zeros();

	static bool is_first_time_calc_subtotal = true;
	static bool is_first_time_add_digits_to_subtotal = true;

	size_t iteration = 1;
	while
		(
			dm.subtotal < dm.divisorInt &&
			dm.curIndexOfDigitOfDividend <= dm.dividendInt.last_digit_position()
		)
	{
/*
		// #calcsubdig(bi) 2
		std::cout
			<< "calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) iteration " << iteration << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			<< "\n(subtotal < divisorInt): " << std::boolalpha << (dm.subtotal <= dm.divisorInt) << std::noboolalpha
			<< "\nbecause subtotal (before next digit was pushed back) is " << dm.subtotal.get_number()
			<< " and divisorInt is " << dm.divisorInt.get_number()
			<< "\n&& (curIndexOfDigitOfDividend <= dividendInt.last_digit_position()): " << std::boolalpha << (dm.curIndexOfDigitOfDividend <= dm.dividendInt.last_digit_position()) << std::noboolalpha
			<< "\nbecause curIndexOfDigitOfDividend is " << dm.curIndexOfDigitOfDividend
			<< "\nand dividendInt.last_digit_position() is " << dm.dividendInt.last_digit_position()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 2\n\n"
			;
*/		
		dm.subtotal.push_back_elem
		(
			dm.dividendInt.elem_value_as_char(dm.curIndexOfDigitOfDividend)
		);
		
		dm.subtotal.pop_front_extra_zeros();
		++dm.curIndexOfDigitOfDividend;

		if (!is_first_time_calc_subtotal)
		{
			if (!is_first_time_add_digits_to_subtotal)
			{
				dm.quotientInt.push_back_elem('0');
			}
		}

/*
		// #calcsubdig(bi) 3
		std::cout
			<< "subtotal after next digit was pushed back is " << dm.subtotal.get_number()
			<< "\nand curIndexOfDigitOfDividend after increment is " << dm.curIndexOfDigitOfDividend
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 3\n\n"
			;
*/
		is_first_time_add_digits_to_subtotal = false;
		is_first_time_add_digits_to_subtotal = true;
		++iteration;
	}

	static bool addition_was_already_done = true;	
	if
		(
			!dm.subtotal.is_zero() &&
			dm.subtotal < dm.divisorInt &&
			dm.curIndexOfDigitOfDividend > dm.dividendInt.last_digit_position()
		)
	{
		static bool quotient_dot_pos_was_already_set = false;
		if (!quotient_dot_pos_was_already_set)
		{
			dm.quotientDotPos = dm.subtotal.quantity_of_digits();
			quotient_dot_pos_was_already_set = true;
		}
		
/**/
		// #calcsubdig(bi) 4
		std::cout
		<< "dm.quotientDotPos is " << dm.quotientDotPos << " .................................."
		<< "\nbecause dm.subtotal.quantity_of_digits() is " << dm.subtotal.quantity_of_digits()
		<< "\nbecause dm.subtotal is " << dm.subtotal.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 4\n\n"
		;
		

/*
		// #calcsubdig(bi) 5
		std::cout
			<< "subtotal before second phase is " << dm.subtotal.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 5\n\n"
			;
*/
		if (addition_was_already_done)
		{
/*
		// #calcsubdig(bi) 6
		std::cout
			<< dm.subtotal.quantity_of_digits() << " zeros will pushed back to dm.quotientInt."
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 6"
			<< " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"
			;
*/
			for (size_t i = 0; i < dm.subtotal.last_digit_position(); ++i)
			{
				dm.quotientInt.push_back_elem('0');
			}
			addition_was_already_done = false;
		}

/*
		// #calcsubdig(bi) 7
		std::cout
			<< "dm.quotientInt after zeros has been pushed back: " << dm.quotientInt.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 7"
			<< " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"
			;
*/
		calc_subtotal_and_add_digits_to_quotient();
	}

	is_first_time_calc_subtotal = false;
	/**/
	// #calcsubdig(bi) 8
	std::cout
		<< "calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) is done."
		<< "\ndm.subtotal after that is " << dm.subtotal.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #calcsubdig(bi) 8\n\n"
		;
} // endof calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) const

void BigFloat::add_zeros_to_quotient() const
{
	if (dm.subtotal.is_zero() && all_remaining_digits_of_dividend_are_zeros())
	{
		for (size_t i = dm.curIndexOfDigitOfDividend; i < dm.dividendInt.quantity_of_digits(); ++i)
		{
			dm.quotientInt.push_back_elem('0');
		}
	}
}

void BigFloat::define_quotient_sign
(
	BigFloat & quotient,
	BigFloat & dividend,
	BigFloat & divisor
)
const
{
	if (dividend.get_sign() == divisor.get_sign())
	{
		if (dividend.get_sign() == '+')
		{
			quotient.set_sign('+');
		}
		else
		{
			quotient.set_sign('-');
		}
	}
	else
	{
		quotient.set_sign('-');
	}
}

BigFloat BigFloat::finalize_division() const
{
	BigFloat quotient;
/**/
	// #findiv 1
	std::cout
		<< "Local object BigFloat quotient in beginning:\n"
		<< quotient.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #findiv 1.\n\n"
		;

	quotient.clear_number();
	/**/
	// #findiv 2
	std::cout
		<< "Local object BigFloat quotient after quotient.clear_number():\n"
		<< quotient.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #findiv 2.\n\n"
		;

	add_dot();
	/**/
	// #findiv 3
	std::cout
		<< "quotientInt after add_dot():\n"
		<< dm.quotientInt.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #findiv 3.\n\n"
		;


	quotient.push_back_elem(dm.quotientInt.get_number());
	/**/
	// #findiv 4
	std::cout
		<< "Local object BigFloat quotient after quotient.push_back_elem(quotientInt.get_number()):\n"
		<< quotient.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #findiv 4.\n\n"
		;

	return quotient;
}

bool BigFloat::division_is_finished() const
{
	bool result =
		(dm.quotientInt.quantity_of_digits() >= PRECISION) ||
		(dm.curIndexOfDigitOfDividend > dm.dividendInt.last_digit_position() && dm.subtotal.is_zero()) ||
		(dm.subtotal.is_zero() && all_remaining_digits_of_dividend_are_zeros());
/*
	// #divisfin 1
	std::cout
		<< "division_is_finished() has been called."
		<< "\nquotientInt.quantity_of_digits() >= PRECISION: " << std::boolalpha << (dm.quotientInt.quantity_of_digits() >= PRECISION)
		<< "\nbecause quotientInt.quantity_of_digits() is " << dm.quotientInt.quantity_of_digits()
		<< "\ncurIndexOfDigitOfDividend > dividendInt.last_digit_position(): " << std::boolalpha << (dm.curIndexOfDigitOfDividend > dm.dividendInt.last_digit_position())
		<< "\nbecause curIndexOfDigitOfDividend is " << dm.curIndexOfDigitOfDividend
		<< " and dividendInt.last_digit_position() is " << dm.dividendInt.last_digit_position()
		<< "\nand dividendInt is " << dm.dividendInt
		<< "\nsubtotal.is_zero(): " << std::boolalpha  << dm.subtotal.is_zero()
		<< "\nbecause subtotal is " << dm.subtotal.get_number()
		<< "\nall_remaining_digits_of_dividend_are_zeros() is " << std::boolalpha << all_remaining_digits_of_dividend_are_zeros()
		<< "\ndivision_is_finished() is " << std::boolalpha << result
		<< "\nAssertion occured in BigFloat.cpp, #divisfin 1.\n\n"
		;
*/
	return result;
}

void BigFloat::divide_abs_greater_by_less() const
{
	dm.divisorInt.pop_front_extra_zeros();
	while (!division_is_finished())
	{
		calc_subtotal_and_add_digits_to_quotient(dm.subtotal);
		char nextDigitOfQuotient = next_digit_of_quotient();
		dm.quotientInt.push_back_elem(nextDigitOfQuotient);
		dm.subtotal = dm.subtotal - (dm.divisorInt * nextDigitOfQuotient);
	}
	add_zeros_to_quotient();
	dm.quotientInt.pop_front_extra_zeros();
}

void BigFloat::divide_abs_less_by_greater() const
{
	dm.subtotal = dm.dividendInt;
	static bool zeroWasPushedBackInSubtotalInPrevStep = false;
	while (!division_is_finished())
	{
		calc_subtotal_and_add_digits_to_quotient();
		char nextDigitOfQuotient = next_digit_of_quotient();
		dm.quotientInt.push_back_elem(nextDigitOfQuotient);
		dm.subtotal = dm.subtotal - (dm.divisorInt * nextDigitOfQuotient);
	}
}

void BigFloat::align_divident_and_divisor(BigFloat & dividend, BigFloat & divisor) const
{
	size_t shift = 0;

	if (dividend.digits_after_dot() >= divisor.digits_after_dot())
	{
		shift = dividend.digits_after_dot();
	}
	else
	{
		shift = divisor.digits_after_dot();
	}

	dividend.move_floating_point(RIGHT, shift);
	divisor.move_floating_point(RIGHT, shift);
}

void BigFloat::prepare_divident_and_divisor(BigFloat & dividend, BigFloat & divisor) const
{
	align_divident_and_divisor(dividend, divisor);

	dividend.erase_elem(dividend.dot_position());
	divisor.erase_elem(divisor.dot_position());

	dividend.erase_elem(dividend.last_digit_position());
	divisor.erase_elem(divisor.last_digit_position());

	dm.dividendInt = dividend.get_number();
	dm.divisorInt = divisor.get_number();
}

bool BigFloat::all_remaining_digits_of_dividend_are_zeros() const
{
	bool result = true;
/*
	// #allremdig 1
	std::cout
		<< "dm.curIndexOfDigitOfDividend: " << dm.curIndexOfDigitOfDividend
		<< "\nAssertion occured in BigFloat.cpp, #allremdig 1.\n\n"
		;
*/
	for (size_t i = dm.curIndexOfDigitOfDividend; i < dm.dividendInt.quantity_of_digits(); ++i)
	{
		if (dm.dividendInt.elem_value_as_digit(i) != 0)
		{
			result = false;
			break;
		}
	}
/*
	// #allremdig 2
	std::cout
		<< "all_remaining_digits_of_dividend_are_zeros() is " << std::boolalpha << result
		<< "\nAssertion occured in BigFloat.cpp, #allremdig 2.\n\n"
		;
*/
	return result;
}

void BigFloat::add_dot() const
{
	if (dm.dividendInt < dm.divisorInt)
	{
		dm.quotientInt.insert_elem('.', 1);
	}
	else if (dm.dividendInt > dm.divisorInt)
	{
		if (dm.subtotal.is_zero())
		{
			dm.quotientInt.push_back_elem(".0");
		}
		else
		{
			dm.quotientInt.insert_elem('.', dm.quotientDotPos);
		}
	}

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

	return b < a;
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

bool BigFloat::operator!=(const BigFloat & bf) const
{
	BigFloat a(*this);
	BigFloat b(bf);

	return (a < b) || (a > b);
} // endof operator!=



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
	if (this->get_number() != &obj[0]) // &obj.front()
	{
		set_number(obj);

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
	return *this;
} // endof operator=



// arithmetic operators (both operand are same type) ===========================
BigFloat BigFloat::operator+(const BigFloat& addendum) const // #op+(bf)
{
	BigFloat sum;
/*
	// #op+(bf) 1
	std::cout
		<< "sum in beginning: " << sum.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 1.\n\n"
		;
*/
	sum.clear_number();
/*
	// #op+(bf) 2
	std::cout
		<< "sum after cleaning: " << sum.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 2.\n\n"
		;
*/
	BigFloat a(*this);
	BigFloat b(addendum);

/*
	// #op+(bf) 3
	std::cout
		<< "Data of temporary objects a and b in beginning: "
		<< "\na.get_sign() and a.get_number(): " << a.get_sign() << a.get_number()
		<< "\na itself: " << a
		<< "\nb.get_sign() and b.get_number(): " << b.get_sign() << b.get_number()
		<< "\nb itself: " << b
		<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 3.\n\n"
		;
*/
	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();
/*
	// #op+(bf) 4
	std::cout
		<< "Size of temporary objects a and b in beginning: "
		<< "\naSize: " << aSize
		<< "\nbSize: " << bSize
		<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 4.\n\n"
		;
*/
	if (a.get_sign() == b.get_sign())
	{
/*
		// #op+(bf) 5
		std::cout
			<< "Signs of temporary objects a and b are the same: "
			<< "\na.get_sign(): " << a.get_sign()
			<< "\nb.get_sign(): " << b.get_sign()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 5.\n\n"
			;
*/
		size_t diff; // разница между количеством разрядов

		// уравниваем количество разрядов обоих чисел до плавающей точки:		
		size_t aDigitsBeforeDot = a.digits_before_dot();
		size_t bDigitsBeforeDot = b.digits_before_dot();

/*
		// #op+(bf) 6
		std::cout
			<< "The quantity of digits before dot: "
			<< "\naDigitsBeforeDot: " << aDigitsBeforeDot
			<< "\nbDigitsBeforeDot: " << bDigitsBeforeDot
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 6.\n\n"
			;
*/
		if (aDigitsBeforeDot < bDigitsBeforeDot)
		{
			diff = bDigitsBeforeDot - aDigitsBeforeDot;
			for (size_t i = 0; i < diff; ++i)
			{
				a.push_front_elem('0');
			}
		}
		else if (bDigitsBeforeDot < aDigitsBeforeDot)
		{
			diff = aDigitsBeforeDot - bDigitsBeforeDot;
			for (size_t i = 0; i < diff; ++i)
			{
				b.push_front_elem('0');
			}
		}
/*
		// #op+(bf) 7
		std::cout
			<< "The numbers after aligning digits before dot: "
			<< "\na.get_number(): " << a.get_number()
			<< "\nb.get_number(): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 7.\n\n"
			;
*/
		// уравниваем количество разрядов обоих чисел после плавающей точки:
		size_t aDigitsAfterDot = a.digits_after_dot();
		size_t bDigitsAfterDot = b.digits_after_dot();

/*
		// #op+(bf) 8
		std::cout
			<< "The quantity of digits after dot: "
			<< "\naDigitsAfterDot: " << aDigitsAfterDot
			<< "\nbDigitsAfterDot: " << bDigitsAfterDot
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 8.\n\n"
			;
*/
		if (aDigitsAfterDot < bDigitsAfterDot) // #op+3
		{
			diff = bDigitsAfterDot - aDigitsAfterDot;
			for (size_t i = 0; i < diff; ++i)
			{
				a.push_back_elem('0');
			}
		}
		else if (bDigitsAfterDot < aDigitsAfterDot) // #op+4
		{
			diff = aDigitsAfterDot - bDigitsAfterDot;
			for (size_t i = 0; i < diff; ++i)
			{
				b.push_back_elem('0');
			}
		}
/*
		// #op+(bf) 9
		std::cout
			<< "The numbers after aligning digits after dot: "
			<< "\na.get_number(): " << a.get_number()
			<< "\nb.get_number(): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 9.\n\n"
			;
*/
		// запомним позицию плавающей точки:
		size_t aDotPos = a.dot_position();
		size_t bDotPos = b.dot_position();

/*
		// #op+(bf) 10
		std::cout
			<< "The dot position: "
			<< "\naDotPos: " << aDotPos
			<< "\nbDotPos: " << bDotPos
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 10.\n\n"
			;
*/
		// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
		a.erase_elem(aDotPos);
		b.erase_elem(bDotPos);
/*
		// #op+(bf) 11
		std::cout
			<< "The numbers after erasing dot: "
			<< "\na.get_number(): " << a.get_number()
			<< "\nb.get_number(): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 11.\n\n"
			;
*/
		// будем складывать, начиная с млаших разрядов, для этого перевернём числа:
		a.reverse_number();
		b.reverse_number();
/*
		// #op+(bf) 12
		std::cout
			<< "The numbers after reversing: "
			<< "\na.get_number(): " << a.get_number()
			<< "\nb.get_number(): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 12.\n\n"
			;
*/
		// излишки (то, что обычно при сложении в столбик "пишем в уме") будем складывать в переменную extra;
		size_t extra = 0;
		// промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
		size_t subtotal = 0;

		size_t limit = aSize > bSize ? aSize - 1 : bSize - 1;
		for (size_t i = 0; i < limit; ++i)
		{
/*
			// #op+(bf) 65
			std::cout
				<< i + 1 << " iteration begins: "
				<< "\na.elem_value_as_digit(i): " << a.elem_value_as_digit(i)
				<< "\nb.elem_value_as_digit(i): " << b.elem_value_as_digit(i)
				<< "\nextra: " << extra
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 65.\n\n"
				;
*/
			subtotal = a.elem_value_as_digit(i) + b.elem_value_as_digit(i) + extra;
/*
			// #op+(bf) 66
			std::cout
				<< "subtotal after compute according to formula"
				<< "\nsubtotal = a.elem_value_as_digit(i) + b.elem_value_as_digit(i) + extra;"
				<< "\nsubtotal: " << subtotal
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 66.\n\n"
				;
*/
/*
			// #op+(bf) 67
			std::cout
				<< "\nsubtotal: " << subtotal
				<< "\nBigInt::MAX_DIGIT: " << BigInt::MAX_DIGIT
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 67.\n\n"
				;
*/
			if (subtotal > BigInt::MAX_DIGIT) // десятичная система, поэтому последняя цифра в разряде 9
			{
				extra = subtotal / BigInt::BASE;
				subtotal = subtotal % BigInt::BASE;
/*
				// #op+(bf) 68
				std::cout
					<< "subtotal > BigInt::MAX_DIGIT, hence"
					<< "\nsubtotal = subtotal % BigInt::BASE: " << subtotal
					<< "\nextra = subtotal / BigInt::BASE: " << extra
					<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 68.\n\n"
					;
*/
			}
			else
			{
				extra = 0;
/*
				// #op+(bf) 69
				std::cout
					<< "subtotal < BigInt::MAX_DIGIT, hence"
					<< "\nsubtotal = " << subtotal
					<< "\nextra = " << extra
					<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 69.\n\n"
					;
*/
			}

/*
			// #op+(bf) 70
			std::cout
				<< subtotal << " we write, and "
				<< extra << " we keep in mind."
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 70.\n\n"
				;
*/
			sum.push_back_elem(digit_to_char(subtotal));

/*
			// #op+(bf) 71
			std::cout
				<< "The sum after sum.push_back_elem(digit_to_char(subtotal)): "
				<< "\nsum.get_number(): " << sum.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 71.\n\n"
				;
*/
		}

		size_t extraDotShift = 0;
		if (extra)
		{
			sum.push_back_elem(digit_to_char(extra));
/*
			// #op+(bf) 72
			std::cout
				<< "The sum after sum.push_back_elem(digit_to_char(extra)): "
				<< "\nsum.get_number(): " << sum.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 72.\n\n"
				;
*/
			extraDotShift = 1;
		}

		sum.reverse_number();
/*
		// #op+(bf) 73
		std::cout
			<< "The sum after reversing: "
			<< "\nsum.get_number(): " << sum.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 73.\n\n"
			;
*/
		sum.insert_elem('.', aDotPos + extraDotShift);
/*
		// #op+(bf) 74
		std::cout
			<< "The sum after dot inserting: "
			<< "\nsum.get_number(): " << sum.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 74.\n\n"
			;
*/


		sum.set_number(sum.get_number());
/*
		// #op+(bf) 75
		std::cout
			<< "The sum after sum.set_number(sum.get_number()): "
			<< "\nsum.get_number(): " << sum.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 75.\n\n"
			;
*/
		sum.set_sign(a.get_sign());

/*
		// #op+(bf) 76
		std::cout
			<< "The sign after sum.set_sign(a.get_sign()): "
			<< "sum.get_sign(): " << sum.get_sign()
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 76.\n\n"
			;
*/
/*
		// #op+(bf) 77
		std::cout
			<< "The sum itself after all: " << sum
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 77.\n\n"
			;
*/
	}
	else
	{
		if (b.abs_value() > a.abs_value())
		{
			sum = b.abs_value() - a.abs_value();
		}
		else if (a.abs_value() > b.abs_value())
		{
			sum = a.abs_value() - b.abs_value();
		}
\

		if (a.get_sign() == '-')
		{
			sum.set_sign('+');
/*
			// #op+(bf) 77
			std::cout
				<< "sum.get_sign() and sum.get_number() after all: "
				<< sum.get_sign() << sum.get_number()
				<< "\nSum after all: " << sum
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 77.\n\n"
				;
*/
		}
		else if (b.get_sign() == '-')
		{
			sum.set_sign('-');
/*
			// #op+(bf) 78
			std::cout
				<< "sum.get_sign() and sum.get_number() after all: "
				<< sum.get_sign() << sum.get_number()
				<< "\nSum after all: " << sum
				<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 78.\n\n"
				;
*/
		}

		if (a.abs_value() == b.abs_value())
		{
			sum = "0.0";
			sum.set_sign('+');
		}
/*
		// #op+(bf) 79
		std::cout
			<< "sum.get_sign() and sum.get_number() after all: "
			<< sum.get_sign() << sum.get_number()
			<< "\nSum after all: " << sum
			<< "\nAssertion occured in BigFloat.cpp, #op+(bf) 79.\n\n"
			;
*/
	}
	
	return sum;
} // endof #op+(bf)

BigFloat BigFloat::operator-(const BigFloat& subtrahend) const // #op-(bf)
{
	BigFloat diff;

/*
	// #op-(bf) 1
	std::cout
		<< "diff in beginning: " << diff.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 1.\n\n"
		;
*/
	diff.clear_number();
/*
	// #op-(bf) 2
	std::cout
		<< "diff after cleaning: " << diff.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 2.\n\n"
		;
*/
	BigFloat a(*this);
	BigFloat b(subtrahend);

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

	if (a.get_sign() == b.get_sign())
	{
		size_t quantityOfDigitsDiff;

		size_t aDigitsBeforeDot = a.digits_before_dot();
		size_t bDigitsBeforeDot = b.digits_before_dot();
		// уравниваем количество разрядов обоих чисел до плавающей точки:
		if (aDigitsBeforeDot < bDigitsBeforeDot) // #op-1
		{
			quantityOfDigitsDiff = bDigitsBeforeDot - aDigitsBeforeDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				a.push_front_elem('0');
			}
		}
		else if (bDigitsBeforeDot < aDigitsBeforeDot) // #op-2
		{
			quantityOfDigitsDiff = aDigitsBeforeDot - bDigitsBeforeDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				b.push_front_elem('0');
			}
			//std::cout << "string bStr after pushing front zeros: " << bStr << "\n";
		}

		// уравниваем количество разрядов обоих чисел после плавающей точки:
		size_t aDigitsAfterDot = a.digits_after_dot();
		size_t bDigitsAfterDot = b.digits_after_dot();
		if (aDigitsAfterDot < bDigitsAfterDot) // #op-3
		{
			quantityOfDigitsDiff = bDigitsAfterDot - aDigitsAfterDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				a.push_back_elem('0');
			}
			//std::cout << "string aStr after pushing back zeros: " << aStr << "\n";
		}
		else if (bDigitsAfterDot < aDigitsAfterDot) // #op-4
		{
			quantityOfDigitsDiff = aDigitsAfterDot - bDigitsAfterDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				b.push_back_elem('0');
			}
			//std::cout << "string bStr after pushing back zeros: " << bStr << "\n";
		}

	/*
		// #op-(bf) 50
		std::cout
		<< "Data members after #op-(bf) finished align numbers:"
		<< "\na (without sign): " << a.get_number()
		<< "\nb (without sign): " << b.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 50.\n\n"
		;
	*/	
		// запомним позицию плавающей точки:
		size_t aDotPos = a.dot_position();
		size_t bDotPos = b.dot_position();

		// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
		a.erase_elem(aDotPos);
		b.erase_elem(bDotPos);
	/*
		// #op-(bf) 51
		std::cout
			<< "Data members after #op-(bf) finished erase dots from numbers:"
			<< "\na (without sign): " << a.get_number()
			<< "\nb (without sign): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 51.\n\n"
			;
	*/
		// считать будем с младших разрядов, поэтому "перевернём" оба числа:
		a.reverse_number();
		b.reverse_number();

	/*
		// #op-(bf) 51a
		std::cout
			<< "Data members after #op-(bf) finished reverse numbers:"
			<< "\na (without sign): " << a.get_number()
			<< "\nb (without sign): " << b.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 51a.\n\n"
			;
	*/
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

		size_t limit = aSize > bSize ? aSize - 1 : bSize - 1;
		for (size_t i = 0; i < limit; ++i)
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
	/*
			// #op-(bf) 52
			std::cout
				<< "Data on " << i + 1 << " step:"
				<< "\nminuendDigit: " << minuendDigit
				<< "\nsubtrahendDigit: " << subtrahendDigit
				<< "\nsubtotal: " << subtotal
				<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 52.\n\n"
				;
	*/
			diff.push_back_elem(digit_to_char(subtotal));
			prevBorrowed = borrowed;

	/*
			// #op-(bf) 53
			std::cout
				<< "Diff on " << i + 1 << " step: " << diff.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 53.\n\n"
				;
	*/
		}

	/*
		_	49310,120
			07025,891
		-------------
	*/
	/*
		===================== 1 виток: =====================
		prevBorrowed = 0
		minuendDigit = a.elem_value_as_digit(i) = 0
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 1 + 0 = 1
		subtrahendDigit = 1
		is else -> (minuendDigit < subtrahendDigit) -> true, because (0 < 1) -> borrowed = 1
		borrowed = 1
		minuendDigit = minuendDigit + borrowed * 10 = 0 + 1*10 = 0 + 10 = 10
		minuendDigit = 10
		subtotal = minuendDigit - subtrahendDigit = 10 - 1 = 9
		subtotal = 9, значит:
		_	49310,120
			07025,891
		-------------
					9
		prevBorrowed = borrowed;
		prevBorrowed = 1
	*/
	/*
		===================== 2 виток: =====================
		prevBorrowed = 1
		minuendDigit = a.elem_value_as_digit(i) = 2
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 9 + 1 = 10
		subtrahendDigit = 10
		is else -> (minuendDigit < subtrahendDigit) -> true, because (2 < 10) -> borrowed = 1
		borrowed = 1
		minuendDigit = minuendDigit + borrowed * 10 = 2 + 1*10 = 2 + 10 = 12
		minuendDigit = 12
		subtotal = minuendDigit - subtrahendDigit = 12 - 10 = 2
		subtotal = 2, значит:
		_	49310,120
			07025,891
		-------------
				   29
		prevBorrowed = borrowed;
		prevBorrowed = 1
	*/
	/*
		===================== 3 виток: =====================
		prevBorrowed = 1
		minuendDigit = a.elem_value_as_digit(i) = 1
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 8 + 1 = 9
		subtrahendDigit = 9
		is else -> (minuendDigit < subtrahendDigit) -> true, because (1 < 9) -> borrowed = 1
		borrowed = 1
		minuendDigit = minuendDigit + borrowed * 10 = 1 + 1*10 = 1 + 10 = 11
		minuendDigit = 11
		subtotal = minuendDigit - subtrahendDigit = 11 - 9 = 2
		subtotal = 2, значит:
		_	49310,120
			07025,891
		-------------
				  229
		prevBorrowed = borrowed;
		prevBorrowed = 1
	*/
	/*
		===================== 4 виток: =====================
		prevBorrowed = 1
		minuendDigit = a.elem_value_as_digit(i) = 0
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 5 + 1 = 6
		subtrahendDigit = 6
		is else -> (minuendDigit < subtrahendDigit) -> true, because (0 < 6) -> borrowed = 1
		borrowed = 1
		minuendDigit = minuendDigit + borrowed * 10 = 0 + 1*10 = 0 + 10 = 10
		minuendDigit = 10
		subtotal = minuendDigit - subtrahendDigit = 10 - 6 = 4
		subtotal = 2, значит:
		_	49310,120
			07025,891
		-------------
				4,229
		prevBorrowed = borrowed;
		prevBorrowed = 1
	*/
	/*
		===================== 5 виток: =====================
		prevBorrowed = 1
		minuendDigit = a.elem_value_as_digit(i) = 1
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 2 + 1 = 3
		subtrahendDigit = 3
		is else -> (minuendDigit < subtrahendDigit) -> true, because (1 < 3) -> borrowed = 1
		borrowed = 1
		minuendDigit = minuendDigit + borrowed * 10 = 1 + 1*10 = 1 + 10 = 11
		minuendDigit = 11
		subtotal = minuendDigit - subtrahendDigit = 11 - 3 = 8
		subtotal = 8, значит:
		_	49310,120
			07025,891
		-------------
			   84,229
		prevBorrowed = borrowed;
		prevBorrowed = 1
	*/
	/*
		===================== 6 виток: =====================
		prevBorrowed = 1
		minuendDigit = a.elem_value_as_digit(i) = 3
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 0 + 1 = 1
		subtrahendDigit = 3
		is else -> (minuendDigit < subtrahendDigit) -> false, because (3 > 1) -> borrowed = 0
		borrowed = 0
		minuendDigit = minuendDigit + borrowed * 10 = 3 + 0*10 = 3 + 0 = 3
		minuendDigit = 3
		subtotal = minuendDigit - subtrahendDigit = 3 - 1 = 2
		subtotal = 2, значит:
		_	49310,120
			07025,891
		-------------
			  284,229
		prevBorrowed = borrowed;
		prevBorrowed = 0
	*/
	/*
		===================== 7 виток: =====================
		prevBorrowed = 0
		minuendDigit = a.elem_value_as_digit(i) = 9
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 7 + 0 = 7
		subtrahendDigit = 7
		is else -> (minuendDigit < subtrahendDigit) -> false, because (9 > 7) -> borrowed = 0
		borrowed = 0
		minuendDigit = minuendDigit + borrowed * 10 = 9 + 0*10 = 9 + 0 = 9
		minuendDigit = 9
		subtotal = minuendDigit - subtrahendDigit = 9 - 7 = 2
		subtotal = 2, значит:
		_	49310,120
			07025,891
		-------------
			 2284,229
		prevBorrowed = borrowed;
		prevBorrowed = 0
	*/
	/*
		===================== 8 виток: =====================
		prevBorrowed = 0
		minuendDigit = a.elem_value_as_digit(i) = 4
		subtrahendDigit = b.elem_value_as_digit(i) + prevBorrowed = 0 + 0 = 0
		subtrahendDigit = 0
		is else -> (minuendDigit < subtrahendDigit) -> false, because (4 > 0) -> borrowed = 0
		borrowed = 0
		minuendDigit = minuendDigit + borrowed * 10 = 4 + 0*10 = 4 + 0 = 4
		minuendDigit = 4
		subtotal = minuendDigit - subtrahendDigit = 4 - 0 = 4
		subtotal = 4, значит:
		_	49310,120
			07025,891
		-------------
			42284,229
		prevBorrowed = borrowed;
		prevBorrowed = 0
	*/

	/*
		// #op-(bf) 54
		std::cout
			<< "Diff before reversing: " << diff.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 54.\n\n"
			;
	*/
		diff.reverse_number();
	/*
		// #op-(bf) 55
		std::cout
			<< "Diff after reversing: " << diff.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 55.\n\n"
			;
	*/
		diff.insert_elem('.', aDotPos);

	/*
		// #op-(bf) 56
		std::cout
			<< "Diff after dot inserting: " << diff.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 56.\n\n"
			;
	*/
		diff.set_number(diff.get_number());
	/*
		// #op-(bf) 57
		std::cout
			<< "\nDiff after all in decimal notation: " << diff.get_sign() << diff.get_number()
			<< "\nDiff after all in scientific notation: " << diff
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 57.\n\n"
			;
	*/
		diff.set_sign(a.get_sign());
	}
	else
	{
/**/
		// #op-(bf) 70
		std::cout
			<< "Signs of the minuend a and subtrahend b are different: "
			<< "\n<< a.get_sign(): " << a.get_sign()
			<< "\n<< b.get_sign(): " << b.get_sign()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 70.\n\n"
			;
		
		if (a.abs_value() != b.abs_value())
		{
			diff = a.abs_value() + b.abs_value();
			/*
			// #op-(bf) 71
			std::cout
			<< "a.abs_value() != b.abs_value()"
			<< "\ndiff.get_number(): " << diff.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 71.\n\n"
			;
			*/
			diff.set_number(diff.get_number());
			if (a.get_sign() == '-')
			{
				diff.set_sign('-');
			}
			else if (b.get_sign() == '-')
			{
				diff.set_sign('+');
			}
		}
		else 
		{
			diff.reset();
			diff.set_number(diff.get_number());
			diff.set_sign('+');
			/**/
			// #op-(bf) 72
			std::cout
				<< "a.abs_value() == b.abs_value()"
				<< "\nDiff equals to zero:"
				<< "\ndiff.get_number(): " << diff.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op-(bf) 72.\n\n"
				;
		}
	}

	return diff;
} // endof // #op-(bf)

BigFloat BigFloat::operator*(const BigFloat& multiplier) const // #op*(bf)
{
	BigFloat product;
/*
	// #op*(bf) 1
		std::cout
		<< "product in beginning: " << product.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 1.\n\n"
		;
*/
	product.clear_number();
/*
	// #op*(bf) 2
		std::cout
		<< "product after cleaning: " << product.clear_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 2.\n\n"
		;
*/
	BigFloat a(*this);
	BigFloat b(multiplier);

/*
	// #op*(bf) 3
	std::cout
		<< "Data of temporary objects a and b in beginning: "
		<< "\na.get_sign() and a.get_number(): " << a.get_sign() << a.get_number()
		<< "\na itself: " << a
		<< "\nb.get_sign() and b.get_number(): " << b.get_sign() << b.get_number()
		<< "\nb itself: " << b
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 3.\n\n"
		;
*/

	// запомним размер сдвига плавающей точки для будущего результата:
	size_t shift = a.digits_after_dot() + b.digits_after_dot();

	// запомним позицию плавающей точки объектов a и b:
	size_t aDotPos = a.dot_position();
	size_t bDotPos = b.dot_position();

/*
	// #op*(bf) 10
	std::cout
		<< "The dot position: "
		<< "\naDotPos: " << aDotPos
		<< "\nbDotPos: " << bDotPos
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 10.\n\n"
		;
*/

	// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
	a.erase_elem(aDotPos);
	b.erase_elem(bDotPos);
/*
	// #op*(bf) 11
	std::cout
		<< "The numbers after erasing dot: "
		<< "\na.get_number(): " << a.get_number()
		<< "\nb.get_number(): " << b.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 11.\n\n"
		;
*/

	// запомним размер обоих чисел (уже без плавающей точки):
	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();
/*
	// #op*(bf) 4
	std::cout
		<< "Size of temporary objects a and b in beginning: "
		<< "\naSize: " << aSize
		<< "\nbSize: " << bSize
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 4.\n\n"
		;
*/

	// будем умножать, начиная с млаших разрядов, для этого перевернём числа:
	a.reverse_number();
	b.reverse_number();
/*
	// #op*(bf) 12
	std::cout
		<< "The numbers after reversing: "
		<< "\na.get_number(): " << a.get_number()
		<< "\nb.get_number(): " << b.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 12.\n\n"
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
	// #op*(bf) 13
	std::cout
		<< "The number named subtotalProd of type BigInt has been created."
		<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 13.\n\n"
		;
*/

	// сумму промежуточных результатов умножения
	// будем складывать в переменную sumOfSubtotals:
	BigInt sumOfSubtotals;
	sumOfSubtotals.clear_number();
/*
	// #op*(bf) 14
	std::cout
		<< "The number named sumOfSubtotals of type BigInt has been created."
		<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 14.\n\n"
		;
*/
	for (size_t i = 0; i < bSize; ++i)
	{
/*
		// #op*(bf) 15
		std::cout
			<< "Outer for loop: iteration " << i + 1
			<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 15.\n\n"
			;
*/
		for (size_t j = 0; j < aSize; ++j)
		{
/*
			// #op*(bf) 16
			std::cout
				<< "Inner for loop: iteration " << j + 1
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 16.\n\n"
				;
*/
/*
			// #op*(bf) 17
			std::cout
				<< "digitsProd before assignment: " << digitsProd
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 17.\n\n"
				;
*/
/*
			// #op*(bf) 18
			std::cout
				<< "b.get_number(): " << b.get_number()
				<< "\nb.elem_value_as_digit(i): " << b.elem_value_as_digit(i)
				<< "\nindex i: " << i
				<< "\nbSize: " << bSize
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 18.\n\n"
				;
*/
/*
			// #op*(bf) 19
			std::cout
				<< "a.get_number(): " << a.get_number()
				<< "\na.elem_value_as_digit(j): " << a.elem_value_as_digit(j)
				<< "\nindex j: " << j
				<< "\naSize: " << aSize
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 19.\n\n"
				;
*/
/**/
			// #op*(bf) 20
			std::cout
				<< "extra: " << extra
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 20.\n\n"
				;

			digitsProd = b.elem_value_as_digit(i) * a.elem_value_as_digit(j) + extra;
/**/
			// #op*(bf) 21
			std::cout
				<< "digitsProd after assignment: " << digitsProd
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 21.\n\n"
				;

			subtotalProd.push_back_elem(digit_to_char(digitsProd % BigNumber::BASE));
/**/
			// #op*(bf) 22
			std::cout
				<< "subtotalProd after calling push_back_elem: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 27.\n\n"
				;

			extra = digitsProd / BigNumber::BASE;
		} // endof inner for

		if (i)
		{
			subtotalProd.push_front_additional_zeros(i);
/**/
			// #op*(bf) 28
			std::cout
				<< "subtotalProd after pushing back additional zeros: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 28.\n\n"
				;

		}

		if (extra)
		{
			subtotalProd.push_back_elem(digit_to_char(extra));
/**/
			// #op*(bf) 29
			std::cout
				<< "subtotalProd after pushing back remaining extra: "
				<< "\nsubtotalProd.get_number(): " << subtotalProd.get_number()
				<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 29.\n\n"
				;

		}

		sumOfSubtotals.reverse_number();
		subtotalProd.reverse_number();

		sumOfSubtotals = sumOfSubtotals + subtotalProd;

		sumOfSubtotals.reverse_number();

		subtotalProd.clear_number();
		extra = 0;
/**/
		// #op*(bf) 30
		std::cout
			<< "sumOfSubtotals at " << i + 1 << " iteration: "
			<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
			<< " ======================================"
			<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 30.\n\n"
			;

	} // endof outer for

	sumOfSubtotals.reverse_number();

/**/
	  // #op*(bf) 31
	std::cout
		<< "sumOfSubtotals at the end: "
		<< "\nsumOfSubtotals.get_number(): " << sumOfSubtotals.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 31.\n\n"
		;

	product.set_number(sumOfSubtotals);

/**/
	// #op*(bf) 32
	std::cout
		<< "Product after product.set_number(sumOfSubtotals.get_number()): "
		<< "\nproduct.get_number(): " << product.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 32.\n\n"
		;

	product.move_floating_point(LEFT, shift);

/**/
	// #op*(bf) 33
	std::cout
		<< "Product after inserting floating point: "
		<< "\nproduct.get_number(): " << product.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 33.\n\n"
		;

	product.pop_back_trailing_zeros();
/**/
	// #op*(bf) 34
	std::cout
		<< "Product after erasing trailing zeros: "
		<< "\nproduct.get_number(): " << product.get_number()
		<< " ======================================"
		<< "\nAssertion occured in BigFloat.cpp, #op*(bf) 34.\n\n"
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
} // endof // #op*(bf)

BigFloat BigFloat::operator/(const BigFloat& divider) const // #op/(bf)
{
	BigFloat quotient;
	quotient.clear_number();

	BigFloat dividend(*this);
	BigFloat divisor(divider);

	dm.divisorDigitsAfterDot = divisor.digits_after_dot();
/*
	// #op/(bf) 1
	std::cout
		<< "dm.dividendDigitsAfterDot is " << dm.divisorDigitsAfterDot
		<< "\nAssertion occured in BigFloat.cpp, #op/(bf) 1.\n\n"
		;
*/
	prepare_divident_and_divisor(dividend, divisor);

	if (dm.dividendInt < dm.divisorInt)
	{
		divide_abs_less_by_greater();
/*
		// #op/(bf) 24a
		std::cout
			<< "finalize_division(quotientInt, quotientDotPos) will be called."
			<< "\nargs passed to the function are:"
			<< "\nquotientInt: " << dm.quotientInt.get_number()
			<< "\nquotientDotPos: " << dm.quotientDotPos
			<< "\nAssertion occured in BigFloat.cpp, #op/(bf) 24a.\n\n"
			;
*/
		quotient = finalize_division();
	}
	else if (dm.dividendInt > dm.divisorInt)
	{
		divide_abs_greater_by_less();
/*
		// #op/(bf) 24b
		std::cout
			<< "finalize_division(quotientInt, quotientDotPos) will be called."
			<< "\nargs passed to the function are:"
			<< "\nquotientInt: " << dm.quotientInt.get_number()
			<< "\nquotientDotPos: " << dm.quotientDotPos
			<< "\nAssertion occured in BigFloat.cpp, #op/(bf) 24b.\n\n"
			;
*/
		quotient = finalize_division();
	}
	else
	{
		quotient.push_back_elem("1.0");
	}

	quotient.set_number(quotient.get_number());
	define_quotient_sign(quotient, dividend, divisor);
/**/
	// #op/(bf) 33
		std::cout
			<< "\nquotient after all: " << quotient.get_number()
			<< "\nAssertion occured in BigFloat.cpp, #op/(bf) 33.\n\n"
			;

	return quotient;

} // endof #op/(bf)



// arithmetic operators (each operand is different type) =======================
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
/*
	std::cout
		<< "The sign of the number after std::cin finished his work: "
		<< bf.get_sign()
		<< "\nand the number itself: "
		<< bf.get_number()
		<< "\n\n";
*/
	
	char sign = num[0] == '-' ? '-' : '+'; // костыль
	bf.set_sign(sign); // костыль

	return is;
} // endof // #op>>(bf)

std::ostream& operator<<(std::ostream& os, const BigFloat& bf) // #op<<(bf)
{
	BigFloat temp = bf;

	if (temp.is_decimal())
	{
/*
		// #op<<(bf) 1
		std::cout
			<< "is_correct(DECIMAL) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<<(bf) 1.\n\n"
			;
*/
		temp.convert_to(BigFloat::SCIENTIFIC);
/*
		// #op<<(bf) 2
		std::cout
			<< "convert_to(SCIENTIFIC) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<<(bf) 2.\n\n"
			;
*/
	}
	else if (temp.is_scientific())
	{
/*
		// #op<<(bf) 3
		std::cout
			<< "is_correct(SCIENTIFIC) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<<(bf) 3.\n\n"
			;
*/
		// do nothing
	}
	else if (temp.is_zero())
	{
		temp.reset();
/*
		// #op<<(bf) 3a
		std::cout
		<< "reset() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 3a.\n\n"
		;
*/
		temp.push_back_elem(" E+0");
/*
		// #op<<(bf) 3b
		std::cout
		<< "push_back_elem(e_tail()) has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 3b.\n\n"
		;
*/
	}
	else
	{
		temp.reset();
/*
		// #op<<(bf) 4
		std::cout
			<< "reset() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<<(bf) 4.\n\n"
			;
*/
		temp.push_back_elem(" E+0");
/*
		// #op<<(bf) 5
		std::cout
		<< "push_back_elem(e_tail()) has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 5.\n\n"
		;
*/
	}

	os << temp.get_sign() << temp.get_number();

/*
	// #op<< 5
	std::cout
		<< "\n\nget_sign() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<< 6.\n\n"
		;
*/
/*
	// #op<< 6
	std::cout
		<< "get_number() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<< 7.\n\n"
		;
*/
	return os;
} // endof // #op<<(bf)
