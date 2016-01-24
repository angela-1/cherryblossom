#pragma once


#include "sqlite3.h"

#pragma comment(lib, "sqlite3.lib")


class Model
{
private:


	static const char* db_path;
	static sqlite3* db;
	static char* err_msg;


public:
	Model();
	~Model();

	static int open_db();
	static void close_db();
	static void exec_sql(char* sql, int(*callback)(void*, int, char**, char**));
	static char** get_table(char *sql, int *row, int *column, char **result);
	static void free_table(char** result);

};
