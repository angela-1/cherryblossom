#include "stdafx.h"




#include "OldDB.h"
#include "pinyin.h"
#include "utils.h"



#include "Dispather.h"

#include "global.h"

Dispatcher::Dispatcher()
{
    
}


Dispatcher::~Dispatcher()
{
}

Dispatcher::Dispatcher(const Dispatcher&)
{

}


Dispatcher& Dispatcher::operator=(const Dispatcher&)
{
    return *this;
}


Dispatcher* Dispatcher::instance = new Dispatcher();
Dispatcher* Dispatcher::GetInstance()
{
    return instance;
}



bool Dispatcher::CheckAccount(LPTSTR tag)
{
    bool isValid = true;

    for each (auto var in account_list)
    {
        if (wcscmp(var.tag, tag) == 0)
        {
            isValid = false;

        }
    }

    return isValid;
}

std::list<AccountItem>* Dispatcher::GetList()
{

    return &account_list;


}

AccountCard * Dispatcher::GetAccountCard()
{
    return &account_item;
}

static int detialcallback(void *NotUsed, int argc, char **argv, char **azColName)
{
    wchar_t tag[MAX_STR_LEN];
    wchar_t group[MAX_STR_LEN];
    wchar_t url[MAX_STR_LEN];
    wchar_t user[MAX_STR_LEN];
    wchar_t password[MAX_STR_LEN];
    wchar_t phone[MAX_STR_LEN];
    wchar_t mail[MAX_STR_LEN];
    wchar_t note[MAX_STR_LEN];
    wchar_t last_mod[MAX_STR_LEN];


    utf8_to_unicode(argv[1], tag);
    utf8_to_unicode(argv[2], group);
    utf8_to_unicode(argv[3], url);
    utf8_to_unicode(argv[4], user);
    utf8_to_unicode(argv[5], password);
    utf8_to_unicode(argv[6], phone);
    utf8_to_unicode(argv[7], mail);
    utf8_to_unicode(argv[8], note);
    utf8_to_unicode(argv[10], last_mod);



    AccountCard* item = Dispatcher::GetInstance()->GetAccountCard();

    lstrcpy(item->tag, tag);
    lstrcpy(item->group, group);
    lstrcpy(item->url, url);
    lstrcpy(item->user, user);
    lstrcpy(item->password, password);
    lstrcpy(item->phone, phone);
    lstrcpy(item->mail, mail);
    lstrcpy(item->note, note);
    lstrcpy(item->last_mod, last_mod);




    return 0;
}

AccountCard * Dispatcher::GetAccount(LPTSTR tag)
{
    OldDB::open_db(g_chr_db_file);

    wchar_t sql[MAX_SQL_LEN];

    wchar_t* ii = L"select * from accounts";
    swprintf_s(sql, L"%s where tag='%s';",
        ii, tag);
    char csql[MAX_SQL_LEN];
    unicode_to_utf8(sql, csql);

    OldDB::exec_sql(csql, detialcallback);


    OldDB::close_db();

    return Dispatcher::GetInstance()->GetAccountCard();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    wchar_t tag[MAX_STR_LEN];
    wchar_t pinyin_tag[MAX_STR_LEN];

    //if (strcmp(argv[0], "") != 0)
    //{
        utf8_to_unicode(argv[0], tag);

        utf8_to_unicode(argv[1], pinyin_tag);


        AccountItem account;
        lstrcpy(account.tag, tag);
        lstrcpy(account.pinyin_tag, pinyin_tag);

        Dispatcher::GetInstance()->GetList()->push_back(account);
        

    return 0;
}


void Dispatcher::MakeAccountList()
{

    OldDB::open_db(g_chr_db_file);




    char* csql = "select tag, pinyin_tag from accounts;";

    OldDB::exec_sql(csql, callback);


    OldDB::close_db();

}


void Dispatcher::ClearAccountList()
{
    account_list.clear();
}

void Dispatcher::RefreshAccountList()
{
    ClearAccountList();
    MakeAccountList();
}

void Dispatcher::AddAccount(LPTSTR* value_array)
{
    TCHAR pinyin_tag[MAX_STR_LEN]; 

    OldDB::open_db(g_chr_db_file);
    wchar_t sql[MAX_SQL_LEN];

    TCHAR py_str[MAX_STR_LEN] = L"";

    Pinyin::get_pinyin_str(value_array[0], py_str);

    lstrcpy(pinyin_tag, py_str);

    TCHAR tmp_str[MAX_STR_LEN] = L"";

    wchar_t* ii = L"insert into accounts (tag, group, url, user, password, phone, mail, note, pinyin_tag) values";

    swprintf_s(sql, L"%s ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
        ii,
        value_array[0],
        value_array[1],
        value_array[2],
        value_array[3],
        value_array[4],
        value_array[5],
        value_array[6],
        value_array[7],
        pinyin_tag);

    char csql[MAX_SQL_LEN];
    unicode_to_utf8(sql, csql);

    OldDB::exec_sql(csql, NULL);



    OldDB::close_db();


    // update account_list
    RefreshAccountList();
}



void Dispatcher::EditAccount(LPTSTR* value_array)
{

    OldDB::open_db(g_chr_db_file);
    wchar_t sql[MAX_SQL_LEN];

    wchar_t* ii = L"update accounts";
    swprintf_s(sql, L"%s set group='%s', url='%s', user='%s', password='%s', phone='%s', mail='%s', note='%s', last_mod=%s where tag='%s';",
        ii,
        value_array[1],
        value_array[2],
        value_array[3],
        value_array[4],
        value_array[5],
        value_array[6],
        value_array[7],
        L"datetime('now','localtime')",
        value_array[0]);

    char csql[MAX_SQL_LEN];

    unicode_to_utf8(sql, csql);

    OldDB::exec_sql(csql, NULL);



    OldDB::close_db();

}

void Dispatcher::DeleteAccount(LPTSTR tag)
{

    OldDB::open_db(g_chr_db_file);
    wchar_t sql[MAX_SQL_LEN];

    wchar_t* ii = L"delete from accounts";
    swprintf_s(sql, L"%s where tag='%s';",
        ii, tag);
    char csql[MAX_SQL_LEN];
    unicode_to_utf8(sql, csql);

    OldDB::exec_sql(csql, NULL);



    OldDB::close_db();


}

