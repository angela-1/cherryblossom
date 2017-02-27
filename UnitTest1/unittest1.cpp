#include "stdafx.h"
#include "CppUnitTest.h"

#include "../cherryblossom/pinyin.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test__get_pinyin_str)
		{

     
      TCHAR py_str[MAX_STR_LEN] = L"";
      Pinyin::PinyinString(L"³¤³ÇÒ¥", py_str);

      
      Assert::AreEqual(L"chang,zhang|cheng|yao", py_str);

		}


    TEST_METHOD(Test__get_pinyin_char)
    {
      wstring py_dict = wstring(L"F:\\home\\angela\\repo\\cherryblossom\\UnitTest1\\share\\pydic.txt");
      ifstream dict(py_dict, ios::in);

      TCHAR py_str[MAX_STR_LEN] = L"";

      if (dict.is_open()) {

        cout << "fuck" << endl;
        //Pinyin::get_pinyin_char(L"³¤", &dict, py_str);

        dict.close();
      }

      Assert::AreEqual(L"chang,zhang", py_str);

    }

    TEST_METHOD(Test_get_pinyin_char2)
    {
      wstring py_dict = wstring(L"F:\\home\\angela\\repo\\cherryblossom\\UnitTest1\\share\\pydic.txt");
      ifstream dict(py_dict, ios::in);

      TCHAR py_str[MAX_STR_LEN] = L"";

      if (dict.is_open()) {

        //Pinyin::get_pinyin_char(L"F", &dict, py_str);

        dict.close();
      }

      Assert::AreEqual(L"f", py_str);

    }


	};
}