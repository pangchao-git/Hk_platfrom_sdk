#ifndef __HIKPTSDK_DEFINE_H__
#define __HIKPTSDK_DEFINE_H__

#include <string>
#include<windows.h>
#include <list>

#ifdef __cplusplus
extern "C" {
#endif  //#ifdef __cplusplus


//�û���¼��Ϣ
typedef struct tagHikLoginInfo
{
    char    szUserName[64];         // ��¼����
    char    szPassword[64];         // ����
    char    szServerUrl[64];        // CMS�����ַ
    unsigned int uServerPort;       // �������˿�
    int     nErrCode;               // ����ʧ�ܴ�����
    char    szErrInfo[512];         // ����ʧ�ܴ�������
}HikLoginInfo;

//����
typedef struct tagHikCellInfo
{
    int     nId;                    // ����ID
    int     nParentId;              // ���ڵ�ID
    char    szIndexCode[64];        // �������
    char    szCellName[130];        // ��������
    char	szRegCode[40];			// ��֯���
    int     nSeqIndex;              // չʾ�������
    char	szCascCode[40];			// ������ʶ������ƽ̨�ı���
    char 	szPinyin[40];		    // ƴ�����ֽ�
    bool    bPrivilege;             // �Ƿ���Ȩ��
    char    szPath[32];             //��֯����·��("1,3,5") Add at 2015-09-30
    tagHikCellInfo* pNext;
}HikCellInfo;

//�û���֯
typedef struct tagHikUserOrg
{
    char szOrgName[130]; // �û���֯����
    char szOrgIndex[64]; // �û���֯indexcode
    int  nParentID;      // �ϼ�ID
    int  nID;            // �û���֯ID
    int  nSeqIndex;      // �������
    bool bPrivilege;     // �Ƿ���Ȩ��
    tagHikUserOrg* pNext;       
}HikUserOrg;

//�û���Ϣ
typedef struct tagHikPlatformUser
{
    int nId;          // �û�ID
    char szName[130]; // �û�����
    char szLoginName[130];//��¼����
    int nLevel;       // �û����𣬹���Ա: 50
    int nStatus;      // �û�״̬  ���������ڣ����õȣ�ʵ��ʹ�ù���ֻ��Ҫ����״̬��
    int nCellID;      // ������֯ID
    tagHikPlatformUser* pNext;
}HikPlatformUser;   

//��ص���Ϣ
typedef struct tagHikCameraInfo
{
    int nCamId;        //��ص�ID
    int nCellId;       //������֯�ܹ�
    int nChannel;       //ͨ����
    char szDevIndexCode[64];  //�����豸���
    char szIndexCode[64];  //���
    char szCameraName[260]; //����
    int nCameraType;        //���������ǹ���������
    char szMatrixCode[64]; //���̱���
    int nSeqIndex;      // չʾ�������
    bool bOnlineStatus;  //����״̬
    int nInstallType;   // ��װ��ʽ
    int nVideoDevType;  // ���� �����������  16����
    char szCascCode[40];				   //������ʶ������ƽ̨�ı���
    char szCascDecodeTag[32];              //���������־ hikvision,dahua,db33
    int nPlayParam;	//�������ܲ���
    int nSubStream;	//��ʼ������ʽ��0~��������1~������
    int nProtocal;	//����Э�飬TCP or UDP
    int nPassage;   //��������  1��ڣ�2���ڣ�3�����
    bool bEzviz;    //�Ƿ�Ϊөʯ�Ƽ�ص�
    tagHikCameraInfo* pNext;
}HikCameraInfo;

//�豸��Ϣ
typedef struct tagHikDeviceInfo
{
    int nDevId;             //�豸ID
    char szDevName[260];    //�豸����
    char szIndexCode[64];   //�豸���
    char szIp[32];          //�豸IP
    unsigned int uPort;     //�豸�˿�
    char szUserName[130];   //�û���
    char szPassword[64];    //����
    int nDevType;           //�豸���ͣ�0~������1~��
    int nDomainId;          //�豸����DI
	int nProSeries;	        //��Ʒϵ��
    int nOrgId;             //��֯ID
    char szOrgName[130];    //��֯����
    /*����Э�飨ȫ��д����
    ������HIKSDK(�����豸)  DAHUASDK�����豸��  EHOME��EHOME�豸��  GB28181(�����豸)  
    ���������PISA��ONVIF  ��ô�ͻ���PISA��ONVIF*/
    char szTreatyType[64];          //�����ж����ܷ������豸��֧�ֺ���SDK(���� ���� + Э������ SDK) 
    char szDevKey[260];             //�豸Key������ƽ̨�ж��豸���ͼ���ص�������׼ȷ���ֶ�
    bool bDevOnline;                            //�豸����״̬��Add at 2015-07-14
    bool bDevUnit;                              //�Ƿ�Ϊ���豸Ϊ��λ������豸 1~�� 0~��
    /*
	001-7000ϵ��
	002-8000ϵ��
	003-9000ϵ��
	004-7100ϵ��
	005-8100ϵ��
	006-9100ϵ��
	007-����ϵ��
	008-ATMϵ��
	009-PCDVR
	010-GB28181ϵ��
	098-����ϵ��
	101-6000ϵ��
	102-6100ϵ��
	103-9001ϵ��
	104-����ʶ��ϵ��
	105-���ܷ���ϵ��
	106-����ϵ��
	107-������ϵͳ
	201-����ϵ��
	202-����ϵ��
	203-������������ϵ��
	204-������������ϵ��
	205-���ܽ�ͨϵ��
	099-ȫϵ��
	*/
    tagHikDeviceInfo* pNext;
}HikDeviceInfo;

//����ǽ��Ϣ�б�
typedef struct tagTvwall
{
    int iTvwallId;					        //����ǽid
    int nCellID;                            //��֯ID
    char szIndexCode[64 ];                  //����ǽindexcode
    char szTvwallName[128];                 //����ǽ����
    int iPrivilege;							//Ȩ��
    char szVmmIp[32];					    //����ǽ������ip
    unsigned int uPort;						//����ǽ�������˿�
    tagTvwall* pNext;
}HikTvwallInfo;

//��ȡ�豸�Խ��б�
typedef struct tagHikTalkChannel
{
    int nTalkId;       //�Խ�ͨ��ID
    int nTalkChannelNo;//�Խ�ͨ������ͨ����
    int nCellId;   //������֯�ܹ�
    char szDevIndexCode[64];  //�����豸���
    char szIndexCode[64];  //�Խ����
    char szTalkName[260];   //����
    tagHikTalkChannel* pNext;
}HikTalkChannel;

//�Խ��豸ͨ����Ϣ�����
typedef struct tagHikTalkDevChan
{
    char szIndexCode[64];    //�Խ����
    int  nResType;           //��Դ����: 503000-�Խ��豸ͨ��;503100-�Խ�����ͨ��
    char szSvrIp[128];       //��Դ���ڷ���IP
    int  nSvrPort;           //��Դ���ڷ���˿�
    int  nSvrType;           //��Դ�����������(3~VAG��17~DAG, 23~PEAG)
}HikTalkDevChan;

typedef struct tagHikTalkDevParam
{
    char szIndexCodeMain[64]; //�Խ�����ͨ�����
    char szIndexCode[64];    //�Խ�ͨ�����
    char szDevIndexCode[64];     //�Խ��豸���
    char szSvrIp[128];       //��Դ���ڷ���IP
    int  nSvrPort;           //��Դ���ڷ���˿�
    int  nSvrType;           //��Դ�����������(3~VAG��17~DAG, 23~PEAG)
}HikTalkDevParm;

//IO��Ϣ�б�
typedef struct tagHikIOInfo
{
    int nId;    //IO��ԴID
    int nCellId;   //������֯�ܹ�
    int nType;  //0~IO���룬1~IO���
    char szDevIndexCode[64];  //�����豸���
    char szIndexCode[64]; //���
    char szIoName[260];   //����
    int iChannalNO;       //IOͨ����
    tagHikIOInfo* pNext;
}HikIOInfo;

//ץͼ����
typedef struct _taghikSnapParam
{
    int nPicType;           // 0~JPG 1~BMP
    int nSnapType;          // 0~���� 1~����
    int nMultiType;         // ����ץͼ��ʽ ��ʱ�� 0 ����֡ 1
    int nSpanTime;          // ����ʱ ʱ���� ms
    int nSnapCount;         // ��ץ����  
    int Quality;            // ͼ������
    char szSaveFolder[256]; // ����·��
    long lOpenFlag;         // �򿪷�ʽ
    int nFormatType;        // ��ʽ����ʽ
}HikSnapParam;


//¼���������
typedef struct _tagHikRecordCfgParam
{
    int nType;              // 0��ʱ��ְ� 1�������� ��С
    char szFolder[256];     // ¼��洢�ļ���
    DWORD dwMaxRecordTimes; // �¼��ʱ�� �� 0 ������
    DWORD dwTimes;          // �ְ���С ����
    ULONGLONG dwPackSize;   // �ְ���С��0�򲻷ְ�,��λ �ֽ�
    int nFormatType;        // ��ʽ����ʽ
}HikRecordCfgParam,*LPHikRecordCfgParam;

typedef struct tagHikCruiseInfo
{
    int nPresetNo;  //Ԥ�õ��
    int nDwell;     //ͣ��ʱ����
    int nSpeed;     //Ѳ���ٶ�
    tagHikCruiseInfo* pNext;   
}HikCruiseInfo;

//�澯�¼�״̬(iAlarmStatus) 
#define    HIK_EVENT_STATE_INSTANT   0         /* ˲ʱ�¼� */
#define    HIK_EVENT_STATE_START     1         /* �¼���ʼ */
#define    HIK_EVENT_STATE_STOP      2         /* �¼����� */
#define    HIK_EVENT_STATE_PULSE     3         /* �¼����� */

//ʵʱ�澯�¼��ṹ��
typedef struct _tagSubscribeAlarmInfo
{
    char    alarmStarttime[32];             //�澯��ʼʱ��
    char    alarmStoptime[32];              //�澯����ʱ��
    char    csEventDesc[128];               //�澯����
    char    csLogId[64];                    //�澯ID
    char    alarmObjName[256];              //�澯Դ
    char    alarmObjIndexcode[64];          //�澯Դindexcode
    int     alarmObjType;                   //�澯Դ����
    int     iEventId;                       //�澯�¼�ID
    int     iAlarmLevel;                    //�澯�ȼ� 0~�ͣ�1~�еȣ�2~��
    int     iAlarmStatus;                   //�澯״̬���ο�HIK_EVENT_STATE_INSTANT�궨��
    char    csPicUrl[256];                  //ͼƬURL
    unsigned int uevent_type;               //�¼�����
} ALARMINFO, *LPALARMINFO;

//Ŀ����Դ�б� 
typedef struct HikResource_List
{
    int     iResouceType; //��Դ����(��δʹ�ã�Ĭ����)
    int     nResID;       //��ԴID(��δʹ�ã�Ĭ����0)
    long    nUserData;    //�û�ID(��δʹ�ã�Ĭ����0)
    char    szIndex[64];  //��Դ����
    HikResource_List* pNext;
}HIKRESOURCE_LIST,*pHIKRESOURCE_LIST;

//������ʷ�澯����
typedef struct HikSearchAlarmLogParam
{
    int  iAlarmState;        //�澯״̬ /*����ȫ��״̬�ֶ� 0 ȫ��*/
    int  iConfirmState;      //ȷ��״̬

    char sObjKeyName[512];   /* �澯�������� ֧��LIKEģ��ƥ�� ����һ�����ݿ��ֶ�*/
    char sEventKeyName[512]; //�澯�¼���ѯ�ؼ���
    char sBeginTime[65];     //��ѯ�澯 ����(��ʼ)ʱ�� ��ʼ��/* ��ʽ-01-02 01:00:00 */
    char sEndTime[65];       //��ѯ�澯 ����(��ʼ)ʱ�� ��ֹ�� 

    int  iSortType;          /*�������ʽ ��CMS��������,1 ���� 2 ����*/
    char szSortName[128];    /*�����ֶ����� Ŀǰ�̶���UI��Ƶ�ʱ�䡢�ȼ������ơ�״̬����������*/

    int* pEventTypes;        //�¼�ID����  �ƶ����ʲô��
    int nEventTypeNum;       //�¼�ID�����С

    int* pLevels;          //�ȼ�
    int nLevelNum;         //�¼��ȼ������С

    pHIKRESOURCE_LIST pTarget; //Ŀ���б�
    int nTargetLen;            //Ŀ���б���
}HIKSEARCHALARMLOGPARAM,*pHIKSEARCHALARMLOGPARAM;

////�澯¼����Ϣ �澯��ʷ��ʹ��
//typedef struct tagHikAlarmRecordLinkInfo
//{
//    char sLinkCamera[64];          /* ����¼���ص�*/
//    char sLinkStaTime[65];         /* ����¼��ʼʱ��*/
//    char sLinkStpTime[65];         /* ����¼�����ʱ��*/
//    tagHikAlarmRecordLinkInfo* pNext;
//}HikAlarmRecordLinkInfo;
//
////�澯ͼƬ��Ϣ �澯��ʷ��ʹ��
//typedef struct tagHikAlarmSnapLinkInfo
//{
//    char sLinkUrl[256];            /* ����ͼƬUrl*/
//    char sLinkCamera[64];          /* ����ͼƬ��ص�*/
//    char sLinkTriggerTime[65];           /* ����ͼƬ��ʼʱ��*/
//    tagHikAlarmSnapLinkInfo* pNext;
//}HikAlarmSnapLinkInfo;
//
////�澯ȷ����Ϣ �澯��ʷ��ʹ��
//typedef struct tagHikAlarmConfrimInfo
//{
//    int nConfirmer;                                       //ȷ����
//    char sConfirmTime[65];				          // ȷ��ʱ��
//    char sConfirmDsc[1028];				              // ȷ������
//}HikAlarmConfrimInfo;
//
////�澯Դ��Ϣ �澯��ʷ��ʹ��
//typedef struct tagHikAlarmSrcObjInfo
//{
//    int  iObjType;                                                    //�����澯�Ķ�������
//    char szObjName[128];                     //�����澯�Ķ�����
//    char szObjIndex[64];					//�����澯�Ķ���index
//}HikAlarmSrcObjInfo;
//
////�澯������Ϣ
//typedef struct tagHikAlarmCfgInfo
//{
//    int   iAlarmType;                                                 //�澯�¼�����
//    int   iAlarmEventlevel;                                        //�澯�ȼ�      
//    char  szAlarmEventCfgID[128];      //����ID
//    char  sAlarmEventname[1024];   //�澯�¼�����
//}HikAlarmCfgInfo;
//
//typedef struct tagHikAlarmTime
//{
//    char sBeginTime[65];                               //��ʼʱ��
//    char sEndTime[65];                                  //����ʱ��
//}HikAlarmTime;

////������־���صĽ����Ϣ
//typedef struct tagHikSearchAlarmLogResult
//{
//    char sAlarmlogid[128];                      //�澯��־ID          
//    int  iStatus;                                        //�澯״̬
//
//    char sLogtxt[512];					             //��־��Ϣ	
//    char sLogRemark[512];                            //��־��ע 
//    char sPicUrl[256];                               //ͼƬ��Ϣ
//
//    bool isRecord;                                       //�Ƿ�¼��
//    bool isConfrim;                                      //�Ƿ�ȷ��
//    bool isPicture;                                      //�Ƿ�������ͼƬ
//    HikAlarmRecordLinkInfo* pRcInfo;                        //¼����Ϣ
//    HikAlarmConfrimInfo        confriminfo;                 //ȷ����Ϣ
//    HikAlarmSrcObjInfo          objinfo;                    //�澯Դ��Ϣ
//    HikAlarmCfgInfo               cfginfo;                  //�澯������Ϣ
//    HikAlarmTime                   timeinfo;                //�澯ʱ��
//    HikAlarmSnapLinkInfo* pSnapInfo;
//
//    tagHikSearchAlarmLogResult* pNext;
//}HIKSEARCHALARMLOGRESULT,*pHIKSEARCHALARMLOGRESULT;

/*�澯�¼��ȼ�*/
enum HikAlarmLevel				
{
    HIK_LEVEL_HIGH = 1,    //��
    HIK_LEVEL_MEDIUM = 2,  //��
    HIK_LEVEL_LOW = 3      //��
};

//ʵʱ�����澯����ͳ������
typedef enum tagRealFlowAlarmType
{
    eIndex_AlarmType_FrmStatic = 0,
    eIndex_AlarmType_UnitStatic = 1
}RealFlowAlarmType;

/*�澯�¼�����*/
enum HikAlarmEventType
{   
    //��ص�澯�¼�
    Hik_AlarmEventType_LOSE = 131329,       /*��Ƶ��ʧ*/
    Hik_AlarmEventType_COVER = 131330,      /*�ڵ�*/
    Hik_AlarmEventType_MD = 131331,         /*�ƶ����*/
    Hik_AlarmEventType_VIDEO_PIR            = 131332,   /* ������ⱨ�� */ 
    Hik_AlarmEventType_VIDEO_WIRELESS       = 131333,   /* ���߱��� */ 
    Hik_AlarmEventType_VIDEO_CALLHELP       = 131334,   /* ���ȱ��� */

    //�������澯�¼�
    Hik_AlarmEventType_IOIN = 589825,   //��������

    //���ܼ�ص�澯�¼�
    Hik_AlarmEventType_VCA_TRAVERSE_PLANE   = 131585,   /* ��Խ������ */
    Hik_AlarmEventType_VCA_ENTER_AREA       = 131586,   /* �������� */
    Hik_AlarmEventType_VCA_EXIT_AREA        = 131587,   /* �뿪���� */
    Hik_AlarmEventType_VCA_INTRUSION        = 131588,   /* �ܽ����� */
    Hik_AlarmEventType_VCA_LOITER           = 131590,   /* �ǻ� */
    Hik_AlarmEventType_VCA_LEFT_TAKE        = 131589,   /* ��Ʒ��ȡ���� */
    Hik_AlarmEventType_VCA_PARKING          = 131591,   /* ͣ�� */
    Hik_AlarmEventType_VCA_RUN              = 131592,   /* �����ƶ�  */
    Hik_AlarmEventType_VCA_HIGH_DENSITY     = 131593,   /* ��Ա�ۼ� */
    Hik_AlarmEventType_VCA_LEFT             = 131594,   /* ��Ʒ���� */
    Hik_AlarmEventType_VCA_TAKE             = 131595,   /* ��Ʒ��ȡ */
    Hik_AlarmEventType_VCA_VIOLENT_MOTION   = 131596,   /* ����ͻ�� */
    Hik_AlarmEventType_VCA_REACH_HIGHT      = 131597,   /* �ʸ߼�� */
    Hik_AlarmEventType_VCA_GET_UP           = 131598,   /* ������ */
    Hik_AlarmEventType_VCA_HUMAN_ENTER      = 131599,   /* �˿���ATM  */
    Hik_AlarmEventType_VCA_OVER_TIME        = 131600,   /* ������ʱ    */
    Hik_AlarmEventType_VCA_STICK_UP         = 131601,   /* ��ֽ��,֧���������   */
    Hik_AlarmEventType_VCA_INSTALL_SCANNER  = 131602,   /* ��װ������,֧��������� */
    Hik_AlarmEventType_VCA_LEAVE_POSITION   = 131603,   /* ��� */
    Hik_AlarmEventType_VCA_TRAIL            = 131604,   /* β�� */
    Hik_AlarmEventType_VCA_FALL_DOWN        = 131605,   /* ���ؼ�� */
    Hik_AlarmEventType_VCA_AUDIO_ABNORMAL   = 131606,   /* ��ǿͻ���� */
    Hik_AlarmEventType_VCA_ADV_REACH_HEIGHT = 131607,   /* �����ʸ� */
    Hik_AlarmEventType_VCA_TOILET_TARRY     = 131608,   /* ��޳�ʱ  */
    Hik_AlarmEventType_VCA_YARD_TARRY       = 131609,   /* �ŷ糡����  */
    Hik_AlarmEventType_VCA_FACE             = 131621,   /* �������  */
    Hik_AlarmEventType_VCA_PLATE            = 131622,   /* �������  */

    //������������ʶ���¼�
    Hik_AlarmEventType_VCA_FACESNAP_RESULT  = 131614,   /*����ʶ����*/
    Hik_AlarmEventType_VCA_FACESNAP_ALARM   = 131615,   /*�������ʶ�𱨾�*/
    Hik_AlarmEventType_VCA_PDC_DATA         = 131616,   /*������ͳ��*/
    Hik_AlarmEventType_VCA_PDC_FULL         = 131617,   /* ������Ա */
    Hik_AlarmEventType_VCA_PDC_FULL_ALARM   = 131618,   /* ����Ա */

    //�Ž��¼�
    Hik_AlarmEventType_ACCESS_CARD_DOOR     = 198914,   // ˢ������
    Hik_AlarmEventType_ACCESS_OUT_DOOR      = 198916,   // ��ť����
    Hik_AlarmEventType_ACCESS_IGL_DOOR      = 197633,   // �Ƿ���
    Hik_AlarmEventType_ACCESS_WRONG_PWD     = 197121,   // ˢ�������
    Hik_AlarmEventType_ACCESS_DOOR_OPEN     = 198657,   // �Ƿ�����
    Hik_AlarmEventType_ACCESS_OPEN_TIMEOUT  = 198400,   // ��ʱ��δ����
    Hik_AlarmEventType_ACCESS_FORCE_OPEN    = 199425,   // в�ȿ���
    Hik_AlarmEventType_ACCESS_DOOR_ON       = 198913,   // �Ŵ�
    Hik_AlarmEventType_ACCESS_SUPER_PWD     = 198915,   // �������뿪��
    Hik_AlarmEventType_ACCESS_OUT_OFF       = 199169,   // �Źر�

    //Ѳ���豸
    AlarmEventType_PATROL_NORMAL             = 262145,   // ����
    AlarmEventType_PATROL_EARLIER            = 262146,   // ��Ѳ
    AlarmEventType_PATROL_LATER              = 262147,   // ��Ѳ
    AlarmEventType_PATROL_LEAK               = 262148,   // ©Ѳ
    AlarmEventType_PATROL_MAKEUP             = 262149,   // ��©Ѳ
    AlarmEventType_PATROL_ALARM              = 262150,   // Ѳ���¼�

    //��������
    Hik_AlarmEventType_ENV_TEMPERATURE           = 459009,   // �¶�ʵʱ����
    Hik_AlarmEventType_ENV_HUMIDITY              = 459010,   // ʪ��ʵʱ����
    
    // �����豸    
    Hik_AlarmEventType_ELECNET_NORMAL            = 786433,   // ������Ϣ
    Hik_AlarmEventType_ELECNET_TOUCHNET          = 786434,   // ��������
    Hik_AlarmEventType_ELECNET_SHORTOUT          = 786435,   // ��·����
    Hik_AlarmEventType_ELECNET_WIREBREAK         = 786436,   // ���߱���
    Hik_AlarmEventType_ELECNET_SENSOR            = 786437,   // ���б���

    // GPS�¼�
    Hik_AlarmEventType_GPS           = 851969,   /* GPS�澯 */
    Hik_AlarmEventType_GPS_SPEED     = 851970,   /* GPS���� */
    Hik_AlarmEventType_GPS_OFFSET    = 851971,   /* GPSƫ�� */

    // �ͻ����¼�
    Hik_AlarmEventType_MANUAL               = 655361, /* �ͻ����ֶ��¼� */
    Hik_AlarmEventType_MANUAL_FAULT         = 655362, /* �ͻ��˹����ϱ� */
};

//////////////////////////////////////////////////////////////////////////
//��ҳ��Ϣ
typedef struct PageInfo
{
    int iNum;      //@��δʹ��
    int iAllRow;   //@��δʹ��
    int iCurPage;  //��ǰҳ��
    int iTotalPage; //ȫ��ҳ��
    int iPageSize; //ÿҳ������С
    int iOffSet;   //@��δʹ��
    int iTotalNum; //�ܴ�С
}HikPAGEINFO,*pHikPAGEINFO;

/** @enum HIK_STREAM_DATATYPE
* @brief ��������������
*/
enum HIK_STREAM_DATATYPE
{
    HIK_STREAM_FORWARD = 1, // ����ͷ���
    HIK_STREAM_DATA = 2,    // ��������
    HIK_STREAM_END = 100,   // �������(�طš����ػ򵹷Ž���)
};

/** 
*  @brief ʵʱ�澯�¼����ջص�
*  @param const ALARMINFO* pAlrInfo��ʵʱ�澯��Ϣ
*  @param void* pUser���û�����
*/
typedef void (__stdcall* pAlarmEventCallback)(const ALARMINFO* pAlrInfo, void* pUser);

/** 
*  @brief ȡ���ص�(����Ԥ���ͻط�)
*  @param long lSession��ȡ��ʵ��
*  @param int iStreamType����������������,��ϸ�ɲο�HIK_STREAM_DATATYPE����
*  @param const char* data�����������ַ�
*  @param int dataLen���������ݳ���
*  @param void* pUser���û�����
*/
typedef void (__stdcall *pStreamCallback)(long lSession, int iStreamType, const char* data, int dataLen, void* pUser);

/** 
*  @brief ץͼ���ջص�(����Ԥ���ͻط�)
*  @param long lSession��ȡ��ʵ��
*  @param int nErr�������룬һ��Ϊ0����ʾ�ɹ��������ݲ�����
*  @param const char* picPath��ץͼ�ɹ��󱣴��ͼƬȫ·��
*  @param void* pUser���û�����
*/
typedef void (__stdcall *pSnapShotCallback)(long lSession,int nErr,const char* picPath,void* pUser);

/** 
*  @brief Ԥ������¼��ص�
*  @param long lSession��ȡ��ʵ��
*  @param int nErr�������룬һ�㲻����
*  @param const char* data����������
*  @param void* pUser���û�����
*/
typedef void (__stdcall *pPreviewRecordEndCallback)(long lSession,int nErr,const char* data,void* pUser);

/** 
*  @brief MQ��Ϣ�ص�������GPS��Ϣ
*  @param int nMsgId����ϢID
*  @param int lParam��Ԥ������
*  @param const char* szInfo��GPS��Ϣ
*  @param void* pUser���û�����
*/
typedef void (__stdcall *pGPSReceiveCallback)(int nMsgId,int lParam,const char* szInfo,void* pUser);

//���ò���Ȩ����
#define HIK_WBS_OPCODE_PLAYVIEW         10001   //ʵʱԤ��
#define HIK_WBS_OPCODE_PLAYBACK         10006   //¼��ط�
#define HIK_WBS_OPCODE_IO               40002   //�鿴�澯��
#define HIK_WBS_OPCODE_TALKCHANNEL      90001   //�鿴�Խ�ͨ��
#define HIK_WBS_OPCODE_PDCPASSANGERCFG  10033 //����������

//��������Ȩ����
#define HIK_WBS_OPCODE_SERVIDEOPARAM    10002   //��Ƶ��������
#define HIK_WBS_OPCODE_LOCALRECORD      10003   //����¼��
#define HIK_WBS_OPCODE_PTZCONTROL       10004   //�ƾ�����
#define HIK_WBS_OPCODE_SERPTZ           10005   //�ƾ�����

//����C#�Խṹ��������ʽ���������Դ�б�
#define HIK_MAX_SIZE_RES_CELL          10000    //��֯�б�������
#define HIK_MAX_SIZE_RES_CAMERA        2000     //��֯�¼�ص��б�������
#define HIK_MAX_SIZE_RES_IO            2000     //��֯�±������б�������
#define HIK_MAX_SIZE_RES_TALK_CAHNEL   2000     //��֯�¶Խ�ͨ���б�������
#define HIK_MAX_SIZE_RES_USER          1000      //��֯���û��б�������
#define HIK_MAX_SIZE_RES_TVWALL        200      //����ǽ�б�������

//���ĸ��ڵ�ID
#define HIK_RS_CELL_PARENT_ID_ALL        -1     //��ȡȫ����֯�б�

//��֯����
#define HIK_RS_CELL             1000 //��֯
#define HIK_RS_USERCELL         3000 //�û���֯

//��Դ��Ϣ
#define HIK_RS_CAMERA           10000 //��ص�
#define HIK_RS_DEV_CODE         30000 //����
#define HIK_RS_IO_ALARM         40000 //IO����
#define HIK_RS_TALK_CHANNEL     90000 //�Խ�ͨ��
#define HIK_RS_USER             2000  //�û���Դ

//[¼��ط�]���ſ�������
#define PLAY_START              10001 //��ʼ����
#define PLAY_PAUSE              10002 //��ͣ����
#define PLAY_SPEED_CHG          10003 //�����ٶȿ���
#define PLAY_OFFSET             10004 //���Ŷ�λ
#define PLAY_ONEFRAMEFORWARD    10005 //��֡��
#define PLAY_OneFRAMEBACKWARD   10006 //��֡��

//��̨��������
#define PLAT_SET_PRESET	    8	//����Ԥ��λ
#define PLAT_CLE_PRESET	    9	//ɾ��Ԥ��λ
#define PLAT_ZOOM_IN	    11	//��ͷ����
#define PLAT_ZOOM_OUT	    12	//��ͷ��Զ
#define PLAT_FOCUS_NEAR	    13	//����ǰ��
#define PLAT_FOCUS_FAR	    14	//������
#define PLAT_IRIS_OPEN	    15 	//��Ȧ����
#define PLAT_IRIS_CLOSE	    16 	//��Ȧ��С
#define PLAT_TILT_UP	    21	//��ͷ����
#define PLAT_TILT_DOWN	    22	//��ͷ����
#define PLAT_PAN_LEFT	    23	//��ͷ����
#define PLAT_PAN_RIGHT	    24	//��ͷ����
#define PLAT_UP_LEFT	    25	//��̨��������ת
#define PLAT_UP_RIGHT	    26	//��̨��������ת
#define PLAT_DOWN_LEFT	    27	//��̨�¸�����ת
#define PLAT_DOWN_RIGHT	    28	//��̨�¸�����ת
#define PLAT_PAN_AUTO		29	//��̨�����Զ�ɨ��
#define PLAT_FILL_PRE_SEQ	30	//��Ԥ�õ����Ѳ������
#define PLAT_STA_MEM_CRUISE	34	//��ʼ��¼�켣
#define PLAT_STO_MEM_CRUISE	35	//ֹͣ��¼�켣
#define PLAT_RUN_CRUISE		36	//��ʼ�켣
#define PLAT_STOP_CRUISE	44	//ֹͣ�켣
#define PLAT_RUN_SEQ	    37	//��ʼѲ��
#define PLAT_STOP_SEQ	    38	//ֹͣѲ��
#define PLAT_GOTO_PRESET	39	//����Ԥ��λ
#define PLAT_CMD_3D_ZOOM    99  //3D�Ŵ�
#define PLAT_CAMERA_UNLOCK	201	//�����̨����


#define PLAT_STATUS_DEFENCE     1   //����
#define PLAT_STATUS_DISDEFENCE  2   //����

#define PLAT_STATUS_IOOPEN      8   //IO��
#define PLAT_STATUS_IOCLOSE     9   //IO�ر�

/* @brief ¼������ö��
*/
enum HIK_RECORD_TYPE
{
    HIK_RECTYPE_UNKNOWN = 0,     // δ֪
    HIK_RECTYPE_PLAN = 0x01,     // �ƻ�¼��
    HIK_RECTYPE_MOVE = 0x02,     // �ƶ�¼��
    HIK_RECTYPE_ALARM = 0x04,    // �澯¼��
    HIK_RECTYPE_MANUAL = 0x10,   // �ֶ�¼��
    HIK_RECTYPE_ALL = 0xFF,      // ȫ������
};

#define PLAT_RECORD_RESULT_XML_BUFFER_SIZE   1024 * 200 //¼���ѯ����Ƭ�����ݻ�������С

#define PLAT_MAX_PAGE_HISTORY_ALARMEVENT    2000        //��ʷ�澯��־��ѯ��ҳ�������

//������궨��
#define	HIKPT_E_OK						    (0)	                                // û�д���
#define	HIKPT_E_ERROR						(-1)                                // ����ͨ�ô���

//ͨ�ô�����
#define SDK_ERROR_BASE					    (1000)						        ///���������
#define SDK_ERROR_LOGINFAIL				    (SDK_ERROR_BASE+1)					///��¼ʧ��
#define SDK_ERROR_CONNECTCMS_FAIL		    (SDK_ERROR_BASE+2)					///����CMSʧ��
#define SDK_ERROR_SERVER_FAIL_NAME_PASW	    (SDK_ERROR_BASE+3)					///�û������������
#define SDK_ERROR_SERVERURL_ERROR           (SDK_ERROR_BASE+4)					///��������ַΪ�ջ�����Ч��Ч
#define SDK_ERROR_SERVER_MAIN_KICK_OUT      (SDK_ERROR_BASE+5)                  ///������Ա������
#define SDK_ERROR_PLUG_LOAD                 (SDK_ERROR_BASE+6)                  ///�������ʧ��
#define SDK_ERROR_PARA_OVER                 (SDK_ERROR_BASE+7)                  ///��������Ƿ�
#define SDK_ERROR_NOLOGIN                   (SDK_ERROR_BASE+8)                  ///�û�δ��¼
#define SDK_ERROR_ALREADYLOGIN              (SDK_ERROR_BASE+9)                  ///�û��ѵ�¼
#define SDK_ERROR_CLIENTFRAME_INIT          (SDK_ERROR_BASE+10)                 ///��ʼ�������ʧ��


//Ԥ������
#define SDK_ERROR_PREVIEW_FAIL	            (SDK_ERROR_BASE+20)					///Ԥ��ʧ��
#define SDK_ERROR_PREVIEW_PERMISSION_FAIL   (SDK_ERROR_BASE+21)					///û�иü�ص��ʵʱԤ��Ȩ��
#define SDK_ERROR_PREVIEW_OUTOF_RES         (SDK_ERROR_BASE+22)					///����ʵʱ�����Ƶʧ��,ϵͳ��Դ����
#define SDK_ERROR_PREVIEW_MAX_CONN          (SDK_ERROR_BASE+23)					///����ʵʱ�����Ƶʧ��,�ѳ�����ý�����������
#define SDK_ERROR_PREVIEW_LINCENE_MAX_CONN  (SDK_ERROR_BASE+24)					///����ʵʱ�����Ƶʧ��,�ѳ���Lincene���������
#define SDK_ERROR_PREVIEW_PB_FAILED         (SDK_ERROR_BASE+25)					///���漴ʱ�ط�¼��ʧ��
#define SDK_ERROR_PREVIEW_PB_FAILED_SPACE   (SDK_ERROR_BASE+26)					///���漴ʱ�ط�¼��ʧ��,û�д��̿ռ�
#define SDK_ERROR_PREVIEW_DOWN              (SDK_ERROR_BASE+27)					///�豸������

//��̨����
#define SDK_ERROR_PTZ_NET_ERROR             (SDK_ERROR_BASE+40)					///�ƾ�����ʧ��!������������
#define SDK_ERROR_PTZ_OPER_FAILED_LEVEL     (SDK_ERROR_BASE+41)					///�ƾ�����ʧ��!�ƾ�����Ȩ���û���ռ
#define SDK_ERROR_PTZ_NO_SUPPORT            (SDK_ERROR_BASE+42)					///�ƾ�����ʧ��!��������豸��֧�ָù���
#define SDK_ERROR_CRUISE_FAILED_TIP         (SDK_ERROR_BASE+43)					///����Ѳ��·��ʧ��
#define SDK_ERROR_CRUISE_NAME_EXIST         (SDK_ERROR_BASE+44)					///����Ѳ��·��ʧ��!Ѳ��·�������Ѵ���
#define SDK_ERROR_CRUISE_NOT_ALL_NUM        (SDK_ERROR_BASE+45)					///Ѳ��·�����Ʋ���ȫ����������
#define SDK_ERROR_CRUISE_NOT_CONTAIN        (SDK_ERROR_BASE+46)					///Ѳ��·�����Ʋ��ð��������ַ�
#define SDK_ERROR_PRESET_FAIL               (SDK_ERROR_BASE+50)					///����Ԥ�õ�ʧ��


//�ط�
#define SDK_ERROR_SEARCH_RECORD_FAILED      (SDK_ERROR_BASE+80)					///��ѯ¼��ʧ��
#define SDK_ERROR_PLAYBACK_FAIL             (SDK_ERROR_BASE+81)					///�ط�¼��ʧ��
#define SDK_ERROR_PLAYBACK_PERMISSION_FAIL	(SDK_ERROR_BASE+82)					///û�лط�Ȩ��
#define SDK_ERROR_PLAYBACK_CHECKTIME    	(SDK_ERROR_BASE+83)					///¼���ѯʱ�䲻���Ϲ涨���߿�ʼʱ����ڽ���ʱ��
#define SDK_ERROR_CURTIME_NO_RECORD    	    (SDK_ERROR_BASE+84)					///��ǰʱ���û��¼���ļ�
#define SDK_ERROR_DOWNLOADFILE_FAIL    	    (SDK_ERROR_BASE+85)					///����¼���ļ�ʧ��

//��Դ�б�
#define SDK_ERROR_CELLINFO_LIST_CUTOFF           (SDK_ERROR_BASE+101)                ///��֯�б��ض�
#define SDK_ERROR_USERORG_LIST_CUTOFF            (SDK_ERROR_BASE+102)                ///�û���֯�б��ض�
#define SDK_ERROR_CAMERAINFO_LIST_CUTOFF         (SDK_ERROR_BASE+103)                ///��ص��б��ض�
#define SDK_ERROR_IOINFO_LIST_CUTOFF             (SDK_ERROR_BASE+104)                ///IO�б��ض�
#define SDK_ERROR_TALKCHANNEL_LIST_CUTOFF        (SDK_ERROR_BASE+105)                ///�Խ�ͨ���б��ض�
#define SDK_ERROR_PLATFORMUSER_LIST_CUTOFF       (SDK_ERROR_BASE+106)                ///�û���Ϣ�б��ض�
#define SDK_ERROR_TVWALL_LIST_CUTOFF             (SDK_ERROR_BASE+107)                ///����ǽ��Ϣ�б��ض�

//���
#define SDK_ERROR_PLUG_LOAD_GETDATA             (SDK_ERROR_BASE+150)                 ///��ȡ�����������ʧ��
#define SDK_ERROR_PLUG_LOAD_GETPREVIEW          (SDK_ERROR_BASE+151)                 ///��ȡԤ�����ʧ��
#define SDK_ERROR_PLUG_LOAD_GETALARMIMPL        (SDK_ERROR_BASE+152)                 ///��ȡ�澯���ʧ��
#define SDK_ERROR_PLUG_LOAD_GETPTZ              (SDK_ERROR_BASE+153)                 ///��ȡ�ƾ�����ʧ��
#define SDK_ERROR_PLUG_LOAD_GETAPC              (SDK_ERROR_BASE+154)                 ///��ȡAPCʧ��
#define SDK_ERROR_PLUG_LOAD_GETAPCNETWORK       (SDK_ERROR_BASE+155)                 ///��ȡAPC����ʧ��
#define SDK_ERROR_PLUG_LOAD_GETAPCHANDLE        (SDK_ERROR_BASE+156)                 ///��ȡAPC���ʧ��
#define SDK_ERROR_PLUG_LOAD_GETNET              (SDK_ERROR_BASE+157)                 ///��ȡ����ʧ��
#define SDK_ERROR_PLUG_LOAD_GETNETTALK          (SDK_ERROR_BASE+158)                 ///��ȡ�Խ����ʧ��

#define SDK_ERROR_PLUG_NETTALKINIT              (SDK_ERROR_BASE+159)                 ///����Խ���ʼ��ʧ��
#define SDK_ERROR_PLUG_NETTALKCREATE            (SDK_ERROR_BASE+160)                 ///����Խ�����ʧ��

#define SDK_ERROR_FILEPATH_NOTEXIST             (SDK_ERROR_BASE+170)                 ///�ļ�Ŀ¼������

//��������
enum HIK_STREAM_TYPE
{
    default_stream = -1, //ʹ��ƽ̨��ص�����Ĭ�����õ�����
    main_stream = 0, //������
    sub_stream = 1, //������
    third_stream = 2, //��������
};

/** @struct tagControlInfo
 *  @brief ������Ϣ�ṹ��;
*/
typedef struct tagHikControlInfo
{
    int nCtrlType;          ///< �������ͣ���CTRL_TYPE_*;;
    int nCtrlValue;         ///< ����ֵ����CTRL_VALUE_*;
    char* pExtInfo;         ///< �����ַ��ֶ�,����������ϢXML���ĵ�;
}HikDAG_CONTROLINFO, *LPHikDAG_CONTROLINFO;

/** @struct tagDAG_LISTRESSTATUS
*  @brief  ��Դ����״̬;
*/
typedef struct tagHikDAG_RESRUNSTATUS
{
    char szIndexCode[256];      ///< ��Դindexcode
    int  nStatusType;                             ///< ״̬���ͣ��μ�STATUS_TYPE_���壻�������ͣ��μ�CTRL_TYPE_*����
    int  nStatusValue;                            ///< ״ֵ̬���μ�STATUS_VALUE_���壻����ֵ���μ�CTRL_VALUE_*����
    char szContent[256];             ///< ״̬��Ϣ
}HikDAG_RESRUNSTATUS, *LPHikDAG_RESRUNSTATUS;

// �豸��������
#define CTRL_TYPE_TALK                    5 ///< �Խ���������Ӧ����ֵ��CTRL_VALUE_TALK_*

//�Խ���������ֵ
#define CTRL_VALUE_TALK_BDSTART           0     ///< ��ʼ�㲥
#define CTRL_VALUE_TALK_BDSTOP            1     ///< ֹͣ�㲥
#define CTRL_VALUE_TALK_CALL              2     ///< ����
#define CTRL_VALUE_TALK_ANSWER            3     ///< ����
#define CTRL_VALUE_TALK_HANGUP            4     ///< �Ҷ�
#define CTRL_VALUE_TALK_TALK              5     ///< �Խ�
#define CTRL_VALUE_TALK_MONITORSTART      6     ///< ��ʼ����
#define CTRL_VALUE_TALK_MONITORSTOP       7     ///< ֹͣ����

// �豸����״̬����
#define STATUS_TYPE_UNKNOW   -1 ///< δ֪������״̬
#define STATUS_TYPE_DEFENCE   0 ///< ����������Ӧ״ֵ̬��STATUS_VALUE_DEFENCE_*
#define STATUS_TYPE_BYPASS    1 ///< ��·����Ӧ״ֵ̬��STATUS_VALUE_BYPASS_*
#define STATUS_TYPE_DOOR      2 ///< ��״̬����Ӧ״ֵ̬��STATUS_VALUE_DOOR_*
#define STATUS_TYPE_BROADCAST 3 ///< �㲥ͨ��״̬����Ӧ״ֵ̬��STATUS_VALUE_BROADCAST_*
#define STATUS_TYPE_IPPHONE   4 ///< �绰ͨ������Ӧ״ֵ̬ STATUS_VALUE_IPPHONE_* @DEV_Status.h
#define STATUS_TYPE_TALK      5 ///< �Խ�ͨ��״̬����Ӧ״ֵ̬��STATUS_VALUE_TALK_*

#define STATUS_TYPE_COMMON   99 ///< ͨ��ͨ��״̬����Ӧ״ֵ̬��STATUS_VALE_COMMON_*
/*-------------------docontrol״̬,��ҪʱҲ��GetStatus���أ���ʱ�����Ͷ����1000��ʼ  ��1000+CTRL_TYPE_*��--------------------------------------------------*/

// ��״ֵ̬
#define STATUS_VALUE_DOOR_NORMAL    0 ///< ����
#define STATUS_VALUE_DOOR_UNLOCKED  1 ///< ����
#define STATUS_VALUE_DOOR_LOCKED    2 ///< ����

// ������״ֵ̬
#define STATUS_VALUE_DEFENCE_ON     1 ///< ����״̬
#define STATUS_VALUE_DEFENCE_OFF    0 ///< ����״̬

// ��·״ֵ̬
#define STATUS_VALUE_BYPASS_ON      1
#define STATUS_VALUE_BYPASS_OFF     0

// �㲥״ֵ̬
#define STATUS_VALUE_BROADCAST_FREE 0   ///< ����-����;
#define STATUS_VALUE_BROADCAST_BUSY 1   ///< ����-����;

//�绰״ֵ̬
#define STATUS_VALUE_IPPHONE_IDLE               0  //������
#define STATUS_VALUE_IPPHONE_RINGING            1  //������
#define STATUS_VALUE_IPPHONE_DIALING            2  //������
#define STATUS_VALUE_IPPHONE_COMUNICATION       3  //ͨ����

//�Խ�״ֵ̬
#define STATUS_VALUE_TALK_FREE         0   ///< ����;
#define STATUS_VALUE_TALK_CALLING      1   ///< ������;
#define STATUS_VALUE_TALK_TALKING      2   ///< �Խ���;
#define STATUS_VALUE_TALK_BROADCASTING 3   ///< �㲥��;
#define STATUS_VALUE_TALK_CALLEDING    4   ///< ��������;
#define STATUS_VALUE_TALK_MONITORING   5   ///< ������;

// ͨ��״̬
#define STATUS_VALE_COMMON_NORMAL      0   ///< ����
#define STATUS_VALE_COMMON_OFFLINE     1   ///< ����
#define STATUS_VALE_COMMON_BREAKDOWN   2   ///< ����
#define STATUS_VALE_COMMON_UNKNOWN     3   ///< δ֪
#define STATUS_VALE_COMMON_ALARM       4   ///< ����

//�ط��ٶ�
enum HIK_PLAYBACK_SPEED
{
    HIK_PB_SPEED_MIN = -4,                  //��С�ٶ�
    HIK_PB_SPEED_1_16 = -4,                 //1/16����
    HIK_PB_SPEED_1_8 = -3,                  //1/8����
    HIK_PB_SPEED_1_4 = -2,                  //1/4����
    HIK_PB_SPEED_1_2 = -1,                  //1/2����
    HIK_PB_SPEED_1_1 = 0,                   //1����
    HIK_PB_SPEED_2_1 = 1,                   //2����
    HIK_PB_SPEED_4_1 = 2,                   //4����
    HIK_PB_SPEED_8_1 = 3,                   //8����
    HIK_PB_SPEED_16_1 = 4,                  //16����(8���ٵ���Ҫ��֤GOP����������Ҫͻ����16����ȫ֡ȡ��)
    HIK_PB_SPEED_MAX = 4,                   //����ٶ�
    HIK_PB_SPEED_INVALID = 100,             //��Чֵ
};

//3D�Ŵ�-�Ŵ��������
typedef struct _tagSelZoomInfo
{
    int xTop;                                   //��ʼ������X���Ӧֵ
    int yTop;                                   //��ʼ������Y���Ӧֵ
    int xBottom;                                //����������X���Ӧֵ
    int yBottom;                                //����������Y���Ӧֵ
    int nWidth;                                 //(��ǰ)���Ŵ��ڵĿ��
    int nHeigh;                                 //(��ǰ)���Ŵ��ڵĸ߶�
}HikSelZoomInfo;

//���û�ȡԤ�õ�
typedef struct tagHikPresetInfo
{
    int nPresetNo;      //Ԥ�õ�ţ���Ӧ���豸�е�˳��
    char szPresetName[130];    //����
    tagHikPresetInfo* pNext;
}HikPresetInfo;

#ifdef __cplusplus
}
#endif  //#ifdef __cplusplus

