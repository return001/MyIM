#include "StdAfx.h"
#include "CliEventProc.h"
#include "AddFriToList.h"

HIMAGELIST g_Imglist1 = {0};
LVCOLUMN g_list1;

int CreateFriendList(HWND hWnd)
{
	HWND listview1 = FindWindowEx(hWnd,NULL,TEXT("SysListView32"),NULL);



	
	g_list1.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;//掩码
	g_list1.fmt = LVCFMT_CENTER;//左对齐
	g_list1.cx = 50;//列宽
	g_list1.pszText = TEXT("头像");
	SendMessage(listview1, LVM_INSERTCOLUMN, 0, (LPARAM)&g_list1);//创建列
	
	g_list1.pszText = TEXT("昵称");
	g_list1.cx = 80;
	SendMessage(listview1, LVM_INSERTCOLUMN, 1, (LPARAM)&g_list1);
	
	g_list1.pszText = TEXT("ID");
	g_list1.cx = 90;
	SendMessage(listview1, LVM_INSERTCOLUMN, 2, (LPARAM)&g_list1);

	
	//创建图片列表
	g_Imglist1 = ImageList_Create(20, 20, ILC_MASK, 1, 1);
	ImageList_AddIcon(g_Imglist1, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
	ImageList_AddIcon(g_Imglist1, LoadIcon((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDI_ICON2)));
	ImageList_AddIcon(g_Imglist1, LoadIcon((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDI_ICON3)));
	ListView_SetImageList(listview1, g_Imglist1, LVSIL_SMALL);
	
	
	//内存清零
	RtlZeroMemory(&g_list1, sizeof(LVCOLUMN));

	return 0;
}
int AddFriendItem(HWND hWnd,void *pVoid,int nCount)
{
	USER_FRIEND_BASIC_PACK *pFriend = (USER_FRIEND_BASIC_PACK *)pVoid;
	HWND listview1 = FindWindowEx(hWnd,NULL,TEXT("SysListView32"),NULL);
	int HeadNum = 0;

	pFriend->FName[19] = '\0';
	pFriend->IdStr[11] = '\0';
	pFriend->PicStr[9] = '\0';
	//((char *)pFriend->FState)[3] = '\0';

	if(0 == strcmp(pFriend->PicStr,"头像1    "))
	{
		HeadNum = 0;
	}
	else if(0 == strcmp(pFriend->PicStr,"头像2    "))
	{
		HeadNum = 1;
	}
	else if(0 == strcmp(pFriend->PicStr,"头像3    "))
	{
		HeadNum = 2;
	}


	LVITEM item1 = {0};
	RtlZeroMemory(&item1, sizeof(LVITEM));
	
	
	item1.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT;
	item1.pszText = TEXT("");
	item1.iItem = nCount-1;//项目号
	item1.iImage = HeadNum;//图片号
	item1.iIndent = 0;
	SendMessage(listview1, LVM_INSERTITEM, 0, (LPARAM)&item1);
	
	item1.mask = LVIF_TEXT;
	item1.iItem = nCount-1;
	item1.iSubItem = 1;
	item1.pszText = TEXT(pFriend->FName);
	SendMessage(listview1, LVM_SETITEM, 0, (LPARAM)&item1);
	item1.iItem = 0;
	item1.iSubItem = 2;
	item1.pszText = TEXT(pFriend->IdStr);
	SendMessage(listview1, LVM_SETITEM, 0, (LPARAM)&item1);

	return 0;
}

int DeleteFriendItem(HWND hWnd,char *IdStr)
{
	return 0;
}

