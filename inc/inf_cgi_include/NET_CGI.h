#ifndef _NETCGI_INC_
#define _NETCGI_INC_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "curl.h"
#include "libxml/xmlmemory.h"
#include "libxml/parser.h"
#include "libiconv/iconv.h"

#include <string>
#include <vector>
using namespace std;

#define RET_SUCCESS 200
#define RET_ICHANNAL 401
#define RET_IPARAMVALUE 402
#define RET_IPARAMNAME 403
#define RET_NOTSUPPORT 501
#define RET_MODESUPPORT 502
#define RET_SERVERFAIL 503
#define RET_ERROR_FILE 601  /*���ļ�����*/
#define RET_ERROR_INIT 602  /*libcurl���ʼ������*/
//#define RET_CURL_FAIL 603   /*ʹ��libcurl��������*/
#define RET_ERROR_XML 604   /*����XML����*/

#define OSD_TEXT_COUNT 5

typedef struct
{
	char deviceID[32];
	char firmware[32];
	char serialNum[64];
	char mac[18];
}CGISystemInfo;
 
typedef struct
{
	char res[32];
	int bitRate;
	int videoQuality;
	int frameRate;
	int IPRate;
	int Payload;/*encode type 1:h265,0:h264*/
}CGIDevInfo;

typedef struct
{
	vector<string> vres;
	vector<int> bitRate;
	vector<int> videoQuality;
	vector<int> frameRate;
	vector<int> IPRate;
}CGIVideoQueryInfo;

typedef struct{
	int CameraTime;
	int tz;
	int EnDaylight;
	int timeMethod;
	char ntpIP[20];
}SetTimeInfo;

/*Justin add start 2014.1.8*/
typedef struct
{
	char codec[16];
	int sampleRate;
	int enable;
	int volume;
}CGI_AUDIO_INFO;

typedef struct
{
	vector<string> vcodec;
	vector<int> sampleRate;
	vector<int> bitRate;
	vector<int> track;
}CGIAudioQueryInfo;

typedef struct
{
	int ioNum;
	int ioLevel;
}CGI_ALARM_IO_INFO;

typedef struct 
{
	vector<int> ioNum;
	vector<int> ioLevel;
}CGIIOTrigQueryInfo;

#define AREA_NUM_MAX 	4
#define MD_SCOPE_AREA	18
typedef struct
{
	int areaNum;
	int mdEnable;
	int mdSensitivity;
	int mdX0;
	int mdY0;
	int mdX1;
	int mdY1;
}CGI_ALARM_MD_SET_INFO;

typedef struct
{
	unsigned  int area[MD_SCOPE_AREA];
	int mdEnable;
	int mdSensitivity;
}CGI_ALARM_MD_INFO;

typedef struct
{
	vector<int> mdNum;			
	vector<int> mdEnable;
	vector<int> mdSensitivity;
	vector<int> mdX0;
	vector<int> mdY0;
	vector<int> mdX1;
	vector<int> mdY1;
}CGIMDQueryInfo;

typedef struct
{
	int accessScope;
}CGI_ACCESS_SCOPE_INFO;

typedef struct
{
	vector<int> accessScope;
}CGIAccessScopeQueryInfo;

#define IO_ACCESS_NUM_MAX 		2

typedef struct
{
	int ioTrigNum;
	int ioAlarm1;
	int ioAlarm2;
	int ioMail;
	int ioFtp;
	int ioAudio;
}CGI_IO_ACCESS_SET_INFO;

typedef struct
{
	int ioInNum[IO_ACCESS_NUM_MAX];
	int ioAlarm1[IO_ACCESS_NUM_MAX];
	int ioAlarm2[IO_ACCESS_NUM_MAX];
	int ioMail[IO_ACCESS_NUM_MAX];
	int ioFtp[IO_ACCESS_NUM_MAX];
	int ioAudio[IO_ACCESS_NUM_MAX];
}CGI_IO_ACCESS_INFO;

typedef struct
{
	vector<int> ioInNum;
	vector<int> ioAlarm1;
	vector<int> ioAlarm2;
	vector<int> ioMail;
	vector<int> ioFtp;
	vector<int> ioAudio;
}CGIIOAccessQueryInfo;

typedef struct
{
	int mdArea;
	int mdAlarm1;
	int mdAlarm2;
	int mdMail;
	int mdFtp;
	int mdAudio;
}CGI_MD_ACCESS_SET_INFO;

