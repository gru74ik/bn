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
	BigFloat a("+1.2345 E+5"); // 123450
	std::cout
		<< "a(+1.2345 E+5): " << a << "\n\n"
		;

	BigFloat b("+1.2345 E-3"); // 0.0012345
	std::cout
		<< "b(+1.2345 E-3): " << b << "\n\n"
		;
*/
	BigFloat x;
	BigFloat y;
	std::cout << "Enter two big floating numbers one by one:\n";
	std::cin >> x >> y;
	std::cout
		<< "\nx: " << x
		<< "\ny: " << y
		<< "\n\n";
	
	return 0;
}