#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <string>
#include "Global.h"
#include <fstream>

const string client_file = "Clients.txt";

class clsBankClient : public clsPerson
{
public:
	struct stTransferHistory
	{
		string Date;
		string Sender_Account;
		string Receiver_Account;
		int Amount_Sent;
		double New_Sender_Amount;
		double New_Receiver_Amount;
		string User;
	};

private:
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2, DeleteMode = 3};
	enMode _Mode;

	string _Password;
	string _AccountNumber;
	double _Balance;

	string _PrepareLine(clsBankClient Receiver, int Amount, string Seperator = "|#|")
	{
		string line = "";

		line += (clsDate::GetSystemDateTimeString() + Seperator);
		line += (AccountNumber + Seperator);
		line += (Receiver.AccountNumber + Seperator);
		line += (to_string(Amount) + Seperator);
		line += (to_string(Balance) + Seperator);
		line += (to_string(Receiver.Balance) + Seperator);
		line += CurrentUser.Username;

		return line;
	}

	static clsBankClient _ConvertLineToClientObject(string line, string Seperator = "|#|")
	{
		vector<string> Data = clsString::Split(line, Seperator);

		return clsBankClient(enMode::UpdateMode, Data[2], Data[3], Data[4], clsUtil::DecryptText(Data[1], 442), Data[0], stod(Data[5]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "|#|")
	{
		return (Client.AccountNumber + Seperator +
			    clsUtil::EncryptText(Client.Password, 442) + Seperator +
			    Client.FirstName + Seperator +
			    Client.LastName + Seperator +
			    Client.PhoneNumber + Seperator +
			    to_string(Client.Balance));
	}

	static stTransferHistory _ConvertLineToTransferHistoryStructure(string line, string Seperator = "|#|")
	{
		vector<string> SeperateData = clsString::Split(line, Seperator);

		stTransferHistory Info;

		Info.Date = SeperateData[0];
		Info.Sender_Account = SeperateData[1];
		Info.Receiver_Account = SeperateData[2];
		Info.Amount_Sent = stoi(SeperateData[3]);
		Info.New_Sender_Amount = stod(SeperateData[4]);
		Info.New_Receiver_Amount = stod(SeperateData[5]);
		Info.User = SeperateData[6];

		return Info;
	}

	static vector<clsBankClient> _LoadDataFromFile()
	{
		vector<clsBankClient> vClients;
		string line;

		fstream File;
		File.open(client_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankClient Client = _ConvertLineToClientObject(line);
					vClients.push_back(Client);
				}
			}
			File.close();
		}
		return vClients;
	}

	static void _SaveDataToFile(vector<clsBankClient> Clients, string Seperator = "|#|")
	{
		fstream File;

		File.open(client_file, ios::out);

		if (File.is_open())
		{
			for (clsBankClient& x : Clients)
				File << _ConvertClientObjectToLine(x, Seperator) << endl;
		}

		File.close();
	}

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", 0);
	}

	void _Update()
	{
		vector<clsBankClient> Clients = _LoadDataFromFile();

		for(clsBankClient& x : Clients)
			if (x.GetAccountNumber() == GetAccountNumber())
			{
				x = *this;
				break;
			}

		_SaveDataToFile(Clients);
	}

	void _AddNew()
	{
		AddDataToFile(_LoadDataFromFile());
	}

	void _Delete()
	{
		vector<clsBankClient> Clients = _LoadDataFromFile();

		for (short i = 0; i < Clients.size(); i++)
		{
			if (Clients.at(i).GetAccountNumber() == GetAccountNumber())
			{
				Clients.erase(Clients.begin() + i);
				break;
			}
		}

		_SaveDataToFile(Clients);
	}

	void AddDataToFile(vector<clsBankClient> Clients)
	{
		Clients.push_back(*this);

		_SaveDataToFile(Clients);
	}

