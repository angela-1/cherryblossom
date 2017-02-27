
/*
  This is the implementation file of controller class.

  Copyright © 2016-2017 Angela

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files(the “Software”), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions :

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.

*/


#include "stdafx.h"
#include "controller.h"

Controller* Controller::instance_ = nullptr;


Controller::Controller() {}

Controller::~Controller() {}

Controller::Controller(const Controller&) {}


Controller& Controller::operator=(const Controller&) {
  return *this;
}



Controller* Controller::GetInstance() {
  if (instance_ == nullptr) {
    static Controller instance;
    instance_ = &instance;
  }
  return instance_;

}

std::list<AccountItem>* Controller::GetAccountList() {
  return &account_list_;
}

Account* Controller::GetAccount() {
  return &account_;
}

void Controller::MakeAccountList() {
  Account::FindAll(&account_list_);
}

void Controller::ClearAccountList() {
  account_list_.clear();
}

void Controller::RefreshAccountList() {
  ClearAccountList();
  MakeAccountList();
}

bool Controller::CheckAccount(LPTSTR tag) {
  bool exists = true;

  for each (auto account in account_list_) {
    if (wcscmp(account.tag, tag) == 0) {
      exists = false;
    }
  }
  return exists;
}

void Controller::AddAccount(LPTSTR* value_array) {
  Account new_account = Account{};
  lstrcpy(new_account.tag, value_array[0]);
  lstrcpy(new_account.category, value_array[1]);
  lstrcpy(new_account.url, value_array[2]);
  lstrcpy(new_account.user, value_array[3]);
  lstrcpy(new_account.password, value_array[4]);
  lstrcpy(new_account.phone, value_array[5]);
  lstrcpy(new_account.mail, value_array[6]);
  lstrcpy(new_account.note, value_array[7]);
  new_account.Save();
}

void Controller::UpdateAccount(LPTSTR* value_array) {
  Account account = Account{};
  account.FindByTag(value_array[0]);

  lstrcpy(account.category, value_array[1]);
  lstrcpy(account.url, value_array[2]);
  lstrcpy(account.user, value_array[3]);
  lstrcpy(account.password, value_array[4]);
  lstrcpy(account.phone, value_array[5]);
  lstrcpy(account.mail, value_array[6]);
  lstrcpy(account.note, value_array[7]);

  account.Update();
}

void Controller::DelAccount(LPTSTR tag) {
  Account account = Account{};
  account.FindByTag(tag);
  account.Del();
}

void Controller::ReadAccount(LPTSTR tag) {
  account_ = Account{};
  account_.FindByTag(tag);

}


