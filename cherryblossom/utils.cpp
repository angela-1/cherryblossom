
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



bool file_exists(LPTSTR file)
{
  DWORD dwAttrib = GetFileAttributes(file);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
    !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


void ansi_to_unicode(char *str, wchar_t *end)
{
    wchar_t *wstr;
    int len;
    len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    wstr = new wchar_t[len + 1];
    memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
    wcscpy_s(end, len, wstr);

    delete[] wstr;
}


void utf8_to_unicode(char *str, wchar_t *end)
{
    wchar_t *wstr;
    int len;
    len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wstr = new wchar_t[len + 1];
    memset((void*)wstr, 0, sizeof(wchar_t) * (len + 1));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    wcscpy_s(end, len, wstr);

    delete[] wstr;


}

void unicode_to_utf8(wchar_t * str, char *end)
{
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

void unicode_to_ansi(wchar_t * str, char *end)
{
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