#pragma once

#include <list>

// controls on the main window.
#define IDC_EDIT_SEARCH 3001
#define IDC_BUTTON_CLEAR 3002
#define IDC_LISTBOX_ACCOUNT 3003
#define IDC_BUTTON_ADD 3004
#define IDC_BUTTON_EDIT 3005
#define IDC_BUTTON_DELETE 3006

#define IDC_RDEDIT1 9991
#define IDC_RDEDIT2 9992
#define IDC_RDEDIT3 9993
#define IDC_RDEDIT4 9994
#define IDC_RDEDIT5 9995
#define IDC_RDEDIT6 9996
#define IDC_RDEDIT7 9997
#define IDC_RDEDIT8 9998
#define IDC_RDEDIT9 9999


void OnInitEdit(HWND hWnd);

void OnPaintEdit(HWND hWnd, HDC hdc);

// define global fonts
BOOL OnInitFont(HWND hWnd);

// show all the controls on main window
BOOL OnInitControl(HWND hWnd);

// resize controls to fit size.
BOOL OnResizeControl(HWND hWnd, LPARAM lParam);

// show the export menu
BOOL OnShowMenu(HWND hWnd);

// Refresh the items in listbox
void RefreshListbox(HWND hWnd);
//void RefreshListboxNew(HWND hWnd, std::list<AccountItem>* list);
// Show the detial
void OnPaint(HWND hWnd, HDC hdc);

// show complete list
void OnSearchChanged(HWND hWnd);

// set control font
void OnSetFont(HWND hWnd, LPARAM lParam);
BOOL CALLBACK SetFontProc(HWND hWnd, LPARAM lParam);
    
// refresh static
void ShowStaticTip(HWND hDlg, int control_id, LPTSTR str);