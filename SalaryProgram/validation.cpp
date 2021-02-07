#include "validation.h"
#include <windows.h>
#include <iostream>
using namespace std;

int inputNumber(int left_range, int right_range)
{
	int number;
	while (true)
	{
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range))
		{
			return number;
		}
		else
		{
			cout << "\n\tНекорректный ввод!" << endl;
			cout << "\n\tВведите корректные данные:" << endl;
			cout << "\n\t";
		}
	}
}

bool isNumberNumeric()
{
	if (cin.get() == '\n')return true;
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}

bool isNumberRangeCorrect(int number, int left_range, int right_range)
{
	if ((number >= left_range) && (number <= right_range))return true;
	else return false;
}


/*

while (true)
				{
					cout << "\n\tВведите номер группы: ";
					cin >> Stud.group_number;

					if (Stud.group_number > 100000 && Stud.group_number < 999999 && cin.get() == '\n')
					{
						break;
					}
					else
					{
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Неккоректный ввод!" << endl;

					}
				}


*/