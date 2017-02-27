/*
  This is the header file of model.
  
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





#ifndef CHERRYBLOSSOM_MODEL_H_
#define CHERRYBLOSSOM_MODEL_H_


#include "sqlite3.h"

#pragma comment(lib, "sqlite3.lib")


class Model {
 private:
  static sqlite3* db;
  static char* errmsg;

 protected:
  static int open_db(char* db_path);
  static void close_db();
  static void exec_sql(char* sql,
                       int(*callback)(void*, int, char**, char**),
                       void* para);
  static char** get_table(char *sql, int *row, int *column, char **result);
  static void free_table(char** result);

 public:
  Model();
  ~Model();

  virtual Model& FindByTag(wchar_t* tag) = 0;
  virtual Model& Save() = 0;
  virtual Model& Update() = 0;
  virtual int Del() = 0;
};

#endif  // CHERRYBLOSSOM_MODEL_H_


