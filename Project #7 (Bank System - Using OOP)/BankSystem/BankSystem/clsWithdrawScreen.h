#pragma once
class clsWithdrawScreen : protected clsScreen
{
private:
	static const void _PrintClientInfo(clsBankClient& Client, string Title)
	{
		system("cls");

		clsScreen::_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Tabs(3) << "Information Card" << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl;

		cout << clsUtil::Tabs(6) << "Account Number:  " << Client.AccountNumber << endl;
		cout << clsUtil::Tabs(6) << "Password      :  " << Client.Password << endl;
		cout << clsUtil::Tabs(6) << "First Name    :  " << Client.FirstName << endl;
		cout << clsUtil::Tabs(6) << "Last Name     :  " << Client.LastName << endl;
		cout << clsUtil::Tabs(6) << "Phone Number  :  " << Client.PhoneNumber << endl;
		cout << clsUtil::Tabs(6) << "Balance       :  " << Client.Balance << endl;

		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl << endl;
	}


public:
	static void Withdraw()
	{
		string Title = "Withdraw Screen";

		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = "";
		bool isTrue;

		do
		{
			AccountNumber = clsInputValidate::ReadString("Please enter an account number: ");

			if (!(isTrue = clsBankClient::isClientExist(AccountNumber)))
				cout << "Client NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankClient Client = clsBankClient::find(AccountNumber);

		_PrintClientInfo(Client, Title);

		Client.Withdraw(clsInputValidate::ReadIntegerNumberBetween("Enter the amount to withdraw (Multiple of 5): ", 0, Client.Balance, "The amount is greater than your balance\n"));

		cout << "\nThe withdraw has been done successfuly\n";

		cout << "\nYour new balance is: " << Client.Balance << endl << endl;
	}
};

