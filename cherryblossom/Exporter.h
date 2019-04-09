#include <string>
#include "account.h"
#pragma once
class Exporter
{
private:
	std::string assembleAccount(Account account);
	std::wstring getSavePath();

public:
	Exporter();
	~Exporter();

	void Export(std::list<Account>& account_list, std::string format);
};

