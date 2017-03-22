#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include "stdafx.h"

class BigNumber
{
private:
    char sign_;
    std::string number_;

public:
    static const size_t BASE = 10; // десятичная система счисления
    static const size_t MAX_DIGIT = BASE - 1; // максимальная цифра в разряде 9

    // ctors =======================================================================
    BigNumber();
    BigNumber(const std::string& num);

    // dtors =======================================================================
    virtual ~BigNumber() {}

    // checkers ====================================================================
    virtual bool is_greater_than_zero() const = 0;
    virtual bool is_less_than_zero() const = 0;
    virtual bool is_zero() const = 0;

    // changers ====================================================================
    void discard_sign();

    void push_front_additional_zeros(const size_t quantity);

    void reverse_number();

    void erase_elem(const size_t pos);
    void erase_elem(const size_t first, const size_t last);

    void insert_elem(const char ch, const size_t pos);
    void insert_elem(const std::string& str, const size_t pos);

    void push_back_elem(const char ch);
    void push_back_elem(const std::string& str);

    void push_front_elem(const char ch);
    void push_front_elem(const std::string& str);

    void pop_back_elem();
    void pop_back_elem(const size_t quantity);

    void pop_front_elem();
    void pop_front_elem(const size_t quantity);

    void clear_number();

    // getters =====================================================================
    size_t leading_zeros() const;		// TODO: implement for BigFloat his own version
    //size_t trailing_zeros() const;	// I changed my mind - this function member have to be in BigFloat only.

    size_t elem_value(size_t index) const;

    size_t first_digit_position() const;
    virtual size_t last_digit_position() const = 0;

    size_t first_digit_value() const;
    virtual size_t last_digit_value() const = 0;

    size_t position_before(size_t pos) const;
    size_t position_after(size_t pos) const;

    char define_sign() const;
    char get_sign() const;
    std::string get_number() const;

    // setters =====================================================================
    void reset();	// TODO: implement for BigFloat his own version
    void set_number(const std::string & num);
    void set_sign(const char sign);
};

#endif // BIGNUMBER_H
