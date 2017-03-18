/*
������������� �������� ������� ������ ����� ������ �� 30 ���������� ���� ��
�������������� ����� � ����� (zn)m.n � N, ��� ��������� ����� �������� (m+n)
� �� 30 �������� ����, � �������� ������� N � �� 5 ����.

��������� ������ � ����� (zn)0.m1 � N1.

�������� ����������� (zn) � ���� ����� N, N1 � �������� ������� E � ���������
�����. ������ ����� (zn)0.m � N ������������� ��������� ������ �����
N mzn 10 *. 0) ( . ��������, ����� 2.5 ����� �������� � ����: +0.25 E+1.

������� ���������� ������:
1.  ���������� ��������� ������ ��� �������� �������� �����.
2.  ������������� ���� � ����� ����� ����������� � ��� �������, ������� ������
� �������.
3.  ��������� ����� �� ������������ ��� ����� ������ (�.�. ����� ������
����������� ����� ���������).
4.  STL �� ������������.
*/

#include "stdafx.h"
#include "BigInt.h"
#include "BigFloat.h"
#include "bn_functions.h"

int main()
{
/*
	BigFloat c("123.47");

	// �����: 1234.47
	// �� ������ ������ ����: +1.2347 �+2
	// � �� ����� ����: +123.47�+2
	// ������:
	/// 1. ���� ���������� - ������
	/// 2. ������� - ������
	/// 3. ��������� ����� ������ ��������� �����, �� ��� ������-�� ������ �� ����������
	/// 4. "���������" ������ ����� ��������
	std::cout
		<< "c: "
		<< c
		<< "\n\n"
		;
*/

/**/
	BigFloat d("0.089");

	// �����: 0.089
	// �� ������ ������ ����: +8.9 �-2
	// � �� ����� ����: +0.008 E-2
	// ������:
	/// 1. ���� ���������� - ������
	/// 2. ������� - ������
	/// 3. ��������� ����� ������ ��������� ������ �� 2, �� ��� ������-�� ���������� ����� �� 1
	/// 4. "���������" ��������� ����� ��������

	std::cout
		<< "d: "
		<< d
		<< "\n\n"
		;

/*
	BigInt x("0000000000000000000000000000000000001984");
	BigInt y("02000");
	BigInt z("000000000000007770000000000999");
	x.insert_elem("777", 0);
	y.insert_elem('6', y.last_digit_position());
	z.insert_elem('4', z.get_number().size());

	std::cout
		<< "\n\n"
		<< "x: " << x << "\n\n"
		<< "y: " << y << "\n\n"
		<< "z: " << z << "\n\n"
		;
*/	
	return 0;
}