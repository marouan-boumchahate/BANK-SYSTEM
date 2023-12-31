#pragma once

#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransfersHistoryScreen.h"

class clsTransactions : protected clsScreen
{
private:
	enum enTransactionMenuOptions { eDeposit = 1, eWithdraw = 2, eTotalBalance = 3, eTransfer = 4, eTransfersHistory = 5, eMainMenu = 6 };


	static short ReadTransactionMenuOption()
	{
		return clsInputValidate::ReadIntegerNumberBetween((clsUtil::Tabs(5) + "Enter a choice from above (1-6): "), 1, 6);
	}

	static void _GoBackToTheTransactionsMenu()
	{
		cout << clsUtil::Tabs(2) << "Press any key to return to the Transactions menu page... ";
		system("pause > 0");

		TransactionsMenu();
	}

	static void _PerformTransactionMenuOptions(enTransactionMenuOptions option)
	{
		switch (option)
		{
		case enTransactionMenuOptions::eDeposit:
		{
			system("cls");
			_DepositScreen();
			_GoBackToTheTransactionsMenu();
			break;
		}
		case enTransactionMenuOptions::eWithdraw:
		{
			system("cls");
			_WithdrawScreen();
			_GoBackToTheTransactionsMenu();
			break;
		}
		case enTransactionMenuOptions::eTotalBalance:
		{
			system("cls");
			_TotalBalanceScreen();
			_GoBackToTheTransactionsMenu();
			break;
		}
		case enTransactionMenuOptions::eTransfer:
		{
			system("cls");
			_TransferScreen();
			_GoBackToTheTransactionsMenu();
			break;
		}
		case enTransactionMenuOptions::eTransfersHistory:
		{
			system("cls");
			_TransfersHistoryScreen();
			_GoBackToTheTransactionsMenu();
			break;
		}
		case enTransactionMenuOptions::eMainMenu:
		{
			system("cls");
			break;
		}
		}
	}



	static void _DepositScreen()
	{
		clsDepositScreen::Deposit();
	}

	static void _WithdrawScreen()
	{
		clsWithdrawScreen::Withdraw();
	}

	static void _TotalBalanceScreen()
	{
		clsTotalBalancesScreen::DisplayTotalClientsBalances();
	}

	static void _TransferScreen()
	{
		clsTransferScreen::Transfer();
	}

	static void _TransfersHistoryScreen()
	{
		clsTransfersHistoryScreen::TransfersHistoryList();
	}


public:
	static void TransactionsMenu()
	{
		system("cls");

		_DrawScreenHeader("Transaction Screen");

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;
		cout << clsUtil::Tabs(7) << "     Transactions Menu" << endl;
		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		cout << clsUtil::Tabs(6) << "[1] Deposit" << endl;
		cout << clsUtil::Tabs(6) << "[2] Withdraw" << endl;
		cout << clsUtil::Tabs(6) << "[3] Total Balance" << endl;
		cout << clsUtil::Tabs(6) << "[4] Transfer" << endl;
		cout << clsUtil::Tabs(6) << "[5] Transfers History" << endl;
		cout << clsUtil::Tabs(6) << "[6] Main Menu" << endl;

		cout << clsUtil::Tabs(5) << clsUtil::Design('=', 50) << endl;

		_PerformTransactionMenuOptions((enTransactionMenuOptions)ReadTransactionMenuOption());
	}
};

