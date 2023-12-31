#pragma once
class clsDeleteUser : clsScreen
{
private:
	static const void _PrintUserInfo(clsBankUser& User, string Title)
	{
		system("cls");

		clsScreen::_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Tabs(3) << "User Information Card" << endl;
		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl;

		cout << clsUtil::Tabs(6) << "Username       :  " << User.Username << endl;
		cout << clsUtil::Tabs(6) << "Password       :  " << User.Password << endl;
		cout << clsUtil::Tabs(6) << "Permissions    :  " << User.Permissions << endl;

		cout << clsUtil::Tabs(6) << clsUtil::Design('-', 40) << endl << endl;
	}


public:
	static void DeleteUser()
	{
		string Title = "Delete User";

		clsScreen::_DrawScreenHeader(Title);

		string Username = "";
		bool isTrue;

		do
		{
			Username = clsInputValidate::ReadString("Please enter the username: ");

			if (!(isTrue = clsBankUser::isUserExist(Username)))
				cout << "User NOT found!!\nTry Again\n\n";

		} while (!isTrue);

		clsBankUser User = clsBankUser::GetDeleteUserObject(Username);

		if (Username == "admin")
		{
			cout << "\nYou Cannot delete the admin!!!" << endl << endl;
		}
		else
		{
			_PrintUserInfo(User, Title);

			if (clsUtil::isYes("Are you sure you wanna delete this client (Y/N): "))
			{
				clsBankUser::enSaveResults SaveResult = User.Save();

				switch (SaveResult)
				{
				case clsBankUser::svSucceded:
				{
					cout << "\nThe User has been Deleted successfuly!!" << endl << endl;
					break;
				}
				case clsBankUser::svFailedEmptyObject:
				{
					cout << "\nError The User has NOT updated because it was empty!!!!" << endl << endl;
					break;
				}
				case clsBankUser::svFailedAccountNumberExist:
				{
					cout << "\nError The User is NOT exist!!!!" << endl << endl;
					break;
				}
				}
			}
			else
				cout << "\nThe User Unsuccessfuly deleted!!" << endl << endl;
		}

	}
};

