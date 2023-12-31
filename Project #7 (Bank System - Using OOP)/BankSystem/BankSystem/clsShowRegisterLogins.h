#pragma once
class clsShowRegisterLogins : protected clsScreen
{
private:
	static const void _PrintLoginInfo(clsBankUser::stRegisterLoginData& login)
	{

		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(30) << login.date;
		cout << "|" << left << setw(25) << login.username;
		cout << "|" << left << setw(25) << login.password;
		cout << "|" << left << setw(25) << login.permissions;
		cout << endl;
	}

public:
	static void LoginsList()
	{
		vector<clsBankUser::stRegisterLoginData> logins = clsBankUser::GetRegisterLoginLines();

		string Tittle = "List Register Logins";
		string Subtittle = clsUtil::Design(' ', 2) + to_string(logins.size()) + " Login(s)";

		clsScreen::_DrawScreenHeader(Tittle, Subtittle);

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl;

		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(30) << "Date";
		cout << "|" << left << setw(25) << "Username";
		cout << "|" << left << setw(25) << "Password";
		cout << "|" << left << setw(25) << "Permissions";

		cout << endl << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl;

		if (logins.empty())
			cout << clsUtil::Tabs(7) << "No User available!!!" << endl;
		else
		{
			for (clsBankUser::stRegisterLoginData& x : logins)
			{
				_PrintLoginInfo(x);
			}
		}

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl << endl;
	}
};

