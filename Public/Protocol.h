#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "List.h"


#define IDC_LISTCTL                 (128)
#define NAME_LEN					(20)				//昵称的长度
#define ID_LEN						(12)				//id:的长度
#define SEX_LEN						(10)				//性别的长度
#define EVENT_LEN					(4)					//事件的长度
#define TIPSTR_LEN					(20)				//提示事件字符串的长度
#define STATE_LEN					(4)					//状态的长度
#define AGE_LEN						(4)					//性别的长度
#define CHOOSE						(TRUE)				//被选中
#define NO_CHOOSE					(FALSE)				//未被选中
#define OFF_LINE					(0)					//离线
#define LINE						(1)					//在线
#define SERVICE_IP_STR				("127.0.0.1")	//服务器Ip
#define CLIENT_IP_STR				("127.0.0.1")		//客户区Ip
#define SZBUF_MAX					(4096)				//发送字符串消息最大长度
#define PORT_NUM					(5000)				//端口号
#define LISTEN_NUM					(3)					//监听套接字可同时接收发送消息客户的数量
#define WM_MAIN_SOCKET				(WM_USER + 2)		//主窗口套接字
#define WM_REGISTER_SOCKET			(WM_USER + 3)		//注册框套接字消息
#define WM_LOGIN_SOCKET				(WM_USER + 4)		//登录框套接字消息
#define PROC_SOCK_NUM				(64)				


//===============Services Send Events=============
#define SER_OPER_ERROR				(-1)   //服务端返回操作错误事件
#define SER_SEND_USER_ID			(1)    //注册成功返回用户Id事件
#define SER_NOTFINDID_ERROR			(3)		//登录未找到注册Id事件
#define SER_USERPWD_ERROR			(4)		//用户密码错误事件
#define SER_LOGIN_SUCCESS			(32)	//登录成功事件
#define SER_SEND_FRIEND_LIST		(5)		//登录成功，发送好友列表
#define SER_SEND_OFFLINE_MSG		(6)		//登录后发送服务器里好友发送的离线消息
#define SER_USER_LOGIN				(7)		//向用户好友发用户上线事件
#define SER_ADD_ASK					(8)		//向用户发送好友请求事件
#define SER_ADD_YET					(30)	//向用户发送已经添加此用户为好友
#define SER_ASK_AGREE				(9)		//向用户发送好友添加成功事件
#define SER_ASK_REFUSE				(10)	//箱用户发送好友拒绝事件
#define SER_NOTFIND_ID				(11)	//向用户发送查无此人事件
#define SER_BE_DELETED				(12)	//向用户发送被删除的事件
#define SER_SEND_USER_INFORMATION	(13)	//向用户发送被查看好友的信息的事件
#define SER_SEND_DATA				(14)	//转发用户发送给好友的消息（包括表情）
#define SER_SEND_PICTURE			(15)	//转发图片
#define SER_CHANGE_FINISH			(16)	//信息修改完成
#define SER_SEND_FILE				(17)	//转发文件
#define SER_USER_EXIT				(18)	//用户退出事件
#define SER_ADD_ERROR				(31)	//好友添加失败
#define SER_
#define SER_
#define SER_



//====================Services Structs===============
struct USER_ID           //所有只Id的都可用这个结构体
{
	LINKER linker;   //id已经保存到linker中
};

struct USER_ID_PACK //所有只用发送Id的消息都可用这个结构体
{
	int nEvent;

	char IdStr[12];
};

struct SER_USER_NODE   //服务端保存已注册用户的信息 
{
	LINKER linker;     //Id已经在linker中保存

	char uPwd[17];
	char uName[20];
	USER_ID *FriendListHead;
	int Index;
	char PicStr[10];//图片
                 //图片路径，或者图片类型
	int uState;      //1为在线状态，0为离线状态
	SOCKET uSock;
	char FilePath[50];   //文件路径，或者文件句柄

	//其他用户数据，可添加
	int uAge;
	char uHoro[10];    //星座
};

struct USER_FRIEND_BASIC_PACK    //好友基本信息
{
	int nEvent;
	char IdStr[12];
	char FName[20];
	char PicStr[10];//图片
	int FState;
};

struct	SER_SEND_DATA_PACK   //转发消息
{
	int nEvent;
	char SourId[12];
	
	union DATA_TYPE
	{
		char szBuf[SZBUF_MAX];
		//图片
	}DataType;
	
};

struct SER_FRIEND_INFOMATION_PACK   //用户查看好友详细信息时的好友信息包
{	
	int nEvent;
	char IdStr[12];
	char uName[20];
	char PicStr[10];  //图片
	int uState;      //1为在线状态，0为离线状态


	char uHoro[10];    //星座
	int uAge;
};


struct USER_EXIT_PACK   //通知用户有好友退出
{
	int nEvent;
	char IdStr[12];

};

