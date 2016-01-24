#pragma once

#include <iostream> 
#include <fstream>

#define MAX_STR_LEN 100
#define MAX_PATH_LEN 200

class PinYin
{
public:
	PinYin();
	~PinYin();

	static TCHAR** GetPYChar(TCHAR* tag, std::ifstream* dict, TCHAR py_char[2][MAX_STR_LEN]);
	static TCHAR** GetPYStr(TCHAR* tag, TCHAR py_str[2][MAX_STR_LEN]);

};

