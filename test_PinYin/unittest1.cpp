#include "stdafx.h"
#include "CppUnitTest.h"

#include "PinYin.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_PinYin
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod3chinesepinyin)
		{
			// TODO: 在此输入测试代码

			TCHAR src[MAX_STR_LEN] = L"你说你想要逃";

			TCHAR py_str[2][MAX_STR_LEN] = { L"",L"" };

			PinYin::GetPYStr(src, py_str);
			//Assert::AreEqual(0,0);
			Assert::AreEqual(wcscmp(py_str[0], L"nsnxyt"), 0);
			Assert::AreEqual(wcscmp(py_str[1], L"nishuinixiangyaotao"), 0);
			//Assert::AreEqual(py_str[0], L"s");
			//Assert::AreEqual(py_str[1], L"shuigepi");


		}

		TEST_METHOD(TestMethod4englishpinyin)
		{
			// TODO: 在此输入测试代码

			TCHAR src[MAX_STR_LEN] = L"google";

			TCHAR py_str[2][MAX_STR_LEN] = { L"",L"" };

			PinYin::GetPYStr(src, py_str);
			//Assert::AreEqual(0,0);
			Assert::AreEqual(wcscmp(py_str[0], L"google"), 0);
			Assert::AreEqual(wcscmp(py_str[1], L"google"), 0);
			//Assert::AreEqual(py_str[0], L"s");
			//Assert::AreEqual(py_str[1], L"shuigepi");


		}

	};
}