//�澯¼����Ϣ �澯��ʷ��ʹ��
typedef struct tagHikAlarmRecordLinkInfo
{
    char sLinkCamera[64];          /* ����¼���ص�*/
    char sLinkStaTime[65];         /* ����¼��ʼʱ��*/
    char sLinkStpTime[65];         /* ����¼�����ʱ��*/
    tagHikAlarmRecordLinkInfo* pNext;
    tagHikAlarmRecordLinkInfo()
    {
        memset(sLinkCamera,0,sizeof(char)*64);
        memset(sLinkStaTime,0,sizeof(char)*65);
        memset(sLinkStpTime,0,sizeof(char)*65);
        pNext = NULL;
    }
    tagHikAlarmRecordLinkInfo(const tagHikAlarmRecordLinkInfo& obj)
    {
        strncpy_s(sLinkStaTime,_countof(sLinkStaTime),obj.sLinkStaTime,_TRUNCATE);
        strncpy_s(sLinkStpTime,_countof(sLinkStpTime),obj.sLinkStpTime,_TRUNCATE);
        strncpy_s(sLinkCamera,_countof(sLinkCamera),obj.sLinkCamera,_TRUNCATE);
        pNext = NULL;
    }
}HikAlarmRecordLinkInfo;

//�澯ͼƬ��Ϣ �澯��ʷ��ʹ��
typedef struct tagHikAlarmSnapLinkInfo
{
    char sLinkUrl[256];            /* ����ͼƬUrl*/
    char sLinkCamera[64];          /* ����ͼƬ��ص�*/
    char sLinkTriggerTime[65];           /* ����ͼƬ��ʼʱ��*/
    int nLinkPicRet;                           /* ������ͼƬ����*/
    tagHikAlarmSnapLinkInfo* pNext;
    tagHikAlarmSnapLinkInfo()
    {
        memset(sLinkCamera,0,sizeof(char)*64);
        memset(sLinkUrl,0,sizeof(char)*256);
        memset(sLinkTriggerTime,0,sizeof(char)*65);
        nLinkPicRet = 0;
        pNext = NULL;
    }
    tagHikAlarmSnapLinkInfo(const tagHikAlarmSnapLinkInfo& obj)
    {
        strncpy_s(sLinkUrl,_countof(sLinkUrl),obj.sLinkUrl,_TRUNCATE);
        strncpy_s(sLinkCamera,_countof(sLinkCamera),obj.sLinkCamera,_TRUNCATE);
        strncpy_s(sLinkTriggerTime,_countof(sLinkTriggerTime),obj.sLinkTriggerTime,_TRUNCATE);
        nLinkPicRet = obj.nLinkPicRet;
        pNext = NULL;
    }
}HikAlarmSnapLinkInfo;

