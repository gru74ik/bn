#include "stdafx.h"
#include "BigNumber.h"
#include "bn_functions.h"


// ctors =======================================================================
BigNumber::BigNumber()
	:
		number_("0"),
		sign_('+')
{
/*
	std::cout
		<< "Default ctor BigNumber::BigNumber() has been called."
		;
*/
/*
	std::cout
		<< "\nThe sign of the number after ctor finished his work: "
		<< sign_
		<< "\nThe number after ctor finished his work: "
		<< number_ << "\n\n"
		;
*/
}

BigNumber::BigNumber(const char num)
{
/*
	// #bnctor(ch) 1
	std::cout
		<< "Ctor BigNumber::BigNumber(const char num) has been called."
		<< "\nAssertion occured in BigNumber.cpp, #bnctor(ch) 1.\n\n"
		;
*/
	if (num == '0')
	{
		reset();
	}
	else
	{
		number_ = "";
		number_ = number_ + num;
		sign_ = define_sign();
		discard_sign();
	}


/*
	std::cout
		<< "\nThe sign of the number after ctor finished his work: "
		<< sign_
		<< "\nThe number after ctor finished his work: "
		<< number_ << "\n\n"
		;
*/
}

BigNumber::BigNumber(const std::string& num)
{
/*
	// #bnctor(str) 1
	std::cout
		<< "Ctor BigNumber::BigNumber(const std::string& num) has been called."
		<< "\nAssertion occured in BigNumber.cpp, #bnctor(str) 1.\n\n"
		;
*/
	if (num.size() == 0)
	{
		reset();
	}	
	else
	{
/*
		// #bnctor(str) 2
		std::cout
			<< "signAlreadyDefined is " << std::boolalpha
			<< signAlreadyDefined << std::noboolalpha
			<< "\nAssertion occured in BigNumber.cpp, #bnctor(str) 2.\n\n"
			;
*/
		number_ = num;
		sign_ = define_sign();
		discard_sign();
	}
	

/*
	std::cout
		<< "\nThe sign of the number after ctor finished his work: "
		<< sign_
		<< "\nThe number after ctor finished his work: "
		<< number_ << "\n\n"
		;
*/
}

BigNumber::BigNumber(const BigNumber &)
{
/*
	std::cout << "Copy ctor BigNumber::BigNumber(const BigNumber &) has been called."
		<< "\nThe sign of the number after ctor finished his work: "
		<< sign_
		<< "\nThe number after ctor finished his work: "
		<< number_ << "\n\n"
		;
*/
}



// changers ====================================================================

// отбросить знак
void BigNumber::discard_sign()
{
	if (is_sign(number_[0]))
	{
		erase_elem(0);
	}
/*
	// #dissn() 666
	std::cout
		<< "\nData members after discard_sign() finished his work:"
		<< "\nsign_: " << get_sign()
		<< "\nnumber_: " << get_number()
		<< "\nAssertion occured in BigNumber.cpp, BigNumber::discard_sign(), ##dissn() 666.\n\n"
		;
*/
}

// затолкать вперёд добавочные нули
void BigNumber::push_front_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_front(number_, '0');
	}
}

void BigNumber::push_back_additional_zeros(const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		push_back(number_, '0');
	}
}

// "перевернуть" число (поменять местами старшие разряды и младшие)
void BigNumber::reverse_number()
{
	reverse(number_);
}

void BigNumber::erase_elem(const size_t pos)
{
	erase_part_of(number_, pos, pos);
}

void BigNumber::erase_elem(const size_t first, const size_t last)
{
	erase_part_of(number_, first, last);
}

void BigNumber::insert_elem(const char ch, const size_t pos)
{
	insert_to(number_, ch, pos);
}

void BigNumber::insert_elem(const std::string & str, const size_t pos)
{
	insert_to(number_, str, pos);
}

void BigNumber::push_back_elem(const char ch)
{
	push_back(number_, ch);
}

