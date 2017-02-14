#include "stdafx.h"

#include <iostream> 
#include <fstream>
#include <string>

#include "Exporter.h"
#include "convert.h"
#include "global.h"

using namespace std;

Exporter::Exporter()
{
}


Exporter::~Exporter()
{
}

int Exporter::count = 0;


static int detialcallback(void *NotUsed, int argc, char **argv, char **azColName)
{
    wchar_t tag[MAX_STR_LEN];
    wchar_t category[MAX_STR_LEN];
    wchar_t url[MAX_STR_LEN];
    wchar_t user[MAX_STR_LEN];
    wchar_t password[MAX_STR_LEN];
    wchar_t phone[MAX_STR_LEN];
    wchar_t mail[MAX_STR_LEN];
    wchar_t note[MAX_STR_LEN];
    wchar_t lastmod[MAX_STR_LEN];


    //UTF8ToUnicode(argv[1], tag);
    //UTF8ToUnicode(argv[2], category);
    //UTF8ToUnicode(argv[3], url);
    //UTF8ToUnicode(argv[4], user);
    //UTF8ToUnicode(argv[5], password);
    //UTF8ToUnicode(argv[6], phone);
    //UTF8ToUnicode(argv[7], mail);
    //UTF8ToUnicode(argv[8], note);
    //UTF8ToUnicode(argv[9], lastmod);

    
//    Exporter::count = argv[1];



    return 0;
}


void Exporter::AssembleHtml()
{
    Model::open_db(g_chr_db_file);

    wchar_t sql[MAX_SQL_LEN];

    wchar_t* ii = L"select count(*) from accounts;";
    swprintf_s(sql, L"%s", ii);
    char csql[MAX_SQL_LEN];
    UnicodeToUTF8(sql, csql);

//    Model::exec_sql(csql, countcallback);


    Model::close_db();


}



void Exporter::ExportTxt(TCHAR* output_file, TCHAR* content)
{
    // get dic file path
    TCHAR dir[MAX_PATH_LEN];
    GetModuleFileName(NULL, dir, MAX_PATH_LEN);
    wstring output_file_path = wstring(dir);
    size_t index = output_file_path.find_last_of(L"/\\");
    if (index >= 0) output_file_path = output_file_path.substr(0, index);
    output_file_path += L"\\output\\fk.txt";

    // open file
    ofstream output_file_p(output_file_path, ios::out);

    char buf[MAX_STR_LEN];

    if (output_file_p.is_open())
    {

        output_file_p << "fuck" << endl;

        UnicodeToUTF8(content, buf);
        output_file_p << buf << endl;
        //TCHAR p[2];
        //TCHAR* q = tag;
        //TCHAR py_char[2][MAX_STR_LEN];

        //for (int i = 0; i < len; i++)
        //{

        //    wcsncpy_s(p, q, 1);
        //    q++;

        //    get_pinyin_char(p, &output_file_p, py_char);
        //    //if (i == 0)
        //    //{
        //    //    lstrcat(py_str[0], py_char[0]);
        //    //}
        //    lstrcat(py_str[0], py_char[0]);
        //    lstrcat(py_str[1], py_char[1]);

        //    output_file_p.clear();
        //    output_file_p.seekg(0, ios::beg);

        /*}*/


        output_file_p.close();
    }



}