

/*	global.h
*
*	ȫ�ֱ���������
*
*	����ļ����������б�����
*
*/

#pragma once






// ȫ�ֱ�������������
extern HINSTANCE g_inst;                                // ��ǰʵ��
extern WCHAR g_app_title[MAX_LOADSTRING];                  // �������ı�
extern WCHAR g_window_class[MAX_LOADSTRING];            // ����������

// fonts
extern HFONT g_main_font;
extern HFONT g_mono_font;
extern HFONT g_symbol;

// resource
extern HINSTANCE g_resource;



extern TCHAR g_cur_var_dir[MAX_STR_LEN];
extern TCHAR g_key_file[MAX_STR_LEN];
extern TCHAR g_db_file[MAX_STR_LEN];
extern TCHAR g_db_file_s[MAX_STR_LEN];
extern TCHAR g_config_file[MAX_STR_LEN];
extern char g_chr_db_file[MAX_STR_LEN];


extern TCHAR g_key[MAX_STR_LEN];

