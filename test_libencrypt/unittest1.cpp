#include "stdafx.h"
#include "CppUnitTest.h"


#include "libencrypt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_libencrypt
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1salt)
		{
			// TODO: 在此输入测试代码

			uchar usalt0[16];
			salt(usalt0, 16);

			uchar usalt1[16];
			salt(usalt1, 16);

			Assert::AreNotEqual(usalt0, usalt1);

			for (size_t i = 0; i < 16; i++)
			{
				Assert::AreNotEqual(usalt0[i], usalt1[i]);
			}


		}
		
		TEST_METHOD(TestMethod2saltsave)
		{
			// TODO: 在此输入测试代码
			char src[200] = "fuck";
			uchar ubuf[32];
			uchar usaltmd5[16];
			uchar usalt[16];

			salt(usalt, 16);

			int len = strlen(src);
			char* p = src + len;
			memcpy_s(p, 16, usalt, 16);
			p += 16;
			*p = '\0';
			

			digest_md5(src, usaltmd5);

			memcpy_s(ubuf, 32, usaltmd5, 16);
			uchar* q = ubuf + 16;
			memcpy_s(q, 32, usalt, 16);


			for (size_t i = 0; i < 16; i++)
			{
				Assert::AreEqual(usalt[i], ubuf[16 + i]);
				
				
			}




		

		}



	};
}