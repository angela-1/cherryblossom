#pragma once

#include <list>



typedef struct account_item
{
	wchar_t tag[MAX_ITEM_LEN];
	wchar_t pyshort[MAX_ITEM_LEN];
	wchar_t pyfull[MAX_ITEM_LEN];

} AccountItem;


typedef struct account_card
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

} AccountCard;





class Dispatcher
{
private:
	Dispatcher();


	static Dispatcher* instance;
	Dispatcher(const Dispatcher&);
	Dispatcher& operator=(const Dispatcher&);

	std::list<AccountItem> account_list;
	AccountCard account_item;



public:
	
	~Dispatcher();

	std::list<AccountItem>* GetList();
	AccountCard* GetAccountCard();

	static Dispatcher* GetInstance();

	void MakeAccountList();
	void ClearAccountList();
	void RefreshAccountList();

	bool CheckAccount(LPTSTR tag); // check exist
	AccountCard* GetAccount(LPTSTR tag);
	

	void AddAccount(LPTSTR* value_array);
	void EditAccount(LPTSTR* value_array);
	void DeleteAccount(LPTSTR tag);

	// for complete
	std::list<AccountItem> hit_list;
	std::list<AccountItem> company_list;


	
	

};

