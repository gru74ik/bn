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
	BigInt bi;
	BigFloat  bf;

		std::cout << "Enter big integer number:\n";
		std::cin >> bi;

		std::cout << "Enter big float number:\n";
		std::cin >> bf;

		std::cout
			<< "\na: " << bi
			<< "\nb: " << bf
			<< "\na / b: " << bi / bf
			<< "\n\n";

	return 0;
}