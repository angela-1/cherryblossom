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
	unicode_to_utf8(L"��ǩ��", label);
	result += label + str + "\n";
	strcpy_s(label, "");
	strcpy_s(value, "");
	


	unicode_to_utf8(account.category, value);
	str = value;
	unicode_to_utf8(L"���", label);
	result += label + str + "\n";

	unicode_to_utf8(account.url, value);
	str = value;
	unicode_to_utf8(L"���ӣ�", label);
	result += label + str + "\n";

	unicode_to_utf8(account.user, value);
	str = value;
	unicode_to_utf8(L"�û�����", label);
	result += label + str + "\n";

	unicode_to_utf8(account.password, value);
	str = value;
	unicode_to_utf8(L"���룺", label);
	result += label + str + "\n";

	unicode_to_utf8(account.phone, value);
	str = value;
	unicode_to_utf8(L"�绰��", label);
	result += label + str + "\n";

	unicode_to_utf8(account.mail, value);
	str = value;
	unicode_to_utf8(L"���䣺", label);
	result += label + str + "\n";

	unicode_to_utf8(account.note, value);
	str = value;
	unicode_to_utf8(L"��ע��", label);
	result += label + str + "\n";


	unicode_to_utf8(account.last_mod, value);
	str = value;
	unicode_to_utf8(L"����޸ģ�", label);
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
	ofn.lpstrFilter = L"�ı��ĵ�(*.txt)\0*.txt\0�����ļ�(*.*)\0*.*\0\0";
	ofn.lpstrDefExt = L"txt";
	ofn.lpstrTitle = L"���浽";
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
