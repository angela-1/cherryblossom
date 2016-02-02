#pragma once



// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    EditProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DeleteProc(HWND, UINT, WPARAM, LPARAM);

// login proc
INT_PTR CALLBACK LoginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// load resource
BOOL LoadResDll(LANGID lang_id);

