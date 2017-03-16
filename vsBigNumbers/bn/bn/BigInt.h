#ifndef BIGINT_H
#define BIGINT_H

#include "stdafx.h"
#include "BigNumber.h"

class BigFloat; // forward declaration

class BigInt : public BigNumber
{
public:
	// constructors:
	BigInt();							// is done
	BigInt(const std::string& number);	// is done
	BigInt(const BigInt& number);
	virtual ~BigInt() {}				// is done

private:
	// checkers:	
	bool is_correct(const std::string& number) const; // is done
	bool is_correct() const;			// is done
	bool is_greater_than_zero() const;	// is almost done
	bool is_less_than_zero() const;		// is done
	bool is_zero() const;				// is almost done

	// getters:
	size_t last_digit_position() const; // is done
	size_t last_digit_value() const;	// is done
	
	size_t leading_zeros() const;	// TODO: implement this function member!

public:
	// setters:
	void set_number(const std::string & str);	// is done


	// assignment operators:
	BigInt operator=(const BigInt& bi);			// is done
	BigInt operator=(const std::string& str);	// is done

	// comparison operators:
	bool operator<(const BigInt& bi) const;		// TODO: implement it right!
	bool operator<=(const BigInt& bi) const;	// TODO: implement it right!
	bool operator>(const BigInt& bi) const;		// TODO: implement it right!
	bool operator>=(const BigInt& bi) const;	// TODO: implement it right!
	bool operator==(const BigInt& bi) const;

	// arithmetic operators:
	BigInt operator+(const BigInt& addendum) const;			// TODO: implement it right!
	BigInt operator-(const BigInt& subtrahend) const;		// TODO: implement this function member!
	BigInt operator*(const BigInt& multiplier) const;		// TODO: implement this function member!
	BigInt operator/(const BigInt& divider) const;			// TODO: implement this function member!

	BigFloat operator+(const BigFloat& addendum) const;		// TODO: implement this function member!
	BigFloat operator-(const BigFloat& subtrahend) const;	// TODO: implement this function member!
	BigFloat operator*(const BigFloat& multiplier) const;	// TODO: implement this function member!
	BigFloat operator/(const BigFloat& divider) const;		// TODO: implement this function member!

	// prefix increment:
	friend const BigInt& operator++(BigInt& i);
	// postfix increment:
	friend const BigInt operator++(BigInt& i, int fakeArg); // fakeArg - trick for compiler

	// input-output operators:
	friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
	friend std::istream& operator >> (std::istream& is, BigInt& bi);
};

#endif // BIGINT_H