#pragma once



// �˴���ģ���а����ĺ�����ǰ������: 
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

