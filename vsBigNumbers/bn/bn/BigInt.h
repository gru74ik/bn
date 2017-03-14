#ifndef BIGINT_H
#define BIGINT_H

#include "stdafx.h"
#include "BigNumber.h"

class BigFloat; // forward declaration

class BigInt : public BigNumber
{
public:
	// constructors:
	BigInt();
	BigInt(const std::string& number);

private:
	// checkers:	
	bool is_correct(const std::string & number) const;
	bool is_correct() const;
	bool is_greater_than_zero() const;
	bool is_less_than_zero() const;
	bool is_zero() const;

	// getters:
	size_t last_digit_position() const;
	size_t last_digit() const;

public:
	std::string number() const;


private:
	// setters:
	void set_number(const std::string & str);
	void mark_as_wrong();

public:
	void set_number(const std::string & number);

	// assignment operators:
	BigInt operator=(const BigInt& bi);
	BigInt operator=(const std::string& str);

	// comparison operators:
	bool operator<(const BigInt& bi) const;
	bool operator<=(const BigInt& bi) const;
	bool operator>(const BigInt& bi) const;
	bool operator>=(const BigInt& bi) const;
	bool operator==(const BigInt& bi) const;

	// arithmetic operators:
	BigInt operator+(const BigInt& addendum) const;
	BigInt operator-(const BigInt& subtrahend) const;
	BigInt operator*(const BigInt& multiplier) const;
	BigInt operator/(const BigInt& divider) const;

	BigFloat operator+(const BigFloat& addendum) const;
	BigFloat operator-(const BigFloat& subtrahend) const;
	BigFloat operator*(const BigFloat& multiplier) const;
	BigFloat operator/(const BigFloat& divider) const;

	// prefix increment:
	friend const BigInt& operator++(BigInt& i);
	// postfix increment:
	friend const BigInt operator++(BigInt& i, int fakeArg); // fakeArg - trick for compiler

	// input-output operators:
	friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
	friend std::istream& operator >> (std::istream& is, BigInt& bi);
};

#endif // BIGINT_H