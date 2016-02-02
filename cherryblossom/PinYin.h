#pragma once

#include <iostream> 
#include <fstream>


class PinYin
{
public:
	PinYin();
	~PinYin();

	static TCHAR** GetPYChar(TCHAR* tag, std::ifstream* dict, TCHAR py_char[2][MAX_STR_LEN]);
	static TCHAR** GetPYStr(TCHAR* tag, TCHAR py_str[2][MAX_STR_LEN]);

};