//�澯ȷ����Ϣ �澯��ʷ��ʹ��
typedef struct tagHikAlarmConfrimInfo
{
    int nConfirmer;                                       //ȷ����
    char sConfirmerUser[130];	                  //ȷ�����û��� �� ���ڼ����澯ȷ����ʾȷ����
    char sConfirmTime[65];				          // ȷ��ʱ��
    char sConfirmDsc[1028];				              // ȷ������
    tagHikAlarmConfrimInfo()
    {
        nConfirmer = -1;
        memset(sConfirmTime,0,sizeof(char)*65);
        memset(sConfirmDsc,0,sizeof(char)*1028);
        memset(sConfirmerUser,0,sizeof(char)*130);
    }
    tagHikAlarmConfrimInfo(const tagHikAlarmConfrimInfo& obj)
    {
        strncpy_s(sConfirmTime,_countof(sConfirmTime),obj.sConfirmTime,_TRUNCATE);
        strncpy_s(sConfirmDsc,_countof(sConfirmDsc),obj.sConfirmDsc,_TRUNCATE);
        strncpy_s(sConfirmerUser,_countof(sConfirmerUser),obj.sConfirmerUser,_TRUNCATE);
        nConfirmer = obj.nConfirmer;
    }
}HikAlarmConfrimInfo;

