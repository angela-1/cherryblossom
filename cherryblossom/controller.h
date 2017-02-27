/*
  This is the header file of controller class.

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


#ifndef CHERRYBLOSSOM_CONTROLLER_H_
#define CHERRYBLOSSOM_CONTROLLER_H_

#include "stdafx.h"
#include <list>

#include "account.h"


class Controller {
 private:
   Controller();
   ~Controller();

   static Controller* instance_;
   Controller(const Controller&);
   Controller& operator=(const Controller&);

   std::list<AccountItem> account_list_;
   Account account_;




public:
  // get singleton of instance and the account of this
  static Controller* GetInstance();
  
  // get method of account_list
  std::list<AccountItem>* GetAccountList();
  // get method of account
  Account* GetAccount();
  void MakeAccountList();
  void ClearAccountList();
  void RefreshAccountList();
  bool CheckAccount(LPTSTR tag); // check exist

  void AddAccount(LPTSTR* value_array);
  void UpdateAccount(LPTSTR* value_array);
  void DelAccount(LPTSTR tag);
  void ReadAccount(LPTSTR tag);

  // for fuzzy complete
  std::list<AccountItem> hit_list;
  std::list<AccountItem> company_list;
};

#endif  // CHERRYBLOSSOM_CONTROLLER_H_