#pragma once
class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void PrintClientBalanceInfo(clsBankClient& Client)
	{
		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << Client.AccountNumber;
		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << Client.GetFullName();
		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << Client.Balance << endl;
	}

public:
	static void DisplayTotalClientsBalances()
	{
		vector<clsBankClient> Clients = clsBankClient::GetClientList();

		string Title = "Total Balances Screen";
		string Subtitle = "    " + to_string(Clients.size()) + " Client(s)";

		_DrawScreenHeader(Title, Subtitle);

		cout << clsUtil::Tabs(3) << clsUtil::Design('-', 100) << endl;

		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << "Account Number";
		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << "Full Name";
		cout << clsUtil::Tabs(3) << "|" << left << setw(30) << "Balance" << endl;

		cout << clsUtil::Tabs(3) << clsUtil::Design('-', 100) << endl;

		if (Clients.empty())
			cout << "No Client available!!!" << endl;
		else
		{
			for (clsBankClient& x : Clients)
				PrintClientBalanceInfo(x);
		}

		cout << clsUtil::Tabs(3) << clsUtil::Design('-', 100) << endl << endl;

		cout << clsUtil::Tabs(7) << "Total Balances is: " << clsBankClient::GetTotalBalance() << endl;
		cout << clsUtil::Tabs(4) << clsUtil::NumberToText((unsigned int)clsBankClient::GetTotalBalance()) << endl << endl;

	}
};