public:
	// Public Enums
	enum enSaveResults { svFailedEmptyObject = 0, svSucceded = 1, svFailedAccountNumberExist = 2 };

	// Constructor
	clsBankClient(enMode Mode, string FirstName, string LastName, string PhoneNumber, string Password, string AccountNumber, double Balance)
		: clsPerson(FirstName, LastName, PhoneNumber)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_Password = Password;
		_Balance = Balance;
	}

	// Setters
	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	void SetAccountNumber(string AccountNumber)
	{
		_AccountNumber = AccountNumber;
	}
	void SetBalance(double Balance)
	{
		_Balance = Balance;
	}

	// Getters
	string GetPassword()
	{
		return _Password;
	}
	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	double GetBalance()
	{
		return _Balance;
	}
	enMode GetMode()
	{
		return _Mode;
	}

	string GetFullName()
	{
		return (GetFirstName() + " " + GetLastName());
	}

	// Set & Get using Equal
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	__declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;
	__declspec(property(get = GetBalance, put = SetBalance)) double Balance;
	__declspec(property(get = GetMode, put = SetMode)) enMode Mode;


	// Functions
	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient find(string AccNumber)
	{
		string line;

		fstream File;
		File.open(client_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankClient Client = _ConvertLineToClientObject(line);

					if (Client.AccountNumber == AccNumber)
					{
						File.close();
						return Client;
					}
				}
			}

			File.close();
		}

		return _GetEmptyClient();

	}

	static clsBankClient find(string AccNumber, string Psw)
	{
		string line;

		fstream File;
		File.open(client_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankClient Client = _ConvertLineToClientObject(line);

					if (Client.AccountNumber == AccNumber && Client.Password == Psw)
					{
						File.close();
						return Client;
					}
				}
			}

			File.close();
		}

		return _GetEmptyClient();

	}

	static bool isClientExist(string AccNumber)
	{
		clsBankClient Client = find(AccNumber);

		return (!Client.isEmpty());
	}

	bool isClientExist()
	{
		clsBankClient Client = find(this->_AccountNumber);

		return (!Client.isEmpty());
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::isClientExist(AccountNumber))
				return enSaveResults::svFailedAccountNumberExist;
			else
			{
				_AddNew();
				return enSaveResults::svSucceded;
			}
		}
		case enMode::DeleteMode:
		{
			if (!clsBankClient::isClientExist(AccountNumber))
				return enSaveResults::svFailedAccountNumberExist;
			else
			{
				_Delete();
				*this = _GetEmptyClient();
				return enSaveResults::svSucceded;
			}
		}
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, 0);
	}

	static clsBankClient GetDeleteClientObject(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::find(AccountNumber);
		Client.Mode = enMode::DeleteMode;

		return Client;
	}

	static vector<clsBankClient> GetClientList()
	{
		return _LoadDataFromFile();
	}

	static double GetTotalBalance()
	{
		vector<clsBankClient> Clients = clsBankClient::GetClientList();

		double total = 0;

		for (clsBankClient& x : Clients)
			total += x.Balance;

		return total;
	}

	void Deposit(int Amount)
	{
		Balance += Amount;
		Save();
	}

	void Withdraw(int Amount)
	{
		Balance -= Amount;
		Save();
	}

	void Transfer(int Amount, clsBankClient& Receiver)
	{
		this->Withdraw(Amount);

		Receiver.Deposit(Amount);
	}

	void RegisterTransfers(clsBankClient Receiver, int Amount, string Seperator = "|#|")
	{
		fstream File;

		File.open("Transfers.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << _PrepareLine(Receiver, Amount) << endl;
		}

		File.close();
	}

	static vector<stTransferHistory> GetTransfersList()
	{
		fstream File;
		string line;

		vector<stTransferHistory> Transfers;

		File.open("Transfers.txt", ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if(line != "")
					Transfers.push_back(_ConvertLineToTransferHistoryStructure(line));
			}

			File.close();
		}

		return Transfers;
	}
};