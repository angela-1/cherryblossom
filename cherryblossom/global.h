#pragma once

#define MAX_STR_STRING 200
#define MAX_LOADSTRING 100

// 全局变量，这是声明
extern HINSTANCE g_inst;                                // 当前实例
extern WCHAR g_app_title[MAX_LOADSTRING];                  // 标题栏文本
extern WCHAR g_window_class[MAX_LOADSTRING];            // 主窗口类名

// fonts
extern HFONT g_main_font;
extern HFONT g_mono_font;
extern HFONT g_symbol;

// resource
extern HINSTANCE g_resource;

// 这是声明
extern Dispatcher* g_dispatcher;