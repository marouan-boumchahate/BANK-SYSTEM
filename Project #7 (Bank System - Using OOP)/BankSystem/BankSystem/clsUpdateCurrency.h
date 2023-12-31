#pragma once

#include "clsScreen.h"
#include "clsCurrency.h"

class clsUpdateCurrency : protected clsScreen
{
private:
	enum enFindingType { eByCode = 1, eByName = 2 };

	static void _PrintingCurrencyCard(clsCurrency Currency)
	{
		cout << clsUtil::Design('_', 50) << endl << endl;

		cout << "Country   : " << Currency.Get_CountryName() << endl;
		cout << "Code      : " << Currency.Get_CurrencyCode() << endl;
		cout << "Name      : " << Currency.Get_CurrencyName() << endl;
		cout << "Value (1$): " << Currency.Get_CurrencyValue() << endl;

		cout << clsUtil::Design('_', 50) << endl << endl;
	}

	static short _ReadFindingTypeOption()
	{
		return clsInputValidate::ReadIntegerNumberBetween(clsUtil::Tabs(2) + "Updating By: [1] Code    [2] Name: ", 1, 2);
	}

	static void _PerformingChoice(enFindingType Type)
	{
		switch (Type)
		{
		case enFindingType::eByCode:
		{
			clsCurrency Currency = clsCurrency::ReturnTheEmptyCurrency();
			bool isEmpty = false;

			do
			{
				do
				{

					string Code = clsInputValidate::ReadString("\n\nEnter The Currency code you wanna find: ");
					Currency = clsCurrency::FindByCurrencyCode(Code);

					isEmpty = Currency.isEmpty();

					if (isEmpty = Currency.isEmpty())
						cout << "\nCurrency Code NOT found\nTryAgain";
					else
					{
						cout << clsUtil::Tabs(3) << "Currency Card" << endl;
						_PrintingCurrencyCard(Currency);

						Currency.Set_CurrencyValue(clsInputValidate::ReadDoubleNumberBetween("\n\nEnter the update value of the currency against a Dollar (1$): ", 0, 10000));
					}

				} while (isEmpty);

				cout << endl << endl << clsUtil::Tabs(2) << "Update Currency Card" << endl;
				_PrintingCurrencyCard(Currency);

			} while (clsUtil::isYes("Do You Wanna Updating More Currencies (Y/N): "));

			cout << endl << endl;

			break;

		}
		case enFindingType::eByName:
		{
			clsCurrency Currency = clsCurrency::ReturnTheEmptyCurrency();
			bool isEmpty = false;

			do
			{
				do
				{

					string Country = clsInputValidate::ReadString("\n\nEnter The Country that you wanna update its currency: ");
					Currency = clsCurrency::FindByCountryName(Country);

					isEmpty = Currency.isEmpty();

					if (isEmpty = Currency.isEmpty())
						cout << "\nCountry NOT found\nTryAgain";
					else
					{
						cout << clsUtil::Tabs(3) << "Currency Card" << endl;
						_PrintingCurrencyCard(Currency);

						Currency.Set_CurrencyValue(clsInputValidate::ReadDoubleNumberBetween("\n\nEnter the update value of the currency against a Dollar (1$): ", 0, 10000));
					}

				} while (isEmpty);

				cout << endl << endl  << clsUtil::Tabs(2) << "Update Currency Card" << endl;
				_PrintingCurrencyCard(Currency);

			} while (clsUtil::isYes("Do You Wanna Updating More Currencies (Y/N): "));

			cout << endl << endl;

			break;
		}
		}
	}

public:
	static void UpdateCurrency()
	{
		string Title = "Upadte Currency";

		_DrawScreenHeader(Title);

		_PerformingChoice((enFindingType) _ReadFindingTypeOption());
	}
};

