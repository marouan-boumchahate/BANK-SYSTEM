#pragma once
class clsTransfersHistoryScreen : protected clsScreen
{
private:
	static const void _PrintTransfersInfo(clsBankClient::stTransferHistory& info)
	{
		cout << endl;
		cout << "|" << left << setw(25) << info.Date;
		cout << "|" << left << setw(15) << info.Sender_Account;
		cout << "|" << left << setw(15) << info.Receiver_Account;
		cout << "|" << left << setw(15) << info.Amount_Sent;
		cout << "|" << left << setw(20) << info.New_Sender_Amount;
		cout << "|" << left << setw(20) << info.New_Receiver_Amount;
		cout << "|" << left << setw(10) << info.User;
		cout << endl;
	}

public:
	static void TransfersHistoryList()
	{
		vector<clsBankClient::stTransferHistory> transfers = clsBankClient::GetTransfersList();

		string Tittle = "List Transfers History";
		string Subtittle = clsUtil::Design(' ', 2) + to_string(transfers.size()) + " Transfer(s)";

		clsScreen::_DrawScreenHeader(Tittle, Subtittle);

		cout << clsUtil::Design('-', 125) << endl << endl;

		cout << "|" << left << setw(25) << "Date";
		cout << "|" << left << setw(15) << "Sender";
		cout << "|" << left << setw(15) << "Receiver";
		cout << "|" << left << setw(15) << "Amount";
		cout << "|" << left << setw(20) << "Sender Balance";
		cout << "|" << left << setw(20) << "Receiver Balance";
		cout << "|" << left << setw(10) << "User";

		cout << endl << clsUtil::Design('-', 125) << endl;

		if (transfers.empty())
			cout << clsUtil::Tabs(9) << "No User available!!!" << endl;
		else
		{
			for (clsBankClient::stTransferHistory& x : transfers)
			{
				_PrintTransfersInfo(x);
			}
		}

		cout << clsUtil::Design('-', 125) << endl << endl;
	}
};

