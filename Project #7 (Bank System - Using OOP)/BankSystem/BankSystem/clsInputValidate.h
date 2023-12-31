#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:
	static string ReadString(string msg)
	{
		string str;

		cout << msg;
		getline(cin >> ws, str);

		return str;
	}

	static int ReadIntegerNumber(string msg, string ErrorMsg = "Invalid Number!!\nTry Again\n\n")
	{
		string a;
		bool istrue;

		do
		{
			cout << msg;
			getline(cin >> ws, a);

			if (!(istrue = clsString::isStringDigit(a, clsString::Integer)))
				cout << ErrorMsg;

		} while (!istrue);

		return (stoi(a));

		/*int number;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMsg;
		}

		return number;*/
	}

	static double ReadDoubleNumber(string msg, string ErrorMsg = "Invalid Number!!\nTry Again\n\n")
	{
		string a;
		bool istrue;

		do
		{
			cout << msg;
			getline(cin >> ws, a);

			if (!(istrue = clsString::isStringDigit(a, clsString::Double)))
				cout << ErrorMsg;

		} while (!istrue);

		return (stod(a));
	}

	static bool IsNumberBetween(int num, int from, int to)
	{
		return (num >= from && num <= to);
	}

	static bool IsNumberBetween(double  num, double from, double to)
	{
		return (num >= from && num <= to);
	}

	static bool IsDateBetween(clsDate  date, clsDate date_1, clsDate date_2)
	{
		return ((clsDate::IsDate1AfterDate2(date, date_1) || clsDate::IsDate1EqualDate2(date, date_1))
			&& (clsDate::IsDate1AfterDate2(date_2, date) || clsDate::IsDate1EqualDate2(date_2, date)))

			||

			((clsDate::IsDate1AfterDate2(date, date_2) || clsDate::IsDate1EqualDate2(date, date_2))
				&& (clsDate::IsDate1AfterDate2(date_1, date) || clsDate::IsDate1EqualDate2(date_1, date)));
	}

	static int ReadIntegerNumberBetween(string msg, int from, int to, string error = "")
	{
		bool istrue;
		int num;

		do
		{
			num = ReadIntegerNumber(msg);

			istrue = IsNumberBetween(num, from, to);

			if (!istrue)
			{
				if (error == "")
					cout << "Number is NOT within the range (" << from << ", " << to << ")!!\nTry Again\n\n";
				else
					cout << error << "Try Again\n\n";
			}

		} while (!istrue);

		return num;
	}

	static double ReadDoubleNumberBetween(string msg, double from, double to, string error = "")
	{
		bool istrue;
		double num;

		do
		{
			num = ReadDoubleNumber(msg);

			istrue = IsNumberBetween(num, from, to);

			if (!istrue)
			{
				if (error == "")
					cout << "Number is NOT within the range (" << from << ", " << to << ")!!\nTry Again\n\n";
				else
					cout << error << "Try Again\n\n";
			}

		} while (!istrue);

		return num;
	}

	static bool isValideDate(clsDate date)
	{
		return clsDate::IsValidDate(date);
	}
};

