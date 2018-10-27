#include "stdafx.h"
#include "BigFloat.h"
#include "bn_functions.h"

const size_t PRECISION = 30;

// ctors =======================================================================
BigFloat::BigFloat()
	:
		BigNumber("0.0"),
		notation_(DEFAULT),
		eSign_('+'),
		eValueAsString_("0")
{
}

BigFloat::BigFloat(const std::string& num)
	:
		BigNumber(num)
{
	char temporaryCrutch = get_sign();
	set_number(num);
	set_sign(temporaryCrutch);
}

BigFloat::BigFloat(const BigInt& bi)
	:
		BigNumber(bi.get_sign() + bi.get_number())
{
	char temporaryCrutch = bi.get_sign();
	std::string tempNumber(bi.get_number());
	tempNumber = tempNumber + ".0";

	set_number(tempNumber);
	set_sign(temporaryCrutch);
}

BigFloat::BigFloat(const BigFloat& bf)
	: 
		BigNumber(bf.get_sign() + bf.get_number()),
		notation_(bf.notation_),
		eSign_(bf.eSign_),
		eValueAsString_(bf.eValueAsString_)
{	
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
		if (spacePos == numSize)
		{
			result = false;
		}
		else if (ePos == numSize)
		{
			result = false;
		}
		else if (!contains_one_dot_only(get_number()))
		{
			result = false;
		}
		else
		{
			for (size_t i = 0; i < spacePos; ++i)
			{
				if (!is_digit(get_number()[i]) && !is_dot(get_number()[i]))
				{
					result = false;
					break;
				}
			}
			if (ePos != position_after(spacePos))
			{
				result = false;
			}
			else if (!is_sign(get_number()[eSignPos]))
			{
				result = false;
			}
			else
			{
				for (size_t i = position_after(eSignPos); i < numSize; ++i)
				{
					if (!is_digit(get_number()[i]))
					{
						result = false;
						break;
					}
				}
			}
		}
		break;
	}

	case DECIMAL:
		if (contains_one_dot_only(get_number()))
		{
			for (size_t i = 0; i < numSize; ++i)
			{
				if (!is_digit(get_number()[i]) && !is_dot(get_number()[i]))
				{
					result = false;
					break;
				}
			}
		}
		else
		{
			result = false;
		}
		break;

	case DEFAULT:
		if (!is_zero())
		{
			result = false;
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
	if (is_zero())
	{

		return;	
	}

	size_t dotPos = dot_position();
	size_t digitsAfterDot = digits_after_dot();
	size_t lastDigitPos = last_digit_position();

	switch (dir)
	{
	case RIGHT:
	{
		if (digitsAfterDot > shiftSize)
		{
			insert_elem('.', position_after(dotPos) + shiftSize);
		}
		else if (digitsAfterDot == shiftSize)
		{
			insert_elem(".0", position_after(lastDigitPos));
		}
		else
		{
			size_t additionalZeros = shiftSize - digitsAfterDot;
			size_t posToInsertAdditionalZeros = position_after(lastDigitPos);
			for (size_t i = 0; i < additionalZeros; ++i)
			{				
				insert_elem('0', posToInsertAdditionalZeros);
			}

			insert_elem
				(
					".0",
					position_after(last_digit_position())	 
				);	// This is so on purpose! Do not change the 2nd
					// arg of function insert_elem() in this case.
		}

		erase_elem(dotPos);
		break;
	}
	case LEFT:
	{
		size_t digitsBeforeDot = digits_before_dot();
		erase_elem(dotPos);

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
			push_front_additional_zeros(shiftSize);
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
	if (is_zero())
	{
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
			move_floating_point(LEFT, dotShift);

			if (has_trailing_zeros())
			{
				pop_back_trailing_zeros();
			}


			eSign_ = '+';
			eValueAsString_ = number_to_string(dotShift);
			push_back_elem(e_tail());	
		}
		else
		{
			if (has_leading_zeros())
			{
				dotShift = leading_zeros();
				move_floating_point(RIGHT, dotShift);

				if (has_extra_leading_zeros())
				{
					pop_front_extra_leading_zeros();
				}
				else
				{
				}

				eSign_ = '-';
				eValueAsString_ = number_to_string(dotShift);
				push_back_elem(e_tail());
			}
			else
			{
				eSign_ = '+';
				eValueAsString_ = "0";
				push_back_elem(e_tail());
			}
		}

		notation_ = SCIENTIFIC;
		break;
	}

	case DECIMAL:
	{
		size_t ePos = e_position();
		size_t eValAsNum = e_value_as_number();

		if (e_sign() == '+')
		{
			move_floating_point(RIGHT, eValAsNum);
			discard_e_tail();
		}
		else if (e_sign() == '-')
		{
			move_floating_point(LEFT, eValAsNum);
			discard_e_tail();
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
		reset();

	default:
		std::cout << "\nError: incorrect function argument.\n";
		break;
	}

} // endof convert_to()

void BigFloat::pop_front_leading_zeros()
{
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
	size_t lastDigitPos = last_digit_position();
	size_t from_pos_inclusive = position_after(lastDigitPos - trailing_zeros());

	size_t to_pos_inclusive = lastDigitPos;

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

	return trailingZeros;
}

size_t BigFloat::dot_position() const
{
	return char_position(get_number(), '.');
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

	return ePos;
}

size_t BigFloat::digits_after_e() const
{   // TODO: implement count() function?
	return get_number().size() - position_before(space_position());
}

size_t BigFloat::e_value_as_number() const
{
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

	return eSignPos;
}

char BigFloat::e_sign() const
{
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
	return position_before(space_position());
}

size_t BigFloat::last_digit_value() const
{
	return elem_value_as_digit(last_digit_position());
}

size_t BigFloat::space_position() const
{
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

	return mantissa;
}

BigFloat::Notation BigFloat::notation() const
{
	return notation_;
}



// setters =====================================================================
void BigFloat::set_number(const BigFloat& bf)
{
	BigNumber::set_number(bf.get_sign() + bf.get_number());
	notation_ = bf.notation_;
	eSign_ = bf.eSign_;
	eValueAsString_ = bf.eValueAsString_;
}

void BigFloat::set_number(const std::string& num)
{	
	size_t numSize = get_number().size();

	if (num == "0.0" || num == "0" || numSize == 0)
	{
		reset();
	}
	else if (contains_digits_only(num))
	{
		if (numSize == 1)
		{

			BigNumber::set_number(num);
			notation_ = DECIMAL;
			eSign_ = '+';				
			eValueAsString_ = "0";
			insert_elem(".0", numSize);
		}
		else
		{
			BigNumber::set_number(num);

			if (has_extra_leading_zeros())
			{
				pop_front_extra_leading_zeros();
			}

			notation_ = DECIMAL;
			eSign_ = '+';
			eValueAsString_ = number_to_string(numSize - 1);
			insert_elem('.', 1);
		}		
	}
	else
	{
		BigNumber::set_number(num);

		if (has_extra_leading_zeros())
		{
			pop_front_extra_leading_zeros();
		}

		if (has_trailing_zeros())
		{
			pop_back_trailing_zeros();
		}

		if (is_correct(SCIENTIFIC))
		{
			eSign_ = e_sign();
			eValueAsString_ = e_value_as_string();

			convert_to(DECIMAL);
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
			// do nothing
		}
		else
		{
			reset();
		}
	}

	if (has_extra_leading_zeros())
	{
		pop_front_extra_leading_zeros();
	}

	if (has_trailing_zeros())
	{
		pop_back_trailing_zeros();
	}
}

void BigFloat::reset()
{
	//clear_number();
	BigNumber::set_number("0.0");
	notation_ = DEFAULT;
	eSign_ = '+';
	eValueAsString_ = "0";
}



// division helpers ============================================================
static BigFloat::DivisionMembers dm;

char BigFloat::next_digit_of_quotient() const
{
	BigInt fitSubtrahend = dm.divisorInt;
	BigInt curSubtrahend = dm.divisorInt;
	BigInt fitMultiplier('1');
	BigInt curMultiplier('1');
	
	while (curSubtrahend <= dm.subtotal)
	{	
		fitSubtrahend = curSubtrahend;
		fitMultiplier = curMultiplier;
		++curMultiplier;
		curSubtrahend = dm.divisorInt * curMultiplier;
	}

	return fitMultiplier.elem_value_as_char(0);
}

// divides a smaller number by a larger:
void BigFloat::calc_subtotal_and_add_digits_to_quotient(bool zeroWasPushedBackInSubtotalInPrevStep) const
{
	dm.subtotal.pop_front_extra_zeros();


	while (dm.subtotal < dm.divisorInt)
	{
		dm.subtotal.push_back_elem('0');

		if (zeroWasPushedBackInSubtotalInPrevStep)
		{
			dm.quotientInt.push_back_elem('0');
		}

		zeroWasPushedBackInSubtotalInPrevStep = true;

		dm.subtotal.pop_front_extra_zeros();
	}

	dm.curIndexOfDigitOfDividend = dm.divisorInt.quantity_of_digits() + 1;
	zeroWasPushedBackInSubtotalInPrevStep = false;
} // endof calc_subtotal_and_add_digits_to_quotient(args)

// divides a larger number by a smaller:
void BigFloat::calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) const
{
	dm.subtotal = prevSubtotal;
	dm.subtotal.pop_front_extra_zeros();

	static bool is_first_time_calc_subtotal = true;
	static bool is_first_time_add_digits_to_subtotal = true;

	while
		(
			dm.subtotal < dm.divisorInt &&
			dm.curIndexOfDigitOfDividend <= dm.dividendInt.last_digit_position()
		)
	{	
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

		is_first_time_add_digits_to_subtotal = false;
	}

	// second phase (when the division ended the digits in the dividend and there was nothing to demolish,
	// it remains only to insert additional zeros at the end of dm.subtotal):
	if
		(
			!dm.subtotal.is_zero() &&
			dm.subtotal < dm.divisorInt &&
			dm.curIndexOfDigitOfDividend > dm.dividendInt.last_digit_position()
		)
	{
		dm.quotientInt.pop_front_extra_zeros();

		static bool quotient_dot_pos_was_already_set = false;
		if (!quotient_dot_pos_was_already_set)
		{
			if (dm.subtotal.last_digit_value())
			{
				dm.quotientDotPos = dm.quotientInt.quantity_of_digits();
			}
			else
			{
				dm.quotientDotPos = dm.quotientInt.quantity_of_digits() + 1;
			}

			quotient_dot_pos_was_already_set = true;

		} // endif (!quotient_dot_pos_was_already_set)

		calc_subtotal_and_add_digits_to_quotient(!is_first_time_add_digits_to_subtotal);
	}

	is_first_time_calc_subtotal = false;
	is_first_time_add_digits_to_subtotal = true;
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
	quotient.clear_number();
	add_dot();
	quotient.push_back_elem(dm.quotientInt.get_number());

	return quotient;
}

bool BigFloat::division_is_finished() const
{
	bool result =
		(dm.quotientInt.quantity_of_digits() >= PRECISION) ||
		(dm.curIndexOfDigitOfDividend > dm.dividendInt.last_digit_position() && dm.subtotal.is_zero()) ||
		(dm.subtotal.is_zero() && all_remaining_digits_of_dividend_are_zeros());

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
	bool zeroWasPushedBackInSubtotalInPrevStep = false;
	while (!division_is_finished())
	{
		calc_subtotal_and_add_digits_to_quotient(zeroWasPushedBackInSubtotalInPrevStep);
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

	for (size_t i = dm.curIndexOfDigitOfDividend; i < dm.dividendInt.quantity_of_digits(); ++i)
	{
		if (dm.dividendInt.elem_value_as_digit(i) != 0)
		{
			result = false;
			break;
		}
	}

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


	// TODO: compare one position with another one by one

	return result;
}

bool BigFloat::operator<=(const BigFloat& bf) const
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a > b);
}

