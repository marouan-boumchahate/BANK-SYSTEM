#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

class clsShowClientList : protected clsScreen
{
private:
	static const void PrintClientInfo(clsBankClient& Client)
	{
		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(20) << Client.AccountNumber;
		cout << "|" << left << setw(28) << Client.GetFullName();
		cout << "|" << left << setw(20) << Client.Password;
		cout << "|" << left << setw(20) << Client.PhoneNumber;
		cout << "|" << left << setw(20) << Client.Balance;
	}

public:
	static void ClientList()
	{
		vector<clsBankClient> Clients = clsBankClient::GetClientList();

		string Tittle = "List Clients Info";
		string Subtittle = clsUtil::Design(' ', 2) + to_string(Clients.size()) + " Client(s)";

		clsScreen::_DrawScreenHeader(Tittle, Subtittle);

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl;

		cout << clsUtil::Tabs(2);
		cout << "|" << left << setw(20) << "Account Number";
		cout << "|" << left << setw(28) << "Full Name";
		cout << "|" << left << setw(20) << "Password";
		cout << "|" << left << setw(20) << "Phone Number";
		cout << "|" << left << setw(20) << "Balance";

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl;

		if (Clients.empty())
			cout << clsUtil::Tabs(7) << "No Client available!!!" << endl;
		else
		{
			for (clsBankClient& x : Clients)
				PrintClientInfo(x);
		}

		cout << clsUtil::Tabs(2) << clsUtil::Design('-', 100) << endl << endl;
	}

};

