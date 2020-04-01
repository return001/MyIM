#ifndef __ADDBGPTOWND_H__
#define __ADDBGPTOWND_H__


//设置控件背景图片
void ControlMap(int BmpID, int ControlID, char *pStr, LPARAM lParam);
//设置窗口背景图片
void BackgroundMap(HWND hDlg, int BmpID, HDC hdc);
//设置静态文本框背景图片
void SetStatic(WPARAM wParam);
//多态文本框里面贴表情
void   __fastcall   InsertBmpToRich(HWND hWnd,PWCHAR pStr);
//设置窗口背景图片
int SetBgToWnd(HWND hWnd,HDC hdc,LPSTR Str);

#endif