void BigNumber::push_back_elem(const std::string & str)
{
	push_back(number_, str);
}

void BigNumber::push_front_elem(const char ch)
{
	push_front(number_, ch);
}

void BigNumber::push_front_elem(const std::string & str)
{
	push_front(number_, str);
}

void BigNumber::pop_back_elem()
{
	pop_back(number_);
}

void BigNumber::pop_back_elem(const size_t quantity)
{
	erase_part_of(number_, number_.size() - quantity, number_.size() - 1);
}

void BigNumber::pop_front_elem()
{
	pop_front(number_);
}

void BigNumber::pop_front_elem(const size_t quantity)
{
	erase_part_of(number_, 0, quantity - 1);
}

void BigNumber::clear_number()
{
	//number_.clear();
	erase_elem(0, number_.size() - 1);
}

// getters =====================================================================

// найти количество лидирующих нулей
size_t BigNumber::leading_zeros() const
{
	size_t quantity_of_leading_zeros = 0;
	for (size_t i = 0; i < number_.size(); ++i)
	{
		if (number_[i] == '0')
		{
			++quantity_of_leading_zeros;
		}
		else
		{
			break;
		}
	}
/**/
	std::cout
		<< "The quantity of leading zeros is: "
		<< quantity_of_leading_zeros
		<< ". Assertion occured in BigNumber.cpp, leading_zeros().\n\n"
		;

	return quantity_of_leading_zeros;
}

size_t BigNumber::elem_value_as_digit(size_t index) const
{
	return char_to_digit(number_[index]);
}

char BigNumber::elem_value_as_char(size_t index) const
{
	return number_[index];
}

// найти позицию первой цифры числа
size_t BigNumber::first_digit_position() const
{
	size_t first_digit_pos = number_.size();

	for (size_t i = 0; i < number_.size(); ++i)
	{
		if (is_digit(number_[0]))
		{
			first_digit_pos = i;
			break;
		}
	}

	return first_digit_pos;
}

// найти значение первой цифры числа
size_t BigNumber::first_digit_value() const
{
	return char_to_digit(number_[first_digit_position()]);
	//return char_to_digit(number_[0]);
}

// найти позицию перед заданной позицией
size_t BigNumber::position_before(size_t pos) const
{
	size_t posBeforePos = number_.size();
	if (pos > 0)
	{
		posBeforePos = pos - 1;
	}

	return posBeforePos;
}

// найти позицию после заданной позицией
size_t BigNumber::position_after(size_t pos) const
{
	size_t numSize = number_.size();
	size_t posAfterPos = numSize;

	if (pos + 1 < numSize)
	{
		posAfterPos = pos + 1;
	}

	return posAfterPos;
}

// определить знак числа
char BigNumber::define_sign() const
{
	return number_[0] == '-' ? '-' : '+';
	/**/
	// #defsn() 444
	std::cout
		<< "\nData members after define_sign() finished his work:"
		<< "\nsign_: " << get_sign()
		<< "\nnumber_: " << get_number()
		<< "\nAssertion occured in BigNumber.cpp, BigNumber::define_sign(), #defsn() 444.\n\n"
		;
}

// получить знак числа
char BigNumber::get_sign() const
{
	return sign_;
}

// достать (to get) содержимое поля number_
std::string BigNumber::get_number() const
{
/*
	std::cout
		<< "get_number() function has been called. The number is: "
		<< number_
		<< "\nAssertion occured in BigNumber.cpp, get_number().\n\n"
		;
*/
	return number_;
}



// setters =====================================================================

// сбросить значения полей в значения по умолчанию (обнулить)
void BigNumber::reset()
{
	sign_ = '+';
	number_ = "0";
}

// установить знак
void BigNumber::set_sign(const char sign)
{
	sign_ = sign;
}

// установить значение полей в соответствии с переданным аргументом
void BigNumber::set_number(const std::string & num)
{
	number_ = num;
	sign_ = define_sign();
	discard_sign();
}


