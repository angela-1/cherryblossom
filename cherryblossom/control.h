#pragma once

#include <list>

// controls on the main window.
#define IDC_EDIT_SEARCH 3001
#define IDC_BUTTON_CLEAR 3002
#define IDC_LISTBOX_ACCOUNT 3003
#define IDC_BUTTON_ADD 3004
#define IDC_BUTTON_EDIT 3005
#define IDC_BUTTON_DELETE 3006




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
	