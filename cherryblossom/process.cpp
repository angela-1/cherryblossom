

#include "stdafx.h"
#include "Resource.h"


#include "control.h"
#include "process.h"
#include "global.h"

#include "../res804/resource.h"


// for test
#include "PinYin.h"


//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHERRYBLOSSOM));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CHERRYBLOSSOM); // read menu from resource dll
		
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_window_class;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HMENU hmenu = LoadMenu(g_resource, MAKEINTRESOURCE(IDC_CHERRYBLOSSOM));
	HWND hWnd = CreateWindowW(g_window_class, g_app_title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 600, 360, nullptr, hmenu, hInstance, nullptr);

	if (!hWnd)
	{
		return nil;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return t;
}




//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:

		OnInitControl(hWnd);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_BUTTON_ADD:
		{
			TCHAR src[200] = L"˵��ƨ";

			TCHAR py_str[2][100] = { L"",L"" };

			PinYin::GetPYStr(src, py_str);

			MessageBox(NULL, py_str[0], L"SE", MB_OK);
			MessageBox(NULL, py_str[1], L"SE", MB_OK);


		}

		break;
		case IDM_ABOUT:
			
			DialogBox(g_inst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 600;  
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 360;
		break;
	case WM_SIZE:
		OnResizeControl(hWnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: show account detial
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)t;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)t;
		}
		break;
	}
	return (INT_PTR)nil;
}

BOOL LoadResDll(LANGID lang_id)
{
	TCHAR g_tcsTemp[MAX_LOADSTRING];

	if (lang_id != NULL)
	{
		
		_stprintf_s(g_tcsTemp, _TEXT("res%x.dll"), lang_id);

		if ((g_resource = LoadLibrary(g_tcsTemp)) == NULL)
		{
			// we didn't find the desired language satellite DLL, lets go with English (default).
			g_resource = LoadLibrary(_TEXT("res804.dll"));
		}

	}
	else
	{
		LANGID wLangId = GetUserDefaultUILanguage();

		_stprintf_s(g_tcsTemp, _TEXT("res%x.dll"), wLangId);

		if ((g_resource = LoadLibrary(g_tcsTemp)) == NULL)
		{
			// we didn't find the desired language satellite DLL, lets go with English (default).
			g_resource = LoadLibrary(_TEXT("res804.dll"));
		}
	}

	
	return t;
}


