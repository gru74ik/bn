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
		<< "\nc: "
		<< c
		<< "\nd: "
		<< d
		<< "\n\n"
		;
*/
    
	std::string str("123456789");
	std::cout << "str: " << str << "\n\n";

	BigInt x(str);
	std::cout << "x: " << x << "\n\n";

	erase_part_of(str, 1, 7); // 19
	std::cout << "str after erasing characters from pos 1 to pos 7: " << str << "\n\n";

	x.erase_elem(1, 7); // 19
	std::cout << "x after erasing characters from pos 1 to pos 7: " << x << "\n\n";

/*
	x.erase_elem(1);	// 1
	std::cout << "x after erasing 7: " << x << "\n";

	std::cout << "x.first_digit_position: " << x.first_digit_position() << "\n";	// 0

	std::cout << "x.first_digit_value: " << x.first_digit_value() << "\n";		// x[0]
*/


	return 0;
}