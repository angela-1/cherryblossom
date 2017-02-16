

/*
  This is the header file of account object.

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



#include "model.h"



class Account : public Model {
 private:
  static int account_callback(void *para, int argc, 
                              char **argv, char **azColName);

 public:
  Account ();
  ~Account ();

  wchar_t tag[MAX_STR_LEN];
  wchar_t group[MAX_STR_LEN];
  wchar_t url[MAX_STR_LEN];
  wchar_t user[MAX_STR_LEN];
  wchar_t password[MAX_STR_LEN];
  wchar_t phone[MAX_STR_LEN];
  wchar_t mail[MAX_STR_LEN];
  wchar_t note[MAX_STR_LEN];
  wchar_t last_mod[MAX_STR_LEN];


  Account* find_by_tag(wchar_t* tag);


};




