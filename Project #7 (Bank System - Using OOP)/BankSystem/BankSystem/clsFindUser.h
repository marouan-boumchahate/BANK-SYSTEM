#pragma once
class clsFindUser : protected clsScreen
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

public:
	static void FindUser()
	{
		string Title = "Find User";

		clsScreen::_DrawScreenHeader(Title);

		string Username = "";
		bool isTrue;

		do
		{
			Username = clsInputValidate::ReadString("Please enter the username: ");

			if (!(isTrue = clsBankUser::isUserExist(Username)))
				cout << "User NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankUser Client = clsBankUser::find(Username);

		cout << "\nUser has been found Successfuly!!" << endl << endl;
		cout << "Press any key to say its card information...";
		system("pause > 0");

		_PrintUserInfo(Client, Title);
	}
};

