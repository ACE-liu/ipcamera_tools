#ifndef _INFI_STREAM_PROTOCOL_H_
#define _INFI_STREAM_PROTOCOL_H_

//#include "IPCNetSDK.h"
///////////////////////////////////////////////////////////////////////////////

#define INFI_STREAM_PORT			90


//��������
#define CMD_REQ_LOGON				1			//�����¼
#define CMD_BACK_LOGON				2			//Ӧ���¼
#define CMD_REQ_AV					3			//��������Ƶ
#define CMD_BACK_AUDIO				4			//Ӧ������
#define CMD_BACK_VIDEO				6			//Ӧ����Ƶ
#define CMD_REQ_SEND_AV				7			//��������Ƶ
#define CMD_BACK_SEND_AUDIO			8			//Ӧ������Ƶ

#define CMD_REQ_GET_PARA			11			//�����ȡ����
#define CMD_BACK_GET_PARA			12			//Ӧ���ȡ����
#define CMD_REQ_SET_PARA			13			//�������ò���
#define CMD_BACK_SET_PARA			14			//Ӧ�����ò���
#define CMD_REQ_PTZ					15			//����PTZ����
#define CMD_BACK_PTZ					16			//Ӧ��PTZ����
#define CMD_REQ_UPGRADE				17			//�����豸����
#define CMD_BACK_UPGRADE				18			//Ӧ���豸����
#define CMD_REQ_VIDEO_SHIFT			19			//������Ƶ�л�
#define CMD_BACK_VIDEO_SHIFT			20			//Ӧ����Ƶ�л�
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
//����Ƶ��Э��ṹ��

typedef struct tagCMD_HEADER
{
	unsigned char	cStartCode[3];				//'I','N','F'
	unsigned char	cCmdType;					//��������
	unsigned short	sPacketSN;					//����ţ���1��ʼ
	unsigned short	sPacketNum;					//�ܰ�������СΪ1
	unsigned int   dwDataLength;				//��ͷ������ݳ���
}CMD_HEADER,*LPCMD_HEADER;

typedef struct tagLOGON_ACK_INFO
{
	unsigned long	dwUserID;					//�û�ID
	unsigned short	sErrorCode;					//������
	unsigned short	sExtLength;					//��չ����
}LOGON_ACK_INFO,*LPLOGON_ACK_INFO;

typedef struct tagAV_REQ_INFO
{
	unsigned char	cVersion;					//�汾
	unsigned char	cAVType;					//����Ƶ����
	unsigned char	cEncoderType;				//��������
	unsigned char	cReserved;					//����
	unsigned char	cIP[16];					//�豸IP
	unsigned short	sChannel;					//ͨ��
	unsigned short	sExtLength;					//��չ����
}AV_REQ_INFO,*LPAV_REQ_INFO;

typedef struct tagAV_VIDEO_INFO
{
	unsigned char	cFrameType;					//֡����
	unsigned char	cAVType;					//����Ƶ����
	unsigned char	cEncoderType;				//��������
	unsigned char	cFrameRate;					//֡��
	unsigned short	sVideoWidth;				//��Ƶ���
	unsigned short	sVideoHeight;				//��Ƶ�߶�
	unsigned long	dwFrameID;					//֡ID
	unsigned long   dwFrameSize;				//֡��С
	unsigned long   dwTimeStamp;				//ʱ���
	unsigned short	sErrorCode;					//�����
	unsigned short	sExtLength;					//��չ����	
}AV_VIDEO_INFO,*LPAV_VIDEO_INFO;

typedef struct tagAV_AUDIO_INFO
{
	unsigned char	cFrameType;					//֡����
	unsigned char	cAVType;					//����Ƶ����
	unsigned char	cEncoderType;				//��������
	unsigned char	cChannels;					//ͨ������
	unsigned short	sSamples;					//������
	unsigned short	sBitCount;					//����λ��
	unsigned long	dwwFrameID;					//֡ID
	unsigned long   dwFrameSize;				//֡��С
	unsigned long   dwTimeStamp;				//ʱ���
	unsigned short	sErrorCode;					//�����
	unsigned short	sExtLength;					//��չ����	
}AV_AUDIO_INFO,*LPAV_AUDIO_INFO;

typedef struct tagPTZ_SEND_INFO
{
	unsigned char  cCommand;		//��������
	unsigned char  cPanSpeed;		//Pan�����ٶ�
	unsigned char  cTiltSpeed;     //Tilt�����ٶ�
	unsigned char  cReserved[1];   //Ԥ��
	unsigned short sChannel;       //ͨ��
	unsigned short sExtLength;		//��չ����
}PTZ_SEND_INFO, *LPPTZ_SEND_INFO;

typedef struct tag3D_SEND_INFO
{
	unsigned char m_Command;  		/**< ��������*/
	unsigned char m_ActionType;		/**< ��������*/
	unsigned int 	m_SrcHeight;			/**< ��Ļ�߶�*/
	unsigned int	m_SrcWidth;			/**< ��Ļ���*/
	unsigned int 	m_SelHeight;			/**< ��ѡ�߶�*/
	unsigned int 	m_SelWidth;			/**< ��ѡ���*/
	unsigned int 	m_MidPointY;		/**< ��ѡ�е����λ��*/
	unsigned int 	m_MidPointX;		/**< ��ѡ�е����λ��*/
	unsigned int 	m_Reserved;			/**< Ԥ��*/
	unsigned int	m_ExtLength;		/**< ��չ����*/
	unsigned char m_Channel;			/**< ͨ��*/
}tag3D_SEND_INFO, *LPPTZ_3D_SEND_INFO;

typedef struct tagPTZ_REPLY_INFO
{
	unsigned short m_ErrorCode;		//�����
	unsigned short m_ExtLength;		//��չ����
}PTZ_REPLY_INFO, *LPPTZ_REPLY_INFO;

typedef struct tagVIDEO_SHIFT_REQ_INFO
{
	unsigned char	cVersion;					//�汾
	unsigned char	cDecoderChan;				//����ͨ��
	unsigned char	cResolution;				//�ֱ���
	unsigned char	cDisplayOsd;				//OSD��ʾ
	char			szOsdCamNum[16];			//CAM��		
	char			szOsdStatus[16];			//״̬
	unsigned char	cEncoderIP[16];				//����IP
	unsigned char	cEncoderChan;				//����ͨ��
	unsigned char	cReserved;					//����
	short			sExtLength;					//��չ����
}VIDEO_SHIFT_REQ_INFO, *LPVIDEO_SHIFT_REQ_INFO;

typedef struct tagVIDEO_SHIFT_ACK_INFO
{
	short			sErrorCode;					//������
	short			sExtLength;					//��չ����
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
//ץ�Ļ�ͨ��Э��
#define CMD_INFO_SET    21 //��������
#define CMD_HEART_BEAT  22
#define CMD_PHOTO_RECV   23
#define CMD_INFO_GET    25

#define NUM_SNAP_CIRCLE 4   //ץ����Ȧͨ�����������ӵ��ĸ���ѡͨ����2011.11.17
#define PHOTO_PATH_LEN  128
#define RECV_PORT       8888
#define RECV_BUF_SIZE   512*1024 
#define INFI_CONTROLE   8886
#define INF_VIDEO_STREAM_MAX_STREAM_ID_NUM 32
#define INF_AUDIO_STREAM_MAX_STREAM_ID_NUM 32

#define Packed __attribute__((aligned(1),packed))

#endif
