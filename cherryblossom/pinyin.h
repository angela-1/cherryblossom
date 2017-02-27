
/*
  This is the header file of Pinyin class. To get the pinyin of tag.

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





#ifndef CHERRYBLOSSOM_PINYIN_H_
#define CHERRYBLOSSOM_PINYIN_H_

#define MAX_PINYIN_LEN 100


#include <iostream>
#include <fstream>


class Pinyin {
 private:
  static TCHAR* get_pinyin_char(TCHAR* tag, std::ifstream* dict,
    TCHAR pinyin_char[MAX_PINYIN_LEN]);

 public:
  Pinyin();
  ~Pinyin();

  static TCHAR* PinyinString(TCHAR* tag,
                                TCHAR py_str[MAX_PINYIN_LEN]);
};

#endif  // CHERRYBLOSSOM_PINYIN_H_




