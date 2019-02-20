#ifndef _INFI_STREAM_PROTOCOL_H_
#define _INFI_STREAM_PROTOCOL_H_


///////////////////////////////////////////////////////////////////////////////

#define INFI_STREAM_PORT			90


//命令类型
#define CMD_REQ_LOGON				1			//请求登录
#define CMD_ACK_LOGON				2			//应答登录
#define CMD_REQ_AV					3			//请求音视频
#define CMD_ACK_AUDIO				4			//应答音视
#define CMD_ACK_VIDEO				6			//应答视频
#define CMD_REQ_SEND_AV				7			//请求发送音频
#define CMD_ACK_SEND_AUDIO			8			//应答发送音频

#define CMD_REQ_GET_PARA			11			//请求获取参数
#define CMD_ACK_GET_PARA			12			//应答获取参数
#define CMD_REQ_SET_PARA			13			//请求设置参数
#define CMD_ACK_SET_PARA			14			//应答设置参数
#define CMD_REQ_PTZ					15			//请求PTZ命令
#define CMD_ACK_PTZ					16			//应答PTZ命令
#define CMD_REQ_UPGRADE				17			//请求设备升级
#define CMD_ACK_UPGRADE				18			//应答设备升级
#define CMD_REQ_VIDEO_SHIFT			19			//请求视频切换
#define CMD_ACK_VIDEO_SHIFT			20			//应答视频切换
#define CMD_REQ_3D					49

#define CMD_REQ_MDSET				55
#define CMD_BACK_MDSET				56
#define CMD_REQ_MDGET				57
#define CMD_BACK_MDGET				58

//版本
#define IP_VERSION4					4			//IPV4
#define IP_VERSION6					6			//IPV6

//音视频类型
#define DATA_VIDEO					1			//视频流
#define DATA_AUDIO					2			//音频流
#define DATA_AV						3			//复合流

//视频编码类型
#define VIDEO_MPEG4_MAJOR			1			//MPEG4主码流
#define VIDEO_MPEG4_MINOR			2			//MPEG4次码流
#define VIDEO_MJPEG					3			//MJPEG码流
#define VIDEO_H264_MAJOR			4			//H264主码流
#define VIDEO_H264_MINOR			5			//H264次码流
#define VIDEO_MJPEG2000				8			// yesun13

//音频编码类型
#define	AUDIO_G711_U				0x01		//G711_U
#define	AUDIO_G711_A				0x02		//G711_A
#define	AUDIO_ADPCM_A				0x03		//ADPCM_A
#define	AUDIO_G726					0x04		//G726
#define	AUDIO_G711_A_HI				0x05		//HI H264
#define	AUDIO_G711_U_HI				0x06		//HI H264
#define	AUDIO_G726_HI				0x07		//HI H264

//帧类型
#define FRAME_VOL					0xD0		//VOL
#define FRAME_IVOP					0xD1		//I帧
#define FRAME_PVOP					0xD2		//P帧
#define FRAME_AUDIO					0xD3		//音频帧

//登录请求错误码
#define RE_SUCCESS					0			//成功
#define RE_USERNAME_ERROR			1			//用户名错误
#define RE_PASSWORD_ERROR			2			//密码错误


//视频请求错误码
#define RE_AV_SUCCESS               0           //正常
#define RE_AV_FULL_ERROR            1           //连接已满
#define RE_AV_LOST_ERROR            2           //视频丢失
#define RE_AV_TYPE_ERROR            3           //非音视频类型
#define RE_AV_NONSUPPORT_ERROR      4           //不支持 
#define RE_AV_NO_PRIVILEGE          5           //没有权限
#define RE_AV_UNREACH               6           //前端网络不可达




#define TEXT_LENGTH					32

//音频采样类型
#define PLAY_AUDIO_SAMPLE_POOR		8000
#define PLAY_AUDIO_SAMPLE_LOW		11025
#define PLAY_AUDIO_SAMPLE_NORMAL	22050
#define PLAY_AUDIO_SAMPLE_HIGH		44100

//转发请求客户端类型
#define	CLIENT_DECODER				0x01		//DECODER
#define	CLIENT_LMC					0x02		//LMC
#define	CLIENT_SMT					0x03		//SMT
#define	CLIENT_NVR					0x04		//NVR
#define CLIENT_WEB					0x05		//Web 

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

typedef struct tagLOGON_REQ_INFO
{
	unsigned char	szUserName[TEXT_LENGTH];		//用户名
	unsigned char	szPassword[TEXT_LENGTH];		//密码
}LOGON_REQ_INFO,*LPLOGON_REQ_INFO;

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
	unsigned long	dwFrameID;					//帧ID
	unsigned long   dwFrameSize;				//帧大小
	unsigned long   dwTimeStamp;				//时间戳
	unsigned short	sErrorCode;					//错误号
	unsigned short	sExtLength;					//扩展长度	
}AV_AUDIO_INFO,*LPAV_AUDIO_INFO;

typedef struct tagPTZ_REQ_INFO
{
	unsigned char	cCommand;					//控制命令
	unsigned char	cPanSpeed;					//Pan控制速度
	unsigned char	cTiltSpeed;					//Tilt控制速度
	unsigned char	cReserved;					//预留
	unsigned short	sChannel;					//通道
	unsigned short	sExtLength;					//扩展长度
}PTZ_REQ_INFO, *LPPTZ_REQ_INFO;

typedef struct tagPTZ_ACK_INFO
{
	unsigned short	sErrorCode;					//错误号
	unsigned short	sExtLength;					//扩展长度
}PTZ_ACK_INFO, *LPPTZ_ACK_INFO;

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

#endif
