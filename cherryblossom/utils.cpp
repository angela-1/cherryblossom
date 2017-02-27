/*
  This is the utils file. Offers the convert function
  and other utils.

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
#include "utils.h"

#include <string>

using std::wstring;


LPTSTR trim_space(TCHAR* str)
{

  int result = 0;
  int n = 0;
  //定义两个下标  一个从0开始  一个从后面开始  
  int i, j;

  if (str == NULL)
  {
    return NULL;
  }

  //第一个下标
  i = 0;
  //最后一个下标， 是 \0前面的字符的下标  
  j = lstrlen(str) - 1;

  //如果是空白字符 并且不为'\0' 开始下标自增
  while (str[i] == L' ' && str[i] != L'\0')
  // while (isspace(str[i]) && str[i] != '\0')
  {
    i++;
  }

  //如果是空白字符 并且j不是0 末尾下标自减  
  while (str[j] == L' ' && j > 0)
  {
    j--;
  }

  //用后面的下标 减去 前面的下标 获取到中间的字符数量    
  //因为多减一个 所以再加一  
  //这就获取到了 有效字符串 不含有\0 的字符个数   
  n = j - i + 1;

  //从 p+i的位置 拷贝 n个字符到 buf中去
  TCHAR dest[MAX_STR_LEN] = L"";
  lstrcpyn(dest, str + i, n + 1);
  dest[n] = '\0';

  lstrcpy(str, dest);
  return str;
}


bool fuzzy_search(wchar_t* src_str, wchar_t* search_str) {
  wstring src(src_str);
  wstring search(search_str);
  bool result = true;
  size_t len = search.length();
  size_t pos = -1;
  for (size_t i = 0; i < len; ++i) {
    pos = src.find_first_of(search[i], pos + 1);
    if (pos == wstring::npos) {
      result = false;
    }
  }
  return result;
}


bool file_exists(LPTSTR file) {
  DWORD dwAttrib = GetFileAttributes(file);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
    !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


void ansi_to_unicode(char *str, wchar_t *end) {
    wchar_t *wstr;
    int len;
    len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    wstr = new wchar_t[len + 1];
    memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
    wcscpy_s(end, len, wstr);

    delete[] wstr;
}


void utf8_to_unicode(char *str, wchar_t *end) {
    wchar_t *wstr;
    int len;
    len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wstr = new wchar_t[len + 1];
    memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    wcscpy_s(end, len, wstr);

    delete[] wstr;


}

void unicode_to_utf8(wchar_t * str, char *end) {
    char*     cstr;
    int    len;
    // wide char to multi char
    len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
    cstr = new char[len + 1];
    memset((void*)cstr, 0, sizeof(char) * (len + 1));
    WideCharToMultiByte(CP_UTF8, 0, str, -1, cstr, len, NULL, NULL);
    strcpy_s(end, len, cstr);
    delete[] cstr;

}

void unicode_to_ansi(wchar_t * str, char *end) {
    char*     cstr;
    int    len;
    // wide char to multi char
    len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
    cstr = new char[len + 1];
    memset((void*)cstr, 0, sizeof(char) * (len + 1));
    WideCharToMultiByte(CP_ACP, 0, str, -1, cstr, len, NULL, NULL);
    strcpy_s(end, len, cstr);
    delete[] cstr;
}