bool BigFloat::operator>(const BigFloat& bf) const
{
	BigFloat a = *this;
	BigFloat b = bf;

	return b < a;
}

bool BigFloat::operator>=(const BigFloat& bf) const
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a < b);
}

bool BigFloat::operator==(const BigFloat& bf) const
{
	BigFloat a(*this);
	BigFloat b(bf);

	return !(a < b) && !(a > b);
}

bool BigFloat::operator!=(const BigFloat & bf) const
{
	BigFloat a(*this);
	BigFloat b(bf);

	return (a < b) || (a > b);
}



// assignment operators ========================================================
BigFloat BigFloat::operator=(const BigFloat& bf)
{
	if (this != &bf)
	{
		set_number(bf);
	}
	return *this;
}

BigFloat BigFloat::operator=(const std::string& obj)
{
	if (this->get_number() != &obj[0])
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
}



// arithmetic operators (both operand are same type) ===========================
BigFloat BigFloat::operator+(const BigFloat& addendum) const
{
	BigFloat sum;
	sum.clear_number();
	BigFloat a(*this);
	BigFloat b(addendum);

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

	if (a.get_sign() == b.get_sign())
	{
		size_t diff;		
		size_t aDigitsBeforeDot = a.digits_before_dot();
		size_t bDigitsBeforeDot = b.digits_before_dot();

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

		size_t aDigitsAfterDot = a.digits_after_dot();
		size_t bDigitsAfterDot = b.digits_after_dot();

		if (aDigitsAfterDot < bDigitsAfterDot)
		{
			diff = bDigitsAfterDot - aDigitsAfterDot;
			for (size_t i = 0; i < diff; ++i)
			{
				a.push_back_elem('0');
			}
		}
		else if (bDigitsAfterDot < aDigitsAfterDot)
		{
			diff = aDigitsAfterDot - bDigitsAfterDot;
			for (size_t i = 0; i < diff; ++i)
			{
				b.push_back_elem('0');
			}
		}

		size_t aDotPos = a.dot_position();
		size_t bDotPos = b.dot_position();

		a.erase_elem(aDotPos);
		b.erase_elem(bDotPos);

		a.reverse_number();
		b.reverse_number();

		size_t extra = 0;
		size_t subtotal = 0;

		size_t limit = aSize > bSize ? aSize - 1 : bSize - 1;
		for (size_t i = 0; i < limit; ++i)
		{
			subtotal = a.elem_value_as_digit(i) + b.elem_value_as_digit(i) + extra;

			if (subtotal > BigInt::MAX_DIGIT)
			{
				extra = subtotal / BigInt::BASE;
				subtotal = subtotal % BigInt::BASE;
			}
			else
			{
				extra = 0;
			}

			sum.push_back_elem(digit_to_char(subtotal));
		}

		size_t extraDotShift = 0;
		if (extra)
		{
			sum.push_back_elem(digit_to_char(extra));
			extraDotShift = 1;
		}

		sum.reverse_number();
		sum.insert_elem('.', aDotPos + extraDotShift);
		sum.set_number(sum.get_number());
		sum.set_sign(a.get_sign());
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

		if (a.get_sign() == '-')
		{
			sum.set_sign('+');
		}
		else if (b.get_sign() == '-')
		{
			sum.set_sign('-');
		}

		if (a.abs_value() == b.abs_value())
		{
			sum = "0.0";
			sum.set_sign('+');
		}
	}
	
	return sum;
} // endof #op+(bf)

