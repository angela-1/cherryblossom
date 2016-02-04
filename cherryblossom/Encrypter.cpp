#include "stdafx.h"
#include "Encrypter.h"

#include "convert.h"

#include "global.h"

#include "../libencrypt/libencrypt.h"

#pragma comment(lib, "libencrypt.lib")



int Encrypter::_WriteBinFile(LPTSTR file, UCHAR* buf, int buf_len)
{
	HANDLE hFile = CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD numofbyte;
	WriteFile(hFile, buf, buf_len, &numofbyte, NULL);

	CloseHandle(hFile);
	return 0;
}

int Encrypter::_ReadBinFile(LPTSTR file, UCHAR* buf, int buf_len)
{
	HANDLE hFile = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD numofbyte;
	ReadFile(hFile, buf, buf_len, &numofbyte, NULL);


	CloseHandle(hFile);

	return 0;
}

Encrypter::Encrypter()
{
	
}


Encrypter::~Encrypter()
{
}

bool Encrypter::Validate(LPTSTR key)
{
	bool is_valid = true;

	// read md5 and salt
	uchar md5salt[MD5_BLOCK*2];

	_ReadBinFile(g_key_file, md5salt, MD5_BLOCK * 2);

	uchar md5part[MD5_BLOCK];
	uchar* q = md5salt + MD5_BLOCK;
	memcpy_s(md5part, MD5_BLOCK, q, MD5_BLOCK);

	// transform wide char to char
	char keystr[MAX_STR_LEN];
	memset(keystr, 0, MAX_STR_LEN);

	UnicodeToANSI(key, keystr);

	int len = strlen(keystr);
	// move the point
	char* p = keystr + len;
	// add md5 to key string
	memcpy_s(p, MD5_BLOCK, md5part, MD5_BLOCK);
	p += MD5_BLOCK;
	*p = '\0';
	
	uchar keysaltmd5[MD5_BLOCK]; //128bit
	digest_md5(keystr, keysaltmd5);

	
	for (size_t i = 0; i < MD5_BLOCK; i++)
	{
		if (keysaltmd5[i] != md5salt[i])
		{
			is_valid = false;
		}
	}

	return is_valid;
}

int Encrypter::CreateKeyFile(LPTSTR password)
{
	uchar keysaltmd5[MD5_BLOCK]; //128bit md5
	uchar md5salt[MD5_BLOCK*2]; // + 128bit salt

	uchar saltnum[16];
	salt(saltnum, 16);


	char keystr[MAX_STR_LEN];
	memset(keystr, 0, MAX_STR_LEN);

	UnicodeToANSI(password, keystr);

	int len = strlen(keystr);
	char* q = keystr + len;
	memcpy_s(q, MD5_BLOCK, saltnum, MD5_BLOCK);
	q += MD5_BLOCK;
	*q = '\0';
	
	digest_md5(keystr, keysaltmd5);

	memcpy_s(md5salt, MD5_BLOCK*2, keysaltmd5, MD5_BLOCK);
	uchar* p = md5salt + MD5_BLOCK;
	memcpy_s(p, MD5_BLOCK*2, saltnum, MD5_BLOCK);

	_WriteBinFile(g_key_file, md5salt, MD5_BLOCK*2);

	return 0;
}
