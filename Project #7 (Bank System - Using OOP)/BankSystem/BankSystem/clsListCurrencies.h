#pragma once

#include "clsUtil.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsScreen.h"

class clsListCurrencies : protected clsScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(30) << Currency.Get_CountryName();
		cout << "|" << left << setw(20) << Currency.Get_CurrencyCode();
		cout << "|" << left << setw(40) << Currency.Get_CurrencyName();
		cout << "|" << left << setw(20) << Currency.Get_CurrencyValue();
		cout << endl;
	}

public:
	static void DisplayCurrenciesList()
	{
		vector<clsCurrency> Currencies = clsCurrency::GetCurrenciesList();

		string Title = "Currencies Info";
		string Subttitle = clsUtil::Design(' ', 2) + to_string(Currencies.size()) + " Currency(s)";

		_DrawScreenHeader(Title, Subttitle);

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 110) << endl;

		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(30) << "Country";
		cout << "|" << left << setw(20) << "Code";
		cout << "|" << left << setw(40) << "Name";
		cout << "|" << left << setw(20) << "Value / 1$";
		cout << endl;

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 110) << endl;

		if (Currencies.empty())
			cout << clsUtil::Tabs(8) << "No Data Available!!!" << endl;
		else
			for (clsCurrency& x : Currencies)
				_PrintCurrencyInfo(x);

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 110) << endl << endl;

	}
};