BigFloat BigFloat::operator-(const BigFloat& subtrahend) const
{
	BigFloat diff;
	diff.clear_number();

	BigFloat a(*this);
	BigFloat b(subtrahend);

	size_t aSize = a.get_number().size();
	size_t bSize = b.get_number().size();

	if (a.get_sign() == b.get_sign())
	{
		size_t quantityOfDigitsDiff;

		size_t aDigitsBeforeDot = a.digits_before_dot();
		size_t bDigitsBeforeDot = b.digits_before_dot();

		if (aDigitsBeforeDot < bDigitsBeforeDot)
		{
			quantityOfDigitsDiff = bDigitsBeforeDot - aDigitsBeforeDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				a.push_front_elem('0');
			}
		}
		else if (bDigitsBeforeDot < aDigitsBeforeDot)
		{
			quantityOfDigitsDiff = aDigitsBeforeDot - bDigitsBeforeDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				b.push_front_elem('0');
			}
		}

		size_t aDigitsAfterDot = a.digits_after_dot();
		size_t bDigitsAfterDot = b.digits_after_dot();
		if (aDigitsAfterDot < bDigitsAfterDot)
		{
			quantityOfDigitsDiff = bDigitsAfterDot - aDigitsAfterDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				a.push_back_elem('0');
			}
		}
		else if (bDigitsAfterDot < aDigitsAfterDot)
		{
			quantityOfDigitsDiff = aDigitsAfterDot - bDigitsAfterDot;
			for (size_t i = 0; i < quantityOfDigitsDiff; ++i)
			{
				b.push_back_elem('0');
			}
		}

		size_t aDotPos = a.dot_position();
		size_t bDotPos = b.dot_position();

		a.erase_elem(aDotPos);
		b.erase_elem(bDotPos);

		a.reverse_number();
		b.reverse_number();
		size_t subtotal = 0;
		size_t minuendDigit = 0;
		size_t subtrahendDigit = 0;
		size_t borrowed = 0;
		size_t prevBorrowed = 0;

		size_t limit = aSize > bSize ? aSize - 1 : bSize - 1;
		for (size_t i = 0; i < limit; ++i)
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
		}

		diff.reverse_number();
		diff.insert_elem('.', aDotPos);
		diff.set_number(diff.get_number());
		diff.set_sign(a.get_sign());
	}
	else
	{	
		if (a.abs_value() != b.abs_value())
		{
			diff = a.abs_value() + b.abs_value();
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
		}
	}

	return diff;
} // endof // #op-(bf)

