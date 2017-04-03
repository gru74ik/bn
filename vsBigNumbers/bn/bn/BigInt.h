#ifndef BIGINT_H
#define BIGINT_H

#include "stdafx.h"
#include "BigNumber.h"

class BigFloat; // forward declaration

class BigInt
	: public BigNumber
{
public:
	// ctors =======================================================================
	BigInt();							// is done
	BigInt(const char num);
	BigInt(const std::string& num);		// is done
	BigInt(const BigInt& bi);			// is done

	// dtors =======================================================================
	virtual ~BigInt() {}				// is done

	// checkers ====================================================================
	bool has_leading_zeros() const;						// is done
	bool is_correct(const std::string& num) const;		// is done
	bool is_correct() const;							// is done
	virtual bool is_greater_than_zero() const;			// is done
	virtual bool is_less_than_zero() const;				// is done
	virtual bool is_zero() const;						// is done

	// changers ====================================================================
	void pop_front_extra_zeros();

	// getters =====================================================================
	BigInt abs_value() const;							// is done
	size_t quantity_of_digits() const;					// is done
	virtual size_t last_digit_position() const;			// is done
	virtual size_t last_digit_value() const;			// is done

	// setters =====================================================================
	void set_number(const BigInt& bi);	// is done
	void set_number(const std::string & num);	// is done

	// assignment operators ========================================================
	BigInt operator=(const BigInt& bi);			// is done
	BigInt operator=(const std::string& num);	// is done

	// comparison operators ========================================================
	bool operator<(const BigInt& bi) const;		// is done
	bool operator<=(const BigInt& bi) const;	// TODO: implement it right!
	bool operator>(const BigInt& bi) const;		// TODO: implement it right!
	bool operator>=(const BigInt& bi) const;	// TODO: implement it right!
	bool operator==(const BigInt& bi) const;
	bool operator!=(const BigInt& bi) const;

	// arithmetic operators (both operands are same type) ===========================
	BigInt operator+(const BigInt& addendum) const;		// TODO: implement it right!
	BigInt operator-(const BigInt& subtrahend) const;	// TODO: implement this function member!
	BigInt operator*(const BigInt& multiplier) const;	// TODO: implement this function member!
	BigInt operator/(const BigInt& divider) const;		// TODO: implement this function member!
/*
	// Some temporary unresolved troubles here
	friend BigFloat operator+(const BigInt& a, const BigFloat& b);	// TODO: implement this function member!
	friend BigFloat operator-(const BigInt& a, const BigFloat& b);	// TODO: implement this function member!
	friend BigFloat operator*(const BigInt& a, const BigFloat& b);	// TODO: implement this function member!
	friend BigFloat operator/(const BigInt& a, const BigFloat& b);	// TODO: implement this function member!
*/
	// prefix increment:
	friend const BigInt& operator++(BigInt& i);
	// postfix increment:
	friend const BigInt operator++(BigInt& i, int fakeArg); // fakeArg - trick for compiler

	// input-output operators ======================================================
	friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
	friend std::istream& operator >> (std::istream& is, BigInt& bi);
};

#endif // BIGINT_H