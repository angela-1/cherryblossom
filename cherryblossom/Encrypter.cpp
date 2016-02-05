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

int Encrypter::EncryptDBFile(LPTSTR key)
{
	HANDLE hFile = CreateFile(g_db_file, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	size_t file_length = (size_t)GetFileSize(hFile, NULL);
	CloseHandle(hFile);

	size_t a = file_length % AES_BLOCK;
	size_t block_length = 0;
	
	if (a > 0)
	{
		block_length = AES_BLOCK*(file_length / AES_BLOCK) + AES_BLOCK;
		
	} 
	else
	{
		block_length = file_length;
	}


	uchar bytekey[16];
	char strkey[MAX_STR_LEN];

	UnicodeToUTF8(key, strkey);
	memcpy_s(bytekey, 16, strkey, 16);

	uchar* bytesrc = (uchar*)malloc((size_t)block_length);
	uchar* bytedst = (uchar*)malloc((size_t)block_length);

	_ReadBinFile(g_db_file, bytesrc, block_length);

	encrypt(bytesrc, bytedst, block_length, bytekey);

	_WriteBinFile(g_db_file_s, bytedst, block_length);
	
	DeleteFile(g_db_file);

	return 0;
}

int Encrypter::DecryptDBFile(LPTSTR key)
{
	HANDLE hFile = CreateFile(g_db_file_s, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	size_t file_length = (size_t)GetFileSize(hFile, NULL);
	CloseHandle(hFile);

	size_t a = file_length % AES_BLOCK;
	size_t block_length = 0;

	if (a > 0)
	{
		block_length = AES_BLOCK*(file_length / AES_BLOCK) + AES_BLOCK;

	}
	else
	{
		block_length = file_length;
	}


	uchar bytekey[16];
	char strkey[MAX_STR_LEN];

	UnicodeToUTF8(key, strkey);
	memcpy_s(bytekey, 16, strkey, 16);

	uchar* bytesrc = (uchar*)malloc((size_t)block_length);
	uchar* bytedst = (uchar*)malloc((size_t)block_length);

	memset(bytesrc, 0, block_length);
	memset(bytedst, 0, block_length);

	_ReadBinFile(g_db_file_s, bytesrc, block_length);

	decrypt(bytesrc, bytedst, block_length, bytekey);

	_WriteBinFile(g_db_file, bytedst, block_length);

	free(bytesrc);
	free(bytedst);

	return 0;
}