BigFloat BigFloat::operator*(const BigFloat& multiplier) const
{
	BigFloat product;
	product.clear_number();

	BigFloat a(*this);
	BigFloat b(multiplier);

	size_t shift = a.digits_after_dot() + b.digits_after_dot();

	size_t aDotPos = a.dot_position();
	size_t bDotPos = b.dot_position();

	a.erase_elem(aDotPos);
	b.erase_elem(bDotPos);

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
	product.move_floating_point(LEFT, shift);
	product.pop_back_trailing_zeros();

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

BigFloat BigFloat::operator/(const BigFloat& divider) const
{
	BigFloat quotient;
	quotient.clear_number();

	BigFloat dividend(*this);
	BigFloat divisor(divider);

	dm.divisorDigitsAfterDot = divisor.digits_after_dot();
	prepare_divident_and_divisor(dividend, divisor);

	if (dm.dividendInt < dm.divisorInt)
	{
		divide_abs_less_by_greater();
		quotient = finalize_division();
	}
	else if (dm.dividendInt > dm.divisorInt)
	{
		divide_abs_greater_by_less();
		quotient = finalize_division();
	}
	else
	{
		quotient.push_back_elem("1.0");
	}

	quotient.set_number(quotient.get_number());
	define_quotient_sign(quotient, dividend, divisor);

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
	
	char sign = num[0] == '-' ? '-' : '+'; // crutch
	bf.set_sign(sign); // crutch

	return is;
} // endof // #op>>(bf)

std::ostream& operator<<(std::ostream& os, const BigFloat& bf) // #op<<(bf)
{
	BigFloat temp = bf;

	if (temp.is_decimal())
	{
		temp.convert_to(BigFloat::SCIENTIFIC);
	}
	else if (temp.is_scientific())
	{
		// do nothing
	}
	else if (temp.is_zero())
	{
		temp.reset();
		temp.push_back_elem(" E+0");
	}
	else
	{
		temp.reset();
		temp.push_back_elem(" E+0");
	}

	os << temp.get_sign() << temp.get_number();

	return os;
} // endof // #op<<(bf)
