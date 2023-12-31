#pragma once
class clsFindCurrency : protected clsScreen
{
private:
	enum enFindingType {eByCode = 1, eByName = 2};

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
		return clsInputValidate::ReadIntegerNumberBetween(clsUtil::Tabs(2) + "Finding By: [1] Code    [2] Name: ", 1, 2);
	}

	static void _PerformingChoices(enFindingType Type)
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
					if (isEmpty)
						cout << "\nCurrency Code NOT found\nTryAgain";

					string Code = clsInputValidate::ReadString("\n\nEnter The Currency code you wanna find: ");
					Currency = clsCurrency::FindByCurrencyCode(Code);

					isEmpty = Currency.isEmpty();

				} while (isEmpty);

				_PrintingCurrencyCard(Currency);

			} while (clsUtil::isYes("Do You Wanna Finding More Currencies (Y/N): "));
			
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
					if (isEmpty)
						cout << "\Country NOT found\nTryAgain";

					string Country = clsInputValidate::ReadString("\n\nEnter The Country you wanna find its currency: ");
					Currency = clsCurrency::FindByCountryName(Country);

					isEmpty = Currency.isEmpty();

				} while (isEmpty);

				_PrintingCurrencyCard(Currency);

			} while (clsUtil::isYes("Do You Wanna Finding More Currencies (Y/N): "));

			cout << endl << endl;

			break;
		}
		}
	}

public:
	static void FindCurrency()
	{
		string Title = "Finding Currency";

		_DrawScreenHeader(Title);

		_PerformingChoices((enFindingType)_ReadFindingTypeOption());
	}
};

