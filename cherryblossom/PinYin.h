#pragma once

#include <iostream> 
#include <fstream>



class PinYin
{
public:
	PinYin();
	~PinYin();

	static TCHAR** GetPYChar(TCHAR* tag, std::ifstream* dict, TCHAR py_char[2][200]);
	static TCHAR** GetPYStr(TCHAR* tag, TCHAR py_str[2][200]);

};

