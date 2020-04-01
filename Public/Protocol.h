#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "List.h"


#define IDC_LISTCTL                 (128)
#define NAME_LEN					(20)				//�ǳƵĳ���
#define ID_LEN						(12)				//id:�ĳ���
#define SEX_LEN						(10)				//�Ա�ĳ���
#define EVENT_LEN					(4)					//�¼��ĳ���
#define TIPSTR_LEN					(20)				//��ʾ�¼��ַ����ĳ���
#define STATE_LEN					(4)					//״̬�ĳ���
#define AGE_LEN						(4)					//�Ա�ĳ���
#define CHOOSE						(TRUE)				//��ѡ��
#define NO_CHOOSE					(FALSE)				//δ��ѡ��
#define OFF_LINE					(0)					//����
#define LINE						(1)					//����
#define SERVICE_IP_STR				("127.0.0.1")	//������Ip
#define CLIENT_IP_STR				("127.0.0.1")		//�ͻ���Ip
#define SZBUF_MAX					(4096)				//�����ַ�����Ϣ��󳤶�
#define PORT_NUM					(5000)				//�˿ں�
#define LISTEN_NUM					(3)					//�����׽��ֿ�ͬʱ���շ�����Ϣ�ͻ�������
#define WM_MAIN_SOCKET				(WM_USER + 2)		//�������׽���
#define WM_REGISTER_SOCKET			(WM_USER + 3)		//ע����׽�����Ϣ
#define WM_LOGIN_SOCKET				(WM_USER + 4)		//��¼���׽�����Ϣ
#define PROC_SOCK_NUM				(64)				


//===============Services Send Events=============
#define SER_OPER_ERROR				(-1)   //����˷��ز��������¼�
#define SER_SEND_USER_ID			(1)    //ע��ɹ������û�Id�¼�
#define SER_NOTFINDID_ERROR			(3)		//��¼δ�ҵ�ע��Id�¼�
#define SER_USERPWD_ERROR			(4)		//�û���������¼�
#define SER_LOGIN_SUCCESS			(32)	//��¼�ɹ��¼�
#define SER_SEND_FRIEND_LIST		(5)		//��¼�ɹ������ͺ����б�
#define SER_SEND_OFFLINE_MSG		(6)		//��¼���ͷ���������ѷ��͵�������Ϣ
#define SER_USER_LOGIN				(7)		//���û����ѷ��û������¼�
#define SER_ADD_ASK					(8)		//���û����ͺ��������¼�
#define SER_ADD_YET					(30)	//���û������Ѿ���Ӵ��û�Ϊ����
#define SER_ASK_AGREE				(9)		//���û����ͺ�����ӳɹ��¼�
#define SER_ASK_REFUSE				(10)	//���û����ͺ��Ѿܾ��¼�
#define SER_NOTFIND_ID				(11)	//���û����Ͳ��޴����¼�
#define SER_BE_DELETED				(12)	//���û����ͱ�ɾ�����¼�
#define SER_SEND_USER_INFORMATION	(13)	//���û����ͱ��鿴���ѵ���Ϣ���¼�
#define SER_SEND_DATA				(14)	//ת���û����͸����ѵ���Ϣ���������飩
#define SER_SEND_PICTURE			(15)	//ת��ͼƬ
#define SER_CHANGE_FINISH			(16)	//��Ϣ�޸����
#define SER_SEND_FILE				(17)	//ת���ļ�
#define SER_USER_EXIT				(18)	//�û��˳��¼�
#define SER_ADD_ERROR				(31)	//�������ʧ��
#define SER_
#define SER_
#define SER_



//====================Services Structs===============
struct USER_ID           //����ֻId�Ķ���������ṹ��
{
	LINKER linker;   //id�Ѿ����浽linker��
};

struct USER_ID_PACK //����ֻ�÷���Id����Ϣ����������ṹ��
{
	int nEvent;

	char IdStr[12];
};

struct SER_USER_NODE   //����˱�����ע���û�����Ϣ 
{
	LINKER linker;     //Id�Ѿ���linker�б���

