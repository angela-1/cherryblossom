#pragma once

#define MAX_STR_STRING 200
#define MAX_LOADSTRING 100

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

// ��������
extern Dispatcher* g_dispatcher;