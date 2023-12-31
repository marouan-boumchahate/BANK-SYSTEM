#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsShowClientList.h"
#include "clsAddNewClient.h"
#include "clsDeleteClient.h"
#include "clsUpdateClient.h"
#include "clsFindClient.h"
#include "clsTransactions.h"
#include "clsManageUsers.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsShowRegisterLogins.h"
#include "clsCurrencyExchnage.h"
#include <iomanip>

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions { eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
	                         eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7,
	                         eRegisterLogins = 8, eCurrencyExchange = 9, eLogout = 10 };

	static short ReadMenuOption()
	{
		return clsInputValidate::ReadIntegerNumberBetween((clsUtil::Tabs(5) + "Enter a choice from above (1-10): "), 1, 10);
	}

	static void _GoBackToTheMainMenu()
	{
		cout << clsUtil::Tabs(2) << "Press any key to return to the main menu page... ";
		system("pause > 0");

		MainMenu();
	}


	static void _PerformMainMenuOptions(enMainMenuOptions option)
	{
		switch (option)
		{
		case enMainMenuOptions::eShowClientsList:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eListClients))
				_ShowClientList();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eAddNewClient:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eAddClient))
				_AddNewClient();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eDeleteClient:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eDeleteClient))
				_DeleteClient();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eUpdateClient:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eUpdateClient))
				_UpdateClient();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eFindClient:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eFindClient))
				_FindClient();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eTransactions:
		{
			system("cls");

			if (!_isAceessRight(clsBankUser::enPermissions::eTransactions))
				_GoBackToTheMainMenu();
				
			_Transactions();
			MainMenu();
			break;
		}
		case enMainMenuOptions::eManageUsers:
		{
			system("cls");

			if (!_isAceessRight(clsBankUser::enPermissions::eManageUsers))
				_GoBackToTheMainMenu();

			_ManageUsers();
			MainMenu();
			break;
		}
		case enMainMenuOptions::eRegisterLogins:
		{
			system("cls");

			if (_isAceessRight(clsBankUser::enPermissions::eRegisterLogin))
				_ShowRegsiterLogins();

			_GoBackToTheMainMenu();
			break;
		}
		case enMainMenuOptions::eCurrencyExchange:
		{
			system("cls");

			if (!_isAceessRight(clsBankUser::enPermissions::eCurrencyExchange))
				_GoBackToTheMainMenu();

			_CurrencyEchange();
			MainMenu();
			break;
		}
		case enMainMenuOptions::eLogout:
		{
			system("cls");
			_Logout();

			break;
		}
		}
	}


	static void _ShowClientList()
	{
		clsShowClientList::ClientList();
	}

	static void _AddNewClient()
	{
		clsAddNewClient::AddNewClient();
	}

	static void _DeleteClient()
	{
		clsDeleteClient::DeleteClient();
	}

	static void _UpdateClient()
	{
		clsUpdateClient::UpdateClient();
	}

	static void _FindClient()
	{
		clsFindClient::FindClient();
	}

	static void _Transactions()
	{
		clsTransactions::TransactionsMenu();
	}

	static void _ManageUsers()
	{
		clsManageUsers::ManageUsersMenu();
	}

	static void _ShowRegsiterLogins()
	{
		clsShowRegisterLogins::LoginsList();
	}

	static void _CurrencyEchange()
	{
		clsCurrencyExchnage::CurrencyExchangeMenu();
	}

	static void _Logout()
	{
		CurrentUser = clsBankUser::find("", "");
	}

public:
	static void MainMenu()
	{
		system("cls");

		_DrawScreenHeader("Main Screen");

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;
		cout << clsUtil::Tabs(7) << "     Main Menu" << endl;
		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		cout << clsUtil::Tabs(6) << "[1]  Show Clients List" << endl;
		cout << clsUtil::Tabs(6) << "[2]  Add New Client" << endl;
		cout << clsUtil::Tabs(6) << "[3]  Delete Client" << endl;
		cout << clsUtil::Tabs(6) << "[4]  Update Client" << endl;
		cout << clsUtil::Tabs(6) << "[5]  Find Client" << endl;
		cout << clsUtil::Tabs(6) << "[6]  Transactions" << endl;
		cout << clsUtil::Tabs(6) << "[7]  Manage Users" << endl;
		cout << clsUtil::Tabs(6) << "[8]  Show Register Logins" << endl;
		cout << clsUtil::Tabs(6) << "[9]  Currency Exchange" << endl;
		cout << clsUtil::Tabs(6) << "[10] Logout" << endl;

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		_PerformMainMenuOptions((enMainMenuOptions)ReadMenuOption());
	}
};

