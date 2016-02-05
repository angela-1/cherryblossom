#pragma once

#include <fstream>



class Encrypter
{
private:

	int _WriteBinFile(LPTSTR file, UCHAR* buf, int buf_len);
	int _ReadBinFile(LPTSTR file, UCHAR* buf, int buf_len);


public:
	Encrypter();
	~Encrypter();

	

	bool Validate(LPTSTR key);

	int CreateKeyFile(LPTSTR password);
	int EncryptDBFile(LPTSTR key);
	int DecryptDBFile(LPTSTR key);


};

