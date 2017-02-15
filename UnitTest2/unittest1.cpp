#include "stdafx.h"
#include "CppUnitTest.h"



#include "../cherryblossom/utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test__trim_space)
		{

      TCHAR aa[MAX_STR_LEN] = L"   ´å¶á  ";
      TCHAR bb[10] = L"";

      trim_space(aa);

      Assert::AreEqual(L"´å¶á", aa);
			
		}

	};
}