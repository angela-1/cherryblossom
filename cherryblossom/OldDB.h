






#pragma once


#include "sqlite3.h"

#pragma comment(lib, "sqlite3.lib")


class OldDB
{
private:


    
    static sqlite3* db;
    static char* err_msg;


public:
    OldDB();
    ~OldDB();

    

    static int open_db(char* db_path);
    static void close_db();
    static void exec_sql(char* sql, int(*callback)(void*, int, char**, char**));
    static char** get_table(char *sql, int *row, int *column, char **result);
    static void free_table(char** result);

};

