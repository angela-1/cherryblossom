#include "stdafx.h"


#include "OldDB.h"

#include "utils.h"





sqlite3* OldDB::db = NULL;
char* OldDB::err_msg;


OldDB::OldDB()
{
}


OldDB::~OldDB()
{
}


int OldDB::open_db(char* db_path)
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
void OldDB::close_db()
{
    sqlite3_close(db);
}





void OldDB::exec_sql(char *sql, int(*callback)(void*, int, char**, char**))
{
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {

        
        TCHAR uerr[MAX_STR_LEN];
        utf8_to_unicode(err_msg, uerr);
        MessageBox(NULL, uerr, TEXT("¾¯¸æ"), MB_OK);

        sqlite3_free(err_msg);

    }

    //sqlite3_exec(db, sql, 0, 0, 0);
}

char** OldDB::get_table(char *sql, int *row, int *column, char **result)
{
    sqlite3_get_table(db, sql, &result, row, column, &err_msg);
    return result;
}

void OldDB::free_table(char** result)
{
    sqlite3_free_table(result);
}