	char uPwd[17];
	char uName[20];
	USER_ID *FriendListHead;
	int Index;
	char PicStr[10];//ͼƬ
                 //ͼƬ·��������ͼƬ����
	int uState;      //1Ϊ����״̬��0Ϊ����״̬
	SOCKET uSock;
	char FilePath[50];   //�ļ�·���������ļ����

	//�����û����ݣ������
	int uAge;
	char uHoro[10];    //����
};

struct USER_FRIEND_BASIC_PACK    //���ѻ�����Ϣ
{
	int nEvent;
	char IdStr[12];
	char FName[20];
	char PicStr[10];//ͼƬ
	int FState;
};

struct	SER_SEND_DATA_PACK   //ת����Ϣ
{
	int nEvent;
	char SourId[12];
	
	union DATA_TYPE
	{
		char szBuf[SZBUF_MAX];
		//ͼƬ
	}DataType;
	
};

struct SER_FRIEND_INFOMATION_PACK   //�û��鿴������ϸ��Ϣʱ�ĺ�����Ϣ��
{	
	int nEvent;
	char IdStr[12];
	char uName[20];
	char PicStr[10];  //ͼƬ
	int uState;      //1Ϊ����״̬��0Ϊ����״̬


	char uHoro[10];    //����
	int uAge;
};


struct USER_EXIT_PACK   //֪ͨ�û��к����˳�
{
	int nEvent;
	char IdStr[12];

};

struct EVENT_TIP_PACK      //�¼����� 
{
	int nEvent;

	char nExvent[20];
};
/////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////


//================Client Send Events==========================

#define CLI_REGISTER			(19)    //�û�ע���¼�
#define CLI_LOGIN				(20)    //��¼�¼�
#define CLI_ADDFRI_ASK			(21)	//�Ӻ�������
#define CLI_ADD_AGREE			(22)	//ͬ����Ӻ���
#define CLI_ADD_REFUSE			(23)	//�ܾ���Ӻ���
#define CLI_CHAT_DATA			(24)	//��������
#define CLI_PICTURE_DATA		(25)	//ͼƬ����
#define CLI_SEE_FRI_INFOMATION	(26)	//�鿴������ϸ��Ϣ
#define CLI_DELETE_FRI			(27)	//ɾ������
#define CLI_EXIT				(28)	//�˳�
#define CLI_MODIFY				(29)	//�޸ĸ�����Ϣ
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_
#define CLI_





//========================Client Struct===========================


struct REGISTER_PACK   //ע����Ϣ
{
	int nEvent;
	char uName[20];
	char uPwd[17];
	char PicStr[10];//ͼƬ
	char uHro[10];
	int uAge;
};

struct FRIEND_NODE //�ͻ��˱������ 
{
	LINKER linker;	//ID��linker��


	char FName[20];
	BOOL IsBeChoose;
	char FileName[12];   //�ļ���
	int FState;
	char PicStr[10];//ͼƬ
};


struct LOGIN_PACK //��¼����
{
	int nEvent;

	char IdStr[12];
	char PwdStr[17];
};

struct MY_FRI_ID_PACK   //��Ҫ��������Id����Ϣ��
{
	int nEvent;

	char UserId[12];
	char BeAdderId[12];
};


struct USER_SEND_DATA_PACK   //�û����͵���Ϣ
{
	int nEvent;
	char SourId[12];
	char DesId[12];
	
	union DATA_TYPE
	{
		char szBuf[SZBUF_MAX];
		//ͼƬ
	}DataType;	
};

struct MODIFY_PACK 
{
	int nEvent;

	char SourId[12];			//Id���ܸ���

	char uName[20];
	char uPwd[17];
	char PicStr[10];//ͼƬ
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
	MessageBox(hWnd,"ӳ����û������¼�","Error",MB_OK);\
}\
	return 0;\
}


#define CALL_CLI_EVENTPROC(Name,pVoid,hWnd) Name##EventProc(pVoid,hWnd)


#endif