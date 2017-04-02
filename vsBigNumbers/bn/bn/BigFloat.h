#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"

class BigFloat
	: public BigNumber
{

public:
	enum Notation { DEFAULT = 0, DECIMAL, SCIENTIFIC };

private:
	enum Direction { LEFT, RIGHT };
	Notation notation_;
	char eSign_;
	std::string eValueAsString_;

	class DivisionHelper
	{
	private:
		BigInt dividend_;
		BigInt divisor_;
		static bool divisionIsFinished_;

	public:
		DivisionHelper(BigInt dividend, BigInt divisor)
			:
				dividend_(dividend),
				divisor_(divisor)
		{}

		BigInt dividend_itself() const
		{
			return dividend_;
		}

		BigInt divisor_itself() const
		{
			return divisor_;
		}

		BigInt dividend_number() const
		{
			return dividend_.get_number();
		}

		BigInt divisor_number() const
		{
			return divisor_.get_number();
		}

		bool division_is_finished()
		{
			return divisionIsFinished_;
		}

		BigInt mediate_dividend
			(
				BigInt subtotal,
				size_t& indexOfLastUsedDigitOfDividend,
				size_t& additionalZeros
			)
			const
		{
			BigInt mediateDividend = subtotal;

			if (subtotal.is_zero())
			{
				if (indexOfLastUsedDigitOfDividend == divisor_.last_digit_position())
				{
					divisionIsFinished_ = true;
				}
				else
				{
					mediateDividend.push_back_elem
					(
						dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
					);

					while
						(
							mediateDividend.quantity_of_digits() <
							dividend_.quantity_of_digits() - 1
							)
					{
						++indexOfLastUsedDigitOfDividend;
						mediateDividend.push_back_elem
						(
							dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
						);
					}
				}

			}
			else if (subtotal > divisor_)
			{
				mediateDividend.push_back_elem
					(
						dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
					);

				while
					(
						mediateDividend.quantity_of_digits() <
						dividend_.quantity_of_digits() - 1
					)
				{
					++indexOfLastUsedDigitOfDividend;
					mediateDividend.push_back_elem
						(
							dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
						);
				}
			}
			else if (subtotal < divisor_ && !subtotal.is_zero())
			{
				while (mediateDividend < divisor_)
				{
					mediateDividend.push_back_elem('0');
					++additionalZeros;
				}
			}
			else if (subtotal == divisor_)
			{
				// do nothing
			}


			mediateDividend.pop_front_extra_zeros();

			return mediateDividend;
		}

		BigInt mediate_dividend
			(
				size_t& indexOfLastUsedDigitOfDividend,
				size_t& additionalZeros
			)
			const
		{
			// this function have be called in first step of division only
			BigInt mediateDividend;
			mediateDividend.clear_number();

			if (dividend_ > divisor_)
			{
				mediateDividend.push_back_elem
				(
					dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
				);

				while
					(
						mediateDividend.quantity_of_digits() <
						dividend_.quantity_of_digits() - 1
						)
				{
					++indexOfLastUsedDigitOfDividend;
					mediateDividend.push_back_elem
					(
						dividend_.elem_value_as_char(indexOfLastUsedDigitOfDividend)
					);
				}
			}
			else if (dividend_ < divisor_)
			{
				while (mediateDividend < divisor_)
				{
					mediateDividend.push_back_elem('0');
					++additionalZeros;
				}
			}
			else
			{
				mediateDividend = dividend_;
			}

			return mediateDividend;
		}
	};

public:
	// ctors =======================================================================
	BigFloat();
	BigFloat(const std::string & num);
	BigFloat(const BigInt & bi);
	BigFloat(const BigFloat & bf);

	// dtors =======================================================================
	virtual ~BigFloat() {}

	// checkers ====================================================================
	bool has_extra_leading_zeros() const;
	bool has_leading_zeros() const;
	bool has_trailing_zeros() const;

	bool is_correct(Notation notation) const;
	bool is_decimal() const;
	bool is_scientific() const;

	virtual bool is_greater_than_zero() const;
	virtual bool is_less_than_zero() const;
	virtual bool is_zero() const;	// may be is_default() would be more logical?

	// changers ====================================================================
	void discard_e_tail();
	void move_floating_point(Direction dir, size_t shiftSize);
	void convert_to(Notation notation);
	//void reverse();

	void pop_front_leading_zeros();
	void pop_front_extra_leading_zeros();
	void push_back_additional_zeros(const size_t quantity);
	void pop_back_trailing_zeros();

	// getters =====================================================================
	BigFloat abs_value();
	size_t extra_leading_zeros() const;
	size_t leading_zeros() const;
	size_t trailing_zeros() const;

	size_t digits_before_dot() const;
	size_t dot_position() const;
	size_t digits_after_dot() const;
	
	size_t e_position() const;		// returns position of letter 'E'
	size_t digits_after_e() const;	// returns quantity of digits after letter 'E'

	size_t e_value_as_number() const;
	std::string e_value_as_string() const;

	size_t e_sign_position() const;
	char e_sign() const;

	std::string e_tail() const;

	virtual size_t last_digit_position() const;
	virtual size_t last_digit_value() const;

	size_t space_position() const;

	std::string mantissa() const;
	Notation notation() const;

	// setters =====================================================================
	void set_number(const BigFloat& bf);
	void set_number(const std::string& num);
	void reset();

	// comparison operators ========================================================
	bool operator<(const BigFloat& bf) const;
	bool operator<=(const BigFloat& bf) const;
	bool operator>(const BigFloat& bf) const;
	bool operator>=(const BigFloat& bf) const;
	bool operator==(const BigFloat& bf) const;
	bool operator!=(const BigFloat& bf) const;

	// assignment operators ========================================================
	BigFloat operator=(const BigFloat& bf);
	BigFloat operator=(const std::string& obj);

	// arithmetic operators (both operand are same type) ===========================
	BigFloat operator+(const BigFloat& addendum) const;
	BigFloat operator-(const BigFloat& subtrahend) const;
	BigFloat operator*(const BigFloat& multiplier) const;
	BigFloat operator/(const BigFloat& divider) const;

	// arithmetic operators (each operand is different type) =======================
	BigFloat operator+(const BigInt& addendum) const;
	BigFloat operator-(const BigInt& subtrahend) const;
	BigFloat operator*(const BigInt& multiplier) const;
	BigFloat operator/(const BigInt& divider) const;

	// input-output operators ======================================================
	friend std::istream& operator >> (std::istream& is, BigFloat& bf);
	friend std::ostream& operator<<(std::ostream& os, const BigFloat& bf);

};

#endif // BIGFLOAT_H