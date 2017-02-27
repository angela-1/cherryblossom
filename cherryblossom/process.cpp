

#include "stdafx.h"
#include "Resource.h"

#include <Prsht.h>


#include "process.h"

#include "control.h"
#include "utils.h"


//#include "Dispather.h"
#include "controller.h"
#include "Encrypter.h"
#include "global.h"


#include "../res804/resource.h"

// 这是声明
//extern Dispatcher* g_dispatcher;
extern Controller* g_dispatcher;






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
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDB_PNG1));
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

  HMENU hmenu = LoadMenu(g_resource, MAKEINTRESOURCE(IDM_CHERRYBLOSSOM));
  HWND hWnd = CreateWindowW(g_window_class, g_app_title, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, 600, 360, nullptr, hmenu, hInstance, nullptr);

  //MessageBox(NULL, L"o", L"nimei", MB_OK);

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

      g_dispatcher->refresh_account_list();

      RefreshListbox(hWnd);

      InvalidateRect(hWnd, NULL, true);


      //TCHAR src[200] = L"说个屁";

      //TCHAR py_str[2][100] = { L"",L"" };

      //Pinyin::get_pinyin_str(src, py_str);

      //MessageBox(NULL, py_str[0], L"SE", MB_OK);
      //MessageBox(NULL, py_str[1], L"SE", MB_OK);


    }

    break;
    case IDC_BUTTON_EDIT:
    {
      HWND account_list = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
      TCHAR lpch[MAX_STR_LEN];
      LRESULT ind = SendMessage(account_list, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
      if (ind != -1 && g_dispatcher->get_account_list()->size() > 0)
      {

        SendMessage(account_list, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

        //MessageBox(NULL, lpch, TEXT("see"), MB_OK);
        DialogBoxParam(g_inst, MAKEINTRESOURCE(IDD_EDIT), hWnd, EditProc, (LPARAM)lpch);

        InvalidateRect(hWnd, NULL, true);
      }


    }
    break;
    case IDC_BUTTON_DELETE:
    {
      HWND account_list = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
      TCHAR lpch[MAX_STR_LEN];
      LRESULT ind = SendMessage(account_list, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
      if (ind != -1 && g_dispatcher->get_account_list()->size() > 0)
      {
        SendMessage(account_list, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

        DialogBoxParam(g_inst, MAKEINTRESOURCE(IDD_CONFIRM), hWnd, DeleteProc, (LPARAM)lpch);

        g_dispatcher->refresh_account_list();
        g_dispatcher->get_account();
        RefreshListbox(hWnd);

        SendMessage(account_list, LB_SETCURSEL, (WPARAM)ind, (LPARAM)0);

        InvalidateRect(hWnd, NULL, true);
      }



      //Dispatcher* a = Dispatcher::GetInstance();

      //a->ClearAccountList();
      //a->MakeAccountList();

      //for each (auto var in *(a->GetList()))
      //{

      //    SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT), 
      //        LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);

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
    case IDM_SETTING:
      DialogBox(g_inst, MAKEINTRESOURCE(IDD_SETTING), hWnd, SettingProc);
      break;
    case IDM_EXPORT:
      DialogBox(g_inst, MAKEINTRESOURCE(IDD_EXPORT), hWnd, ExportProc);
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

    // for testing

    //RoundRect(hdc, 50, 5, 400, 30,
    //    2, 2);
    //Rectangle(hdc, 5, 5, 300, 100);

    // testting end

    OnPaint(hWnd, hdc);

    EndPaint(hWnd, &ps);
  }
  break;
  case WM_DESTROY:
  {
    // free resource

    FreeLibrary(g_resource);
    //delete g_dispatcher;

    Encrypter a{};
    a.EncryptDBFile(g_key);

    PostQuitMessage(0);
  }

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
  {
    OnSetFont(hDlg, NULL);

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_ABOUT_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    LoadString(g_resource, IDS_ABOUT_VERSION, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_ABOUT_VERSION, WM_SETTEXT, 0, (LPARAM)static_str);
    LoadString(g_resource, IDS_ABOUT_COPYRIGHT, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_ABOUT_COPYRIGHT, WM_SETTEXT, 0, (LPARAM)static_str);
    LoadString(g_resource, IDS_LABEL_OK, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDOK, WM_SETTEXT, 0, (LPARAM)static_str);

  }
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

    _stprintf_s(g_tcsTemp, _TEXT("lang\\res%x.dll"), lang_id);

    if ((g_resource = LoadLibrary(g_tcsTemp)) == NULL)
    {
      // we didn't find the desired language satellite DLL, lets go with English (default).
      g_resource = LoadLibrary(_TEXT("lang\\res804.dll"));
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
  {

    OnSetFont(hDlg, NULL);

    int idc[] =
    {
      IDC_ADD_TAG,
      IDC_ADD_CATEGORY,
      IDC_ADD_URL,
      IDC_ADD_USER,
      IDC_ADD_PASSWORD,
      IDC_ADD_PHONE,
      IDC_ADD_MAIL,
      IDC_ADD_NOTE,
      IDOK,
      IDCANCEL
    };

    int ids[] =
    {
      IDS_LABEL_TAG,
      IDS_LABEL_CATEGORY,
      IDS_LABEL_URL,
      IDS_LABEL_USER,
      IDS_LABEL_PASSWORD,
      IDS_LABEL_PHONE,
      IDS_LABEL_MAIL,
      IDS_LABEL_NOTE,
      IDS_LABEL_OK,
      IDS_LABEL_CANCEL
    };

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_ADD_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);


    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);
      //SendDlgItemMessage(hDlg, idc[i], WM_SETFONT, (WPARAM)g_main_font, TRUE);
    }
  }


  return (INT_PTR)TRUE;



  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    switch (wmId)
    {
    case IDOK:
    {
      TCHAR static_str[MAX_STR_LEN];


      //save to db
      // check first
      TCHAR tag[MAX_STR_LEN];
      TCHAR category[MAX_STR_LEN];
      TCHAR url[MAX_STR_LEN];
      TCHAR user[MAX_STR_LEN];
      TCHAR password[MAX_STR_LEN];
      TCHAR phone[MAX_STR_LEN];
      TCHAR mail[MAX_STR_LEN];
      TCHAR note[MAX_STR_LEN];

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
        IDC_ADD_EDIT_TAG,
        IDC_ADD_EDIT_CATEGORY,
        IDC_ADD_EDIT_URL,
        IDC_ADD_EDIT_USER,
        IDC_ADD_EDIT_PASSWORD,
        IDC_ADD_EDIT_PHONE,
        IDC_ADD_EDIT_MAIL,
        IDC_ADD_EDIT_NOTE,

      };

      for (size_t i = 0; i < 8; i++)
      {
        value_array[i][0] = MAX_STR_LEN;
        SendDlgItemMessage(hDlg, id_array[i], EM_LIMITTEXT, (WPARAM)100, 0);
      }

      for (size_t i = 0; i < 7; i++)
      {
        LRESULT line_len = SendDlgItemMessage(hDlg, id_array[i], EM_GETLINE, 0, (LPARAM)value_array[i]);
        /*HWND editControl = GetDlgItem(hDlg, ids[i]);*/
        //int sendLength = SendMessage(editControl, EM_GETLINE, 0, (LPARAM)wstr);
        value_array[i][line_len] = TEXT('\0');

      }

      SendDlgItemMessage(hDlg, id_array[7], WM_GETTEXT, MAX_STR_LEN, (LPARAM)value_array[7]);

      // trim value_array before send to add account
      for (size_t i = 0; i < 8; i++)
      {
        trim_space(value_array[i]);
      }


      if (wcscmp(tag, L"") != 0)
      {
        if (g_dispatcher->check_account(tag))
        {
          g_dispatcher->add_account(value_array);



          EndDialog(hDlg, LOWORD(wParam));

          return (INT_PTR)TRUE;
        }
        else
        {
          HWND tag_edit = GetDlgItem(hDlg, IDC_ADD_EDIT_TAG);
          LoadString(g_resource, IDS_ADD_TIPEXIST, static_str, MAX_STR_LEN);

          SendMessage(tag_edit, WM_SETTEXT, 0, (LPARAM)static_str);

        }

      }
      else
      {
        HWND tag_edit = GetDlgItem(hDlg, IDC_ADD_EDIT_TAG);
        LoadString(g_resource, IDS_ADD_TIPNULL, static_str, MAX_STR_LEN);

        SendMessage(tag_edit, WM_SETTEXT, 0, (LPARAM)static_str);

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
    OnSetFont(hDlg, NULL);


    int idc[] =
    {

      IDC_EDIT_TAG,
      IDC_EDIT_CATEGORY,
      IDC_EDIT_URL,
      IDC_EDIT_USER,
      IDC_EDIT_PASSWORD,
      IDC_EDIT_PHONE,
      IDC_EDIT_MAIL,
      IDC_EDIT_NOTE,
      IDOK,
      IDCANCEL
    };

    int ids[] =
    {
      IDS_LABEL_TAG,
      IDS_LABEL_CATEGORY,
      IDS_LABEL_URL,
      IDS_LABEL_USER,
      IDS_LABEL_PASSWORD,
      IDS_LABEL_PHONE,
      IDS_LABEL_MAIL,
      IDS_LABEL_NOTE,
      IDS_LABEL_OK,
      IDS_LABEL_CANCEL


    };

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_EDIT_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);
      //SendDlgItemMessage(hDlg, idc[i], WM_SETFONT, (WPARAM)g_main_font, TRUE);
    }

    // old
    TCHAR* lpch = (TCHAR*)lParam;

    //MessageBox(NULL, lpch, TEXT("see"), MB_OK);
    g_dispatcher->read_account(lpch);
    Account* account = g_dispatcher->get_account();


    SendDlgItemMessage(hDlg, IDC_EDIT_TAG, WM_SETTEXT, 0, (LPARAM)account->tag);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_TAG, WM_SETTEXT, 0, (LPARAM)account->tag);

    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_CATEGORY, WM_SETTEXT, 0, (LPARAM)account->category);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_URL, WM_SETTEXT, 0, (LPARAM)account->url);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_USER, WM_SETTEXT, 0, (LPARAM)account->user);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_PASSWORD, WM_SETTEXT, 0, (LPARAM)account->password);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_PHONE, WM_SETTEXT, 0, (LPARAM)account->phone);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_MAIL, WM_SETTEXT, 0, (LPARAM)account->mail);
    SendDlgItemMessage(hDlg, IDC_EDIT_EDIT_NOTE, WM_SETTEXT, 0, (LPARAM)account->note);

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
      TCHAR tag[MAX_STR_LEN];
      TCHAR category[MAX_STR_LEN];
      TCHAR url[MAX_STR_LEN];
      TCHAR user[MAX_STR_LEN];
      TCHAR password[MAX_STR_LEN];
      TCHAR phone[MAX_STR_LEN];
      TCHAR mail[MAX_STR_LEN];
      TCHAR note[MAX_STR_LEN];

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

      for (size_t i = 0; i < 8; i++)
      {
        value_array[i][0] = MAX_STR_LEN;
      }

      int idc_array[8] = {
        IDC_EDIT_EDIT_TAG,
        IDC_EDIT_EDIT_CATEGORY,
        IDC_EDIT_EDIT_URL,
        IDC_EDIT_EDIT_USER,
        IDC_EDIT_EDIT_PASSWORD,
        IDC_EDIT_EDIT_PHONE,
        IDC_EDIT_EDIT_MAIL,
        IDC_EDIT_EDIT_NOTE
      };



      for (size_t i = 0; i < 7; i++)
      {
        LRESULT sendLength = SendDlgItemMessage(hDlg, idc_array[i], EM_GETLINE, 0, (LPARAM)value_array[i]);
        value_array[i][sendLength] = TEXT('\0');
      }

      SendDlgItemMessage(hDlg, idc_array[7], WM_GETTEXT, MAX_STR_LEN, (LPARAM)value_array[7]);


      TCHAR* lpch = (TCHAR*)lParam;

      g_dispatcher->update_account(value_array);


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
    OnSetFont(hDlg, NULL);

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_CONFIRM_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    LoadString(g_resource, IDS_CONFIRM_WILLDEL, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_CONFIRM_DELTIP, WM_SETTEXT, 0, (LPARAM)static_str);



    TCHAR* lpch = (TCHAR*)lParam;
    //MessageBox(NULL, lpch, TEXT("see"), MB_OK);

    SendDlgItemMessage(hDlg, IDC_CONFIRM_DELTAG, WM_SETTEXT, 0, (LPARAM)lpch);

    LoadString(g_resource, IDS_LABEL_OK, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDOK, WM_SETTEXT, 0, (LPARAM)static_str);
    LoadString(g_resource, IDS_LABEL_CANCEL, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDCANCEL, WM_SETTEXT, 0, (LPARAM)static_str);


    /*SendDlgItemMessage(hDlg, IDC_STATIC_DELTIP, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDC_STATIC_DELTAG, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    */


    return (INT_PTR)TRUE;
  }





  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);

    switch (wmId)
    {
    case IDOK:
    {
      TCHAR tag[MAX_STR_LEN];

      LRESULT ind = SendMessage(GetDlgItem(GetParent(hDlg), IDC_LISTBOX_ACCOUNT), LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

      SendMessage(GetDlgItem(GetParent(hDlg), IDC_LISTBOX_ACCOUNT), LB_GETTEXT, (WPARAM)ind, (LPARAM)tag);


      g_dispatcher->del_account(tag);

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
    OnSetFont(hDlg, NULL);

    int idc[] = {
      IDC_LOGIN_EDIT_PWD,
      IDC_LOGIN_STATIC_WELCOME,
      IDC_LOGIN_STATIC_PWD,

      IDOK
    };
    int ids[] = {
      0,
      IDS_LOGIN_WELCOME,
      IDS_LOGIN_PASSWD,

      IDS_LABEL_OK

    };


    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_LOGIN_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    for (size_t i = 1; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);

    }


    SetFocus(GetDlgItem(hDlg, IDC_LOGIN_EDIT_PWD));



  }


  return FALSE;

  case WM_COMMAND:
  {
    int key = LOWORD(wParam);
    int notifyId = HIWORD(wParam);

    switch (key)
    {
    case IDC_LOGIN_EDIT_PWD:
    {
      if (notifyId == EN_CHANGE)
      {

        ShowStaticTip(hDlg, IDC_LOGIN_STATIC_TIP, L"");
      }

    }
    break;
    case IDOK:

    {


      TCHAR key[MAX_STR_LEN]; // less than 16
      SendDlgItemMessage(hDlg, IDC_LOGIN_EDIT_PWD, WM_GETTEXT, (WPARAM)MAX_STR_LEN, (LPARAM)key);


      Encrypter a{};


      if (a.Validate(key))
      {
        lstrcpy(g_key, key);

        a.DecryptDBFile(key);

        EndDialog(hDlg, TRUE);
        return TRUE;

      }
      else
      {
        TCHAR static_str[MAX_STR_LEN];

        LoadString(g_resource, IDS_LOGIN_CAUTION, static_str, MAX_STR_LEN);

        ShowStaticTip(hDlg, IDC_LOGIN_STATIC_TIP, static_str);

        return FALSE;
      }



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

INT_PTR CALLBACK SettingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
  {
    OnSetFont(hDlg, NULL);


    int idc[] =
    {
      IDC_SETTING_GROUPPWD,
      IDC_SETTING_OLDPWD,
      IDC_SETTING_NEWPWD,
      IDC_SETTING_CONFIRMPWD,
      IDC_SETTING_BUTTON_DONE,
      IDC_SETTING_GROUPLANG,
      IDC_SETTING_LANG,
      IDOK,
      IDCANCEL
    };

    INT ids[] =
    {
      IDS_SETTING_MODPWD,
      IDS_SETTING_OLDPWD,
      IDS_SETTING_NEWPWD,
      IDS_SETTING_CONFIRMPWD,
      IDS_SETTING_DONE,
      IDS_SETTING_CHOOSELANG,
      IDS_SETTING_LANG,
      IDS_LABEL_OK,
      IDS_LABEL_CANCEL
    };

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_SETTING_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);
      //SendDlgItemMessage(hDlg, idc[i], WM_SETFONT, (WPARAM)g_main_font, TRUE);
    }

    LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_ADDSTRING, 0, (LPARAM)static_str);
    LoadString(g_resource, IDS_SETTING_LANG_ZH, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_ADDSTRING, 0, (LPARAM)static_str);

    /*SendDlgItemMessage(hDlg, IDC_COMBO_LANG, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDC_SETTING_TIP, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDC_SETTING_STATIC_TIP, WM_SETFONT, (WPARAM)g_main_font, TRUE);*/


    TCHAR lang[MAX_STR_LEN];
    GetPrivateProfileString(TEXT("cherryblossom"),
      TEXT("language"), L"zh-CN", lang, MAX_STR_LEN, g_config_file);
    if (wcscmp(lang, L"en-US") == 0)
    {
      LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);
      LRESULT cursel = SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_FINDSTRING, -1, (LPARAM)static_str);
      SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_SETCURSEL, cursel, (LPARAM)0);
    }
    else
    {
      SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_SETCURSEL, 1, (LPARAM)0);
    }




  }


  return FALSE;

  case WM_COMMAND:
  {
    int key = LOWORD(wParam);
    int notifyId = HIWORD(wParam);

    switch (key)
    {

    case IDC_SETTING_EDIT_NEWPWD:
    case IDC_SETTING_EDIT_CONFIRMPWD:
    {
      if (notifyId == EN_CHANGE)
      {
        TCHAR pwd[MAX_STR_LEN];
        TCHAR confirm_pwd[MAX_STR_LEN];

        if (notifyId == EN_CHANGE)
        {
          SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_NEWPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)pwd);
          SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_CONFIRMPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);

          if (wcscmp(pwd, confirm_pwd) == 0 &&
            wcscmp(pwd, L"") != 0)
          {
            ShowStaticTip(hDlg, IDC_SETTING_TIP, L"");
            EnableWindow(GetDlgItem(hDlg, IDC_SETTING_BUTTON_DONE),
              TRUE);
          }
          else
          {
            TCHAR static_str[MAX_STR_LEN];

            LoadString(g_resource, IDS_WIZARDPWD_NOTSAME,
              static_str, MAX_STR_LEN);


            ShowStaticTip(hDlg, IDC_SETTING_TIP, static_str);
            EnableWindow(GetDlgItem(hDlg, IDC_SETTING_BUTTON_DONE),
              FALSE);

          }

        }
      }
    }
    break;
    case IDC_SETTING_BUTTON_DONE:
    {
      // validate old password
      TCHAR pwd[MAX_STR_LEN];
      SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_OLDPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)pwd);
      TCHAR confirm_pwd[MAX_STR_LEN];
      SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_CONFIRMPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);

      Encrypter a{};
      if (a.Validate(pwd))
      {
        a.CreateKeyFile(confirm_pwd);
        lstrcpy(g_key, confirm_pwd);
        DestroyWindow(GetParent(hDlg));

      }
      else
      {
        TCHAR static_str[MAX_STR_LEN];

        LoadString(g_resource, IDS_SETTING_PWDWRONG,
          static_str, MAX_STR_LEN);
        ShowStaticTip(hDlg, IDC_SETTING_TIP, static_str);
      }



    }

    break;
    case IDC_COMBO_LANG:
    {
      if (HIWORD(wParam) == CBN_SELCHANGE)
      {
        TCHAR lpch[MAX_STR_LEN];
        LRESULT sel_index = SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_GETCURSEL, 0, 0);
        SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_GETLBTEXT, sel_index, (LPARAM)lpch);

        TCHAR static_str[MAX_STR_LEN];

        LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);

        //MessageBox(NULL, lpch, L"see now", MB_OK);
        if (wcscmp(lpch, static_str) == 0)
        {
          WritePrivateProfileString(TEXT("cherryblossom"),
            TEXT("language"), L"en-US", g_config_file);
        }
        else
        {
          WritePrivateProfileString(TEXT("cherryblossom"),
            TEXT("language"), L"zh-CN", g_config_file);
        }


        LoadString(g_resource, IDS_SETTING_LANGTIP, static_str, MAX_STR_LEN);

        SendDlgItemMessage(hDlg, IDC_SETTING_STATIC_TIP,
          WM_SETTEXT, 0, (LPARAM)static_str);


      }

    }
    break;
    case IDOK:
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

    return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));




  }
  return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ExportProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
  {
    OnSetFont(hDlg, NULL);


    int idc[] =
    {
      IDC_SETTING_GROUPPWD,
      IDC_SETTING_OLDPWD,
      IDC_SETTING_NEWPWD,
      IDC_SETTING_CONFIRMPWD,
      IDC_SETTING_BUTTON_DONE,
      IDC_SETTING_GROUPLANG,
      IDC_SETTING_LANG,
      IDOK,
      IDCANCEL
    };

    INT ids[] =
    {
      IDS_SETTING_MODPWD,
      IDS_SETTING_OLDPWD,
      IDS_SETTING_NEWPWD,
      IDS_SETTING_CONFIRMPWD,
      IDS_SETTING_DONE,
      IDS_SETTING_CHOOSELANG,
      IDS_SETTING_LANG,
      IDS_LABEL_OK,
      IDS_LABEL_CANCEL
    };

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_SETTING_CAPTION, static_str, MAX_STR_LEN);
    SetWindowText(hDlg, static_str);

    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);
      //SendDlgItemMessage(hDlg, idc[i], WM_SETFONT, (WPARAM)g_main_font, TRUE);
    }

    LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_ADDSTRING, 0, (LPARAM)static_str);
    LoadString(g_resource, IDS_SETTING_LANG_ZH, static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_ADDSTRING, 0, (LPARAM)static_str);

    /*SendDlgItemMessage(hDlg, IDC_COMBO_LANG, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDC_SETTING_TIP, WM_SETFONT, (WPARAM)g_main_font, TRUE);
    SendDlgItemMessage(hDlg, IDC_SETTING_STATIC_TIP, WM_SETFONT, (WPARAM)g_main_font, TRUE);*/


    TCHAR lang[MAX_STR_LEN];
    GetPrivateProfileString(TEXT("cherryblossom"),
      TEXT("language"), L"zh-CN", lang, MAX_STR_LEN, g_config_file);
    if (wcscmp(lang, L"en-US") == 0)
    {
      LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);
      LRESULT cursel = SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_FINDSTRING, -1, (LPARAM)static_str);
      SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_SETCURSEL, cursel, (LPARAM)0);
    }
    else
    {
      SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_SETCURSEL, 1, (LPARAM)0);
    }




  }


  return FALSE;

  case WM_COMMAND:
  {
    int key = LOWORD(wParam);
    int notifyId = HIWORD(wParam);

    switch (key)
    {

    case IDC_SETTING_EDIT_NEWPWD:
    case IDC_SETTING_EDIT_CONFIRMPWD:
    {
      if (notifyId == EN_CHANGE)
      {
        TCHAR pwd[MAX_STR_LEN];
        TCHAR confirm_pwd[MAX_STR_LEN];

        if (notifyId == EN_CHANGE)
        {
          SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_NEWPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)pwd);
          SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_CONFIRMPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);

          if (wcscmp(pwd, confirm_pwd) == 0 &&
            wcscmp(pwd, L"") != 0)
          {
            ShowStaticTip(hDlg, IDC_SETTING_TIP, L"");
            EnableWindow(GetDlgItem(hDlg, IDC_SETTING_BUTTON_DONE),
              TRUE);
          }
          else
          {
            TCHAR static_str[MAX_STR_LEN];

            LoadString(g_resource, IDS_WIZARDPWD_NOTSAME,
              static_str, MAX_STR_LEN);


            ShowStaticTip(hDlg, IDC_SETTING_TIP, static_str);
            EnableWindow(GetDlgItem(hDlg, IDC_SETTING_BUTTON_DONE),
              FALSE);

          }

        }
      }
    }
    break;
    case IDC_SETTING_BUTTON_DONE:
    {
      // validate old password
      TCHAR pwd[MAX_STR_LEN];
      SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_OLDPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)pwd);
      TCHAR confirm_pwd[MAX_STR_LEN];
      SendDlgItemMessage(hDlg, IDC_SETTING_EDIT_CONFIRMPWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);

      Encrypter a{};
      if (a.Validate(pwd))
      {
        a.CreateKeyFile(confirm_pwd);
        lstrcpy(g_key, confirm_pwd);
        DestroyWindow(GetParent(hDlg));

      }
      else
      {
        TCHAR static_str[MAX_STR_LEN];

        LoadString(g_resource, IDS_SETTING_PWDWRONG,
          static_str, MAX_STR_LEN);
        ShowStaticTip(hDlg, IDC_SETTING_TIP, static_str);
      }



    }

    break;
    case IDC_COMBO_LANG:
    {
      if (HIWORD(wParam) == CBN_SELCHANGE)
      {
        TCHAR lpch[MAX_STR_LEN];
        LRESULT sel_index = SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_GETCURSEL, 0, 0);
        SendDlgItemMessage(hDlg, IDC_COMBO_LANG, CB_GETLBTEXT, sel_index, (LPARAM)lpch);

        TCHAR static_str[MAX_STR_LEN];

        LoadString(g_resource, IDS_SETTING_LANG_EN, static_str, MAX_STR_LEN);

        //MessageBox(NULL, lpch, L"see now", MB_OK);
        if (wcscmp(lpch, static_str) == 0)
        {
          WritePrivateProfileString(TEXT("cherryblossom"),
            TEXT("language"), L"en-US", g_config_file);
        }
        else
        {
          WritePrivateProfileString(TEXT("cherryblossom"),
            TEXT("language"), L"zh-CN", g_config_file);
        }


        LoadString(g_resource, IDS_SETTING_LANGTIP, static_str, MAX_STR_LEN);

        SendDlgItemMessage(hDlg, IDC_SETTING_STATIC_TIP,
          WM_SETTEXT, 0, (LPARAM)static_str);


      }

    }
    break;
    case IDOK:
    {
      //AssembleHtml();
      //Exporter::ExportTxt(L"aa", L"说你妹的nimei");
    }
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

    return (BOOL)((HBRUSH)GetStockObject(WHITE_BRUSH));



  }
  return (INT_PTR)FALSE;
}

