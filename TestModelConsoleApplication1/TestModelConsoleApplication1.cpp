// TestModelConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "account.h"


int _tmain(int argc, _TCHAR* argv[])
{

  Account a = Account{};

  Account& b = a.find_by_tag(L"dsaf");


  lstrcpy(a.user, L"23j@qq.com");

  lstrcpy(b.password, L"23j@qq.com");

  a.update();

  OutputDebugString(a.mail);
  OutputDebugString(b.password);

  Account c = Account{};

  lstrcpy(c.tag, L"你枯");
  lstrcpy(c.mail, L"厅在q.com");

  c.save();


  c.del();

  system("pause");

	return 0;
}

