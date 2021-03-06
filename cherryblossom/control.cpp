
#include "stdafx.h"
#include "Resource.h"

#include "control.h"
#include "utils.h"


//#include "Dispather.h"
#include "controller.h"


#include "global.h"

#include "../res804/resource.h"


// ��������
//extern Dispatcher* g_dispatcher;
extern Controller* g_dispatcher;






void OnInitEdit(HWND hWnd)
{


  LONG64 idc[] = {
    IDC_RDEDIT1,
    IDC_RDEDIT2,
    IDC_RDEDIT3,
    IDC_RDEDIT4,
    IDC_RDEDIT5,
    IDC_RDEDIT6,
    IDC_RDEDIT7,
    IDC_RDEDIT8,
    IDC_RDEDIT9

  };



  for (int i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
  {
    int y = 12 + 25 * i;
    int ht = 25;
    int sty = WS_CHILD | WS_VISIBLE | ES_READONLY;
    if (i == 7) {
      sty = sty | ES_MULTILINE;
      ht = 50;
    }
    if (i == 8) {
      y += 25;
    }
    CreateWindow(_T("EDIT"),
      _T(""), sty,
      310, y, 260, ht, hWnd, (HMENU)idc[i], g_inst, NULL);
    //SendMessage(GetDlgItem(hWnd, idc[i]), WM_SETFONT, (WPARAM)g_main_font, t);
  }

 /* SetWindowLong(GetDlgItem(hWnd, IDC_RDEDIT8), GWL_STYLE, 
    GetWindowLong(GetDlgItem(hWnd, IDC_RDEDIT8), GWL_STYLE) | ES_MULTILINE);*/

  OnSetFont(hWnd, NULL);


 
}


void OnPaintEdit(HWND hWnd, HDC hdc)
{
  int idc[] = {
    IDC_RDEDIT1,
    IDC_RDEDIT2,
    IDC_RDEDIT3,
    IDC_RDEDIT4,
    IDC_RDEDIT5,
    IDC_RDEDIT6,
    IDC_RDEDIT7,
    IDC_RDEDIT8,
    IDC_RDEDIT9

  };

  SetBkMode(hdc, TRANSPARENT);

  SelectObject(hdc, g_main_font);

  RECT grc;
  GetClientRect(hWnd, &grc);
  grc.right = 206;

  HBRUSH gb = CreateSolidBrush(RGB(230, 230, 230));
  FillRect(hdc, &grc, gb);

  HWND account_listbox = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
  TCHAR lpch[MAX_STR_LEN];
  LRESULT ind = SendMessage(account_listbox, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
  SendMessage(account_listbox, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

  if (ind != -1 && g_dispatcher->GetAccountList()->size() > 0)
  {
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
      IDS_LABEL_LASTMOD

    };
    TCHAR static_str[MAX_STR_LEN];

    TCHAR title[9][MAX_STR_LEN];

    for (size_t i = 0; i < (sizeof(ids) / sizeof(ids[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      wcscpy_s(title[i], static_str);

    }

    g_dispatcher->ReadAccount(lpch);
    Account* account = g_dispatcher->GetAccount();
    LPTSTR detial[9] = { account->tag, account->category,
      account->url, account->user, account->password,
      account->phone, account->mail, account->note, account->last_mod };


    for (int i = 0; i < 9; i++)
    {
      int y = 12 + 25 * i;
      if (i == 8) {
        y += 25;
      }
      SetTextAlign(hdc, TA_RIGHT | TA_TOP);
      TextOut(hdc, 300, y, title[i], lstrlen(title[i]));

      /*SetTextAlign(hdc, TA_LEFT | TA_TOP);
      TextOut(hdc, 320, 12 + 25 * i, detial[i], lstrlen(detial[i]));*/

      SendMessage(GetDlgItem(hWnd, idc[i]), WM_SETTEXT, 0, (LPARAM)detial[i]);


    }
  }
  else
  {
    TCHAR static_str[MAX_STR_LEN];
    LoadString(g_resource, IDS_MAIN_MAINTIP, static_str, MAX_STR_LEN);
    SendMessage(GetDlgItem(hWnd, idc[0]), WM_SETTEXT, 0, (LPARAM)static_str);

	for (int i = 1; i < 9; i++)
	{
		SendMessage(GetDlgItem(hWnd, idc[i]), WM_SETTEXT, 0, (LPARAM)L"");
	}
  }

}

BOOL OnInitFont(HWND hWnd)
{
  // Initialize the default font for Windows.
  g_main_font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MicroSoft Yahei");

  g_mono_font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");

  g_symbol = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI Symbol");

  return t;
}

BOOL OnInitControl(HWND hWnd)
{



  LONG64 idc[] = {
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
    IDS_MAIN_BUTTON_CLEAR,
    IDS_MAIN_BUTTON_ADD,
    IDS_MAIN_BUTTON_EDIT,
    IDS_MAIN_BUTTON_DEL
  };

  TCHAR buttontext[MAX_LOADSTRING];



  HWND search_edit = CreateWindow(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE,
    0, 0, 0, 0, hWnd, (HMENU)IDC_EDIT_SEARCH, g_inst, NULL);

  HWND account_listbox = CreateWindow(_T("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
    WS_TABSTOP | LBS_STANDARD | LBS_HASSTRINGS, // | LBS_OWNERDRAWFIXED,
    0, 0, 0, 0, hWnd, (HMENU)IDC_LISTBOX_ACCOUNT, g_inst, NULL);

  //SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"SFS");

  RefreshListbox(hWnd);



  //SendMessage(GetDlgItem(hWnd, IDC_EDIT_SEARCH), WM_SETFONT, (WPARAM)g_main_font, TRUE);
  SendMessage(GetDlgItem(hWnd, IDC_EDIT_SEARCH), EM_LIMITTEXT, (WPARAM)20, 0);
  //SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT), WM_SETFONT, (WPARAM)g_main_font, TRUE);


  for (size_t i = 2; i < (sizeof(idc) / sizeof(idc[0])); i++)
  {
    LoadStringW(g_resource, ids[i], buttontext, MAX_LOADSTRING);
    CreateWindow(_T("BUTTON"),
      buttontext, WS_CHILD | WS_VISIBLE,
      0, 0, 0, 0, hWnd, (HMENU)idc[i], g_inst, NULL);
    //SendMessage(GetDlgItem(hWnd, idc[i]), WM_SETFONT, (WPARAM)g_main_font, t);
  }


  OnSetFont(hWnd, NULL);
  SetFocus(search_edit);

  return t;

}

BOOL OnResizeControl(HWND hWnd, LPARAM lParam)
{
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
    IDS_MAIN_BUTTON_CLEAR,
    IDS_MAIN_BUTTON_ADD,
    IDS_MAIN_BUTTON_EDIT,
    IDS_MAIN_BUTTON_DEL
  };

  int width = LOWORD(lParam);
  int height = HIWORD(lParam);

  RECT rc = { 0, 0, width, height };




  RECT rc_edit = { rc.left + 12, rc.top + 12, rc_edit.left + 138, rc_edit.top + 24 };

  RECT rc_button_clear = { rc_edit.right + 2, rc.top + 11,
    rc_button_clear.left + 40, rc_button_clear.top + 26 };

  RECT rc_listbox = { rc.left + 12, rc_edit.bottom + 12, rc_listbox.left + 180, rc.bottom - 12 };


  RECT rc_button_add = { rc_listbox.right + 24, rc.bottom - 38, rc_listbox.right + 64,
    rc.bottom - 12 };


  RECT rc_button_delete = { rc.right - 52, rc.bottom - 38, rc.right - 12,
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


  for (size_t i = 0; i < (sizeof(idc) / sizeof(idc[0])); i++)
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

//void RefreshListboxNew(HWND hWnd, std::list<AccountItem>* list)
//{
//
//    HWND account_listbox = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
//
//    // delete dirty data
//    size_t nIndex = (int)SendMessage(account_listbox, LB_GETCOUNT, 0, 0);
//
//    for (size_t i = 0; i < nIndex; i++)
//    {
//        SendMessage(account_listbox, LB_DELETESTRING, (WPARAM)0, (LPARAM)0);
//
//
//    }
//
//    // add new data
//
//    for each (auto var in *list)
//    {
//
//        SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);
//    }
//
//    int ind = SendMessage(account_listbox, LB_FINDSTRING, (WPARAM)-1, (LPARAM)(*list).back().tag);
//
//    SendMessage(account_listbox, LB_SETCURSEL, (WPARAM)ind, (LPARAM)0);
//}

// update listbox with current select index
void RefreshListbox(HWND hWnd)
{

  HWND account_listbox = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);

  // delete dirty data
  size_t nIndex = (int)SendMessage(account_listbox, LB_GETCOUNT, 0, 0);

  for (size_t i = 0; i < nIndex; i++)
  {
    SendMessage(account_listbox, LB_DELETESTRING, (WPARAM)0, (LPARAM)0);


  }

  // add new data
  if (g_dispatcher->GetAccountList()->size() > 0)
  {
    for each (auto var in *(g_dispatcher->GetAccountList()))
    {

      SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);

    }
    LRESULT ind = SendMessage(account_listbox, LB_FINDSTRING, (WPARAM)-1, (LPARAM)(*(g_dispatcher->GetAccountList())).back().tag);

    SendMessage(account_listbox, LB_SETCURSEL, (WPARAM)ind, (LPARAM)0);
  }
  else
  {
    TCHAR static_str[MAX_STR_LEN];
    LoadString(g_resource, IDS_MAIN_LISTNEWTIP, static_str, MAX_STR_LEN);
    SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)static_str);

  }

  //for each (auto var in *(g_dispatcher->GetList()))
  //{

  //    SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);
  //}






}


void OnPaint(HWND hWnd, HDC hdc)
{
  // show account detial
  //SetFocus(GetDlgItem(hWnd, IDC_EDIT_SEARCH));


  SetBkMode(hdc, TRANSPARENT);

  SelectObject(hdc, g_main_font);

  //TextOut(hdc, 480, 12, TEXT("Apple"), wcslen(TEXT("Apple")));

  HWND account_listbox = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);
  TCHAR lpch[MAX_STR_LEN];
  LRESULT ind = SendMessage(account_listbox, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
  SendMessage(account_listbox, LB_GETTEXT, (WPARAM)ind, (LPARAM)lpch);

  if (ind != -1 && g_dispatcher->GetAccountList()->size() > 0)
  {
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
      IDS_LABEL_LASTMOD

    };
    TCHAR static_str[MAX_STR_LEN];

    TCHAR title[9][MAX_STR_LEN];

    for (size_t i = 0; i < (sizeof(ids) / sizeof(ids[0])); i++)
    {
      LoadString(g_resource, ids[i], static_str, MAX_STR_LEN);
      wcscpy_s(title[i], static_str);

    }

    g_dispatcher->ReadAccount(lpch);
    Account* account = g_dispatcher->GetAccount();
    LPTSTR detial[9] = { account->tag, account->category,
      account->url, account->user, account->password,
      account->phone, account->mail, account->note, account->last_mod };


    for (int i = 0; i < 9; i++)
    {
      SetTextAlign(hdc, TA_RIGHT | TA_TOP);
      TextOut(hdc, 300, 12 + 25 * i, title[i], lstrlen(title[i]));

      SetTextAlign(hdc, TA_LEFT | TA_TOP);
      TextOut(hdc, 320, 12 + 25 * i, detial[i], lstrlen(detial[i]));


    }
  }
  else
  {
    TCHAR static_str[MAX_STR_LEN];
    LoadString(g_resource, IDS_MAIN_MAINTIP, static_str, MAX_STR_LEN);

    TextOut(hdc, 280, 40, static_str, lstrlen(static_str));
  }


}

void OnSearchChanged(HWND hWnd)
{
  // if text changed, search in list of dispatcher

  // first, get the text

  TCHAR cur_text[20];
  cur_text[0] = 20;
  LRESULT cur_text_len = SendMessage(GetDlgItem(hWnd, IDC_EDIT_SEARCH),
    EM_GETLINE, 0, (LPARAM)cur_text);
  cur_text[cur_text_len] = TEXT('\0');

  HWND account_listbox = GetDlgItem(hWnd, IDC_LISTBOX_ACCOUNT);


  static int search_len = 0;
  static bool is_hit_p = false;

  is_hit_p = cur_text_len < search_len ?
    false : is_hit_p;


  if (!is_hit_p)
  {
    g_dispatcher->hit_list.clear();
  }


  search_len = (int)cur_text_len;
  g_dispatcher->company_list.clear();


  std::list<AccountItem>* search_list;

  if (g_dispatcher->GetAccountList()->size() > 0
    && cur_text_len > 0)
  {
    search_list = is_hit_p ? &g_dispatcher->hit_list : g_dispatcher->GetAccountList();
    for each (auto var in *search_list) {

      if (fuzzy_search(var.pinyin_tag, cur_text)
        // || wcsstr(var.pinyin_tag, cur_text) != NULL
        || wcsstr(var.tag, cur_text) != NULL) {
        g_dispatcher->company_list.push_back(var);
        if (!is_hit_p) {
          g_dispatcher->hit_list.push_back(var);
        }
      }


    }
    if (g_dispatcher->company_list.size() > 0) {
      // hit show the company list to listbox

      is_hit_p = true;

      // **************************



      // delete dirty data
      size_t nIndex = (int)SendMessage(account_listbox, LB_GETCOUNT, 0, 0);

      for (size_t i = 0; i < nIndex; i++) {
        SendMessage(account_listbox, LB_DELETESTRING, (WPARAM)0, (LPARAM)0);


      }

      // add new data

      for each (auto var in g_dispatcher->company_list) {

        SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)var.tag);
      }


      SendMessage(account_listbox, LB_SETCURSEL, (WPARAM)0, (LPARAM)0);

      InvalidateRect(hWnd, NULL, true);

      // *****************

    }
    else {
      is_hit_p = false;

      // delete dirty data
      size_t nIndex = (int)SendMessage(account_listbox, LB_GETCOUNT, 0, 0);

      for (size_t i = 0; i < nIndex; i++) {
        SendMessage(account_listbox, LB_DELETESTRING, (WPARAM)0, (LPARAM)0);


      }
      TCHAR static_str[MAX_STR_LEN];
      LoadString(g_resource, IDS_MAIN_LISTNULLTIP, static_str, MAX_STR_LEN);
      SendMessage(account_listbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)static_str);


    }


  } else {
    is_hit_p = false;


    RefreshListbox(hWnd);


  }


}

void OnSetFont(HWND hWnd, LPARAM lParam)
{
  EnumChildWindows(hWnd, SetFontProc, lParam);

}

BOOL CALLBACK SetFontProc(HWND hWnd, LPARAM lParam)
{
  SendMessage(hWnd, WM_SETFONT, (WPARAM)g_main_font, TRUE);
  return t;
}


void ShowStaticTip(HWND hDlg, int control_id, LPTSTR str)
{
  RECT rctip;

  GetWindowRect(GetDlgItem(hDlg, control_id), &rctip);

  POINT lt{ rctip.left, rctip.top };

  ScreenToClient(hDlg, &lt);

  POINT rb{ rctip.right, rctip.bottom };

  ScreenToClient(hDlg, &rb);

  rctip.left = lt.x;
  rctip.top = lt.y;
  rctip.right = rb.x;
  rctip.bottom = rb.y;

  InvalidateRect(hDlg, &rctip, TRUE);

  SendDlgItemMessage(hDlg, control_id, WM_SETTEXT,
    NULL, (LPARAM)str);
}
