
#include "stdafx.h"
#include "Resource.h"
#include "control.h"
#include "Dispather.h"

#include "global.h"
#include "../res804/resource.h"




int idc[] = {
	IDC_EDIT_SEARCH,
	IDC_LISTBOX_ACCOUNT,
	IDC_BUTTON_CLEAR,
	IDC_BUTTON_ADD,
	IDC_BUTTON_EDIT,
	IDC_BUTTON_DELETE
};
int ids[] = {
	0,
	0,
	IDS_BUTTONTEXT_CLEAR,
	IDS_BUTTONTEXT_ADD,
	IDS_BUTTONTEXT_EDIT,
	IDS_BUTTONTEXT_DELETE
};




BOOL OnInitFont(HWND hWnd)
{
	// Initialize the default font for Windows.
	g_main_font = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MicroSoft Yahei");

	g_mono_font = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");

	g_symbol = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI Symbol");

	return t;
}

BOOL OnInitControl(HWND hWnd)
{
	TCHAR buttontext[MAX_LOADSTRING];



	HWND search_edit = CreateWindow(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		0, 0, 0, 0, hWnd, (HMENU)IDC_EDIT_SEARCH, g_inst, NULL);

	HWND account_listbox = CreateWindow(_T("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |WS_VSCROLL | WS_TABSTOP | LBS_STANDARD | LBS_HASSTRINGS,
		0, 0, 0, 0, hWnd, (HMENU)IDC_LISTBOX_ACCOUNT, g_inst, NULL);

	//SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"SFS");

	for each (auto var in *(g_dispatcher->GetList()))
	{

		SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);

	}

	SendMessage(GetDlgItem(hWnd, IDC_EDIT_SEARCH), WM_SETFONT, (WPARAM)g_main_font, TRUE);
	SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT), WM_SETFONT, (WPARAM)g_main_font, TRUE);


	for (size_t i = 2; i < (sizeof(idc)/sizeof(idc[0])); i++)
	{
		LoadStringW(g_resource, ids[i], buttontext, MAX_LOADSTRING);
		CreateWindow(_T("BUTTON"),
			buttontext, WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)idc[i], g_inst, NULL);
		SendMessage(GetDlgItem(hWnd, idc[i]), WM_SETFONT, (WPARAM)g_main_font, t);
	}



	return t;

}

BOOL OnResizeControl(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);



	RECT rc_edit = { rc.left + 12, rc.top + 12, rc_edit.left + 138, rc_edit.top + 24 };

	RECT rc_button_clear = { rc_edit.right + 2, rc.top + 11,
		rc_button_clear.left + 40,rc_button_clear.top + 26 };

	RECT rc_listbox = { rc.left + 12 ,rc_edit.bottom + 12 ,rc_listbox.left + 180 , rc.bottom - 12 };


	RECT rc_button_add = { rc_listbox.right + 12,rc.bottom - 38,rc_listbox.right + 52,
		rc.bottom - 12 };


	RECT rc_button_delete = { rc.right - 52,rc.bottom - 38 ,rc.right - 12,
		rc.bottom - 12 };
	RECT rc_button_edit = { rc_button_delete.left - 52, rc.bottom - 38, rc_button_delete.left - 12,
		rc.bottom - 12 };

	RECT idr[] = {
		rc_edit,
		rc_listbox,
		rc_button_clear,
		rc_button_add,
		rc_button_edit,
		rc_button_delete
	};


	for (size_t i = 0; i <  (sizeof(idc) / sizeof(idc[0])); i++)
	{
		MoveWindow(GetDlgItem(hWnd, idc[i]),
			idr[i].left,
			idr[i].top,
			idr[i].right - idr[i].left,
			idr[i].bottom - idr[i].top,
			true);

	}


	return t;
}

BOOL OnShowMenu(HWND hWnd)
{
	return 0;
}
