#include "StdAfx.h"
#include "AddBgpToWnd.h"



/*
typedef struct tagDRAWITEMSTRUCT {  
UINT  CtlType; //�ؼ�����  
UINT  CtlID; //�ؼ�ID  
UINT  itemID; //�ؼ������IDֻ���ڲ˵����Ͽ��б��  
UINT  itemAction; //�ؼ���Ϊ��һ����һ����̬����Ϊ����ʱ����  
UINT  itemState; //�ؼ�״̬���ڴ���ĳ����̬ʱ����  
HWND  hwndItem; //�ؼ����  
HDC   hDC; //���ƿؼ����豸�����ľ��  
RECT  rcItem; //�ؼ���ľ��η�Χ  
DWORD itemData; //����Ϊ�˵���б����Ͽ��е��б���ָ����32ֵ  
} DRAWITEMSTRUCT;  */


//WM_DRAWITEM���ռ��������Ի�
void ControlMap(int BmpID, int ControlID, char *pStr,LPARAM lParam)
//�ؼ���ͼ��������
{
	LPDRAWITEMSTRUCT lpDis = (LPDRAWITEMSTRUCT)lParam;
	RECT rtListItem = lpDis->rcItem;  
	if (ODT_BUTTON == lpDis->CtlType)  
	{  
		if (ControlID == lpDis->CtlID) 
		{  
			HDC hMerDc= CreateCompatibleDC(lpDis->hDC); 
			HBITMAP hBitMap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(BmpID));
			SelectObject(hMerDc, hBitMap); 
			BitBlt(lpDis->hDC, lpDis->rcItem.left, lpDis->rcItem.top, lpDis->rcItem.right - lpDis->rcItem.left, lpDis->rcItem.bottom - lpDis->rcItem.top,   
			hMerDc, 0, 0, SRCAND);  
			SelectObject(lpDis->hDC,hBitMap);  
			DeleteObject(hMerDc);  
			SetBkMode(lpDis->hDC, TRANSPARENT);  
                      
			DrawText(lpDis->hDC, pStr,strlen(pStr) , &(lpDis->rcItem) ,DT_CENTER | DT_VCENTER | DT_SINGLELINE); 
		}
	}

}

//���ô��ڱ���ͼƬ
void BackgroundMap(HWND hDlg, int BmpID, HDC hdc)
{
	HBITMAP hbm;
	BITMAP bminfo;
	hbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BmpID));
    GetObject(hbm, sizeof(bminfo), &bminfo);
                 
    HDC memdc = CreateCompatibleDC(hdc);
                 
    SelectObject(memdc, hbm);
    BitBlt(hdc,0,0,bminfo.bmWidth,bminfo.bmHeight,memdc,0,0,SRCCOPY);
	DeleteDC(memdc);
}

int SetBgToWnd(HWND hWnd,HDC hdc,LPSTR Str)
{

	RECT rt = {0};
	GetWindowRect(hWnd,&rt);
	HBITMAP hbm;
	BITMAP bminfo;
	hbm = LoadBitmap(GetModuleHandle(NULL),Str);
    GetObject(hbm, sizeof(bminfo), &bminfo);
	
    HDC memdc = CreateCompatibleDC(hdc);
	
    SelectObject(memdc, hbm);
    BitBlt(hdc,0,0,(rt.right - rt.left),(rt.bottom - rt.top),memdc,0,0,SRCCOPY);
	DeleteDC(memdc);
	return 0;
}
//���þ�̬�ı��򱳾�ͼƬWM_CTLCOLORSTATIC��Ϣ����
void SetStatic(WPARAM wParam)
{
	
}

