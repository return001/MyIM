// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers



#include <windows.h>

// TODO: reference additional headers your program requires here
#include <iostream>
using namespace std;

#include<winsock2.h>

#include <CommCtrl.h>

#define IDC_CHAT 1
#define IDC_CONTENT 2
#define IDB_STATUS 3
#define ID_TOOLBAR 4
#define ID_MUNE_FONT 5
#define ID_MUNE_FACE 6
#define IDC_EDIT_ADDTEXT 7
#define IDC_BUTTON_ADDOK 8
#define ID_MUNE_FILE 9

//#import <ImageOle.dll> raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search
//static CLSID const gif_clsid = { 0x6ADA938, 0xFB0, 0x4BC0, { 0xB1, 0x9B, 0xA, 0x38, 0xAB, 0x17, 0xF1, 0x82 } };


#include <oleidl.h>
#include<richedit.h>
#include <richole.h>
#include <olectl.h>

#include "resource.h"
#include "AddBgpToWnd.h"
#include "../Public/Protocol.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
