#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

string Currency_File = "Currencies.txt";

class clsCurrency
{
private:
	enum enMode { eFullMode = 1, eEmptyMode = 2 };

	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	float  _CurrencyValue;
	enMode _Mode;

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

	static clsCurrency _ConvertLineToCurrencyObject(vector<string> Data)
	{
		return clsCurrency(enMode::eFullMode, Data[0], Data[1], Data[2], stof(Data[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "|#|")
	{
		string line = "";

		line += (Currency.Get_CountryName() + Seperator);
		line += (Currency.Get_CurrencyCode() + Seperator);
		line += (Currency.Get_CurrencyName() + Seperator);
		line += to_string(Currency.Get_CurrencyValue());

		return line;
	}

	static vector<clsCurrency> _LoadDataFromFile()
	{
		fstream File;
		string line;

		vector<clsCurrency> Data;

		File.open(Currency_File, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if(line != "")
					Data.push_back(_ConvertLineToCurrencyObject(clsString::Split(line, "|#|")));
			}

			File.close();
		}

		return Data;
	}

	static void _SaveDataToFile(vector<clsCurrency>& vCurrencies)
	{
		fstream File;

		File.open(Currency_File, ios::out);

		if (File.is_open())
		{
			for (clsCurrency& x : vCurrencies)
				File << _ConvertCurrencyObjectToLine(x) << endl;
		}

		File.close();
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies;

		vCurrencies = _LoadDataFromFile();

		for (clsCurrency& x : vCurrencies)
		{
			if (x.Get_CurrencyCode() == Get_CurrencyCode())
			{
				x = *this;
				_SaveDataToFile(vCurrencies);
				return;
			}
		}
	}


public:
	// Constructors
	clsCurrency(enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float CurrencyValue)
	{
		_CountryName = CountryName;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_CurrencyValue = CurrencyValue;
		_Mode = Mode;
	}

	// Setters
	void Set_CurrencyValue(float CurrencyValue)
	{
		_CurrencyValue = CurrencyValue;
		_Update();
	}

	// Getters
	string Get_CountryName()
	{
		return _CountryName;
	}
	string Get_CurrencyCode()
	{
		return _CurrencyCode;
	}
	string Get_CurrencyName()
	{
		return _CurrencyName;
	}
	float Get_CurrencyValue()
	{
		return _CurrencyValue;
	}
	enMode Get_Mode()
	{
		return _Mode;
	}

	// Functions
	bool isEmpty()
	{
		return (_Mode == enMode::eEmptyMode);
	}

	static clsCurrency FindByCurrencyCode(string CountryCode)
	{
		CountryCode = clsString::UpperAllString(CountryCode);

		fstream file;
		string line;

		file.open(Currency_File, ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(clsString::Split(line, "|#|"));

				if (currency.Get_CurrencyCode() == CountryCode)
				{
					file.close();
					return currency;
				}
			}

			file.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountryName(string CountryName)
	{
		CountryName = clsString::UpperAllString(CountryName);

		fstream file;
		string line;

		file.open(Currency_File, ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(clsString::Split(line, "|#|"));

				if (clsString::UpperAllString(currency.Get_CountryName()) == CountryName)
				{
					file.close();
					return currency;
				}
			}

			file.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string CurrencyCode)
	{
		clsCurrency C = clsCurrency::FindByCurrencyCode(CurrencyCode);

		return (!C.isEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadDataFromFile();
	}

	static clsCurrency ReturnTheEmptyCurrency()
	{
		return _GetEmptyCurrencyObject();
	}
};

