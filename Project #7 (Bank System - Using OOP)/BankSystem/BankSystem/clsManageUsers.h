#pragma once

#include "clsBankUser.h"
#include "clsShowUsersList.h"
#include "clsAddNewUser.h"
#include "clsDeleteUser.h"
#include "clsUpdateUser.h"
#include "clsFindUser.h"

class clsManageUsers : protected clsScreen
{
private:
	enum enManageUsersMenuOptions {
		eShowUserssList = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};


	static short ReadManageUsersMenuOption()
	{
		return clsInputValidate::ReadIntegerNumberBetween((clsUtil::Tabs(5) + "Enter a choice from above (1-6): "), 1, 6);
	}

	static void _GoBackToTheManageUsersMenu()
	{
		cout << clsUtil::Tabs(2) << "Press any key to return to the Manage users menu page... ";
		system("pause > 0");

		ManageUsersMenu();
	}


	static void _PerformMainMenuOptions(enManageUsersMenuOptions option)
	{
		switch (option)
		{
		case enManageUsersMenuOptions::eShowUserssList:
		{
			system("cls");
			_ShowUsersList();
			_GoBackToTheManageUsersMenu();

			break;
		}
		case enManageUsersMenuOptions::eAddNewUser:
		{
			system("cls");
			_AddNewUser();
			_GoBackToTheManageUsersMenu();

			break;
		}
		case enManageUsersMenuOptions::eDeleteUser:
		{
			system("cls");
			_DeleteUser();
			_GoBackToTheManageUsersMenu();

			break;
		}
		case enManageUsersMenuOptions::eUpdateUser:
		{
			system("cls");
			_UpdateUser();
			_GoBackToTheManageUsersMenu();

			break;
		}
		case enManageUsersMenuOptions::eFindUser:
		{
			system("cls");
			_FindUser();
			_GoBackToTheManageUsersMenu();

			break;
		}
		case enManageUsersMenuOptions::eMainMenu:
		{
			system("cls");
			break;
		}
		}
	}


	static void _ShowUsersList()
	{
		clsShowUsersList::UserList();
	}

	static void _AddNewUser()
	{
		clsAddNewUser::AddNewUser();
	}

	static void _DeleteUser()
	{
		clsDeleteUser::DeleteUser();
	}

	static void _UpdateUser()
	{
		clsUpdateUser::UpdateUser();
	}

	static void _FindUser()
	{
		clsFindUser::FindUser();
	}

public:
	static void ManageUsersMenu()
	{
		system("cls");

		_DrawScreenHeader("Manage Users Screen");

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;
		cout << clsUtil::Tabs(7) << "Manage Users Menu" << endl;
		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		cout << clsUtil::Tabs(6) << "[1] Show Users List" << endl;
		cout << clsUtil::Tabs(6) << "[2] Add New User" << endl;
		cout << clsUtil::Tabs(6) << "[3] Delete User" << endl;
		cout << clsUtil::Tabs(6) << "[4] Update User" << endl;
		cout << clsUtil::Tabs(6) << "[5] Find User" << endl;
		cout << clsUtil::Tabs(6) << "[6] Main Menu" << endl;

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		_PerformMainMenuOptions((enManageUsersMenuOptions)ReadManageUsersMenuOption());
	}
};

