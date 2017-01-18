#pragma once



#include"Model.h"


class Exporter
{
private:
	
	TCHAR html_template[MAX_STR_STRING];

public:
	Exporter();
	~Exporter();

	static int count;

	static void AssembleHtml();
	static void ExportHtml(TCHAR* output_file, TCHAR* content);
	static void ExportTxt(TCHAR* output_file, TCHAR* content);


};

