#include "stdafx.h"
#include "BigFloat.h"
#include "bn_functions.h"
// #include <cmath> // ����� ������������ std::pow()



// ctors =======================================================================
BigFloat::BigFloat()
	: BigNumber()
{
	//std::cout << "\nDefault constructor has been used.\n";
	notation_ = DEFAULT;
	set_number("0.0  E+0");
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
	if (is_correct(DEFAULT))
	{
/*
		// #ctor(str) 1
		std::cout
			<< "is_correct(DEFAULT) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #ctor(str) 1.\n\n"
			;
*/
		// do nothing
/*
		std::cout
			<< "\nConstructor will try create object from string"
			<< "\nthat represent number equals to zero.\n";
*/
	}
	else if (is_correct(DECIMAL))
	{
/*
		// #ctor(str) 2
		std::cout
			<< "is_correct(DECIMAL) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #ctor(str) 2.\n\n"
			;
*/
		// do nothing
/*
		std::cout
			<< "\nConstructor will try create object from string"
			<< "\nthat represent number in decimal notation.\n";
*/
	}
	else if (is_correct(SCIENTIFIC))
	{
/*
		// #ctor(str) 3
		std::cout
			<< "is_correct(SCIENTIFIC) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #ctor(str) 3.\n\n"
			;
*/
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
/*
		// #ctor(str) 4
		std::cout
			<< "reset() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, ctor(str) 4.\n\n"
			;
*/
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
/*
	// #cpy ctor() 1
	std::cout
		<< "set_number(str) has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #cpy ctor() 1.\n\n"
		;
*/
}



// checkers ====================================================================
bool BigFloat::has_extra_leading_zeros() const
{
	bool result = false;
	size_t leadingZerosBeforeAnotherDigit = 0;
	if (digits_before_dot() > 1)
	{
		if (first_digit_value() == 0)
		{
			if (is_digit(get_number()[1]))
				result = true;
		}
	}
	
	return result;
}

bool BigFloat::has_leading_zeros() const
{
/*
		std::cout
			<< "The object has leading zeros.\n"
			<< "Assertion occured in BigFloat.cpp, has_leading_zeros().\n\n"
			;
*/
	return first_digit_value() == 0 ? true : false;
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
		// ���������, ��� ������ �������� ������:
		if (spacePos == numSize)
		{
			result = false;
/*
			std::cout <<
				"\nThe scientific number notation is incorrect, because"
				"\nthe number have to contain 1 space at least.\n";
*/
		}
		// ���������, ��� ������ �������� ����� 'e' ��� 'E':
		else if (ePos == numSize)
		{
			result = false;
/*
			std::cout <<
				"\nThe scientific number notation is incorrect, because"
				"\nthe number have to contain 1 letter 'e' or 'E'.\n";
*/
		}
		// ���������, ��� ������ �������� ����� � ����� ������ ����:
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
			// ���������, ��� �� ������� ��� �������� ������ - ����� ��� �����:
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
			// ���������, ��� ����� 'e' ��� 'E' ������� ����� �� ��������:
			if (ePos != position_after(spacePos))
			{
				result = false;
/*
				std::cout <<
					"\nThe scientific number notation is incorrect,"
					"\nbecause letter was not found after space.\n";
*/
			}
			// ��������� ��� �� ������ 'e' ��� 'E' ������� ���� ���� ��� �����:
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
				// ���������, ��� ����� ����� ������� ������ �����:
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
		// #iscor(dec) 2
		std::cout
			<< "\nThe decimal number notation assertion.\n"
			<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(dec) 2.\n\n"
			;
*/
		// ���������, ��� ������ �������� ����� � ����� ������ ����:
		if (contains_one_dot_only(get_number()))
		{
			// ���������, ��� ��� �������� ������ - ����� ��� �����:
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
/*
		// #iscor(dft) 3
		std::cout
			<< "\nThe default number notation assertion.\n"
			<< "Assertion occured in BigFloat.cpp, is_correct(), #iscor(dft) 3.\n\n"
			;
*/
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
			insert_elem('.', position_after(dotPos) + shiftSize);
		}
		else if (digits_after_dot() == shiftSize)
		{
/*
			std::cout
				<< "\ndigits_after_dot() == shiftSize\n"
				<< "\ndigits_after_dot(): " << digits_after_dot()
				<< "shiftSize: " << shiftSize << "\n";
*/
			insert_elem(".0", position_after(last_digit_position()));
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
				insert_elem('0', position_after(last_digit_position()));
			}
			insert_elem(".0", position_after(last_digit_position()));
		}

		erase_elem(dotPos);

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
		erase_elem(dotPos);
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
			insert_elem('.', dotPos - shiftSize);
		}
		else if (digitsBefore == shiftSize)
		{
			insert_elem("0.", 0);
		}
		else if (digitsBefore < shiftSize)
		{			
			push_front_additional_zeros(shiftSize - digitsBefore);

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
	size_t numSize = get_number().size();	
/*
	// #conv(arg) 1
	std::cout
		<< "size_t numSize = get_number().size(): "
		<< numSize
		<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 1\n\n"
		;
*/	
	size_t dotPos = dot_position();	
/*
	// #conv(arg) 2
	std::cout
		<< "dot_position() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #conv(arg) 2\n\n"
		;
*/
	size_t ePos = e_position();
/*
	// #conv(arg) 3
	std::cout
		<< "e_position() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #conv(arg) 3\n\n"
		;
*/
	size_t eValAsNum = e_value_as_number();
/*
	// #conv(arg) 4
	std::cout
		<< "e_value_as_number() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #conv(arg) 4\n\n"
		;
*/

	switch (notation)
	{
	case SCIENTIFIC:

		if (dotPos != 1) 
		{
			size_t shift = position_before(dotPos);
/*
			// #conv(arg) 5
			std::cout
				<< "size_t shift = position_before(dotPos): "
				<< shift
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 5\n\n"
				;
*/
/*
			// #conv(arg) 6
			std::cout
				<< "number before move_floating_point(LEFT, shift): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 6\n\n"
				;
*/
			move_floating_point(LEFT, shift);
/*
			// #conv(arg) 7
			std::cout
				<< "number after move_floating_point(LEFT, shift): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 7\n\n"
				;
*/
/*
			// #conv(arg) 8
			std::cout
				<< "number before push_back_elem(\" E+\" + number_to_string(shift)): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 8\n\n"
				;
*/
			push_back_elem(" E+" + number_to_string(shift));
/*
			// #conv(arg) 9
			std::cout
				<< "number after set_number(get_number() + \" E + \" + number_to_string(shift)): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 9\n\n"
				;
*/
		}
		else
		{	
			size_t leadingZeros = leading_zeros();

			if (leadingZeros) // TODO: ��������� ��� ������ ��������� ���������� ����
			{
/*
				// #conv(arg) 10
				std::cout
					<< "Function leading_zeros() has been called.\n"
					<< "Assertion occured in BigFloat.cpp, #conv(arg) 10\n\n"
					;
*/
/*
				// #conv(arg) 11
				std::cout
					<< "number before move_floating_point(RIGHT, leading_zeros()): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 11\n\n"
					;
*/
				move_floating_point(RIGHT, leadingZeros);
/*
				// #conv(arg) 12
				std::cout
					<< "number after move_floating_point(RIGHT, leading_zeros()): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 12\n\n"
					;
*/
				pop_front_leading_zeros();
/*
				// #conv(arg) 12a
				std::cout
					<< "number after BigFloat::pop_front_leading_zeros(): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 12a\n\n"
					;
*/
/*
				// #conv(arg) 13
				std::cout
					<< "number before push_back_elem(\" E-\" + number_to_string(leadingZeros)): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 13\n\n"
					;
*/
				push_back_elem(" E-" + number_to_string(leadingZeros));
/*
				// #conv(arg) 13a
				std::cout
					<< "number after set_number(get_number() + \" E-\" + number_to_string(leading_zeros())): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 13a\n\n"
					;
*/
/*
				// #conv(arg) 14
				std::cout
					<< "number after set_number(get_number() + \" E-\" + number_to_string(leading_zeros())): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 14\n\n"
					;
*/
			}
			else
			{
/*
				// #conv(arg) 17
				std::cout
					<< "number before push_back_elem(\" E + 0\"): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 17\n\n"
					;
*/
				push_back_elem(" E+0");
/*
				// #conv(arg) 18
				std::cout
					<< "number after push_back_elem(\" E + 0\"): "
					<< get_number()
					<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 18\n\n"
					;
*/
			}
		}

/*
		// #conv(arg) 19
		std::cout
			<< "number before pop_back_extra_zeros(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 19\n\n"
			;
*/
		// TODO: ��������� ��� ������ ��������� ���������� ����:
		pop_back_extra_zeros();

/*
		// #conv(arg) 20
		std::cout
			<< "number after pop_back_extra_zeros(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 20\n\n"
			;
*/
		notation_ = SCIENTIFIC;
		break;

	case DECIMAL:
	{
		if (e_sign() == '+')
		{
/*
		// #conv(arg) 21
		std::cout
			<< "e_sign() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #conv(arg) 21\n\n"
			;
*/
/*
			// #conv(arg) 22
			std::cout
				<< "number before move_floating_point(RIGHT, eValAsNum): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 22\n\n"
				;
*/
			move_floating_point(RIGHT, eValAsNum);
/*
			// #conv(arg) 23
			std::cout
				<< "number after move_floating_point(RIGHT, eValAsNum): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 23\n\n"
				;
*/
/*
			// #conv(arg) 24
			std::cout
				<< "number before erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 24\n\n"
				;
*/
			erase_elem(position_before(ePos), numSize - 1);
/*
			// #conv(arg) 25
			std::cout
				<< "number after erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 25\n\n"
				;
*/
		}
		else if (e_sign() == '-')
		{
/*
			// #conv(arg) 26
			std::cout
				<< "e_sign() has been called.\n"
				<< "Assertion occured in BigFloat.cpp, #conv(arg) 26\n\n"
				;
*/
/*
			// #conv(arg) 27
			std::cout
				<< "number before move_floating_point(LEFT, eValAsNum): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 27\n\n"
				;
*/
			move_floating_point(LEFT, eValAsNum);
/*
			// #conv(arg) 28
			std::cout
				<< "number after move_floating_point(LEFT, eValAsNum): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 28\n\n"
				;
*/
/*
			// #conv(arg) 29
			std::cout
				<< "number before erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 29\n\n"
				;
*/
			erase_elem(position_before(ePos), numSize - 1);
/*
			// #conv(arg) 30
			std::cout
				<< "position_before(ePos): "
				<< position_before(ePos)
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 30\n\n"
				;
*/
/*
			// #conv(arg) 31
			std::cout
				<< "number after erase_elem(position_before(ePos), numSize - 1): "
				<< get_number()
				<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 31\n\n"
*/				;
		}
		else
		{
			std::cout
				<< "\nError: incorrect character instead the sign."
				<< "\nCurrent content of number() is: " << get_number()
				<< "\nAnd character is: " << e_sign() << "\n";
		}
		notation_ = DECIMAL;
		break;
	}

	case DEFAULT:
/*
		// #conv(arg) 32
		std::cout
			<< "number before reset(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 32\n\n"
			;
*/
		reset();
/*
		// #conv(arg) 33
		std::cout
			<< "number after reset(): "
			<< get_number()
			<< ".\nAssertion occured in BigFloat.cpp, #conv(arg) 33\n\n"
			;
*/
	default:
		std::cout << "\nError: incorrect function argument.\n";
		break;
	}

} // endof convert_to()

