#include "stdafx.h"
#include "Dispather.h"
#include "convert.h"
#include "PinYin.h"


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
	wchar_t tag[MAX_ITEM_LEN];
	wchar_t category[MAX_ITEM_LEN];
	wchar_t url[MAX_ITEM_LEN];
	wchar_t user[MAX_ITEM_LEN];
	wchar_t password[MAX_ITEM_LEN];
	wchar_t phone[MAX_ITEM_LEN];
	wchar_t mail[MAX_ITEM_LEN];
	wchar_t note[MAX_ITEM_LEN];
	wchar_t lastmod[MAX_ITEM_LEN];


	UTF8ToUnicode(argv[1], tag);
	UTF8ToUnicode(argv[2], category);
	UTF8ToUnicode(argv[3], url);
	UTF8ToUnicode(argv[4], user);
	UTF8ToUnicode(argv[5], password);
	UTF8ToUnicode(argv[6], phone);
	UTF8ToUnicode(argv[7], mail);
	UTF8ToUnicode(argv[8], note);
	UTF8ToUnicode(argv[9], lastmod);



	AccountCard* item = Dispatcher::GetInstance()->GetAccountCard();

	lstrcpy(item->tag, tag);
	lstrcpy(item->category, category);
	lstrcpy(item->url, url);
	lstrcpy(item->user, user);
	lstrcpy(item->password, password);
	lstrcpy(item->phone, phone);
	lstrcpy(item->mail, mail);
	lstrcpy(item->note, note);
	lstrcpy(item->lastmod, lastmod);




	return 0;
}

AccountCard * Dispatcher::GetAccount(LPTSTR tag)
{
	Model::open_db();

	wchar_t sql[MAX_SQL_LEN];

	wchar_t* ii = L"select * from accounts";
	swprintf_s(sql, L"%s where tag='%s';",
		ii, tag);
	char csql[MAX_SQL_LEN];
	UnicodeToUTF8(sql, csql);

	Model::exec_sql(csql, detialcallback);


	Model::close_db();

	return Dispatcher::GetInstance()->GetAccountCard();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	wchar_t tag[MAX_ITEM_LEN];
	wchar_t pyshort[MAX_ITEM_LEN];
	wchar_t pyfull[MAX_ITEM_LEN];


	UTF8ToUnicode(argv[0], tag);

	UTF8ToUnicode(argv[1], pyshort);
	UTF8ToUnicode(argv[2], pyfull);

	AccountItem account;
	lstrcpy(account.tag, tag);
	lstrcpy(account.pyshort, pyshort);
	lstrcpy(account.pyfull, pyfull);

	Dispatcher::GetInstance()->GetList()->push_back(account);
	//(Dispatcher::GetInstance()->GetList()).push_back(account);


	return 0;
}


void Dispatcher::MakeAccountList()
{

	Model::open_db();

	int row = 0, column = 0;
	char **result = NULL;


	char* csql = "select tag, pyshort, pyfull from accounts;";

	Model::exec_sql(csql, callback);


	Model::close_db();

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



	TCHAR pyshort[MAX_ITEM_LEN];
	TCHAR pyfull[MAX_ITEM_LEN];


	Model::open_db();
	wchar_t sql[MAX_SQL_LEN];



	TCHAR py_str[2][MAX_ITEM_LEN] = { L"",L"" };

	PinYin::GetPYStr(value_array[0], py_str);

	lstrcpy(pyshort, py_str[0]);
	lstrcpy(pyfull, py_str[1]);


	wchar_t* ii = L"insert into accounts (tag, category, url, user, password, phone, mail, note, pyshort, pyfull) values";
	swprintf_s(sql, L"%s ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
		ii,
		value_array[0],
		value_array[1],
		value_array[2],
		value_array[3],
		value_array[4],
		value_array[5],
		value_array[6],
		value_array[7],
		pyshort,
		pyfull);

	char csql[MAX_SQL_LEN];
	UnicodeToUTF8(sql, csql);

	Model::exec_sql(csql, NULL);



	Model::close_db();


	// update account_list
	RefreshAccountList();
}



void Dispatcher::EditAccount(LPTSTR* value_array)
{

	Model::open_db();
	wchar_t sql[MAX_SQL_LEN];

	wchar_t* ii = L"update accounts";
	swprintf_s(sql, L"%s set category='%s', url='%s', user='%s', password='%s', phone='%s', mail='%s', note='%s', lastmod=%s where tag='%s';",
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

	UnicodeToUTF8(sql, csql);

	Model::exec_sql(csql, NULL);



	Model::close_db();

}

void Dispatcher::DeleteAccount(LPTSTR tag)
{

	Model::open_db();
	wchar_t sql[MAX_SQL_LEN];

	wchar_t* ii = L"delete from accounts";
	swprintf_s(sql, L"%s where tag='%s';",
		ii, tag);
	char csql[MAX_SQL_LEN];
	UnicodeToUTF8(sql, csql);

	Model::exec_sql(csql, NULL);



	Model::close_db();


}
