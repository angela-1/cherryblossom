﻿/*
  This is the header file of crypto file.

  Copyright © 2016-2017 Angela

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files(the “Software”), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions :

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.

*/


#ifndef CHERRYBLOSSOM_CRYPTER_H_
#define CHERRYBLOSSOM_CRYPTER_H_

#include <fstream>

class Crypter {
 private:
  size_t write_bin_file(LPTSTR file, UCHAR* buf, size_t buf_len);
  size_t read_bin_file(LPTSTR file, UCHAR* buf, size_t buf_len);

 public:
  Crypter();
  ~Crypter();

  bool Validate(LPTSTR key);

  int CreateKeyFile(LPTSTR password);
  int EncryptDataFile(LPTSTR key);
  int DecryptDataFile(LPTSTR key);
};



#endif  // CHERRYBLOSSOM_CRYPTER_H_


