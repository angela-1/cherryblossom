

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


#include "stdafx.h"


#include "model.h"

#include "utils.h"





sqlite3* Model::db = NULL;
char* Model::err_msg;


Model::Model()
{
}


Model::~Model()
{
}


int Model::open_db(char* db_path)
{
    int rc = sqlite3_open(db_path, &db);
    if (rc)
    {
        sqlite3_close(db);
        return 1;
    }
    else
    {
        return 0;

    }

}
void Model::close_db()
{
    sqlite3_close(db);
}





void Model::exec_sql(char *sql, int(*callback)(void*, int, char**, char**), void* para)
{
  char* errmsg;
    int rc = sqlite3_exec(db, sql, callback, para, &errmsg);
    if (rc != SQLITE_OK) {

        TCHAR uerr[MAX_STR_LEN];
        utf8_to_unicode(errmsg, uerr);
        MessageBox(NULL, uerr, TEXT("警告"), MB_OK);

        sqlite3_free(errmsg);

    }

    //sqlite3_exec(db, sql, 0, 0, 0);
}

char** Model::get_table(char *sql, int *row, int *column, char **result)
{
    sqlite3_get_table(db, sql, &result, row, column, &err_msg);
    return result;
}

void Model::free_table(char** result)
{
    sqlite3_free_table(result);
}




