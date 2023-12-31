#pragma once

#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
//#include "Global.h"
#include <iomanip>

class clsLoginScreen : protected clsScreen
{
private:
	static void _Login()
	{
		bool isLoged = true;
		short Trial = 3;

		do
		{

			if (!isLoged)
			{
				cout << endl << clsUtil::Tabs(2) << "Username or Password is wrong!!\n";
				cout << clsUtil::Tabs(2) << "You have " << Trial << " other Trial(s)!!" << endl << endl;
				cout << clsUtil::Tabs(2) << "Try Again\n\n";
			}

			string Username = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Username: ");
			string Password = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Password: ");

			CurrentUser = clsBankUser::find(Username, Password);

			if (CurrentUser.isEmpty())
			{
				if (Trial != 1)
				{
					isLoged = false;
					Trial--;
				}
				else
				{
					cout << endl << endl;
					cout << clsUtil::Tabs(7) << "Your account has been Blocked\n";
					cout << clsUtil::Tabs(8) << "Contact Your admin\n";

					exit(1);
				}
			}
			else
				isLoged = true;

		} while (!isLoged);

		CurrentUser.RegisterLogIn();

		clsMainScreen::MainMenu();

		LoginScreen();
	}

public:
	static void LoginScreen()
	{
		system("cls");

		string Title = "Login Screen";
		_DrawScreenHeader(Title);

		_Login();
	}
};

