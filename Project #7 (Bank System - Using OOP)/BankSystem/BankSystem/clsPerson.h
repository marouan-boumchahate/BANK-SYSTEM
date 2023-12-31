#pragma once

#include <iostream>

using namespace std;

class clsPerson
{
protected:
	string _FirstName;
	string _LastName;
	string _PhoneNumber;

public:
	// Constructor
	clsPerson(string FirstName, string LastName, string PhoneNumber)
	{
		SetFirstName(FirstName);
		SetLastName(LastName);
		SetPhoneNumber(PhoneNumber);
	}

	// Setters
	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}
	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}
	void SetPhoneNumber(string PhoneNumber)
	{
		_PhoneNumber = PhoneNumber;
	}

	// Getters
	string GetFirstName()
	{
		return _FirstName;
	}
	string GetLastName()
	{
		return _LastName;
	}
	string GetPhoneNumber()
	{
		return _PhoneNumber;
	}

	// Set & Get using Equal
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;
	__declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) string PhoneNumber;
};

