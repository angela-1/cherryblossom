#pragma once


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
BOOL OnResizeControl(HWND hWnd);

// show the export menu
BOOL OnShowMenu(HWND hWnd);
