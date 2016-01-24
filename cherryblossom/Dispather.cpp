#include "stdafx.h"
#include "Dispather.h"
#include "convert.h"


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
	return false;
}

std::list<AccountItem>* Dispatcher::GetList()
{
	return &account_list;
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