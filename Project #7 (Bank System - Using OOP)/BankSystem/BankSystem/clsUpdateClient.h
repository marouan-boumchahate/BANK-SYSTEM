#pragma once
class clsUpdateClient : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client, string Title)
	{
		system("cls");

		clsScreen::_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(5); cout << clsUtil::Tabs(3) << "Taking Information Page" << endl;
		cout << clsUtil::Tabs(5); cout << clsUtil::Design('-', 50) << endl;

		cout << clsUtil::Tabs(5); Client.FirstName = clsInputValidate::ReadString("Enter a first name: "); cout << endl;
		cout << clsUtil::Tabs(5); Client.LastName = clsInputValidate::ReadString("Enter a last name: "); cout << endl;
		cout << clsUtil::Tabs(5); Client.PhoneNumber = clsInputValidate::ReadString("Enter a phone number: "); cout << endl;
		cout << clsUtil::Tabs(5); Client.Password = clsInputValidate::ReadString("Enter a password: "); cout << endl;
		cout << clsUtil::Tabs(5); Client.Balance = clsInputValidate::ReadDoubleNumber("Enter a balance: "); cout << endl;

		cout << clsUtil::Tabs(5); cout << clsUtil::Design('-', 50) << endl;
	}

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
	static void UpdateClient()
	{
		string Title = "Update Client";

		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = "";
		bool isTrue;

		do
		{
			AccountNumber = clsInputValidate::ReadString("Please enter the account number: ");

			if (!(isTrue = clsBankClient::isClientExist(AccountNumber)))
				cout << "Client NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankClient Client = clsBankClient::find(AccountNumber);

		_ReadClientInfo(Client, Title);

		clsBankClient::enSaveResults SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::svSucceded:
		{
			cout << "\nThe Account has updated successfuly!!" << endl << endl;
			cout << "Press any key to show the new card information...";
			system("pause > 0");

			_PrintClientInfo(Client, Title);
			break;
		}
		case clsBankClient::svFailedEmptyObject:
		{
			cout << "\nError The account has NOT updated because it was empty!!!!" << endl;
			break;
		}
		}
	}
};