void ShowWizard(HWND hwndOwner)
{
  TCHAR static_str[MAX_STR_LEN];

  HPROPSHEETPAGE ahpsp[3];

  PROPSHEETPAGE psp = { sizeof(psp) };

  psp.hInstance = g_inst;
  psp.dwFlags = PSP_USEHEADERTITLE;;
  psp.lParam = (LPARAM)NULL;

  LoadString(g_resource, IDS_WIZARD_WELCOME_CAPTION, static_str, MAX_STR_LEN);
  psp.pszHeaderTitle = static_str;

  psp.pszTemplate = MAKEINTRESOURCE(IDD_WIZARD_WELCOME);
  psp.pfnDlgProc = WizardWelcomeProc;
  ahpsp[0] = CreatePropertySheetPage(&psp);

  PROPSHEETPAGE psp1 = { sizeof(psp1) };

  psp1.hInstance = g_inst;
  psp1.dwFlags = PSP_USEHEADERTITLE;
  psp1.lParam = (LPARAM)NULL;
  LoadString(g_resource, IDS_WIZARDPWD_SETPWD, static_str, MAX_STR_LEN);

  psp1.pszHeaderTitle = static_str;

  psp1.pszTemplate = MAKEINTRESOURCE(IDD_WIZARD_PWD);
  psp1.pfnDlgProc = WizardPwdProc;
  ahpsp[1] = CreatePropertySheetPage(&psp1);

  PROPSHEETPAGE psp2 = { sizeof(psp2) };

  psp2.hInstance = g_inst;
  psp2.dwFlags = PSP_USEHEADERTITLE;
  psp2.lParam = (LPARAM)NULL;
  LoadString(g_resource, IDS_WIZARDENJOY_USE, static_str, MAX_STR_LEN);
  psp2.pszHeaderTitle = static_str;

  psp2.pszTemplate = MAKEINTRESOURCE(IDD_WIZARD_ENJOY);
  psp2.pfnDlgProc = WizardEnjoyProc;

  ahpsp[2] = CreatePropertySheetPage(&psp2);

  // g_hInstance is the global HINSTANCE of the application.
  // ahpsp is an array of HPROPSHEETPAGE handles.

  PROPSHEETHEADER psh = { sizeof(psh) };

  psh.hInstance = g_inst;
  psh.hwndParent = NULL;
  psh.phpage = ahpsp;

  psh.dwFlags = PSH_WIZARD | PSH_AEROWIZARD;
  //psh.dwFlags = PSH_WIZARD97 |PSH_WATERMARK | PSH_HEADER;
  //psh.pszbmWatermark = MAKEINTRESOURCE(IDB_BITMAP2);
  //psh.pszbmHeader = MAKEINTRESOURCE(IDB_BITMAP2);

  LoadString(g_resource, IDS_WIZARD_CAPTION, static_str, MAX_STR_LEN);

  psh.pszCaption = static_str;
  psh.nStartPage = 0;
  psh.nPages = 3;

  PropertySheet(&psh);




  return;

}