//�澯Դ��Ϣ �澯��ʷ��ʹ��
typedef struct tagHikAlarmSrcObjInfo
{
    int  iObjType;                                                    //�����澯�Ķ�������
    char szObjName[128];                     //�����澯�Ķ�����
    char szObjIndex[64];					//�����澯�Ķ���index
    tagHikAlarmSrcObjInfo()
    {
        iObjType = -1;
        memset(szObjName,0,sizeof(char)*128);
        szObjIndex[0] = '\0';
    }
    tagHikAlarmSrcObjInfo(const tagHikAlarmSrcObjInfo& obj)
    {
        strncpy_s(szObjName,_countof(szObjName),obj.szObjName,_TRUNCATE);
        strncpy_s(szObjIndex,_countof(szObjIndex),obj.szObjIndex,_TRUNCATE);
        iObjType = obj.iObjType;
    }
}HikAlarmSrcObjInfo;

//�澯������Ϣ
typedef struct tagHikAlarmCfgInfo
{
    int   iAlarmType;                                                 //�澯�¼�����
    int   iAlarmEventlevel;                                        //�澯�ȼ�      
    char  szAlarmEventCfgID[128];      //����ID
    char  sAlarmEventname[1024];   //�澯�¼�����
    tagHikAlarmCfgInfo()
    {
        iAlarmType = -1;
        iAlarmEventlevel = -1;
        memset(sAlarmEventname,0,sizeof(char)*1024);
        memset(szAlarmEventCfgID,0,sizeof(char)*128);
    }
    tagHikAlarmCfgInfo(const tagHikAlarmCfgInfo& obj)
    {
        strncpy_s(sAlarmEventname,_countof(sAlarmEventname),obj.sAlarmEventname,_TRUNCATE);
        strncpy_s(szAlarmEventCfgID,_countof(szAlarmEventCfgID),obj.szAlarmEventCfgID,_TRUNCATE);
        iAlarmEventlevel = obj.iAlarmEventlevel;
        iAlarmType = obj.iAlarmType;
    }
}HikAlarmCfgInfo;

