#ifndef _INFI_STREAM_PROTOCOL_H_
#define _INFI_STREAM_PROTOCOL_H_

//#include "IPCNetSDK.h"
///////////////////////////////////////////////////////////////////////////////

#define INFI_STREAM_PORT			90


//命令类型
#define CMD_REQ_LOGON				1			//请求登录
#define CMD_BACK_LOGON				2			//应答登录
#define CMD_REQ_AV					3			//请求音视频
#define CMD_BACK_AUDIO				4			//应答音视
#define CMD_BACK_VIDEO				6			//应答视频
#define CMD_REQ_SEND_AV				7			//请求发送音频
#define CMD_BACK_SEND_AUDIO			8			//应答发送音频

#define CMD_REQ_GET_PARA			11			//请求获取参数
#define CMD_BACK_GET_PARA			12			//应答获取参数
#define CMD_REQ_SET_PARA			13			//请求设置参数
#define CMD_BACK_SET_PARA			14			//应答设置参数
#define CMD_REQ_PTZ					15			//请求PTZ命令
#define CMD_BACK_PTZ					16			//应答PTZ命令
#define CMD_REQ_UPGRADE				17			//请求设备升级
#define CMD_BACK_UPGRADE				18			//应答设备升级
#define CMD_REQ_VIDEO_SHIFT			19			//请求视频切换
#define CMD_BACK_VIDEO_SHIFT			20			//应答视频切换
#define CMD_REQ_3D					49

#define CMD_REQ_MDSET				55
#define CMD_BACK_MDSET				56
#define CMD_REQ_MDGET				57
#define CMD_BACK_MDGET				58

//PTZ
#define	 PTZ_PORT_ASIC		8000
#define	 PTZ_PORT_DSP		7000
#define	 PTZ_PORT_POWERPC	90

#define NAME_LEN 32

typedef struct tagLOGON_REQ_INFO
{
	unsigned char  szUserName[NAME_LEN];
	unsigned char  szPassword[NAME_LEN];
}LOGON_REQ_INFO,*LPLOGON_REQ_INFO;

typedef struct tagLOGON_INFO
{
	unsigned int   dwUserID;
	unsigned short sErrorCode;
	unsigned short sExtLength;
}LOGON_INFO,*LPLOGON_INFO;

///////////////////////////////////////////////////////////////////////////////
//音视频流协议结构体

typedef struct tagCMD_HEADER
{
	unsigned char	cStartCode[3];				//'I','N','F'
	unsigned char	cCmdType;					//命令类型
	unsigned short	sPacketSN;					//包序号，从1开始
	unsigned short	sPacketNum;					//总包数，最小为1
	unsigned int   dwDataLength;				//包头后的数据长度
}CMD_HEADER,*LPCMD_HEADER;

typedef struct tagLOGON_ACK_INFO
{
	unsigned long	dwUserID;					//用户ID
	unsigned short	sErrorCode;					//错误码
	unsigned short	sExtLength;					//扩展长度
}LOGON_ACK_INFO,*LPLOGON_ACK_INFO;

typedef struct tagAV_REQ_INFO
{
	unsigned char	cVersion;					//版本
	unsigned char	cAVType;					//音视频类型
	unsigned char	cEncoderType;				//编码类型
	unsigned char	cReserved;					//保留
	unsigned char	cIP[16];					//设备IP
	unsigned short	sChannel;					//通道
	unsigned short	sExtLength;					//扩展长度
}AV_REQ_INFO,*LPAV_REQ_INFO;

typedef struct tagAV_VIDEO_INFO
{
	unsigned char	cFrameType;					//帧类型
	unsigned char	cAVType;					//音视频类型
	unsigned char	cEncoderType;				//编码类型
	unsigned char	cFrameRate;					//帧率
	unsigned short	sVideoWidth;				//视频宽度
	unsigned short	sVideoHeight;				//视频高度
	unsigned long	dwFrameID;					//帧ID
	unsigned long   dwFrameSize;				//帧大小
	unsigned long   dwTimeStamp;				//时间戳
	unsigned short	sErrorCode;					//错误号
	unsigned short	sExtLength;					//扩展长度	
}AV_VIDEO_INFO,*LPAV_VIDEO_INFO;

typedef struct tagAV_AUDIO_INFO
{
	unsigned char	cFrameType;					//帧类型
	unsigned char	cAVType;					//音视频类型
	unsigned char	cEncoderType;				//编码类型
	unsigned char	cChannels;					//通道类型
	unsigned short	sSamples;					//采样率
	unsigned short	sBitCount;					//采样位数
	unsigned long	dwwFrameID;					//帧ID
	unsigned long   dwFrameSize;				//帧大小
	unsigned long   dwTimeStamp;				//时间戳
	unsigned short	sErrorCode;					//错误号
	unsigned short	sExtLength;					//扩展长度	
}AV_AUDIO_INFO,*LPAV_AUDIO_INFO;