INT_PTR CALLBACK WizardWelcomeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

  //UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
  {

    CreateDirectory(g_cur_var_dir, NULL);

    CreateDB();

    // show string
    OnSetFont(hDlg, NULL);

    int idc[] =
    {
      IDC_WIZARDWELCOME_TIP1,
      IDC_WIZARDWELCOME_TIP2
    };

    int ids[] =
    {
      IDS_WIZARDWELCOME_TIP2,
      IDS_WIZARDWELCOME_TIP1
    };

    TCHAR static_str[MAX_STR_LEN];



    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);

    }




    return FALSE;
  }



  //case WM_CTLCOLORDLG:
  //{
  //    HBITMAP hBmp = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
  //    
  //    HBRUSH hBsh = CreatePatternBrush(hBmp);   
  //    
  //    //hBsh = CreateSolidBrush(RGB(0, 255, 0));
  //    return (INT_PTR)hBsh;
  //}


  case WM_NOTIFY:
  {

    LPNMHDR pnmh = (LPNMHDR)lParam;

    switch (pnmh->code)
    {



    case PSN_SETACTIVE:
    {
      TCHAR static_str[MAX_STR_LEN];

      LoadString(g_resource, IDS_WIZARD_NEXT, static_str, MAX_STR_LEN);
      PropSheet_SetNextText(hDlg, static_str);

      PropSheet_ShowWizButtons(hDlg,
        PSWIZB_NEXT,
        PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_CANCEL);
    }



    return TRUE;

    }


  }





  }
  return (INT_PTR)FALSE;
}

