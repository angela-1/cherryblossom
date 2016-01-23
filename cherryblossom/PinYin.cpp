#include "stdafx.h"
#include "PinYin.h"
//#include "global.h"
//#include "Model.h"


using namespace std;


#define MAX_STR_STRING 200

PinYin::PinYin()
{
}


PinYin::~PinYin()
{
}




static void UTF8ToUnicode(char *str, wchar_t *end)
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

static void UnicodeToUTF8(wchar_t * str, char *end)
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




TCHAR** PinYin::GetPYChar(TCHAR* tag, ifstream* dict, TCHAR py_char[2][200])
{

	char buf[MAX_STR_STRING];

	//TCHAR tmppy[2][MAX_STR_STRING];

	//memcpy_s(py_char[1], 200, tag, lstrlen(tag));
	
	lstrcpy(py_char[0], tag);

	lstrcpy(py_char[1], tag);
	
	/*LPTSTR fk = tag;
	fk += 1;
	*fk = '\0';
	memcpy_s(py_char[0], 200, tag, 1);*/
	//lstrcpy(py_char[0], tag);

	while (!dict->eof())
	{
		dict->getline(buf, MAX_STR_STRING);


		// get the buf, a utf-8 string
		char* p = strchr(buf, ' ');
		if (p != NULL)
		{
			// cut down the first part
			buf[p - buf] = '\0';

			TCHAR buf_chn[MAX_STR_STRING];
			TCHAR buf_py[MAX_STR_STRING];

			//Model::UTF8ToUnicode(buf, buf_chn);
			//Model::UTF8ToUnicode(p + 1, buf_py);

			// for test
			UTF8ToUnicode(buf, buf_chn);
			UTF8ToUnicode(p + 1, buf_py);

			if (wcscmp(buf_chn, tag) == 0)
			{
				// copy the full py
				lstrcpy(py_char[1], buf_py);
				// cut down the py and save first letter
				buf_py[1] = '\0';
				
				lstrcpy(py_char[0], buf_py);
				// fint the first exist
				break;
			}

		}


	}

	return (TCHAR**)py_char;
}

// return a array, with short and full pinyin
TCHAR** PinYin::GetPYStr(TCHAR* tag, TCHAR py_str[2][200])
{
	// set result if it is NOT Chinese
	//TCHAR py_str[2][MAX_STR_STRING] = {L"",L""};


	// get len of str
	int len = lstrlen(tag);

	//OutputDebugStringA(py_str.c_str());

	// get dic file path
	TCHAR dir[MAX_STR_STRING];
	GetModuleFileName(NULL, dir, MAX_STR_STRING);
	wstring py_dict = wstring(dir);
	size_t index = py_dict.find_last_of(L"/\\");
	if (index >= 0) py_dict = py_dict.substr(0, index);
	py_dict += L"\\share\\pydic.txt";

	// open file
	ifstream dict(py_dict, ios::in);



	if (dict.is_open())
	{
		TCHAR p[2];
		TCHAR* q = tag;
		TCHAR py_char[2][MAX_STR_STRING];

		for (int i = 0; i < len; i++)
		{

			wcsncpy_s(p, q, 1);
			q++;

			GetPYChar(p, &dict, py_char);
			if (i == 0)
			{
				lstrcat(py_str[0], py_char[0]);
			}
			
			lstrcat(py_str[1], py_char[1]);

			dict.clear();
			dict.seekg(0, ios::beg);

		}


		dict.close();
	}


	return (TCHAR**)py_str;
}