typedef struct tagHikAlarmTime
{
    char sBeginTime[65];                               //��ʼʱ��
    char sEndTime[65];                                  //����ʱ��
    tagHikAlarmTime()
    {
        memset(sBeginTime,0,sizeof(char)*65);
        memset(sEndTime,0,sizeof(char)*65);
    }
    tagHikAlarmTime(const tagHikAlarmTime& obj)
    {
        strncpy_s(sBeginTime,_countof(sBeginTime),obj.sBeginTime,_TRUNCATE);
        strncpy_s(sEndTime,_countof(sEndTime),obj.sEndTime,_TRUNCATE);
    }
}HikAlarmTime;

//��������Ϣ
typedef struct tagHikAlarmBlackListInfo
{
    int   iBlackListSex;
    int   iBlackListIdType;
    char  szBlackListName[1024];
    char  szBlackListBirth[1024];
    char  szBlackListId[128];
    char  szBlackSimiValue[128];
    tagHikAlarmBlackListInfo()
    {
        iBlackListSex = -1;
        iBlackListIdType = -1;
        memset(szBlackListName,0,sizeof(char)*1024);
        memset(szBlackListBirth,0,sizeof(char)*1024);
        memset(szBlackListId,0,sizeof(char)*128);
        memset(szBlackSimiValue,0,sizeof(char)*128);
    }
    tagHikAlarmBlackListInfo(const tagHikAlarmBlackListInfo& obj)
    {
        iBlackListSex = obj.iBlackListSex;
        iBlackListIdType = obj.iBlackListIdType;
        strncpy_s(szBlackListName,_countof(szBlackListName),obj.szBlackListName,_TRUNCATE);
        strncpy_s(szBlackListBirth,_countof(szBlackListBirth),obj.szBlackListBirth,_TRUNCATE);
        strncpy_s(szBlackListId,_countof(szBlackListId),obj.szBlackListId,_TRUNCATE);
        strncpy_s(szBlackSimiValue,_countof(szBlackSimiValue),obj.szBlackSimiValue,_TRUNCATE);
    }
}HikBlackListInfo;

