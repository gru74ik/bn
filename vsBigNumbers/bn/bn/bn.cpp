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
	BigFloat c("123.45");
	// �����: 123.45
	// �� ������ ������ ����: +1.2347 �+2
	std::cout
		<< "c: "
		<< c
		<< "\n\n"
		;
*/
/*
	BigFloat d("0.089");
	// �����: 0.089
	// �� ������ ������ ����: +8.9 �-2
	std::cout
		<< "d: "
		<< d
		<< "\n\n"
		;
*/
/*
	std::cout
		<< "c + d = "
		<< (c + d)
		<< "\n\n"
		;
*/
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
/*
	BigFloat x;
	BigFloat y;
	std::cout << "Enter two big floating point numbers one by one:\n";
	std::cin >> x >> y;
	std::cout << "x + y = " << (x + y) << "\n\n";
*/
	
	std::cout << "The number before all is: +1.23456 E+5\n\n";
	BigFloat a("+1.23456 E+5"); // 123456.0
	std::cout << a << "\n\n";

	return 0;
}