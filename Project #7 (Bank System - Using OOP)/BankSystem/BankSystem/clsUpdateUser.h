#pragma once
class clsUpdateUser : protected clsScreen
{
private:
	static const void _PrintUserInfo(clsBankUser& User, string Title)
	{
		system("cls");

		_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(7) << " User Information Card" << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl;

		cout << clsUtil::Tabs(7) << "   Username: " << User.Username << endl;
		cout << clsUtil::Tabs(7) << "   Password: " << User.Password << endl;
		cout << clsUtil::Tabs(7) << "   Permission: " << User.Permissions << endl;

		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl << endl;
	}

	static short _AskForPermission()
	{
		short sum = 0;

		if (clsUtil::isYes(clsUtil::Tabs(5) + "Will the user get all the permissions (Y/N): "))
			return -1;

		cout << endl;

		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Show Clients (Y/N): "))
			sum += clsBankUser::eListClients;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Add Clients (Y/N): "))
			sum += clsBankUser::eAddClient;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Delete Clients (Y/N): "))
			sum += clsBankUser::eDeleteClient;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Update Clients (Y/N): "))
			sum += clsBankUser::eUpdateClient;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Search for Clients (Y/N): "))
			sum += clsBankUser::eFindClient;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Do Clients' Transactions (Y/N): "))
			sum += clsBankUser::eTransactions;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Manage Users (Y/N): "))
			sum += clsBankUser::eManageUsers;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Show Register Logins (Y/N): "))
			sum += clsBankUser::eRegisterLogin;
		if (clsUtil::isYes(clsUtil::Tabs(5) + "Can Get into Currency Exchange (Y/N): "))
			sum += clsBankUser::eCurrencyExchange;

		return (sum == 511 ? -1 : sum);
	}

	static void _ReadUserInfo(clsBankUser& User, string Title)
	{
		system("cls");

		clsScreen::_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(5); cout << clsUtil::Tabs(3) << "Taking Information Page" << endl;
		cout << clsUtil::Tabs(5); cout << clsUtil::Design('-', 50) << endl;

		cout << clsUtil::Tabs(5); cout << "Please enter an username: " << User.Username << endl;
		cout << clsUtil::Tabs(5); User.Password = clsInputValidate::ReadString("Enter a password: "); cout << endl;
		cout << endl << clsUtil::Tabs(5); cout << "Get The User Permissions:" << endl << endl;
		User.Permissions = _AskForPermission();

		cout << clsUtil::Tabs(5); cout << clsUtil::Design('-', 50) << endl;
	}

public:
	static void UpdateUser()
	{
		string Title = "Update User";

		clsScreen::_DrawScreenHeader(Title);

		string Username = "";
		bool isTrue;

		do
		{
			Username = clsInputValidate::ReadString("Please enter the username: ");

			if (!(isTrue = clsBankUser::isUserExist(Username)))
				cout << "User NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankUser User = clsBankUser::find(Username);

		_ReadUserInfo(User, Title);

		clsBankUser::enSaveResults SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsBankClient::svSucceded:
		{
			cout << "\nThe User has updated successfuly!!" << endl << endl;
			cout << "Press any key to show the new card information...";
			system("pause > 0");

			_PrintUserInfo(User, Title);

			break;
		}
		case clsBankClient::svFailedEmptyObject:
		{
			cout << "\nError The user has NOT updated because it was empty!!!!" << endl;
			break;
		}
		}
	}
};

