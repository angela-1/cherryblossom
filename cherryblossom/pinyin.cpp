/*
  This is the Pinyin class. To get the pinyin of tag.

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


#include "stdafx.h"

#include "pinyin.h"
#include "utils.h"



using std::wstring;
using std::ifstream;
using std::ios;



Pinyin::Pinyin() {}


Pinyin::~Pinyin() {}





TCHAR* Pinyin::get_pinyin_char(TCHAR* tag, ifstream* dict,
                   TCHAR pinyin_char[MAX_PINYIN_LEN]) {
  char buf[MAX_PINYIN_LEN] = "";

  TCHAR tmp_pinyin[MAX_PINYIN_LEN] = L"";

  while (!dict->eof()) {
    dict->getline(buf, MAX_PINYIN_LEN);
    // get the buf, a utf-8 string
    char* p = strchr(buf, ' ');
    if (p != NULL) {
      // split the chinese and pinyin
      buf[p - buf] = '\0';

      TCHAR chn_buf[MAX_PINYIN_LEN];
      TCHAR pinyin_buf[MAX_PINYIN_LEN];

      utf8_to_unicode(buf, chn_buf);
      utf8_to_unicode(p + 1, pinyin_buf);

      if (wcscmp(chn_buf, tag) == 0) {
        lstrcat(tmp_pinyin, pinyin_buf);
        lstrcat(tmp_pinyin, L",");
      }
    }
  }

  if (wcscmp(tmp_pinyin, L"") == 0) {
    TCHAR lower_case[MAX_PINYIN_LEN] = L"";
    lstrcpy(lower_case, tag);
    CharLower(lower_case);
    lstrcpy(pinyin_char, lower_case);
  } else {
    // find the last ',' and delete it
    TCHAR* last_comma = _tcsrchr(tmp_pinyin, L',');
    *last_comma = L'\0';

    // copy the pinyin to result
    lstrcpy(pinyin_char, tmp_pinyin);
  }
  return pinyin_char;
}



// return a string of full Pinyin
TCHAR* Pinyin::PinyinString(TCHAR* tag, TCHAR py_str[MAX_PINYIN_LEN]) {
  // get len of str
  int len = lstrlen(tag);
  // get dic file path
  TCHAR dir[MAX_PATH_LEN];
  GetModuleFileName(NULL, dir, MAX_PATH_LEN);
  wstring py_dict = wstring(dir);
  size_t index = py_dict.find_last_of(L"/\\");
  if (index >= 0) py_dict = py_dict.substr(0, index);
  py_dict += L"\\share\\pydic.txt";

  // py_dict = wstring(L"F:\\home\\angela\\repo\\cherryblossom\\
  // UnitTest1\\share\\pydic.txt");  // only for test

  // open file
  ifstream dict(py_dict, ios::in);

  if (dict.is_open()) {
    TCHAR p[2];
    TCHAR* q = tag;
    TCHAR py_char[MAX_PINYIN_LEN];

    for (int i = 0; i < len; i++) {
      wcsncpy_s(p, q, 1);
      q++;

      get_pinyin_char(p, &dict, py_char);

      lstrcat(py_str, py_char);
      lstrcat(py_str, L"|");

      dict.clear();
      dict.seekg(0, ios::beg);
    }
    dict.close();
  }

  // find the last ',' and delete it
  TCHAR* last_vline = _tcsrchr(py_str, L'|');
  *last_vline = L'\0';


  return py_str;
}
