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
	BigFloat a;
	BigFloat b;

	std::string choice = "y";
	while (choice[0] == 'y' || choice[0] == 'Y')
	{
		std::cout << "Enter two big floating numbers one by one:\n";
		std::cin >> a >> b;
		std::cout
			<< "\nx: " << a
			<< "\ny: " << b
			<< "\nx + y: " << a + b
			<< "\nx - y: " << a - b
			<< "\nx * y: " << a * b
			<< "\n\nDo you want proceed? (y/n) ";
		std::cin >> choice;
		std::cout << "\n\n";
	}

	return 0;
}