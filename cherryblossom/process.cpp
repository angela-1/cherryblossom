

#include "stdafx.h"
#include "Resource.h"

#include "process.h"

#include "control.h"




#include "Dispather.h"


#include "global.h"


#include "../res804/resource.h"


// for test
//#include "PinYin.h"





//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
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
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDC_EDIT_SEARCH:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{

				OnSearchChanged(hWnd);

			}


		}
		break;
		case IDC_BUTTON_CLEAR:
		{
			HWND search_edit = GetDlgItem(hWnd, IDC_EDIT_SEARCH);

			SendMessage(search_edit, WM_SETTEXT, 0, 0);
			SetFocus(search_edit);
		}
		break;
		case IDC_BUTTON_ADD:
		{

			DialogBox(g_inst, MAKEINTRESOURCE(IDD_ADD), hWnd, AddProc);

			g_dispatcher->RefreshAccountList();

			RefreshListbox(hWnd);

			InvalidateRect(hWnd, NULL, true);


			//TCHAR src[200] = L"说个屁";

			//TCHAR py_str[2][100] = { L"",L"" };

			//PinYin::GetPYStr(src, py_str);

			//MessageBox(NULL, py_str[0], L"SE", MB_OK);
			//MessageBox(NULL, py_str[1], L"SE", MB_OK);


		}

		break;
		case IDC_BUTTON_EDIT:
		{
			HWND account_list = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
			TCHAR lpch[MAX_ITEM_LEN];
			int ind = SendMessage(account_list, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			SendMessage(account_list, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

			//MessageBox(NULL, lpch, TEXT("see"), MB_OK);
			DialogBoxParam(g_inst, MAKEINTRESOURCE(IDD_EDIT), hWnd, EditProc, (LPARAM)lpch);

			InvalidateRect(hWnd, NULL, true);

		}
		break;
		case IDC_BUTTON_DELETE:
		{
			HWND account_list = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
			TCHAR lpch[MAX_ITEM_LEN];
			int ind = SendMessage(account_list, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (ind != -1)
			{
				SendMessage(account_list, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

				DialogBoxParam(g_inst, MAKEINTRESOURCE(IDD_CONFIRM), hWnd, DeleteProc, (LPARAM)lpch);

				g_dispatcher->RefreshAccountList();

				RefreshListbox(hWnd);

				SendMessage(account_list, LB_SETCURSEL, (WPARAM)ind, (LPARAM)0);

				InvalidateRect(hWnd, NULL, true);
			}



			//Dispatcher* a = Dispatcher::GetInstance();

			//a->ClearAccountList();
			//a->MakeAccountList();

			//for each (auto var in *(a->GetList()))
			//{

			//	SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT), 
			//		LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);

			//}



		}
		break;
		case IDC_LISTBOX_ACCOUNT:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				InvalidateRect(hWnd, NULL, true);

			}
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
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 405;
		break;
	case WM_SIZE:
		OnResizeControl(hWnd, lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		OnPaint(hWnd, hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		// free resource

		FreeLibrary(g_resource);
		delete g_dispatcher;

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
		return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));
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

INT_PTR CALLBACK AddProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:


		return (INT_PTR)TRUE;



	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK:
		{
			//save to db
			// check first
			TCHAR tag[128];
			TCHAR category[128];
			TCHAR url[128];
			TCHAR user[128];
			TCHAR password[128];
			TCHAR phone[128];
			TCHAR mail[128];
			TCHAR note[128];

			TCHAR* value_array[8] = {
				tag,
				category,
				url,
				user,
				password,
				phone,
				mail,
				note
			};

			int id_array[8] = {
				IDC_EDIT_TAG,
				IDC_EDIT_CATEGORY,
				IDC_EDIT_URL,
				IDC_EDIT_USER,
				IDC_EDIT_PASSWORD,
				IDC_EDIT_PHONE,
				IDC_EDIT_MAIL,
				IDC_EDIT_NOTE
			};

			for (size_t i = 0; i < 8; i++)
			{
				int line_len = SendDlgItemMessage(hDlg, id_array[i], EM_GETLINE, 0, (LPARAM)value_array[i]);
				/*HWND editControl = GetDlgItem(hDlg, ids[i]);*/
				//int sendLength = SendMessage(editControl, EM_GETLINE, 0, (LPARAM)wstr);
				value_array[i][line_len] = TEXT('\0');
			}


			if (wcscmp(tag, L"") != 0)
			{
				if (g_dispatcher->CheckAccount(tag))
				{
					g_dispatcher->AddAccount(value_array);



					EndDialog(hDlg, LOWORD(wParam));

					return (INT_PTR)TRUE;
				}
				else
				{
					HWND tag_edit = GetDlgItem(hDlg, IDC_EDIT_TAG);

					SendMessage(tag_edit, WM_SETTEXT, 0, (LPARAM)L"tag exists");

				}

			}
			else
			{
				HWND tag_edit = GetDlgItem(hDlg, IDC_EDIT_TAG);

				SendMessage(tag_edit, WM_SETTEXT, 0, (LPARAM)L"can not be null");

			}


		}


		break;
		case IDCANCEL:
			// do nothing
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		default:
			break;
		}

	}
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
		return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));

	}
	return (INT_PTR)FALSE;
}

