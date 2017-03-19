#include "stdafx.h"
#include "bn_functions.h"

// checkers ====================================================================
bool contains_digits_only(const std::string& num)
{
	bool result = true;
	for (size_t i = 0; i < num.size(); ++i)
	{
		if (!is_digit(num[i]))
		{
			result = false;
			break;
		}
	}
	return result;
} // endof contains_digits_only()

bool contains_one_dot_only(const std::string& num)
{
	int counter = 0;
	for (size_t i = 0; i < num.size(); ++i)
	{
		if (is_dot(num[i]))
		{
			++counter;
		}

		if (counter > 1)
		{
			break;
		}

	}
	return counter == 1;
} // endof contains_one_dot_only()

bool is_digit(const char ch)
{
	//return ch >= '0' && ch <= '9';
	return isdigit(ch);
} // endof is_digit()

bool is_dot(const char ch)
{
	return ch == '.' || ch == ',';
} // endof is_dot()

bool is_one_char(const std::string& num)
{
	return num.size() == 1;
} // endof is_one_char()

bool is_sign(const char ch)
{
	return ch == '+' || ch == '-';
} // endof is_sign()

bool is_space(const char ch)
{
	return ch == ' ';
} // endof is_space()



// finders =====================================================================
size_t char_position(const std::string &str, const char ch)
{
	size_t char_pos = str.size();
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ch)
		{
			char_pos = i;
			break;
		}
	}
	return char_pos;
} // endof char_position()



// changers ====================================================================
void erase_part_of(std::string& str, const size_t first, const size_t last)
{
	if (first <= last)
	{
		std::string part_before = "";
		
		for (size_t i = 0; i < first; ++i)
		{
			part_before = part_before + str[i];
/*
			// #epo() 1
			std::cout
				<< "part_before: "
				<< part_before
				<< "Assertion occured in bn_functions.cpp, erase_part_of(), #epo() 1.\n\n";
*/
		}

		std::string part_after = "";
		if ( last < str.size() - 1)
		{
			for (size_t j = last + 1; j < str.size(); ++j)
			{
				part_after = part_after + str[j];
/*
				// #epo() 2
				std::cout
					<< "part_after: "
					<< part_after
					<< "Assertion occured in bn_functions.cpp, erase_part_of(), #epo() 2.\n\n";
*/
			}
		}
/*
		// #epo() 3
		std::cout
			<< "part_before: "
			<< part_before
			<< "\n";

		std::cout
			<< "part_after: "
			<< part_after
			<< "Assertion occured in bn_functions.cpp, erase_part_of(), #epo() 3.\n\n";
*/
		str = part_before + part_after;
/*
		// #epo() 4
		std::cout
			<< "str = part_before + part_after: "
			<< str
			<< "\n";
*/
	}
} // endof erase_part_of()

void insert_to(std::string& str, const char ch, const size_t pos)
{
	std::string part_before = "";
	for (size_t i = 0; i < pos; ++i)
		part_before = part_before + str[i];

	std::string part_after = "";
	std::string result;

	if (pos < str.size())
	{
		for (size_t i = pos; i < str.size(); ++i)
			part_after = part_after + str[i];

		result = part_before + ch + part_after;
	}
	else
	{
		result = part_before + ch;
	}

	str = result;
}

void insert_to(std::string& str, const std::string& ins, const size_t pos)
{
	std::string part_before = "";
	for (size_t i = 0; i < pos; ++i)
		part_before = part_before + str[i];

	std::string part_after = "";
	std::string result;

	if (pos < str.size())
	{
		for (size_t i = pos; i < str.size(); ++i)
			part_after = part_after + str[i];

		result = part_before + ins + part_after;
	}
	else
	{
		result = part_before + ins;
	}

	str = result;
} //endof insert_to()

void reverse(std::string& str)
{
	for (size_t i = 0, j = str.size() - 1; i < str.size() / 2; ++i, --j)
	{
		//std::cout << i + 1 << " pair: " << number_[i] << " and " << number_[j] << "\n";

		// or standard library algorithm std:swap( number_[i], number_[j] );
		char temp;
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
} // endof reverse()

void pop_back(std::string& str)
{
	erase_part_of(str, str.size() - 1, str.size() - 1);
} // endof pop_back(std::string& str)

void pop_front(std::string& str)
{
	erase_part_of(str, 0, 0);
	//str.erase(0, 1); // or function member 'erase' from std::string class
} // endof pop_front(std::string& str)

void push_back(std::string& str, const std::string& substr)
{
	insert_to(str, substr, str.size());
} // endof push_back(std::string& str, const std::string& substr)

void push_back(std::string& str, const char ch)
{
	std::string substr = "";
	substr = substr + ch;
	insert_to(str, substr, str.size());
} // endof push_back(std::string& str, const char ch)

void push_front(std::string& str, const std::string& substr)
{
	insert_to(str, substr, 0);
} // endof push_front(std::string& str, const std::string& substr)

void push_front(std::string& str, const char ch)
{
	std::string substr = "";
	substr = substr + ch;
	insert_to(str, substr, 0);
} // endof push_front(std::string& str, const char ch)



// converters ==================================================================
size_t char_to_digit(const char ch)
{
	return ch - '0';
} // endof char_to_digit()

char digit_to_char(const size_t num)
{
	return num + '0';
} // endof digit_to_char()

std::string number_to_string(size_t num)
{
	size_t part_of_num;
	std::string result = "";
	while (num)
	{
		part_of_num = num % 10;
		result = digit_to_char(part_of_num) + result;
		num /= 10;
	}
	return result;
} // endof number_to_string()

size_t string_to_number(const std::string& str)
{
	size_t result = 0;
	size_t last_elem_index = str.size() - 1;
	for (size_t i = 0; i < str.size(); ++i)
	{
		result += char_to_digit(str[last_elem_index - i]) * bn_pow(10, i);
	}
	return result;
} // endof string_to_number()



// math functions ==============================================================
size_t bn_pow(size_t base, size_t exp)
{
	size_t result = 1;
	for (size_t i = 0; i < exp; ++i)
	{
		result *= base;
	}
	return result;
} // endof bn_pow()