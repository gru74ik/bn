#include "stdafx.h"
#include "BigFloat.h"
#include "bn_functions.h"
// #include <cmath> // можно использовать std::pow()



// ctors =======================================================================
BigFloat::BigFloat()
	:
		BigNumber("0.0"),
		notation_(DEFAULT),
		eSign_('+'),
		eValueAsString_("0")
{
/**/
	std::cout
		<< "Default ctor BigFloat::BigFloat() has been called.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;

}

BigFloat::BigFloat(const std::string& num)
	:
		BigNumber(num)
{
	/**/
	std::cout
		<< "Ctor BigFloat::BigFloat(const std::string& num) has been called.\n"
		;

	set_number(num);
/**/
	std::cout
		<< "Ctor BigFloat::set_number(get_number()) has been called.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;

}

BigFloat::BigFloat(const BigInt& bi)
	:
		BigNumber(bi.get_sign() + bi.get_number())
{
/**/
	std::cout
		<< "Ctor BigFloat::BigFloat(const BigInt& bi) has been used.\n"
		;

	set_number(bi.get_sign() + bi.get_number());
/**/
	std::cout
		<< "Ctor BigFloat::set_number(bi.get_number()) has been used.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n"
		;

}

BigFloat::BigFloat(const BigFloat& bf)
	: 
		BigNumber(bf.get_sign() + bf.get_number()),
		notation_(bf.notation_),
		eSign_(bf.eSign_),
		eValueAsString_(bf.eValueAsString_)
{
/**/
	std::cout
		<< "Copy ctor BigFloat::BigFloat(const BigFloat& bf) has been used.\n"
		<< "\nThe sign of the number after ctor finished his work: "
		<< get_sign()
		<< "The number after ctor finished his work: "
		<< get_number() << "\n\n";
		;

}



// checkers ====================================================================
bool BigFloat::has_extra_leading_zeros() const
{	
	// for example: the number 0000.01234 has three extra leading zeros

	return
		elem_value_as_char(0) == '0' &&
		elem_value_as_char(1) == '0';
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
			/**/
			// #mfp(r) 2
			std::cout
				<< "BigFloat::move_floating_point(args) has been called."
				<< "\nThe number after new floating point was inserted: "
				<< get_number()
				<< "\nAssertion occured in BigFloat.cpp, #mfp(r) 2.\n\n"
				;
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
					<< "has_trailing_zeros() has been called."
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
					<< "beacuase the number has leading zeros: "
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

				if (has_extra_leading_zeros())
				{
					pop_front_extra_leading_zeros();
				}

/*
				// #conv(sci) 12
				std::cout
					<< "number after move_floating_point(RIGHT, dotShift): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 12\n\n"
					;
*/
				eSign_ = '-';
				eValueAsString_ = number_to_string(dotShift);
/*
				// #conv(sci) 13
				std::cout
					<< "number before push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 13\n\n"
					;
*/
				push_back_elem(e_tail());
/*
				// #conv(sci) 14
				std::cout
					<< "e_tail() has been called and it is:"
					<< e_tail()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 14\n\n"
					;
*/
/*
				// #conv(sci) 15
				std::cout
					<< "number after push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 15\n\n"
					;
*/
			}
			else
			{
				eSign_ = '+';
				eValueAsString_ = "0";
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
					<< "number after push_back_elem(e_tail()): "
					<< get_number()
					<< "\nAssertion occured in BigFloat.cpp, #conv(sci) 17\n\n"
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
	size_t to_pos_inclusive = lastDigitPos;

	erase_elem(from_pos_inclusive, to_pos_inclusive);

}



// getters =====================================================================
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
	size_t dotPos = dot_position();

	for (size_t i = last_digit_position(); i > dotPos; --i)
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

/**/
	// #setn(str) 34
	std::cout
		<< "\nData members after setter finished his work:"
		<< "\nsign_: " << get_sign()
		<< "\nnumber_: " << get_number()
		<< "\neSign_: " << eSign_
		<< "\neValueAsString_: " << eValueAsString_
		<< "\nAssertion occured in BigFloat.cpp, set_number(const std::string& num), #setn(str) 34.\n\n"
		;

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
	BigFloat a(*this);
	BigFloat b(addendum);

	std::string aStr = this->get_number();
	std::string bStr = addendum.get_number();

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
	BigFloat diff;
	diff.clear_number();
	BigFloat a(*this);
	BigFloat b(subtrahend);

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

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

	// запомним позицию плавающей точки:
	size_t aDotPos = a.dot_position();
	size_t bDotPos = b.dot_position();

	// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
	a.erase_elem(aDotPos);
	b.erase_elem(bDotPos);

	// промежуточный итог сложения двух цифр одинакового разряда будем складывать в переменную subtotal:
	size_t subtotal = 0;

	size_t limit = aSize > bSize ? aSize : bSize;
	size_t minuendDigit = 0;
	size_t subTrahendDigit = 0;

	// занимать единичку из старшего разряда будем, складывая её в переменную borrowed:
	for (size_t i = 0, borrowed = 0; i < limit; ++i)
	{
		minuendDigit = a.elem_value_as_digit(i);
		subTrahendDigit = b.elem_value_as_digit(i);
		minuendDigit -= borrowed;

		if (minuendDigit < subTrahendDigit)
		{
			borrowed = 1;
		}
		else
		{
			borrowed = 0;
		}
		subtotal = (minuendDigit + borrowed * 10) - subTrahendDigit;
		diff.push_back_elem(digit_to_char(subtotal));
	}

	diff.reverse_number();

	return diff;
} // endof // #op-(bf)

BigFloat BigFloat::operator*(const BigFloat& multiplier) const // #op*(bf)
{
	BigFloat product(*this);
	BigFloat addition(*this);
	BigFloat mult(multiplier);

	size_t curMultDotPos = mult.dot_position();
	size_t curProdDotPos = product.digits_after_dot();
	size_t finProdDotPos = product.digits_after_dot() + mult.digits_after_dot();

	// уберём из обоих чисел плавающую точку, чтобы не мешала при вычислениях:
	product.erase_elem(curProdDotPos);
	mult.erase_elem(curMultDotPos);

	BigInt limit(mult.get_number());
	for (BigInt i("0"); i < limit; ++i)
	{
		product = product + addition;
	}

	product.insert_elem('.', finProdDotPos);

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
		result.set_number("1.0");
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
/**/
		// #op<<(bf) 3a
		std::cout
		<< "reset() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 3a.\n\n"
		;

		temp.push_back_elem(" E+0");
/**/
		// #op<<(bf) 3b
		std::cout
		<< "push_back_elem(e_tail()) has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 3b.\n\n"
		;

	}
	else
	{
		temp.reset();
/**/
		// #op<<(bf) 4
		std::cout
			<< "reset() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<<(bf) 4.\n\n"
			;

		temp.push_back_elem(" E+0");
/**/
		// #op<<(bf) 5
		std::cout
		<< "push_back_elem(e_tail()) has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<<(bf) 5.\n\n"
		;

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
