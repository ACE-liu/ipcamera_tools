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
#define RET_ERROR_FILE 601  /*打开文件错误*/
#define RET_ERROR_INIT 602  /*libcurl库初始化错误*/
//#define RET_CURL_FAIL 603   /*使用libcurl函数错误*/
#define RET_ERROR_XML 604   /*解析XML错误*/

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
 * @brief - 复位设备
 * @param [IN]	IPStr		设备IP 地址
 * @param [IN]	flag 		复位设备标志0~重启1~恢复出厂设置
 * @param [IN]	iHttpPort	http端口号
 * @param [IN] 	userStr	用户名 
 * @param [IN] 	pwdStr      	密码   
 * @return 返回值     	成功:200 错误:参考错误码的定义
 */
int NETCGI_SystemReset(const char*IPStr, int flag, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
 * @brief - 获取系统信息
 * @param [OUT]	 cgiInfo 	系统信息
 * @param [IN]     IPStr	设备IP 地址
 * @param [IN]	  iHttpPort  http 端口号
 * @param [IN] 	  userStr	 用户名 
 * @param [IN]     pwdStr      密码   
 * @return 返回值     	成功:200 错误:参考错误码的定义
 */
int NETCGI_GetSystemInfo(CGISystemInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 查询图片信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_CamExposure_QueryInfo(const char*IPStr, vector<CGICamExposureQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 获取图片信息
* @param[out] cgiInfo		图片信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Camera_ExposureInfo(CGICamExposureInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置camera exposure 信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		camera exposure 信息
* @param[in] nSelect[12]	1:设置0:不设置
*						数组标号: 0:曝光模式1:文本2:场景选择3:最大增益4:手动增益5:最大快门6:手动快门7:彩黑转换8:转换时间9:背光补偿开关10:背光补偿等级11:强光抑制开关12:曝光补偿
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Camera_ExposureInfo(const char*IPStr,  CGICamExposureInfo cgiInfo, int nSelect[12], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取图片水平垂直等基本信息
* @param[out] cgiInfo		图片信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Camera_BasicInfo(CGICamBasicInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置图片水平垂直等基本信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		camera basic 信息
* @param[in] nSelect[2]	1:设置0:不设置
*						数组标号: 0:水平镜像1:垂直镜像
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Camera_BasicInfo(const char*IPStr,  CGICamBasicInfo cgiInfo, int nSelect[2], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 查询图片信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Image_QueryInfo(const char*IPStr, vector<CGIQueryImageInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 获取图片信息
* @param[out] cgiInfo		图片信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_ImageInfo(CGI_IMAGE_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置图片信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		图片信息
* @param[in] nSelect[2]	1:设置0:不设置
*						数组标号: 0:视频制式1:灰度2:亮度3:饱和度4:对比度
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_ImageInfo(const char*IPStr,  CGI_IMAGE_INFO cgiInfo, int nSelect[5], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 查询OSD 信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_OSD_QueryInfo(const char*IPStr, vector<CGIQueryOSDInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 获取OSD 信息
* @param[out] cgiInfo		OSD 参数信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_OSDInfo(CGI_OSD_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置OSD 信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		OSD 信息
* @param[in] nSelect[2]	1:设置0:不设置
*						数组标号: 0:文本使能1:文本2:文本横坐标3:文本纵坐标4:日期开关5:日期格式6:日期横坐标7:日期纵坐标8:时间开关9:时间横坐标10:时间纵坐标
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_OSDInfo(const char*IPStr,  CGI_OSD_INFO cgiInfo, int nSelect[5*OSD_TEXT_COUNT+12], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取系统时间信息
* @param[out] cgiInfo		系统时间信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_TimeInfo(SetTimeInfo& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - 查询IO 状态信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Alarm_IOTrig_QueryInfo(const char*IPStr,  vector<CGIIOTrigQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - 获取IO 状态信息
* @param[out] cgiInfo		IO 状态
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Alarm_IOTrigInfo(CGI_ALARM_IO_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -设置IO 状态信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		IO 状态信息
* @param[in] nSelect[2]	1:设置0:不设置
*						数组标号: 0:IO 口1:IO 输入状态，接地或开路
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Alarm_IOTrigInfo(const char*IPStr,  CGI_ALARM_IO_INFO cgiInfo, int nSelect[2], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - 查询移动侦测区域信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Alarm_MD_QueryInfo(const char*IPStr,  vector<CGIMDQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - 获取移动侦测区域信息
* @param[out] cgiInfo		区域信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Alarm_MDInfo(CGI_ALARM_MD_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -设置移动侦测区域信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		移动侦测区域信息
* @param[in] nSelect[7]	1:设置0:不设置
*						数组标号: 0:区域号1:使能2:灵敏度3:X0 4:Y0 5:X1 6:Y1
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Alarm_MDInfo(const char*IPStr,  CGI_ALARM_MD_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - 查询报警关联信息
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Alarm_AccessScope_QueryInfo(const char*IPStr,  vector<CGIAccessScopeQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - 获取报警关联信息
* @param[out] cgiInfo		报警关联信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Alarm_AccessScopeInfo(CGI_ACCESS_SCOPE_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -设置报警关联
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		报警关联信息
* @param[in] nSelect[1]	1:设置0:不设置
*						数组标号: 0:本地关联或网络关联
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Alarm_AccessScopeInfo(const char*IPStr,  CGI_ACCESS_SCOPE_INFO cgiInfo, int nSelect[1], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief - 查询IO 报警关联信息
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Alarm_IOAccess_QueryInfo(const char*IPStr,  vector<CGIIOAccessQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 获取IO 报警关联信息
* @param[out] cgiInfo		IO 报警关联信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Alarm_IOAccessInfo(CGI_IO_ACCESS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -设置IO 报警关联信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		IO 报警关联信息
* @param[in] nSelect[6]	1:设置0:不设置
*						数组标号: 0:IO 口 1:IO 输出1 2:IO 输出2 3:smtp 4:ftp 5:音频输出
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Alarm_IOAccessInfo(const char*IPStr,  CGI_IO_ACCESS_SET_INFO cgiInfo, int nSelect[6], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 查询移动侦测报警关联信息函数
* @param [IN]  IPStr       	设备IP地址
* @param [OUT]retVector   	函数返回的查询信息
* @param [IN] pwdStr      	密码   
* @param [IN] userStr	  	用户名 
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Alarm_MDAccess_QueryInfo(const char*IPStr,  vector<CGIMDAccessQueryInfo>& retVector, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL);


/**
* @brief - 获取移动侦测报警关联信息
* @param[out] cgiInfo		移动侦测报警关联信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Alarm_MDAccessInfo(CGI_MD_ACCESS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/**
* @brief -设置移动侦测报警关联信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		移动侦测报警关联信息
* @param[in] nSelect[6]	1:设置0:不设置
*						数组标号: 0:移动侦测区域 1:IO 输出1 2:IO 输出2 3:smtp 4:ftp 5:音频输出
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Alarm_MDAccessInfo(const char*IPStr,  CGI_MD_ACCESS_SET_INFO cgiInfo, int nSelect[6], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取ddns 服务器信息
* @param[out] cgiInfo		ddns 服务器信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Net_DDNSInfo(CGI_NET_DDNS_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置ddns 服务器信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		ddns 服务器信息
* @param[in] nSelect[7]	1:设置0:不设置
*						数组标号: 0:使能开关1:服务器类型2:服务器地址3:服务器端口4:用户名5:密码6:域名
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Net_DDNSInfo(const char*IPStr,  CGI_NET_DDNS_INFO cgiInfo, int nSelect[7], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取smtp 服务器信息
* @param[out] cgiInfo		smtp 服务器信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Net_SmtpInfo(CGI_NET_SMTP_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置smtp 服务器信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		smtp 服务器信息
* @param[in] nSelect[7]	1:设置0:不设置
*						数组标号: 0:服务器ip 1:服务器用户名2:服务器密码3:认证使能4:目的地址5:抄送地址6:源地址
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Net_SmtpInfo(const char*IPStr,  CGI_NET_SMTP_INFO cgiInfo, int nSelect[7], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取ftp 服务器信息
* @param[out] cgiInfo		ftp 服务器信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_Net_FtpInfo(CGI_NET_FTP_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置ftp 服务器信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		ftp 服务器信息
* @param[in] nSelect[3]	1:设置0:不设置
*						数组标号: 0:服务器ip 1:服务器用户名2:服务器密码
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Net_FtpInfo(const char*IPStr,  CGI_NET_FTP_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief - 获取报警 服务器信息
* @param[out] cgiInfo		报警 服务器信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/

int NETCGI_Get_Net_AlarmServerInfo(CGI_NET_ALARM_SERVER_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置报警 服务器信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		报警 服务器信息
* @param[in] nSelect[1]	1:设置0:不设置
*						数组标号: 0:服务器ip 
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_Net_AlarmServerInfo(const char*IPStr, CGI_NET_ALARM_SERVER_INFO cgiInfo, int nSelect[3], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);



/**
* @brief - 获取音频信息参数
* @param[out] cgiInfo 		音频信息 
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_AudioInfo(CGI_AUDIO_INFO& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置音频信息函数
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		音频信息
* @param[in] nSelect[4]	1:设置0:不设置
*						数组标号: 0:编码类型1:采样率2:声音开关3:音量大小，采样率暂时不可设
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_AudioInfo(const char*IPStr,  CGI_AUDIO_INFO cgiInfo, int nSelect[4], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


/*Justin add end 2014.1.8*/

/**
*获取码流信息函数
* @param [OUT] CGIDevInfo 码流信息
* @param [IN] IPStr       设备IP地址
* @param [IN] choice      主副码流选择. 1:主 0:副
* @param [IN] userStr	  用户名 
* @param [IN] pwdStr      密码   
* @param [IN] channel     通道号
* @return 返回如下结果：
* - 成功：RET_SUCCEED
* - 失败：参看错误码的定义
*/
int NETCGI_GetStreamInfo(CGIDevInfo& cgiInfo, const char* IPStr, int choice, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);
/**
*设置码流信息函数
* @param [IN] IPStr       设备IP地址
* @param [IN] choice      主副码流选择. 1:主 0:副
* @param [IN] CGIDevInfo  码流信息
* @param [IN] nSelect[4]  1：设置 0：不设置
*						  数组标号：0:分辨率 1：码率 2：帧率 3：IP率4:视频质量
* @param [IN] userStr	  用户名 
* @param [IN] pwdStr      密码  
* @param [IN] channel     通道号
* @return 返回如下结果：
* - 成功：RET_SUCCEED
* - 失败：参看错误码的定义
*/
int NETCGI_SetStreamInfo(const char*IPStr, int choice, CGIDevInfo cgiInfo, int nSelect[6], int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
*强制I帧函数
* @param [IN] IPStr       设备IP地址
* @param [IN] choice      主副码流选择. 1:主 0:副
* @param [IN] userStr	  用户名 
* @param [IN] pwdStr      密码  
* @param [IN] channel     通道号
* @return 返回如下结果：
* - 成功：RET_SUCCEED
* - 失败：参看错误码的定义
*/
int NETCGI_ForceIframe(const char*IPStr, int choice, int iHttpPort, const char*userStr, const char*pwdStr, int channel);

/**
*获取抓拍图像接口
* @param [IN] IPStr       设备IP地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  用户名 
* @param [IN] pwdStr      密码  
* @param [IN] buf     图片缓存区指针
* @param [IN] buflen     图片缓存区大小，若buflen比实际长度小，则返回失败
* @return 返回如下结果：
* - 成功：图片实际长度
* - 失败：-1
*/
int NETCGI_GetSnapShot(const char* IPStr, int iHttpPort, const char*userStr, const char*pwdStr,char *buf,int buflen);

/**
*查询函数
* @param [IN] IPStr       设备IP地址
* @param [IN] choice      主副码流选择. 1:主 0:副
* @param [OUT]retVector   函数返回的查询信息
* @param [IN] pwdStr      密码   
* @param [IN] userStr	  用户名 
* @param [IN] channel     通道号
* @return 返回如下结果：
* - 成功：RET_SUCCEED
* - 失败：参看错误码的定义
*/
int NETCGI_Video_QueryInfo(const char*IPStr, int choice, vector<CGIVideoQueryInfo>& retVector, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
*设置时间信息函数
* @param [IN] IPStr       设备IP地址
* @param [IN] timeMethod  0:与PC同步 1:与NTP服务器同步
* @param [IN] nSelect[4]  1：设置 0：不设置
*						  数组标号：0:时间 1：时区 2：daylignt使能 3：NTP服务器IP地址
* @param [IN] timeInfo  时间信息
* @param [IN] userStr	  用户名 
* @param [IN] pwdStr      密码 
* @return 返回如下结果：
* - 成功：RET_SUCCEED
* - 失败：参看错误码的定义
*/
int NETCGI_SetTimeInfo(const char*IPStr, int timeMethod, int nSelect[4], SetTimeInfo timeInfo, int iHttpPort = 0, const char*userStr=NULL, const char*pwdStr=NULL);

/**
* @brief - 获取wifi信息
* @param[out] cgiInfo		wifi信息
* @param[in]   IPStr		设备IP 地址
* @param[in]   iHttpPort 	http 端口
* @param [IN] userStr	  	用户名 
* @param [IN] pwdStr      	密码   
* @param [IN] channel     	通道号
* @return 返回值     	成功:200 错误:参考错误码的定义
*/
int NETCGI_Get_WifiInfo(CGI_Wifi_Info& cgiInfo, const char* IPStr, int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);

/**
* @brief -设置wifi 信息
* @param[in] IPStr 		设备IP 地址
* @param[in] cgiInfo 		wifi信息
* @param[in] nSelect[4]	1:设置0:不设置
*						数组标号: 0:wifi 使能开关1:wifi ssid 2:wifi 密码3:自动调整视频质量
* @param[in] iHttpPort 		http 端口号
* @param[in] userStr 		用户名
* @param[in] pwdStr 		密 	    码
* @param[in] channel 		通道号
* @return 返回值 		成功:200 错误:参考错误码的定义
*/
int NETCGI_Set_WifiInfo(const char*IPStr,  CGI_Wifi_Info cgiInfo, int nSelect[4], int iHttpPort=0, const char*userStr=NULL, const char*pwdStr=NULL, int channel=1);


#endif //_NETCGI_INC_