//���ı�������������
/*void   __fastcall   InsertBmpToRich(HWND   hWnd,    PWCHAR  pStr)   
  {   
          IRichEditOle   *RichOle;   
          SendMessage(hWnd,   EM_GETOLEINTERFACE,   0,   int(&RichOle));   
    
          ILockBytes   *FLockBytes;   
          CreateILockBytesOnHGlobal(0,1,&FLockBytes);   
    
          IStorage   *FStorage;   
          StgCreateDocfileOnILockBytes(FLockBytes,STGM_SHARE_EXCLUSIVE   |   
                          STGM_CREATE   |   STGM_READWRITE,0,&FStorage);   
    
          FORMATETC  FormatEtc;   
          FormatEtc.cfFormat=0;   
          FormatEtc.ptd=NULL;   
          FormatEtc.dwAspect=DVASPECT_CONTENT;   
          FormatEtc.lindex=-1;   
          FormatEtc.tymed=TYMED_NULL;  
    
          IOleObject   *FOle;   
          OleCreateFromFile(GUID_NULL,   pStr,   ::IID_IOleObject, 0,   &FormatEtc,   NULL,   FStorage,   (void**)&FOle);   
          OleSetContainedObject(FOle,   true);   
    
          REOBJECT   ReObject;   
          ZeroMemory(&ReObject,   sizeof(REOBJECT));   
          ReObject.cbStruct=sizeof(REOBJECT);   
          CLSID   xt = {0};   
          FOle->GetUserClassID(&xt);   
          ReObject.clsid=xt;   
          ReObject.cp=REO_CP_SELECTION;   
          ReObject.dvaspect=DVASPECT_CONTENT;   
          ReObject.dwFlags=REO_STATIC   |   REO_BELOWBASELINE;   
          ReObject.dwUser=0;   
          ReObject.poleobj=FOle;   
    
          IOleClientSite     *FClientSite;   
          RichOle->GetClientSite(&FClientSite);   
          ReObject.polesite=FClientSite;   
          ReObject.pstg=FStorage;   
          ReObject.sizel.cx=0;   
          ReObject.sizel.cy=0;   
    
          RichOle->InsertObject(&ReObject);   
  } */


 /*BOOL InsertObject(HWND hRichEdit, PWCHAR pszFileName)
{
    HRESULT hr;

    LPRICHEDITOLE pRichEditOle;
    SendMessage(hRichEdit, EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle);

    if (pRichEditOle == NULL)
    {
        return FALSE;
    }

    LPLOCKBYTES pLockBytes = NULL;
    hr = CreateILockBytesOnHGlobal(NULL, TRUE, &pLockBytes);

    if (FAILED(hr))
    {
        return FALSE;
    }

    LPSTORAGE pStorage;
    hr = StgCreateDocfileOnILockBytes(pLockBytes, 
           STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 
           0, &pStorage);

    if (FAILED(hr))
    {
        return FALSE;
    }

    FORMATETC formatEtc;
    formatEtc.cfFormat = 0;
    formatEtc.ptd = NULL;
    formatEtc.dwAspect = DVASPECT_CONTENT;
    formatEtc.lindex = -1;
    formatEtc.tymed = TYMED_NULL;

    LPOLECLIENTSITE pClientSite;
    hr = pRichEditOle->GetClientSite(&pClientSite);

    if (FAILED(hr))
    {
        return FALSE;
    }

    LPUNKNOWN pUnk;
    CLSID clsid = CLSID_NULL;

    hr = OleCreateFromFile(clsid, pszFileName, IID_IUnknown, OLERENDER_DRAW, 
           &formatEtc, pClientSite, pStorage, (void**)&pUnk);

    pClientSite->Release();

    if (FAILED(hr))
    {
        return FALSE;
    }

    LPOLEOBJECT pObject;
    hr = pUnk->QueryInterface(IID_IOleObject, (void**)&pObject);
    pUnk->Release();

    if (FAILED(hr))
    {
        return FALSE;
    }

    OleSetContainedObject(pObject, TRUE);
    REOBJECT reobject = { sizeof(REOBJECT)};
    hr = pObject->GetUserClassID(&clsid);

    if (FAILED(hr))
    {
        pObject->Release();
        return FALSE;
    }

    reobject.clsid = clsid;
    reobject.cp = REO_CP_SELECTION;
    reobject.dvaspect = DVASPECT_CONTENT;
    reobject.dwFlags = REO_RESIZABLE | REO_BELOWBASELINE;
    reobject.dwUser = 0;
    reobject.poleobj = pObject;
    reobject.polesite = pClientSite;
    reobject.pstg = pStorage;
    SIZEL sizel = { 0 };
    reobject.sizel = sizel;

    SendMessage(hRichEdit, EM_SETSEL, 0, -1);
    DWORD dwStart, dwEnd;
    SendMessage(hRichEdit, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
    SendMessage(hRichEdit, EM_SETSEL, dwEnd+1, dwEnd+1);
    SendMessage(hRichEdit, EM_REPLACESEL, TRUE, (WPARAM)L"\n"); 

    hr = pRichEditOle->InsertObject(&reobject);
    pObject->Release();
    pRichEditOle->Release();

    if (FAILED(hr))
    {
        return FALSE;
    }
    
    return TRUE;
}*/
