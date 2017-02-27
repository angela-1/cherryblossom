﻿/*
  This is the entry point of cherryblossom.

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

// cherryblossom.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "cherryblossom.h"


#include "process.h"
#include "control.h"
#include "controller.h"
#include "../res804/resource.h"


// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif




// 全局变量，这是定义！
HINSTANCE g_inst;                                // 当前实例
WCHAR g_app_title[MAX_LOADSTRING];                  // 标题栏文本
WCHAR g_window_class[MAX_LOADSTRING];            // 主窗口类名

// fonts
HFONT g_main_font;
HFONT g_mono_font;
HFONT g_symbol;

// for i18n, load all resource from out resource
HINSTANCE g_resource;

// dispatcher, definition
//Dispatcher* g_dispatcher;
Controller* g_dispatcher;

TCHAR g_cur_var_dir[MAX_STR_LEN];
TCHAR g_key_file[MAX_STR_LEN];
TCHAR g_db_file[MAX_STR_LEN];
TCHAR g_db_file_s[MAX_STR_LEN];
char g_chr_db_file[MAX_STR_LEN];
TCHAR g_config_file[MAX_STR_LEN];

TCHAR g_key[MAX_STR_LEN];


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    g_inst = hInstance; // 将实例句柄存储在全局变量中
    
    
    // set fonts
    OnInitFont(NULL);


    OnInitPath();



    // load langauage resource
    TCHAR lang[MAX_STR_LEN];
    GetPrivateProfileString(TEXT("cherryblossom"),
        TEXT("language"), L"zh-CN", lang, MAX_STR_LEN, g_config_file);
    if (wcscmp(lang, L"en-US") == 0)
    {
        LoadResDll(1033);
    }
    else
    {
        LoadResDll(2052);
    }

    
    // TODO: judge if it is first run. to show guide.
    if (IsFirstRun())
    {
        ShowWizard(NULL);
    }



    

    // TODO: show login page.

    INT_PTR login_p = DialogBox(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL, LoginProc);


    if (!login_p)
    {
        PostQuitMessage(0);
        
        return FALSE;
    }





    // start dispatcher
    g_dispatcher = Controller::GetInstance();
    g_dispatcher->MakeAccountList();





    // 初始化全局字符串
    LoadStringW(g_resource, IDS_APP_TITLE, g_app_title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_CHERRYBLOSSOM, g_window_class, MAX_LOADSTRING);


    MyRegisterClass(hInstance);

    

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        
        return nil;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHERRYBLOSSOM));

    MSG msg;
    
    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}





