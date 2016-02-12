// cherryblossom.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "cherryblossom.h"




#include "process.h"
#include "control.h"



#include "Dispather.h"




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




// ȫ�ֱ��������Ƕ��壡
HINSTANCE g_inst;                                // ��ǰʵ��
WCHAR g_app_title[MAX_LOADSTRING];                  // �������ı�
WCHAR g_window_class[MAX_LOADSTRING];            // ����������

// fonts
HFONT g_main_font;
HFONT g_mono_font;
HFONT g_symbol;

// for i18n, load all resource from out resource
HINSTANCE g_resource;

// dispatcher, definition
Dispatcher* g_dispatcher;

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

	g_inst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
	
	
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
	g_dispatcher = Dispatcher::GetInstance();
	g_dispatcher->MakeAccountList();





    // ��ʼ��ȫ���ַ���
    LoadStringW(g_resource, IDS_APP_TITLE, g_app_title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHERRYBLOSSOM, g_window_class, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return nil;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHERRYBLOSSOM));

    MSG msg;

    // ����Ϣѭ��: 
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





