#include "stdafx.h"
#include "convert.h"


void ANSIToUnicode(char *str, wchar_t *end)
{
	wchar_t *wstr;
	int len;
	len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wstr = new wchar_t[len + 1];
	memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
	wcscpy_s(end, len, wstr);

	delete[] wstr;
}


void UTF8ToUnicode(char *str, wchar_t *end)
{
	wchar_t *wstr;
	int len;
	len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wstr = new wchar_t[len + 1];
	memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
	wcscpy_s(end, len, wstr);

	delete[] wstr;


}

void UnicodeToUTF8(wchar_t * str, char *end)
{
	char*     cstr;
	int    len;
	// wide char to multi char
	len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	cstr = new char[len + 1];
	memset((void*)cstr, 0, sizeof(char) * (len + 1));
	WideCharToMultiByte(CP_UTF8, 0, str, -1, cstr, len, NULL, NULL);
	strcpy_s(end, len, cstr);
	delete[] cstr;

}

void UnicodeToANSI(wchar_t * str, char *end)
{
	char*     cstr;
	int    len;
	// wide char to multi char
	len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	cstr = new char[len + 1];
	memset((void*)cstr, 0, sizeof(char) * (len + 1));
	WideCharToMultiByte(CP_ACP, 0, str, -1, cstr, len, NULL, NULL);
	strcpy_s(end, len, cstr);
	delete[] cstr;
}