void BigFloat::pop_front_leading_zeros()
{
	size_t limit = last_digit_position();
/*
		// #pflz() 1
		std::cout
			<< "BigFloat::last_digit_position() has been called by BigFloat::pop_front_leading_zeros().\n"
			<< "Last digit position is: "
			<< limit
			<< "\nAssertion occured in BigFloat.cpp, #pflz() 1.\n\n"
			;
*/
	for (size_t i = 0; i < limit; ++i)
	{
		if (get_number()[0] == '0')
		{
/*
			// #pflz() 2
			std::cout
				<< "Current content of number is: " << get_number()
				<< "\nCurrent index of digit is: " << i << " and this element will be erased."
				<< "\nCurrent digit of number is: " << get_number()[i]
				<< "\nAssertion occured in BigFloat.cpp, #pflz() 2.\n\n"
				;
*/
			erase_elem(0);
/*
			// #pflz() 3
			std::cout
				<< "BigNumber::erase_elem() has been called by BigFloat::pop_front_leading_zeros()."
				<< "\nThe element with index: " << i << " has been erased."
				<< "\nCurrent content of number is: " << get_number()
				<< "\nAssertion occured in BigFloat.cpp, #pflz() 3.\n\n"
				;
*/
		}
		else if (get_number()[0] == '.')
		{
/*
			// #pflz() 4
			std::cout
				<< "BigNumber::pop_front_elem() has been skipped by BigFloat::pop_front_leading_zeros()."
				<< "\nCurrent content of number is: " << get_number()
				<< "\nCurrent index of digit is: " << i
				<< "\nCurrent digit of number is: " << get_number()[i]
				<< "\nAssertion occured in BigFloat.cpp, #pflz() 4.\n\n"
				;
*/
			continue;
		}
		else
		{
/*
			// #pflz() 5
			std::cout
				<< "BigNumber::pop_front_elem() has been skipped by BigFloat::pop_front_leading_zeros()."
				<< "\nCurrent content of number is: " << get_number()
				<< "\nCurrent index of digit is: " << i
				<< "\nCurrent digit of number is: " << get_number()[i]
				<< "\nAssertion occured in BigFloat.cpp, #pflz() 5.\n\n"
				;
*/
			break;
		}
	}
}