// new dialog
INT_PTR CALLBACK EditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		TCHAR* lpch = (TCHAR*)lParam;

		//MessageBox(NULL, lpch, TEXT("see"), MB_OK);
		AccountCard* account = g_dispatcher->GetAccount(lpch);


		SendDlgItemMessage(hDlg, IDC_STATIC_TAG, WM_SETTEXT, 0, (LPARAM)account->tag);
		SendDlgItemMessage(hDlg, IDC_EDIT_TAG, WM_SETTEXT, 0, (LPARAM)account->tag);

		SendDlgItemMessage(hDlg, IDC_EDIT_CATEGORY, WM_SETTEXT, 0, (LPARAM)account->category);
		SendDlgItemMessage(hDlg, IDC_EDIT_URL, WM_SETTEXT, 0, (LPARAM)account->url);
		SendDlgItemMessage(hDlg, IDC_EDIT_USER, WM_SETTEXT, 0, (LPARAM)account->user);
		SendDlgItemMessage(hDlg, IDC_EDIT_PASSWORD, WM_SETTEXT, 0, (LPARAM)account->password);
		SendDlgItemMessage(hDlg, IDC_EDIT_PHONE, WM_SETTEXT, 0, (LPARAM)account->phone);
		SendDlgItemMessage(hDlg, IDC_EDIT_MAIL, WM_SETTEXT, 0, (LPARAM)account->mail);
		SendDlgItemMessage(hDlg, IDC_EDIT_NOTE, WM_SETTEXT, 0, (LPARAM)account->note);

		//SendDlgItemMessage(hDlg, IDC_STATIC, WM_SETTEXT, 0, (LPARAM)TEXT("FF"));




	}

	return (INT_PTR)TRUE;



	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK:
		{
			//save to db, use update
			// check first
			TCHAR tag[128];
			TCHAR category[128];
			TCHAR url[128];
			TCHAR user[128];
			TCHAR password[128];
			TCHAR phone[128];
			TCHAR mail[128];
			TCHAR note[128];

			TCHAR* value_array[8] = {
				tag,
				category,
				url,
				user,
				password,
				phone,
				mail,
				note
			};

			int idc_array[8] = {
				IDC_EDIT_TAG,
				IDC_EDIT_CATEGORY,
				IDC_EDIT_URL,
				IDC_EDIT_USER,
				IDC_EDIT_PASSWORD,
				IDC_EDIT_PHONE,
				IDC_EDIT_MAIL,
				IDC_EDIT_NOTE
			};



			for (size_t i = 0; i < 8; i++)
			{
				int sendLength = SendDlgItemMessage(hDlg, idc_array[i], EM_GETLINE, 0, (LPARAM)value_array[i]);
				/*HWND editControl = GetDlgItem(hDlg, ids[i]);*/
				//int sendLength = SendMessage(editControl, EM_GETLINE, 0, (LPARAM)wstr);
				value_array[i][sendLength] = TEXT('\0');
			}

			TCHAR* lpch = (TCHAR*)lParam;

			g_dispatcher->EditAccount(value_array);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;


		}


		break;
		case IDCANCEL:
			// do nothing
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		default:
			break;
		}

	}
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
		return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));

	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DeleteProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
	{

		TCHAR* lpch = (TCHAR*)lParam;
		//MessageBox(NULL, lpch, TEXT("see"), MB_OK);



		SendDlgItemMessage(hDlg, IDC_STATIC_DELTAG, WM_SETTEXT, 0, (LPARAM)lpch);

		return (INT_PTR)TRUE;
	}





	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case IDOK:
		{
			TCHAR tag[MAX_ITEM_LEN];

			int ind = SendMessage(GetDlgItem(GetParent(hDlg), IDC_LISTBOX_ACCOUNT), LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			SendMessage(GetDlgItem(GetParent(hDlg), IDC_LISTBOX_ACCOUNT), LB_GETTEXT, (WPARAM)ind, (LPARAM)tag);


			g_dispatcher->DeleteAccount(tag);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;


		}


		break;
		case IDCANCEL:
			// do nothing
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		default:
			break;
		}

	}
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
		return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));

	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK LoginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		int idc[] = {
			IDC_LOGIN_EDIT_PWD,
			IDC_LOGIN_STATIC_PWD,
			IDC_LOGIN_STATIC_WELCOME,
			IDC_LOGIN_STATIC_TIP
		};
		int ids[] = {
			0,
			IDS_LOGIN_STATIC_PWD,
			IDS_LOGIN_STATIC_WELCOME,
			IDS_LOGIN_STATIC_TIP
		};


		TCHAR static_str[128];

		LoadString(g_resource, IDS_LOGIN_TITLE, static_str, 128);
		SetWindowText(hDlg, static_str);

		for (size_t i = 1; i < (sizeof(idc) / sizeof(idc[0]) - 1); i++)
		{
			LoadString(g_resource, ids[i], static_str, 128);
			SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);
			SendDlgItemMessage(hDlg, idc[i], WM_SETFONT, (WPARAM)g_main_font, TRUE);
		}

		

		SendDlgItemMessage(hDlg, idc[0], WM_SETFONT, (WPARAM)g_main_font, TRUE);

		SendDlgItemMessage(hDlg, idc[3], WM_SETTEXT, 0, (LPARAM)NULL);
		SendDlgItemMessage(hDlg, idc[3], WM_SETFONT, (WPARAM)g_main_font, TRUE);

		SetFocus(GetDlgItem(hDlg, IDC_LOGIN_EDIT_PWD));



	}


	return FALSE;

	case WM_COMMAND:
	{
		int key = LOWORD(wParam);
		switch (key)
		{
		case IDOK:

		{


			TCHAR mm[128];
			SendDlgItemMessage(hDlg, IDC_LOGIN_EDIT_PWD, WM_GETTEXT, (WPARAM)128, (LPARAM)mm);



			EndDialog(hDlg, TRUE);
			return TRUE;
		}
		break;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return FALSE;
			break;
		default:
			break;
		}

	}

	break;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
	{
		return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));

		// use a bitmap to brush background
		//HBITMAP hBmp = (HBITMAP)LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_BITMAP1));

		//HBRUSH hBsh = CreatePatternBrush(hBmp);

		////hBsh = CreateSolidBrush(RGB(0, 255, 0));
		//return (INT_PTR)hBsh;
	}


	}
	return (INT_PTR)FALSE;

}

