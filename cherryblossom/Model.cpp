#include "stdafx.h"


#include "Model.h"

#include "convert.h"





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





void Model::exec_sql(char *sql, int(*callback)(void*, int, char**, char**))
{
	int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if (rc != SQLITE_OK) {

		
		TCHAR uerr[MAX_STR_LEN];
		UTF8ToUnicode(err_msg, uerr);
		MessageBox(NULL, uerr, TEXT("Caution"), MB_OK);

		sqlite3_free(err_msg);

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




