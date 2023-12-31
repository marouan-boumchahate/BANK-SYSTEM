#pragma once
class clsTransferScreen : protected clsScreen
{
private:
	static const void _PrintClientInfo(clsBankClient& Client, string Title)
	{
		cout << clsUtil::Design('-', 40) << endl;
		cout << clsUtil::Tabs(3) << Title << endl;
		cout << clsUtil::Design('-', 40) << endl;

		cout << "Account Number:  " << Client.AccountNumber << endl;
		cout << "Full Name     :  " << Client.GetFullName() << endl;
		cout << "Balance       :  " << Client.Balance << endl;

		cout << clsUtil::Design('-', 40) << endl << endl;
	}

public:
	static void Transfer()
	{
		string Title = "Transfer Screen";

		_DrawScreenHeader(Title);

		string AccountNumber = "";
		bool isTrue;


		// Sender Account
		do
		{
			AccountNumber = clsInputValidate::ReadString("Please enter the account number to transfer from: ");

			if (!(isTrue = clsBankClient::isClientExist(AccountNumber)))
				cout << "Client NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankClient Client_From = clsBankClient::find(AccountNumber);

		_PrintClientInfo(Client_From, "Information Card");


		// Receiver Account
		do
		{
			AccountNumber = clsInputValidate::ReadString("Please enter the account number that will receive: ");

			if (!(isTrue = clsBankClient::isClientExist(AccountNumber)))
				cout << "Client NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankClient Client_To = clsBankClient::find(AccountNumber);

		_PrintClientInfo(Client_To, "Information Card");

		// Read Sending Amount

		int Amount = clsInputValidate::ReadIntegerNumberBetween("Enter the amount to be sent: ", 1, Client_From.Balance, "You have expanded your Balance!!\n");

		if(clsUtil::isYes("\nAre you sure you wanna perform this operation: "))
		{
			Client_From.Transfer(Amount, Client_To);

			// Print the New Cards
			system("cls");

			_DrawScreenHeader(Title);

			cout << "The transfer has been done successfuly!!" << endl << endl;

			_PrintClientInfo(Client_From, "New Card");
			_PrintClientInfo(Client_To, "New Card");

			Client_From.RegisterTransfers(Client_To, Amount);

		}
		else
		{
			cout << "\nThe transfer has been done Unsuccessfuly!!!" << endl << endl;
		}
	}
};