//������־���صĽ����Ϣ
typedef struct tagHikSearchAlarmLogResult
{
    char sAlarmlogid[128];                      //�澯��־ID          
    int  iStatus;                                        //�澯״̬

    char sLogtxt[1024];					             //��־��Ϣ	
    char sLogRemark[512];                            //��־��ע 
    char sPicUrl[256];                               //ͼƬ��Ϣ

    bool isRecord;                                       //�Ƿ�¼��
    bool isConfrim;                                      //�Ƿ�ȷ��
    bool isPicture;                                      //�Ƿ�������ͼƬ
    //HikAlarmRecordLinkInfo* pRcInfo;                        //¼����Ϣ
    HikAlarmConfrimInfo        confriminfo;                 //ȷ����Ϣ
    HikAlarmSrcObjInfo          objinfo;                    //�澯Դ��Ϣ
    HikAlarmCfgInfo               cfginfo;                  //�澯������Ϣ
    HikAlarmTime                   timeinfo;                //�澯ʱ��
    //HikAlarmSnapLinkInfo* pSnapInfo;
    HikBlackListInfo      blackListInfo;                         //��������Ϣ

    //tagHikSearchAlarmLogResult* pNext;
    tagHikSearchAlarmLogResult()
    {
        sAlarmlogid[0] = '\0';
        iStatus = -1;
        sLogtxt[0] = '\0';
        sLogRemark[0] = '\0';
        sPicUrl[0] = '\0';
        isConfrim = false;
        isPicture = false;
        isRecord = false;
        //pRcInfo = NULL;
        //pSnapInfo = NULL;
        //pNext = NULL;
    }
    tagHikSearchAlarmLogResult(const tagHikSearchAlarmLogResult& obj):
    confriminfo(obj.confriminfo),
        objinfo(obj.objinfo),
        cfginfo(obj.cfginfo),
        timeinfo(obj.timeinfo),
        isConfrim(obj.isConfrim),
        isRecord(obj.isRecord),
        blackListInfo(obj.blackListInfo)
    {
        strncpy_s(sAlarmlogid,_countof(sAlarmlogid),obj.sAlarmlogid,_TRUNCATE);
        strncpy_s(sLogtxt,_countof(sLogtxt),obj.sLogtxt,_TRUNCATE);
        strncpy_s(sLogRemark,_countof(sLogRemark),obj.sLogRemark,_TRUNCATE);
        strncpy_s(sPicUrl,_countof(sPicUrl),obj.sPicUrl,_TRUNCATE);
        isConfrim = obj.isConfrim;
        isRecord = obj.isRecord;
        isPicture = obj.isPicture;
        iStatus = obj.iStatus;
        //pRcInfo = NULL;
        //copylist(obj.pRcInfo,&pRcInfo);
        //copylist(obj.pSnapInfo,&pSnapInfo);
        //pNext = NULL;
    }
}HIKSEARCHALARMLOGRESULT,*pHIKSEARCHALARMLOGRESULT;

#endif