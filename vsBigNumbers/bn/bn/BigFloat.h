#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include "stdafx.h"
#include "BigNumber.h"
#include "BigInt.h"

class BigFloat
	: public BigNumber
{
	// protected:
public: // remove this label when all tests will completed

	enum Notation { DEFAULT = 0, DECIMAL, SCIENTIFIC };
	enum Direction { LEFT, RIGHT };

	Notation notation_;

public:
	// constructors:
	BigFloat();
	BigFloat(const std::string & num);
	BigFloat(const BigInt & bi);
	BigFloat(const BigFloat & bf);

	// checkers:
	bool is_decimal() const;
	bool is_scientific() const;

	virtual bool is_greater_than_zero() const;
	virtual bool is_less_than_zero() const;
	virtual bool is_zero() const;

	// protected:
public: // remove this label when all tests will completed
	virtual bool is_correct() const {} // TODO: decide what to do with this function
	bool is_correct(Notation notation) const;

	// changers:
	void move_floating_point(Direction dir, size_t shiftSize);
	void convert_to(Notation notation);
	//void reverse();

public: // TODO: remove this label when tests will be completed
	void push_back_additional_zeros(const size_t quantity);
	void pop_back_extra_zeros();

	// getters:
	size_t dot_position() const;
	size_t digits_after_dot() const;
	size_t digits_before_dot() const;
	size_t e_position() const;
	size_t digits_after_e() const;
	size_t e_value_as_number() const;
	std::string e_value_as_string() const;
	size_t e_sign_position() const;
	char e_sign() const;
	size_t last_digit_position() const;
	virtual size_t last_digit_value() const;
	size_t position_after(size_t pos) const;
	size_t position_before(size_t pos) const;
	size_t space_position() const;

	char sign() const;
	std::string mantissa() const;


public:
	std::string number() const;
	Notation notation() const;

	// setters:
	void set_number(const std::string& num);
	void reset();

public:
	// comparison operators:
	bool operator<(const BigFloat& bf) const;
	bool operator<=(const BigFloat& bf) const;
	bool operator>(const BigFloat& bf) const;
	bool operator>=(const BigFloat& bf) const;
	bool operator==(const BigFloat& bf) const;

	// assignment operators:
	BigFloat operator=(const BigFloat& bf);
	BigFloat operator=(const std::string& obj);

	// arithmetic operators (both operand are same type):
	BigFloat operator+(const BigFloat& addendum) const;
	BigFloat operator-(const BigFloat& subtrahend) const;
	BigFloat operator*(const BigFloat& multiplier) const;
	BigFloat operator/(const BigFloat& divider) const;

	// arithmetic operators (each operand are different type):
	BigFloat operator+(const BigInt& addendum) const;
	BigFloat operator-(const BigInt& subtrahend) const;
	BigFloat operator*(const BigInt& multiplier) const;
	BigFloat operator/(const BigInt& divider) const;

	// input-output operators:
	friend std::istream& operator >> (std::istream& is, BigFloat& bf);
	friend std::ostream& operator<<(std::ostream& os, const BigFloat& bf);

};

#endif // BIGFLOAT_H