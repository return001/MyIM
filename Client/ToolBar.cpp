#include "StdAfx.h"
#include "ToolBar.h"



HWND CreateSimpleToolbar(HWND hDlg, RECT rt)
{
	int ImageListID = 0;
	int ImageButtonNums = 3;
	int bitmapSize = 15;
	DWORD buttonStyle = TBSTYLE_BUTTON;   //| TBSTYLE_LIST, CBRS_TOOLTIPS | CBRS_FLYBY
	HWND hToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | CBRS_GRIPPER | CBRS_FLYBY | CCS_NORESIZE, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, hDlg, NULL, GetModuleHandle(NULL), NULL);
	
	static HIMAGELIST imagelist = ImageList_Create(bitmapSize, bitmapSize, ILC_COLOR32 | ILC_MASK, ImageButtonNums, 0);  //ILC_COLOR32|ILC_MASK/  ILC_COLOR24
	//加载自己的位图
	int iBitmap = ImageList_Add(imagelist, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)), NULL);
	int iBitmap1 = ImageList_Add(imagelist, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)), NULL);

    int iBitmap2 = ImageList_Add(imagelist, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5)), NULL);

	SendMessage(hToolbar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)(HIMAGELIST)imagelist);
	//添加按钮
	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	
	static TBBUTTON tbButtons[3] = { 0 };
	tbButtons[0].dwData = 0;
	tbButtons[0].iBitmap = MAKELONG(iBitmap, ImageListID);
	tbButtons[0].fsState = TBSTATE_ENABLED;
	tbButtons[0].fsStyle = TBSTYLE_BUTTON;
	tbButtons[0].iString = 0;
	tbButtons[0].idCommand = (int)ID_MUNE_FONT;
	
	tbButtons[1].iBitmap = MAKELONG(iBitmap + 1, ImageListID);
	tbButtons[1].fsState = TBSTATE_ENABLED;
	tbButtons[1].fsStyle = TBSTYLE_BUTTON;
	tbButtons[1].iString = 0;
	tbButtons[1].idCommand = (int)ID_MUNE_FACE;

	tbButtons[2].iBitmap = MAKELONG(iBitmap + 2, ImageListID);
	tbButtons[2].fsState = TBSTATE_ENABLED;
	tbButtons[2].fsStyle = TBSTYLE_BUTTON;
	tbButtons[2].iString = 0;
	tbButtons[2].idCommand = (int)ID_MUNE_FILE;
	
	SendMessage(hToolbar, TB_ADDBUTTONS, (WPARAM)ImageButtonNums, (LPARAM)&tbButtons);
	SendMessage(hToolbar, TB_SETBUTTONWIDTH, (WPARAM)0, (LPARAM)(DWORD)MAKELONG(15, 30));
//	SendMessage(hToolbar,TB_SETPADDING,0,MAKELPARAM(30,30)); 
	//调整工具栏大小，并展示它
	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hToolbar, TRUE);
	
	return hToolbar;
}