INT_PTR CALLBACK WizardPwdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
  {
    OnSetFont(hDlg, NULL);

    int idc[] =
    {
      IDC_WIZARDPWD_TIP1,
      IDC_WIZARDPWD_PWD,
      IDC_WIZARDPWD_CONFIRMPWD
    };

    int ids[] =
    {
      IDS_WIZARDPWD_FORGET,
      IDS_WIZARDPWD_PWD,
      IDS_WIZARDPWD_CONFIRMPWD
    };

    TCHAR static_str[MAX_STR_LEN];



    for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      SendDlgItemMessage(hDlg, idc[i], WM_SETTEXT, 0, (LPARAM)static_str);

    }
  }

  return FALSE;

  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    int notifyId = HIWORD(wParam);

    switch (wmId)
    {

    case IDC_EDIT_PWD:
    case IDC_EDIT_CONFIRM:
    {
      TCHAR pwd[MAX_STR_LEN];
      TCHAR confirm_pwd[MAX_STR_LEN];

      if (notifyId == EN_CHANGE)
      {
        SendDlgItemMessage(hDlg, IDC_EDIT_PWD, WM_GETTEXT, MAX_STR_LEN, (LPARAM)pwd);
        SendDlgItemMessage(hDlg, IDC_EDIT_CONFIRM, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);

        if (wcscmp(pwd, confirm_pwd) == 0 &&
          wcscmp(pwd, L"") != 0)
        {
          ShowStaticTip(hDlg, IDC_WIZARDPWD_TIP2, L"");

          SendMessage(hDlg, PSM_ENABLEWIZBUTTONS,
            PSWIZB_NEXT, PSWIZB_NEXT);
        }
        else
        {
          TCHAR static_str[MAX_STR_LEN];

          LoadString(g_resource, IDS_WIZARDPWD_NOTSAME,
            static_str, MAX_STR_LEN);


          ShowStaticTip(hDlg, IDC_WIZARDPWD_TIP2, static_str);

          SendMessage(hDlg, PSM_ENABLEWIZBUTTONS,
            NULL, PSWIZB_NEXT);
        }



      }

    }


    break;

    }
    return FALSE;
  }

  case WM_NOTIFY:
  {

    LPNMHDR pnmh = (LPNMHDR)lParam;

    switch (pnmh->code)
    {

    case PSN_WIZNEXT:
    {

      TCHAR confirm_pwd[MAX_STR_LEN];

      SendDlgItemMessage(hDlg, IDC_EDIT_CONFIRM, WM_GETTEXT, MAX_STR_LEN, (LPARAM)confirm_pwd);


      Encrypter a{};
      a.CreateKeyFile(confirm_pwd);

      a.EncryptDBFile(confirm_pwd);

      // TODO: delete g_db_file

      return FALSE;
    }


    case PSN_SETACTIVE:

      TCHAR static_str[MAX_STR_LEN];

      LoadString(g_resource, IDS_WIZARD_NEXT, static_str, MAX_STR_LEN);
      PropSheet_SetNextText(hDlg, static_str);

      PropSheet_ShowWizButtons(hDlg,
        PSWIZB_NEXT,
        PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_CANCEL);

      SendMessage(hDlg, PSM_ENABLEWIZBUTTONS,
        NULL, PSWIZB_NEXT);

      return TRUE;

    }


  }





  }
  return (INT_PTR)FALSE;
}

