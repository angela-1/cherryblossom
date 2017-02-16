﻿

/*
  This is the header file of account.

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
#include "account.h"
#include "global.h"
#include "utils.h"
#include "pinyin.h"


Account::Account() {}

Account::~Account() {}


int Account::account_callback(void *para, int argc, char **argv, char **azColName) {
  Account* a = (Account*)para;
  utf8_to_unicode(argv[1], a->tag);
  utf8_to_unicode(argv[2], a->category);
  utf8_to_unicode(argv[3], a->url);
  utf8_to_unicode(argv[4], a->user);
  utf8_to_unicode(argv[5], a->password);
  utf8_to_unicode(argv[6], a->phone);
  utf8_to_unicode(argv[7], a->mail);
  utf8_to_unicode(argv[8], a->note);
  utf8_to_unicode(argv[10], a->last_mod);
  return 0;
}

Account& Account::find_by_tag(wchar_t* tag) {
  Model::open_db(g_chr_db_file);
  wchar_t sql[MAX_SQL_LEN];
  wchar_t* ii = L"select * from accounts";
  swprintf_s(sql, L"%s where tag='%s';",
             ii, tag);
  char csql[MAX_SQL_LEN];
  unicode_to_utf8(sql, csql);

  Model::exec_sql(csql, account_callback, this);
  Model::close_db();
  return *this;
}

Account& Account::save() {
  TCHAR pinyin_tag[MAX_STR_LEN];
  Model::open_db(g_chr_db_file);
  wchar_t sql[MAX_SQL_LEN];
  TCHAR py_str[MAX_STR_LEN] = L"";

  Pinyin::get_pinyin_str(tag, py_str);

  lstrcpy(pinyin_tag, py_str);

  TCHAR tmp_str[MAX_STR_LEN] = L"";

  wchar_t* ii = L"insert into accounts (tag, category, url, user, \
password, phone, mail, note, pinyin_tag) values";

  swprintf_s(sql, L"%s ('%s', '%s', '%s', '%s', \
'%s', '%s', '%s', '%s', '%s');",
    ii,
    tag,
    category,
    url,
    user,
    password,
    phone,
    mail,
    note,
    pinyin_tag);

  char csql[MAX_SQL_LEN];
  unicode_to_utf8(sql, csql);

  Model::exec_sql(csql, NULL, this);

  Model::close_db();

  return *this;

}

Account& Account::update() {
  Model::open_db(g_chr_db_file);
  wchar_t sql[MAX_SQL_LEN];

  wchar_t* ii = L"update accounts";
  swprintf_s(sql, L"%s set category='%s', url='%s', user='%s', \
password='%s', phone='%s', mail='%s', note='%s', last_mod=%s where tag='%s';",
    ii,
    category,
    url,
    user,
    password,
    phone,
    mail,
    note,
    L"datetime('now','localtime')",
    tag);

  char csql[MAX_SQL_LEN];
  unicode_to_utf8(sql, csql);

  Model::exec_sql(csql, NULL, this);
  Model::close_db();
  return *this;
}

int Account::del() {

  Model::open_db(g_chr_db_file);
  wchar_t sql[MAX_SQL_LEN];

  wchar_t* ii = L"delete from accounts";
  swprintf_s(sql, L"%s where tag='%s';",
    ii, tag);
  char csql[MAX_SQL_LEN];
  unicode_to_utf8(sql, csql);

  Model::exec_sql(csql, NULL, NULL);
  Model::close_db();
  return 0;
}

