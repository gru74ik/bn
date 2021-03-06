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

	// division helpers ============================================================
	struct DivisionMembers
	{
		BigInt subtotal;
		BigInt dividendInt;
		BigInt divisorInt;
		BigInt quotientInt;
		size_t curIndexOfDigitOfDividend;
		size_t quotientDotPos;
		size_t divisorDigitsAfterDot;
	};

	char next_digit_of_quotient() const;

	void calc_subtotal_and_add_digits_to_quotient(bool zeroWasPushedBackInSubtotalInPrevStep) const;

	void calc_subtotal_and_add_digits_to_quotient(const BigInt & prevSubtotal) const;

	void add_zeros_to_quotient() const;

	void BigFloat::define_quotient_sign
		(
			BigFloat & quotient,
			BigFloat & dividend,
			BigFloat & divisor
		)
		const;

	BigFloat finalize_division()const;

	bool division_is_finished() const;

	void divide_abs_greater_by_less() const;

	void divide_abs_less_by_greater() const;

	void align_divident_and_divisor(BigFloat& dividend, BigFloat& divisor) const;

	void prepare_divident_and_divisor(BigFloat& dividend, BigFloat& divisor) const;

	bool all_remaining_digits_of_dividend_are_zeros() const;

	void add_dot() const;

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