typedef struct
{
	int mdArea[AREA_NUM_MAX];
	int mdAlarm1[AREA_NUM_MAX];
	int mdAlarm2[AREA_NUM_MAX];
	int mdMail[AREA_NUM_MAX];
	int mdFtp[AREA_NUM_MAX];
	int mdAudio[AREA_NUM_MAX];
	
}CGI_MD_ACCESS_INFO;

typedef struct
{
	vector<int> mdAreaNum;
	vector<int> mdAlarm1;
	vector<int> mdAlarm2;
	vector<int> mdMail;
	vector<int> mdFtp;
	vector<int> mdAudio;
}CGIMDAccessQueryInfo;

typedef struct
{
	int enable;
	int server_type;
	char user[32];
	char passwd[32];
	char domain_name[32];
	int server_port;
	char server_domain_name[32];
}CGI_NET_DDNS_INFO;

typedef struct
{
	char ip[16];
	char name[32];
	char passwd[32];
	char mailTo[32];
	char mailCo[32];
	char mailFrom[32];
	int 	  author;
}CGI_NET_SMTP_INFO;

typedef struct
{
	char ip[16];
	char name[32];
	char passwd[32];
}CGI_NET_FTP_INFO;

typedef struct
{
	char alarmServerIp[3][16];
}CGI_NET_ALARM_SERVER_INFO;

typedef struct
{
	int format;
	int hue;
	int brightness;
	int saturation;
	int contrast;
}CGI_IMAGE_INFO;

typedef struct
{
	vector<int> format;
	vector<int> hue;
	vector<int> brightness;
	vector<int> saturation;
	vector<int> contrast;
}CGIQueryImageInfo;

typedef struct
{
	char osdText[OSD_TEXT_COUNT][32];
	int textStatus[OSD_TEXT_COUNT];
	int textX[OSD_TEXT_COUNT];
	int textY[OSD_TEXT_COUNT];
	int textSize[OSD_TEXT_COUNT];
	int dateStatus;
	int dateFormat;
	int dateX;
	int dateY;
	int timeStatus;
	int timeX;
	int timeY;
	int timeSize;
	int multipleStatus;
	int multipleX;
	int multipleY;
	int multipleSize;
}CGI_OSD_INFO;

typedef struct
{
	vector<string> osdText;
	vector<int> textStatus;
	vector<int> textX;
	vector<int> textY;
	vector<int> dateStatus;
	vector<int> dateFormat;
	vector<int> dateX;
	vector<int> dateY;
	vector<int> timeStatus;
	vector<int> timeX;
	vector<int> timeY;
}CGIQueryOSDInfo;

typedef struct
{
	int exposureMode;
	int scenceSelect;
	int agcMax;
	int agcManual;
	int shutterMax;
	int shutterManual;
	int icrtSwitch;
	int icrtTimer;
	int blcSwitch;
	int blcLevel;
	int hlcSwitch;
	int elcLevel;
}CGICamExposureInfo;

typedef struct
{
	int mirrorHor;
	int mirrorVer;
}CGICamBasicInfo;

typedef struct
{
	vector<int> exposureMode;
	vector<int> scenceSelect;
	vector<int> agcMax;
	vector<int> agcManual;
	vector<int> shutterMax;
	vector<int> shutterManual;
	vector<int> icrtSwitch;
	vector<int> icrtTimer;
	vector<int> blcSwitch;
	vector<int> blcLevel;
	vector<int> hlcSwitch;
}CGICamExposureQueryInfo;

#define WIFI_SSID_LEN 32
#define WIFI_KEY_LEN 64 

typedef struct
{
    unsigned int enable;
	char ssid[WIFI_SSID_LEN+1];
	char password[WIFI_KEY_LEN+1];
	unsigned int autoMode;
}CGI_Wifi_Info;

/**
 * @brief - ��λ�豸
 * @param [IN]	IPStr		�豸IP ��ַ
 * @param [IN]	flag 		��λ�豸��־0~����1~�ָ���������
 * @param [IN]	iHttpPort	http�˿ں�
 * @param [IN] 	userStr	�û��� 
 * @param [IN] 	pwdStr      	����   
 * @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
 */
