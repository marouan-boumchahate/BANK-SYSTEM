#pragma once
class clsShowUsersList : protected clsScreen
{
private:
	static const void _PrintUserInfo(clsBankUser& User)
	{
		cout << clsUtil::Tabs(3);
		cout << "|" << left << setw(30) << User.Username;
		cout << "|" << left << setw(30) << User.Password;
		cout << "|" << left << setw(30) << User.Permissions;
		cout << endl;
	}

public:
	static void UserList()
	{
		vector<clsBankUser> Users = clsBankUser::GetUserList();

		string Tittle = "List Users Info";
		string Subtittle = clsUtil::Design(' ', 2) + to_string(Users.size()) + " User(s)";

		clsScreen::_DrawScreenHeader(Tittle, Subtittle);

		cout << clsUtil::Tabs(3) << clsUtil::Design('-', 80) << endl;

		cout << clsUtil::Tabs(3);
		cout << "|" << left << setw(30) << "Username";
		cout << "|" << left << setw(30) << "Password";
		cout << "|" << left << setw(30) << "Permissions";

		cout << endl << clsUtil::Tabs(3) << clsUtil::Design('-', 80) << endl;

		if (Users.empty())
			cout << clsUtil::Tabs(8) << "No User available!!!" << endl;
		else
		{
			for (clsBankUser& x : Users)
				_PrintUserInfo(x);
		}

		cout << clsUtil::Tabs(3) << clsUtil::Design('-', 80) << endl << endl;
	}
};

