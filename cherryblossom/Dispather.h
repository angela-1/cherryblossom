#pragma once

#include <list>
#include "Model.h"




#define MAX_SQL_LEN 256
#define MAX_DBPATH_LEN 256
#define MAX_ITEM_LEN 128


typedef struct account_item
{
	wchar_t tag[MAX_ITEM_LEN];
	wchar_t pyshort[MAX_ITEM_LEN];
	wchar_t pyfull[MAX_ITEM_LEN];

} AccountItem;



class Dispatcher
{
private:
	Dispatcher();


	static Dispatcher* instance;
	Dispatcher(const Dispatcher&);
	Dispatcher& operator=(const Dispatcher&);

	std::list<AccountItem> account_list;


public:
	
	~Dispatcher();

	std::list<AccountItem>* GetList();

	static Dispatcher* GetInstance();

	void MakeAccountList();
	void ClearAccountList();


	bool CheckAccount(LPTSTR tag); // check exist

};