int NETCGI_SystemReset(const char*IPStr, int flag, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
 * @brief - ��ȡϵͳ��Ϣ
 * @param [OUT]	 cgiInfo 	ϵͳ��Ϣ
 * @param [IN]     IPStr	�豸IP ��ַ
 * @param [IN]	  iHttpPort  http �˿ں�
 * @param [IN] 	  userStr	 �û��� 
 * @param [IN]     pwdStr      ����   
 * @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
 */
int NETCGI_GetSystemInfo(CGISystemInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ѯͼƬ��Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_CamExposure_QueryInfo(const char*IPStr, vector<CGICamExposureQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ȡͼƬ��Ϣ
* @param[out] cgiInfo		ͼƬ��Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Camera_ExposureInfo(CGICamExposureInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����camera exposure ��Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		camera exposure ��Ϣ
* @param[in] nSelect[12]	1:����0:������
*						������: 0:�ع�ģʽ1:�ı�2:����ѡ��3:�������4:�ֶ�����5:������6:�ֶ�����7:�ʺ�ת��8:ת��ʱ��9:���ⲹ������10:���ⲹ���ȼ�11:ǿ�����ƿ���12:�عⲹ��
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Camera_ExposureInfo(const char*IPStr,  CGICamExposureInfo cgiInfo, int nSelect[12], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡͼƬˮƽ��ֱ�Ȼ�����Ϣ
* @param[out] cgiInfo		ͼƬ��Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Camera_BasicInfo(CGICamBasicInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����ͼƬˮƽ��ֱ�Ȼ�����Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		camera basic ��Ϣ
* @param[in] nSelect[2]	1:����0:������
*						������: 0:ˮƽ����1:��ֱ����
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Camera_BasicInfo(const char*IPStr,  CGICamBasicInfo cgiInfo, int nSelect[2], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ѯͼƬ��Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Image_QueryInfo(const char*IPStr, vector<CGIQueryImageInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ȡͼƬ��Ϣ
* @param[out] cgiInfo		ͼƬ��Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_ImageInfo(CGI_IMAGE_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����ͼƬ��Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		ͼƬ��Ϣ
* @param[in] nSelect[2]	1:����0:������
*						������: 0:��Ƶ��ʽ1:�Ҷ�2:����3:���Ͷ�4:�Աȶ�
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_ImageInfo(const char*IPStr,  CGI_IMAGE_INFO cgiInfo, int nSelect[5], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ѯOSD ��Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_OSD_QueryInfo(const char*IPStr, vector<CGIQueryOSDInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ȡOSD ��Ϣ
* @param[out] cgiInfo		OSD ������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_OSDInfo(CGI_OSD_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����OSD ��Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		OSD ��Ϣ
* @param[in] nSelect[2]	1:����0:������
*						������: 0:�ı�ʹ��1:�ı�2:�ı�������3:�ı�������4:���ڿ���5:���ڸ�ʽ6:���ں�����7:����������8:ʱ�俪��9:ʱ�������10:ʱ��������
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_OSDInfo(const char*IPStr,  CGI_OSD_INFO cgiInfo, int nSelect[5*OSD_TEXT_COUNT+12], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡϵͳʱ����Ϣ
* @param[out] cgiInfo		ϵͳʱ����Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_TimeInfo(SetTimeInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - ��ѯIO ״̬��Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Alarm_IOTrig_QueryInfo(const char*IPStr,  vector<CGIIOTrigQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - ��ȡIO ״̬��Ϣ
* @param[out] cgiInfo		IO ״̬
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Alarm_IOTrigInfo(CGI_ALARM_IO_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -����IO ״̬��Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		IO ״̬��Ϣ
* @param[in] nSelect[2]	1:����0:������
*						������: 0:IO ��1:IO ����״̬���ӵػ�·
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Alarm_IOTrigInfo(const char*IPStr,  CGI_ALARM_IO_INFO cgiInfo, int nSelect[2], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - ��ѯ�ƶ����������Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Alarm_MD_QueryInfo(const char*IPStr,  vector<CGIMDQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - ��ȡ�ƶ����������Ϣ
* @param[out] cgiInfo		������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Alarm_MDInfo(CGI_ALARM_MD_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -�����ƶ����������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		�ƶ����������Ϣ
* @param[in] nSelect[7]	1:����0:������
*						������: 0:�����1:ʹ��2:������3:X0 4:Y0 5:X1 6:Y1
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Alarm_MDInfo(const char*IPStr,  CGI_ALARM_MD_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - ��ѯ����������Ϣ
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Alarm_AccessScope_QueryInfo(const char*IPStr,  vector<CGIAccessScopeQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - ��ȡ����������Ϣ
* @param[out] cgiInfo		����������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Alarm_AccessScopeInfo(CGI_ACCESS_SCOPE_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -���ñ�������
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		����������Ϣ
* @param[in] nSelect[1]	1:����0:������
*						������: 0:���ع������������
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Alarm_AccessScopeInfo(const char*IPStr,  CGI_ACCESS_SCOPE_INFO cgiInfo, int nSelect[1], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - ��ѯIO ����������Ϣ
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Alarm_IOAccess_QueryInfo(const char*IPStr,  vector<CGIIOAccessQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ȡIO ����������Ϣ
* @param[out] cgiInfo		IO ����������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Alarm_IOAccessInfo(CGI_IO_ACCESS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -����IO ����������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		IO ����������Ϣ
* @param[in] nSelect[6]	1:����0:������
*						������: 0:IO �� 1:IO ���1 2:IO ���2 3:smtp 4:ftp 5:��Ƶ���
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Alarm_IOAccessInfo(const char*IPStr,  CGI_IO_ACCESS_SET_INFO cgiInfo, int nSelect[6], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ѯ�ƶ���ⱨ��������Ϣ����
* @param [IN]  IPStr       	�豸IP��ַ
* @param [OUT]retVector   	�������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      	����   
* @param [IN] userStr	  	�û��� 
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Alarm_MDAccess_QueryInfo(const char*IPStr,  vector<CGIMDAccessQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - ��ȡ�ƶ���ⱨ��������Ϣ
* @param[out] cgiInfo		�ƶ���ⱨ��������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Alarm_MDAccessInfo(CGI_MD_ACCESS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -�����ƶ���ⱨ��������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		�ƶ���ⱨ��������Ϣ
* @param[in] nSelect[6]	1:����0:������
*						������: 0:�ƶ�������� 1:IO ���1 2:IO ���2 3:smtp 4:ftp 5:��Ƶ���
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Alarm_MDAccessInfo(const char*IPStr,  CGI_MD_ACCESS_SET_INFO cgiInfo, int nSelect[6], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡddns ��������Ϣ
* @param[out] cgiInfo		ddns ��������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Net_DDNSInfo(CGI_NET_DDNS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����ddns ��������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		ddns ��������Ϣ
* @param[in] nSelect[7]	1:����0:������
*						������: 0:ʹ�ܿ���1:����������2:��������ַ3:�������˿�4:�û���5:����6:����
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Net_DDNSInfo(const char*IPStr,  CGI_NET_DDNS_INFO cgiInfo, int nSelect[7], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡsmtp ��������Ϣ
* @param[out] cgiInfo		smtp ��������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Net_SmtpInfo(CGI_NET_SMTP_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����smtp ��������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		smtp ��������Ϣ
* @param[in] nSelect[7]	1:����0:������
*						������: 0:������ip 1:�������û���2:����������3:��֤ʹ��4:Ŀ�ĵ�ַ5:���͵�ַ6:Դ��ַ
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Net_SmtpInfo(const char*IPStr,  CGI_NET_SMTP_INFO cgiInfo, int nSelect[7], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡftp ��������Ϣ
* @param[out] cgiInfo		ftp ��������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_Net_FtpInfo(CGI_NET_FTP_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����ftp ��������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		ftp ��������Ϣ
* @param[in] nSelect[3]	1:����0:������
*						������: 0:������ip 1:�������û���2:����������
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Net_FtpInfo(const char*IPStr,  CGI_NET_FTP_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - ��ȡ���� ��������Ϣ
* @param[out] cgiInfo		���� ��������Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/

int NETCGI_Get_Net_AlarmServerInfo(CGI_NET_ALARM_SERVER_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -���ñ��� ��������Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		���� ��������Ϣ
* @param[in] nSelect[1]	1:����0:������
*						������: 0:������ip 
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_Net_AlarmServerInfo(const char*IPStr, CGI_NET_ALARM_SERVER_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);



/**
* @brief - ��ȡ��Ƶ��Ϣ����
* @param[out] cgiInfo 		��Ƶ��Ϣ 
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_AudioInfo(CGI_AUDIO_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -������Ƶ��Ϣ����
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		��Ƶ��Ϣ
* @param[in] nSelect[4]	1:����0:������
*						������: 0:��������1:������2:��������3:������С����������ʱ������
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_AudioInfo(const char*IPStr,  CGI_AUDIO_INFO cgiInfo, int nSelect[4], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/*Justin add end 2014.1.8*/

/**
*��ȡ������Ϣ����
* @param [OUT] CGIDevInfo ������Ϣ
* @param [IN] IPStr       �豸IP��ַ
* @param [IN] choice      ��������ѡ��. 1:�� 0:��
* @param [IN] userStr	  �û��� 
* @param [IN] pwdStr      ����   
* @param [IN] channel     ͨ����
* @return �������½����
* - �ɹ���RET_SUCCEED
* - ʧ�ܣ��ο�������Ķ���
*/
int NETCGI_GetStreamInfo(CGIDevInfo& cgiInfo, const char* IPStr, int choice, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);
/**
*����������Ϣ����
* @param [IN] IPStr       �豸IP��ַ
* @param [IN] choice      ��������ѡ��. 1:�� 0:��
* @param [IN] CGIDevInfo  ������Ϣ
* @param [IN] nSelect[4]  1������ 0��������
*						  �����ţ�0:�ֱ��� 1������ 2��֡�� 3��IP��4:��Ƶ����
* @param [IN] userStr	  �û��� 
* @param [IN] pwdStr      ����  
* @param [IN] channel     ͨ����
* @return �������½����
* - �ɹ���RET_SUCCEED
* - ʧ�ܣ��ο�������Ķ���
*/
int NETCGI_SetStreamInfo(const char*IPStr, int choice, CGIDevInfo cgiInfo, int nSelect[6], int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
*ǿ��I֡����
* @param [IN] IPStr       �豸IP��ַ
* @param [IN] choice      ��������ѡ��. 1:�� 0:��
* @param [IN] userStr	  �û��� 
* @param [IN] pwdStr      ����  
* @param [IN] channel     ͨ����
* @return �������½����
* - �ɹ���RET_SUCCEED
* - ʧ�ܣ��ο�������Ķ���
*/
int NETCGI_ForceIframe(const char*IPStr, int choice, int iHttpPort, const char*userStr, const char*pwdStr, int channel);

/**
*��ȡץ��ͼ��ӿ�
* @param [IN] IPStr       �豸IP��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  �û��� 
* @param [IN] pwdStr      ����  
* @param [IN] buf     ͼƬ������ָ��
* @param [IN] buflen     ͼƬ��������С����buflen��ʵ�ʳ���С���򷵻�ʧ��
* @return �������½����
* - �ɹ���ͼƬʵ�ʳ���
* - ʧ�ܣ�-1
*/
int NETCGI_GetSnapShot(const char* IPStr, int iHttpPort, const char*userStr, const char*pwdStr,char *buf,int buflen);

/**
*��ѯ����
* @param [IN] IPStr       �豸IP��ַ
* @param [IN] choice      ��������ѡ��. 1:�� 0:��
* @param [OUT]retVector   �������صĲ�ѯ��Ϣ
* @param [IN] pwdStr      ����   
* @param [IN] userStr	  �û��� 
* @param [IN] channel     ͨ����
* @return �������½����
* - �ɹ���RET_SUCCEED
* - ʧ�ܣ��ο�������Ķ���
*/
int NETCGI_Video_QueryInfo(const char*IPStr, int choice, vector<CGIVideoQueryInfo>& retVector, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
*����ʱ����Ϣ����
* @param [IN] IPStr       �豸IP��ַ
* @param [IN] timeMethod  0:��PCͬ�� 1:��NTP������ͬ��
* @param [IN] nSelect[4]  1������ 0��������
*						  �����ţ�0:ʱ�� 1��ʱ�� 2��dayligntʹ�� 3��NTP������IP��ַ
* @param [IN] timeInfo  ʱ����Ϣ
* @param [IN] userStr	  �û��� 
* @param [IN] pwdStr      ���� 
* @return �������½����
* - �ɹ���RET_SUCCEED
* - ʧ�ܣ��ο�������Ķ���
*/
int NETCGI_SetTimeInfo(const char*IPStr, int timeMethod, int nSelect[4], SetTimeInfo timeInfo, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - ��ȡwifi��Ϣ
* @param[out] cgiInfo		wifi��Ϣ
* @param[in]   IPStr		�豸IP ��ַ
* @param[in]   iHttpPort 	http �˿�
* @param [IN] userStr	  	�û��� 
* @param [IN] pwdStr      	����   
* @param [IN] channel     	ͨ����
* @return ����ֵ     	�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Get_WifiInfo(CGI_Wifi_Info& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -����wifi ��Ϣ
* @param[in] IPStr 		�豸IP ��ַ
* @param[in] cgiInfo 		wifi��Ϣ
* @param[in] nSelect[4]	1:����0:������
*						������: 0:wifi ʹ�ܿ���1:wifi ssid 2:wifi ����3:�Զ�������Ƶ����
* @param[in] iHttpPort 		http �˿ں�
* @param[in] userStr 		�û���
* @param[in] pwdStr 		�� 	    ��
* @param[in] channel 		ͨ����
* @return ����ֵ 		�ɹ�:200 ����:�ο�������Ķ���
*/
int NETCGI_Set_WifiInfo(const char*IPStr,  CGI_Wifi_Info cgiInfo, int nSelect[4], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


#endif //_NETCGI_INC_