INT_PTR CALLBACK WizardEnjoyProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  //UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
  {
    CreateConfigFile();

    OnSetFont(hDlg, NULL);

    TCHAR static_str[MAX_STR_LEN];

    LoadString(g_resource, IDS_WIZARDENJOY_TIP,
      static_str, MAX_STR_LEN);
    SendDlgItemMessage(hDlg, IDC_WIZARDENJOY_TIP, WM_SETTEXT,
      NULL, (LPARAM)static_str);

    return FALSE;
  }




  case WM_NOTIFY:
  {

    LPNMHDR pnmh = (LPNMHDR)lParam;

    switch (pnmh->code)
    {



    case PSN_SETACTIVE:




      PropSheet_ShowWizButtons(hDlg,
        PSWIZB_FINISH,
        PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_CANCEL | PSWIZB_FINISH);

      TCHAR static_str[MAX_STR_LEN];

      LoadString(g_resource, IDS_WIZARDENJOY_DONE,
        static_str, MAX_STR_LEN);

      PropSheet_SetFinishText(hDlg, static_str);
      return TRUE;

    }


  }





  }
  return (INT_PTR)FALSE;
}

void OnInitPath()
{
  // set file paths
  TCHAR file_path[MAX_STR_LEN];

  GetModuleFileName(NULL, file_path, MAX_STR_LEN);

  TCHAR* p = wcsrchr(file_path, '\\');
  *p = '\0';

  lstrcpy(g_cur_var_dir, file_path);
  lstrcat(g_cur_var_dir, L"\\var");

  lstrcpy(g_key_file, file_path);
  lstrcat(g_key_file, L"\\var\\.key");


  lstrcpy(g_db_file, file_path);
  lstrcat(g_db_file, L"\\var\\cherryblossom.db3");

  lstrcpy(g_db_file_s, g_db_file);
  lstrcat(g_db_file_s, L"s");


  lstrcpy(g_config_file, file_path);
  lstrcat(g_config_file, L"\\var\\config.ini");

  unicode_to_utf8(g_db_file, g_chr_db_file);





}





bool IsFirstRun()
{
  return (!file_exists(g_key_file) &&
    !file_exists(g_db_file) &&
    !file_exists(g_config_file));

}

int CreateDB()
{

  HANDLE hFile = CreateFile(g_db_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL, NULL);
  CloseHandle(hFile);

  Account::CreateTable();

  return 0;


}

int CreateConfigFile()
{
  TCHAR lp[MAX_STR_LEN];


  GetUserDefaultLocaleName(lp, MAX_STR_LEN);
  TCHAR locale_name[MAX_STR_LEN] = L"[cherryblossom]\r\nlanguage=";
  //_stprintf_s(locale_name, _TEXT("[cherry]\r\nlanguage=%s"), lp);

  lstrcat(locale_name, lp);

  char buf[MAX_STR_LEN];
  unicode_to_ansi(locale_name, buf);

  HANDLE hFile = CreateFile(g_config_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL, NULL);

  DWORD numofbyte;
  WriteFile(hFile, buf, (DWORD)strlen(buf), &numofbyte, NULL);

  CloseHandle(hFile);
  return 0;

}
