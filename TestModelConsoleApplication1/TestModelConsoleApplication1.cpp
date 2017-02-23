// TestModelConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "account.h"
#include "controller.h"

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

  std::list<AccountItem> d;

  Account::find_all(&d);

  for each (auto ac in d) {
    OutputDebugString(ac.tag);
    OutputDebugString(ac.pinyin_tag);
  }



  // test controller

  Controller* ep = Controller::get_instance();
  ep->make_account_list();

  ep->read_account(L"dsaf");
  ep->get_account();

  bool fb = ep->check_account(L"dsaf");

  bool gb = ep->check_account(L"你在妹");

  system("pause");

	return 0;
}

