#pragma once
class clsDeleteClient : protected clsScreen
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
	static void DeleteClient()
	{
		string Title = "Delete Client";

		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = "";
		bool isTrue;

		do
		{
			AccountNumber = clsInputValidate::ReadString("Please enter an account number: ");

			if (!(isTrue = clsBankClient::isClientExist(AccountNumber)))
				cout << "Client NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankClient Client = clsBankClient::GetDeleteClientObject(AccountNumber);

		_PrintClientInfo(Client, Title);

		if (clsUtil::isYes("Are you sure you wanna delete this client (Y/N): "))
		{
			clsBankClient::enSaveResults SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::svSucceded:
			{
				cout << "\nThe Account has been Deleted successfuly!!" << endl << endl;
				break;
			}
			case clsBankClient::svFailedEmptyObject:
			{
				cout << "\nError The account has NOT updated because it was empty!!!!" << endl << endl;
				break;
			}
			case clsBankClient::svFailedAccountNumberExist:
			{
				cout << "\nError The account is NOT exist!!!!" << endl << endl;
				break;
			}
			}
		}
		else
			cout << "\nThe Account Unsuccessfuly deleted!!" << endl << endl;

	}
};