struct EVENT_TIP_PACK      //事件提醒 
{
	int nEvent;

	char nExvent[20];
};
/////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////


//================Client Send Events==========================

#define CLI_REGISTER			(19)    //用户注册事件
#define CLI_LOGIN				(20)    //登录事件
#define CLI_ADDFRI_ASK			(21)	//加好友请求
#define CLI_ADD_AGREE			(22)	//同意添加好友
#define CLI_ADD_REFUSE			(23)	//拒绝添加好友
#define CLI_CHAT_DATA			(24)	//聊天数据
#define CLI_PICTURE_DATA		(25)	//图片数据
#define CLI_SEE_FRI_INFOMATION	(26)	//查看好友详细信息
#define CLI_DELETE_FRI			(27)	//删除好友
#define CLI_EXIT				(28)	//退出
#define CLI_MODIFY				(29)	//修改个人信息
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_





//========================Client Struct===========================


struct REGISTER_PACK   //注册信息
{
	int nEvent;
	char uName[20];
	char uPwd[17];
	char PicStr[10];//图片
	char uHro[10];
	int uAge;
};

struct FRIEND_NODE //客户端保存好友 
{
	LINKER linker;	//ID在linker中


	char FName[20];
	BOOL IsBeChoose;
	char FileName[12];   //文件名
	int FState;
	char PicStr[10];//图片
};


struct LOGIN_PACK //登录请求
{
	int nEvent;

	char IdStr[12];
	char PwdStr[17];
};

struct MY_FRI_ID_PACK   //需要发送两个Id的消息包
{
	int nEvent;

	char UserId[12];
	char BeAdderId[12];
};


struct USER_SEND_DATA_PACK   //用户发送的消息
{
	int nEvent;
	char SourId[12];
	char DesId[12];
	
	union DATA_TYPE
	{
		char szBuf[SZBUF_MAX];
		//图片
	}DataType;	
};

struct MODIFY_PACK 
{
	int nEvent;

	char SourId[12];			//Id不能更改

	char uName[20];
	char uPwd[17];
	char PicStr[10];//图片
	char uHro[10];
	int uAge;
};

struct EXIT_PACK
{
	int nEvent;

	char SourId[12];
};


//////////////////////////////////////////////////////////////////////////


typedef int (*P_SER_FUN)(void *pVoid,SOCKET nSock);
typedef int (*P_CLI_FUN)(void *pVoid,HWND hWnd);

struct EVENT_MAP 
{
	int nEvent;
	
	P_SER_FUN pSerFun;
	P_CLI_FUN pCliFun;
	
};

#define DECLARE_EVENT_MAP(Name) extern EVENT_MAP g_##Name##EventMap[];

#define BEGIN_EVENT_MAP(Name) EVENT_MAP g_##Name##EventMap[] = {

#define BODY_EVENTMAP(nEvent,pFun,pFun1) {nEvent,pFun,pFun1},

#define END_EVENTMAP {0,NULL,NULL}};


#define DECLARE_EVENTPROC(Name) int Name##EventProc(void *pVoid,SOCKET nSock);

#define IMPLEMENT_EVENTPROC(Name) int Name##EventProc(void *pVoid,SOCKET nSock)\
{\
	EVENT_MAP *pTemp = g_##Name##EventMap;\
\
	int nEvent = CheckEvent(pVoid);\
\
	int i = 0;\
	for(i = 0; NULL != pTemp[i].pSerFun;i++)\
	{\
		if(nEvent == pTemp[i].nEvent)\
		{\
			pTemp[i].pSerFun(pVoid,nSock);\
			break;\
		}\
	}\
\
	if(0 == pTemp[i].nEvent)\
	{\
		cout<<"Event Error"<<endl;\
	}\
	return 0;\
}


#define CALL_EVENTPROC(Name,pVoid,Sock) Name##EventProc(pVoid,Sock);

//////////////////////////////////////////////////////////////////////////////////////////////

#define DECLARE_CLI_EVENTPROC(Name) int Name##EventProc(void *pVoid,HWND hWnd);

#define IMPLEMENT_CLI_EVENTPROC(Name) int Name##EventProc(void *pVoid,HWND hWnd)\
{\
	EVENT_MAP *pTemp = g_##Name##EventMap;\
	\
	int nEvent = CheckEvent(pVoid);\
	\
	int i = 0;\
	for(i = 0; NULL != pTemp[i].pCliFun;i++)\
{\
	if(nEvent == pTemp[i].nEvent)\
{\
	pTemp[i].pCliFun(pVoid,hWnd);\
	break;\
}\
}\
	\
	if(0 == pTemp[i].nEvent)\
{\
	MessageBox(hWnd,"映射里没有这个事件","Error",MB_OK);\
}\
	return 0;\
}


#define CALL_CLI_EVENTPROC(Name,pVoid,hWnd) Name##EventProc(pVoid,hWnd)


#endif