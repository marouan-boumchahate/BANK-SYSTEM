#pragma once

class clsCurrencyCalculator : protected clsScreen
{
private:
	static void _PrintingOperation(string Code_From, string Code_To, float Amount, float Result)
	{
		cout << clsUtil::Design('_', 38) << endl << endl;

		cout << clsUtil::Tabs(2) << Code_From << "\t---->\t" << Code_To << endl;

		cout << clsUtil::Design('_', 38) << endl << endl;

		cout << clsUtil::Tabs(2) << Amount / Amount << "  \t---->\t" << Result / Amount << endl << endl;

		cout << clsUtil::Tabs(2) << Amount << "\t---->\t" << Result << endl;

		cout << clsUtil::Design('_', 38) << endl << endl << endl;

	}

	static bool _CurrencyExist(string name, clsCurrency& Currency)
	{
		Currency = clsCurrency::FindByCurrencyCode(name);

		if (!Currency.isEmpty())
			return true;

		Currency = clsCurrency::FindByCountryName(name);

		if (!Currency.isEmpty())
			return true;

		return false;
	} 

	static float _ConvertingTheAmount(clsCurrency Currency_From, clsCurrency Currency_To, float Amount)
	{
		float Result = 0;

		Result = Amount / Currency_From.Get_CurrencyValue();
		Result *= Currency_To.Get_CurrencyValue();

		return Result;
	}

	static void PerformTheCalculator()
	{
		system("cls");

		_DrawScreenHeader("Currency Calculator");

		string name = "";
		bool isExist;

		clsCurrency Currency_From = clsCurrency::ReturnTheEmptyCurrency();
		clsCurrency Currency_To = clsCurrency::ReturnTheEmptyCurrency();

		// Currency From
		do
		{
			name = clsInputValidate::ReadString("Enter Currency Code/Country you wanna convert from: ");

			if (!(isExist = _CurrencyExist(name, Currency_From)))
				cout << "Currency Code/Country NOT found\nTry Again\n\n";

		} while (!isExist);

		// Currency To
		do
		{
			name = clsInputValidate::ReadString("Enter Currency Code/Country you wanna convert to: ");

			if (!(isExist = _CurrencyExist(name, Currency_To)))
				cout << "Currency Code/Country NOT found\nTry Again\n\n";

		} while (!isExist);

		// Amount To Convert
		float Amount = clsInputValidate::ReadDoubleNumberBetween("\nEnter the amount you wanna convert: ", 0.1, 3402823466);

		// Converting Result
		float Result = _ConvertingTheAmount(Currency_From, Currency_To, Amount);

		// Printing Results
		_PrintingOperation(Currency_From.Get_CurrencyCode(), Currency_To.Get_CurrencyCode(), Amount, Result);
	}

public:
	static void CurrencyCalculator()
	{
		do
		{
			PerformTheCalculator();

		} while (clsUtil::isYes("\nDo you wanna do more calculating (Y/N): "));

		cout << endl << endl;
	}
};

