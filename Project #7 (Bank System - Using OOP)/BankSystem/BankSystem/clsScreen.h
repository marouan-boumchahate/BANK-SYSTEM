#pragma once

#include <iostream>
#include <string>
#include "clsBankUser.h"
#include "clsUtil.h"
#include "Global.h"
#include "clsDate.h"


class clsScreen
{
protected:
	static void _DrawScreenHeader(string Header, string Subtittle = "")
	{
		cout << clsUtil::Tabs(4) << clsUtil::Design('_', 70) << endl << endl;
		cout << clsUtil::Tabs(4) << clsUtil::Tabs(5) << Header << endl;
		if(Subtittle != "")
			cout << clsUtil::Tabs(4) << clsUtil::Tabs(5) << Subtittle << endl;

		cout << clsUtil::Tabs(4) << clsUtil::Design('_', 70) << endl << endl;

		string Username = CurrentUser.Username;
		clsDate Date = clsDate();

		cout << clsUtil::Tabs(7) << "   User: " << CurrentUser.Username << endl;
		cout << clsUtil::Tabs(7) << "   Date: " << clsDate::DateToString(clsDate()) << endl << endl;
	}

	static bool _isAceessRight(clsBankUser::enPermissions Permission)
	{
		if (CurrentUser.HasPermission(Permission))
			return true;
		else
		{
			cout << clsUtil::Tabs(4) << clsUtil::Design('_', 70) << endl << endl;
			cout << clsUtil::Tabs(6) << "Access Denied!!! Contact your admin" << endl;
			cout << clsUtil::Tabs(4) << clsUtil::Design('_', 70) << endl << endl << endl;

			return false;
		}
	}
};

