// TestModelConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "account.h"


int _tmain(int argc, _TCHAR* argv[])
{

  Account a = Account{};

  Account& b = a.find_by_tag(L"Ҫ");

  lstrcpy(a.mail, L"23j@qq.com");

  lstrcpy(b.password, L"23j@qq.com");

  OutputDebugString(a.mail);
  OutputDebugString(b.password);
  system("pause");

	return 0;
}

