#include "stdafx.h"
#include "Exporter.h"
#include <list>
#include <fstream>
#include <iostream>
#include "utils.h"
#include <commdlg.h>




std::string Exporter::assembleAccount(Account account)
{
	std::string str;
	std::string result = "";

	char value[MAX_STR_STRING] = "";
	char label[MAX_STR_STRING] = "";

	unicode_to_utf8(account.tag, value);
	str = value;
	unicode_to_utf8(L"标签：", label);
	result += label + str + "\n";
	strcpy_s(label, "");
	strcpy_s(value, "");
	


	unicode_to_utf8(account.category, value);
	str = value;
	unicode_to_utf8(L"类别：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.url, value);
	str = value;
	unicode_to_utf8(L"链接：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.user, value);
	str = value;
	unicode_to_utf8(L"用户名：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.password, value);
	str = value;
	unicode_to_utf8(L"密码：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.phone, value);
	str = value;
	unicode_to_utf8(L"电话：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.mail, value);
	str = value;
	unicode_to_utf8(L"邮箱：", label);
	result += label + str + "\n";

	unicode_to_utf8(account.note, value);
	str = value;
	unicode_to_utf8(L"备注：", label);
	result += label + str + "\n";


	unicode_to_utf8(account.last_mod, value);
	str = value;
	unicode_to_utf8(L"最后修改：", label);
	result += label + str + "\n";

	result += "--------------------------------------------------\n\n";

	return result;
}

std::wstring Exporter::getSavePath()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	TCHAR filename[MAX_PATH] = { 0 };
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"文本文档(*.txt)\0*.txt\0所有文件(*.*)\0*.*\0\0";
	ofn.lpstrDefExt = L"txt";
	ofn.lpstrTitle = L"保存到";
	ofn.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.FlagsEx = 0;
	ofn.lStructSize = sizeof(OPENFILENAME);  // No OFN_ENABLEHOOK  
	ofn.hwndOwner = NULL;

	std::wstring filePath = L"";
	if (GetSaveFileName(&ofn))
	{
		filePath = filename;
	}
	return filePath;
}


Exporter::Exporter()
{
}


Exporter::~Exporter()
{
}



void Exporter::Export(std::list<Account>& account_list, std::string format)
{

	std::wstring filePath = getSavePath();
	std::ofstream out(filePath);
	if (out.is_open())
	{
		for each (auto account in account_list) {
			out << assembleAccount(account);
		}
		out.close();
	}
}
