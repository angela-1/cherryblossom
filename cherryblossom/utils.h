
/*
  This is the header file of utils file.

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



#ifndef CHERRYBLOSSOM_UTILS_H_
#define CHERRYBLOSSOM_UTILS_H_


LPTSTR trim_space(TCHAR* str);
bool fuzzy_search(wchar_t* string, wchar_t* search);
bool file_exists(LPTSTR file);

void utf8_to_unicode(char *str, wchar_t *end);
void unicode_to_utf8(wchar_t * str, char *end);
void ansi_to_unicode(char *str, wchar_t *end);
void unicode_to_ansi(wchar_t * str, char *end);



#endif  // CHERRYBLOSSOM_UTILS_H_


