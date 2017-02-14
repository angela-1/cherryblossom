#pragma once

#include <fstream>



class Encrypter
{
private:

    size_t _WriteBinFile(LPTSTR file, UCHAR* buf, size_t buf_len);
    size_t _ReadBinFile(LPTSTR file, UCHAR* buf, size_t buf_len);


public:
    Encrypter();
    ~Encrypter();

    

    bool Validate(LPTSTR key);

    int CreateKeyFile(LPTSTR password);
    int EncryptDBFile(LPTSTR key);
    int DecryptDBFile(LPTSTR key);


};