void BigFloat::push_back_additional_zeros(const size_t quantity)
{
	std::string additionalZeros(quantity, '0');
	insert_to(get_number(), additionalZeros, position_after(last_digit_position()));
}

void BigFloat::pop_back_extra_zeros()
{
	size_t lastDigitPos = last_digit_position();

	while
		(
			last_digit_value() == 0 &&
			lastDigitPos > position_after(dot_position())
		)
	{
		erase_elem(lastDigitPos, lastDigitPos);
	}
}



// getters =====================================================================
size_t BigFloat::leading_zeros() const
{
	size_t quantity_of_leading_zeros = 0;
	if (has_leading_zeros())
	{
		for (size_t i = 0; i < last_digit_position(); ++i)
		{
			if (get_number()[i] == '0')
			{
				++quantity_of_leading_zeros;
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
	return quantity_of_leading_zeros;
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
		if (get_number()[i] == 'e' || get_number()[i] == 'E')
		{
			ePos = i;
			break;
		}
	}

/*
	std::cout
		<< "The E position is: "
		<< ePos
		<< "\nAssertion occured in BigFloat.cpp, e_position().\n\n"
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
	size_t posAfterESignPos = position_after(e_sign_position());
	if (posAfterESignPos < get_number().size())
	{
		for (size_t i = position_after(e_sign_position()); i < get_number().size(); ++i)
		{
			eVal = eVal + get_number()[i];
		}
	}

/*
	std::cout
		<< "The E value as string is: "
		<< eVal
		<< "\nAssertion occured in BigFloat.cpp, e_value_as_string().\n\n"
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
	return get_number()[last_digit_position()];
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
	std::string mantissa = get_number();

	if (is_scientific())
	{
		size_t spacePos = space_position();
		if (mantissa[spacePos] == ' ')
		{
			erase_part_of(mantissa, spacePos, spacePos);
		}
		erase_part_of(mantissa, e_position(), mantissa.size() - 1);
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

/*
	std::cout
		<< "Assertion occured in BigFloat.cpp, set_number(const BigFloat& bf).\n\n"
		;
*/
}

void BigFloat::set_number(const std::string& num)
{	
	BigNumber::set_number(num);

/*
	// #setn(str) 1
	std::cout
		<< "ctor(str) has been called."
		<< "\nAssertion occured in BigFloat.cpp, #setn(str) 1.\n\n"
		;
*/
	if (is_correct(SCIENTIFIC))
	{
/*
		// #setn(str) 2
		std::cout
			<< "is_correct(SCIENTIFIC) has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 2.\n\n"
			;
*/
		convert_to(DECIMAL);
/*
		// #setn(str) 3
		std::cout
			<< "convert_to(DECIMAL) has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 3.\n\n"
			;
*/
	}
	else if (is_correct(DECIMAL))
	{
/*
		// #setn(str) 4
		std::cout
			<< "is_correct(DECIMAL) has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 4.\n\n"
			;
*/
		// do nothing
	}
	else
	{
		reset();
/*
		// #setn(str) 5
		std::cout
			<< "reset() has been called."
			<< "\nAssertion occured in BigFloat.cpp, #setn(str) 5.\n\n"
			;
*/
	}
}

void BigFloat::reset()
{
	//clear_number();
	BigNumber::set_number("0.0  E+0");
	notation_ = DEFAULT;
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

	// TODO: ���������� ����������

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

	// TODO: ���������� ����������

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

	size_t diff; // ������� ����� ����������� ��������

				 // ���������� ���������� �������� ����� ����� �� ��������� �����:
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

	// ���������� ���������� �������� ����� ����� ����� ��������� �����:
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

	// �������� ������� ��������� �����:
	size_t dot_pos_a = char_position(aStr, '.');
	size_t dot_pos_b = char_position(bStr, '.');

	// ����� �� ����� ����� ��������� �����, ����� �� ������ ��� �����������:
	erase_part_of(aStr, dot_pos_a, dot_pos_a);
	erase_part_of(bStr, dot_pos_b, dot_pos_b);

	// ����� ����������, ������� � ������ ��������, ��� ����� ���������� �����:
	reverse(aStr);
	reverse(bStr);

	// ������� (��, ��� ������ ��� �������� � ������� "����� � ���") ����� ���������� � ���������� extra;
	size_t extra = 0;
	// ������������� ���� �������� ���� ���� ����������� ������� ����� ���������� � ���������� subtotal:
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
		if (subtotal > BigInt::MAX_DIGIT) // ���������� �������, ������� ��������� ����� � ������� 9
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

	size_t curMultDotPos = mult.dot_position();
	size_t curProdDotPos = product.digits_after_dot();
	size_t finProdDotPos = product.digits_after_dot() + mult.digits_after_dot();

	// ����� �� ����� ����� ��������� �����, ����� �� ������ ��� �����������:
	erase_part_of(product.get_number(), curProdDotPos, curProdDotPos);
	erase_part_of(mult.get_number(), curMultDotPos, curMultDotPos);

	BigInt limit(mult.get_number());
	for (BigInt i("0"); i < limit; ++i)
	{
		product = product + addition;
	}

	insert_to(product.get_number(), ".", finProdDotPos);

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

		// TODO: ���������
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
/*
		// #op<< 1
		std::cout
			<< "is_correct(DECIMAL) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<< 1.\n\n"
			;
*/
		temp.convert_to(BigFloat::SCIENTIFIC);
/*
		// #op<< 2
		std::cout
			<< "convert_to(SCIENTIFIC) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<< 2.\n\n"
			;
*/
	}
	else if (temp.is_correct(BigFloat::SCIENTIFIC))
	{
/*
		// #op<< 3
		std::cout
			<< "is_correct(SCIENTIFIC) has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<< 3.\n\n"
			;
*/
		// do nothing
	}
	else
	{
		temp.reset();
/*
		// #op<< 4
		std::cout
			<< "reset() has been called.\n"
			<< "Assertion occured in BigFloat.cpp, #op<< 4.\n\n"
			;
*/
	}

	temp.has_extra_leading_zeros();
/*
	// #op<< 5
	std::cout
		<< "has_extra_leading_zeros() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<< 5.\n\n"
		;
*/
	os << temp.get_sign() << temp.get_number();

/*
	// #op<< 6
	std::cout
		<< "\n\nget_sign() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<< 6.\n\n"
		;
*/
/*
	// #op<< 7
	std::cout
		<< "get_number() has been called.\n"
		<< "Assertion occured in BigFloat.cpp, #op<< 7.\n\n"
		;
*/
	return os;
} // endof // #op<<(bf)