typedef struct tagPTZ_SEND_INFO
{
	unsigned char  cCommand;		//控制命令
	unsigned char  cPanSpeed;		//Pan控制速度
	unsigned char  cTiltSpeed;     //Tilt控制速度
	unsigned char  cReserved[1];   //预留
	unsigned short sChannel;       //通道
	unsigned short sExtLength;		//扩展长度
}PTZ_SEND_INFO, *LPPTZ_SEND_INFO;

typedef struct tag3D_SEND_INFO
{
	unsigned char m_Command;  		/**< 控制命令*/
	unsigned char m_ActionType;		/**< 动作类型*/
	unsigned int 	m_SrcHeight;			/**< 屏幕高度*/
	unsigned int	m_SrcWidth;			/**< 屏幕宽度*/
	unsigned int 	m_SelHeight;			/**< 框选高度*/
	unsigned int 	m_SelWidth;			/**< 框选宽度*/
	unsigned int 	m_MidPointY;		/**< 框选中点或点击位置*/
	unsigned int 	m_MidPointX;		/**< 框选中点或点击位置*/
	unsigned int 	m_Reserved;			/**< 预留*/
	unsigned int	m_ExtLength;		/**< 扩展长度*/
	unsigned char m_Channel;			/**< 通道*/
}tag3D_SEND_INFO, *LPPTZ_3D_SEND_INFO;

typedef struct tagPTZ_REPLY_INFO
{
	unsigned short m_ErrorCode;		//错误号
	unsigned short m_ExtLength;		//扩展长度
}PTZ_REPLY_INFO, *LPPTZ_REPLY_INFO;

typedef struct tagVIDEO_SHIFT_REQ_INFO
{
	unsigned char	cVersion;					//版本
	unsigned char	cDecoderChan;				//解码通道
	unsigned char	cResolution;				//分辨率
	unsigned char	cDisplayOsd;				//OSD显示
	char			szOsdCamNum[16];			//CAM号		
	char			szOsdStatus[16];			//状态
	unsigned char	cEncoderIP[16];				//编码IP
	unsigned char	cEncoderChan;				//编码通道
	unsigned char	cReserved;					//保留
	short			sExtLength;					//扩展长度
}VIDEO_SHIFT_REQ_INFO, *LPVIDEO_SHIFT_REQ_INFO;

typedef struct tagVIDEO_SHIFT_ACK_INFO
{
	short			sErrorCode;					//错误码
	short			sExtLength;					//扩展长度
}VIDEO_SHIFT_ACK_INFO, *LPVIDEO_SHIFT_ACK_INFO;

/*justin add 2014.1.13*/
typedef struct taySerial_ENABLE
{
	unsigned char chn;			//chnanel : default 1
	unsigned char enable;		//default 1 enable , 0 disable
}SERIAL_ENABLE;

typedef struct tagSerial_CONNECT
{
	unsigned char chn;			//chnanel : default 1
	unsigned char exclusive;	//exclusive other users' operation : default 1 yes, 0 no
	unsigned char read;			//request read from serial : default 1 request, 0 not request
	unsigned char write;		//request write to serial : default 1 request, 0 not request
	int sockfd;		//local client socket fd
}SERIAL_CONNECT;

typedef struct tagSerial_SETTINGS
{
	unsigned char chn;			//enable : default 1 enable transparant , default 0 disable transparant
	unsigned char bits;			//data bits : default 8
	unsigned char stopbit;		//stop bit : default 1
	unsigned char parity;	 	//parity check : default 'N' no parity check, 'E' even parity check, 'O' odd parity check
	unsigned int baudrate;	//baudrate : default 2400*/
}SERIAL_SETTINGS;

typedef struct tagSerial_SEND
{
	unsigned int	datalen;
	unsigned char res[4];
}SERIAL_SEND, *LPSERIAL_SEND;

typedef struct tagSerial_REPLY_INFO
{
	short m_ErrorCode;		//Serialresponsecode_Eum
	short m_ExtLength;		//reply data length
}SERIAL_REPLY_INFO;

typedef struct tagSerial_REQ_INFO
{
	unsigned int type;	// 0 open/close, 1 connect, 2 set, 3 send
	union 
	{
		SERIAL_ENABLE enable;
		SERIAL_CONNECT connect;
		SERIAL_SETTINGS settings;
		SERIAL_SEND send;
	}req_union;
	unsigned char res;
}SERIAL_REQ_INFO, *LPSERIAL_REQ_INFO;


/////////////////////////////////////////////////////////////////////////////
//抓拍机通信协议
#define CMD_INFO_SET    21 //参数设置
#define CMD_HEART_BEAT  22
#define CMD_PHOTO_RECV   23
#define CMD_INFO_GET    25

#define NUM_SNAP_CIRCLE 4   //抓拍线圈通道个数；增加到四个可选通道。2011.11.17
#define PHOTO_PATH_LEN  128
#define RECV_PORT       8888
#define RECV_BUF_SIZE   512*1024 
#define INFI_CONTROLE   8886
#define INF_VIDEO_STREAM_MAX_STREAM_ID_NUM 32
#define INF_AUDIO_STREAM_MAX_STREAM_ID_NUM 32

#define Packed __attribute__((aligned(1),packed))

#endif
