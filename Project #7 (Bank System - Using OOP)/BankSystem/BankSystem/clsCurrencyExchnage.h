#pragma once

#include "clsCurrency.h"
#include "clsListCurrencies.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrency.h"
#include "clsCurrencyCalculator.h"

class clsCurrencyExchnage : protected clsScreen
{
private:
	enum enCurrencyExchangeMenu {eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrency = 3, eCurrencyCalculator = 4, eMainMenu = 5};


	static short _ReadCurrencyExchangeOption()
	{
		return clsInputValidate::ReadIntegerNumberBetween(clsUtil::Tabs(5) + "Enter a number of your choice from above (1-5): ", 1, 5);
	}

	static void _GoBackToTheCurrencyExchangeMenu()
	{
		cout << "Press any key to return to the Currency Exchange Menu...";
		system("pause > 0");

		CurrencyExchangeMenu();
	}


	static void _PerformCurrencyExchangeMenuOptions(enCurrencyExchangeMenu Option)
	{
		switch (Option)
		{
		case enCurrencyExchangeMenu::eListCurrencies:
		{
			system("cls");

			_ListCurrencies();
			_GoBackToTheCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchangeMenu::eFindCurrency:
		{
			system("cls");

			_FindCurrencies();
			_GoBackToTheCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchangeMenu::eUpdateCurrency:
		{
			system("cls");

			_UpdateCurrency();
			_GoBackToTheCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchangeMenu::eCurrencyCalculator:
		{
			system("cls");

			_CurrencyCalculator();
			_GoBackToTheCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchangeMenu::eMainMenu:
		{
			return;
		}
		}
	}


	static void _ListCurrencies()
	{
		clsListCurrencies::DisplayCurrenciesList();
	}

	static void _FindCurrencies()
	{
		clsFindCurrency::FindCurrency();
	}

	static void _UpdateCurrency()
	{
		clsUpdateCurrency::UpdateCurrency();
	}

	static void _CurrencyCalculator()
	{
		clsCurrencyCalculator::CurrencyCalculator();
	}


public:
	static void CurrencyExchangeMenu()
	{
		system("cls");

		string Title = "Currency Exchange";

		_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;
		cout << clsUtil::Tabs(7) << "Currency Exchange Menu" << endl;
		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		cout << clsUtil::Tabs(6) << "[1] List Currencies" << endl;
		cout << clsUtil::Tabs(6) << "[2] Find Currency" << endl;
		cout << clsUtil::Tabs(6) << "[3] Update Currency Value" << endl;
		cout << clsUtil::Tabs(6) << "[4] Currency Calculator" << endl;
		cout << clsUtil::Tabs(6) << "[5] Main Menu" << endl;

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		_PerformCurrencyExchangeMenuOptions((enCurrencyExchangeMenu)_ReadCurrencyExchangeOption());
	}
};

