#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <string>
#include <fstream>

const string user_file = "Users.txt";

class clsBankUser : public clsPerson
{
public:
	struct stRegisterLoginData
	{
		string date;
		string username;
		string password;
		short permissions;
	};

private:
	enum enMode { eEmptyMode = 0, eUpdateMode = 1, eAddNewMode = 2, eDeleteMode = 3 };
	enMode _Mode;

	string _Password;
	string _Username;
	short _Permissions;

	string _PrepareDataLine(string Seperator = "|#|")
	{
		string Data = "";

		Data += (clsDate::GetSystemDateTimeString() + Seperator);
		Data += (Username + Seperator);
		Data += (Password + Seperator);
		Data += to_string(Permissions);

		return Data;
	}

	static clsBankUser _ConvertLineToClientObject(string line, string Seperator = "|#|")
	{
		vector<string> Data = clsString::Split(line, Seperator);

		return clsBankUser(enMode::eUpdateMode, "", "", "", Data[0], clsUtil::DecryptText(Data[1], 391), stoi(Data[2]));
	}

	static string _ConvertClientObjectToLine(clsBankUser User, string Seperator = "|#|")
	{
		return (User.Username + Seperator + clsUtil::EncryptText(User.Password, 391) + Seperator + to_string(User.Permissions));
	}

	static stRegisterLoginData _ConvertLineToRegisterStructure(string line, string Seperator = "|#|")
	{
		stRegisterLoginData info;
		vector<string> data = clsString::Split(line, Seperator);

		info.date = data[0];
		info.username = data[1];
		info.password = data[2];
		info.permissions = stoi(data[3]);

		return info;
	}

	static vector<clsBankUser> _LoadDataFromFile()
	{
		vector<clsBankUser> vUsers;
		string line;

		fstream File;
		File.open(user_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankUser Client = _ConvertLineToClientObject(line);
					vUsers.push_back(Client);
				}
			}
			File.close();
		}
		return vUsers;
	}

	static void _SaveDataToFile(vector<clsBankUser> Users, string Seperator = "|#|")
	{
		fstream File;

		File.open(user_file, ios::out);

		if (File.is_open())
		{
			for (clsBankUser& x : Users)
				File << _ConvertClientObjectToLine(x, Seperator) << endl;
		}

		File.close();
	}

	static clsBankUser _GetEmptyUser()
	{
		return clsBankUser(enMode::eEmptyMode, "", "", "", "", "", 0);
	}

	void _Update()
	{
		vector<clsBankUser> Users = _LoadDataFromFile();

		for (clsBankUser& x : Users)
			if (x.GetUsername() == GetUsername())
			{
				x = *this;
				break;
			}

		_SaveDataToFile(Users);
	}

	void _AddNew()
	{
		AddDataToFile(_LoadDataFromFile());
	}

	void _Delete()
	{
		vector<clsBankUser> Users = _LoadDataFromFile();

		for (short i = 0; i < Users.size(); i++)
		{
			if (Users.at(i).GetUsername() == GetUsername())
			{
				Users.erase(Users.begin() + i);
				break;
			}
		}

		_SaveDataToFile(Users);
	}

	void AddDataToFile(vector<clsBankUser> Users)
	{
		Users.push_back(*this);

		_SaveDataToFile(Users);
	}

public:
	// Public Enums
	enum enSaveResults { svFailedEmptyObject = 0, svSucceded = 1, svFailedAccountNumberExist = 2 };
	enum enPermissions { eAll = -1, eListClients = 1, eAddClient = 2, eDeleteClient = 4, eUpdateClient = 8, eFindClient = 16,
	                     eTransactions = 32, eManageUsers = 64, eCurrencyExchange = 128, eRegisterLogin = 256};

	// Constructor
	clsBankUser(enMode Mode, string FirstName, string LastName, string PhoneNumber, string UserName, string Password, short Permissions)
		: clsPerson(FirstName, LastName, PhoneNumber)
	{
		_Mode = Mode;
		_Username = UserName;
		_Password = Password;
		_Permissions = Permissions;
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
	void SetUsername(string Username)
	{
		_Username = Username;
	}
	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	// Getters
	string GetPassword()
	{
		return _Password;
	}
	string GetUsername()
	{
		return _Username;
	}
	short GetPermissions()
	{
		return _Permissions;
	}
	enMode GetMode()
	{
		return _Mode;
	}

	// Set & Get using Equal
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;
	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;
	__declspec(property(get = GetMode, put = SetMode)) enMode Mode;


	// Functions
	bool isEmpty()
	{
		return (_Mode == enMode::eEmptyMode);
	}

	static clsBankUser find(string Username)
	{
		string line;

		fstream File;
		File.open(user_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankUser User = _ConvertLineToClientObject(line);

					if (User.Username == Username)
					{
						File.close();
						return User;
					}
				}
			}

			File.close();
		}

		return _GetEmptyUser();

	}

	static clsBankUser find(string Username, string Psw)
	{
		string line;

		fstream File;
		File.open(user_file, ios::in);

		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line != "")
				{
					clsBankUser User = _ConvertLineToClientObject(line);

					if (User.Username == Username && User.Password == Psw)
					{
						File.close();
						return User;
					}
				}
			}

			File.close();
		}

		return _GetEmptyUser();

	}

	static bool isUserExist(string Username)
	{
		clsBankUser User = find(Username);

		return (!User.isEmpty());
	}

	bool isUserExist()
	{
		clsBankUser User = find(this->_Username);

		return (!User.isEmpty());
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::eEmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}
		case enMode::eUpdateMode:
		{
			_Update();
			return enSaveResults::svSucceded;
		}
		case enMode::eAddNewMode:
		{
			_AddNew();
			return enSaveResults::svSucceded;
		}
		case enMode::eDeleteMode:
		{
			_Delete();
			*this = _GetEmptyUser();
			return enSaveResults::svSucceded;
		}
		}
	}

	static clsBankUser GetAddNewUserObject(string Username)
	{
		return clsBankUser(enMode::eAddNewMode, "", "", "", Username, "", 0);
	}

	static clsBankUser GetDeleteUserObject(string Username)
	{
		clsBankUser user = clsBankUser::find(Username);
		user.Mode = enMode::eDeleteMode;

		return user;
	}

	static vector<clsBankUser> GetUserList()
	{
		return _LoadDataFromFile();
	}

	bool HasPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((this->Permissions & Permission) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn(string Seperator = "|#|")
	{
		fstream File;

		File.open("registerusers.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << _PrepareDataLine(Seperator) << endl;
		}

		File.close();
	}

	static vector<stRegisterLoginData> GetRegisterLoginLines(string Seperator = "|#|")
	{
		fstream File;
		string Data;

		stRegisterLoginData Login;
		vector<stRegisterLoginData> Logins;

		File.open("registerusers.txt", ios::in);

		if (File.is_open())
		{
			while (getline(File, Data))
			{
				Login = _ConvertLineToRegisterStructure(Data);
				Logins.push_back(Login);
			}
		}

		File.close();

		return Logins;
	}
};
