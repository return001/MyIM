#ifndef __ADDBGPTOWND_H__
#define __ADDBGPTOWND_H__


//���ÿؼ�����ͼƬ
void ControlMap(int BmpID, int ControlID, char *pStr, LPARAM lParam);
//���ô��ڱ���ͼƬ
void BackgroundMap(HWND hDlg, int BmpID, HDC hdc);
//���þ�̬�ı��򱳾�ͼƬ
void SetStatic(WPARAM wParam);
//��̬�ı�������������
void   __fastcall   InsertBmpToRich(HWND hWnd,PWCHAR pStr);
//���ô��ڱ���ͼƬ
int SetBgToWnd(HWND hWnd,HDC hdc,LPSTR Str);

#endif