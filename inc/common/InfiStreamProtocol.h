#ifndef _INFI_STREAM_PROTOCOL_H_
#define _INFI_STREAM_PROTOCOL_H_


///////////////////////////////////////////////////////////////////////////////

#define INFI_STREAM_PORT			90


//��������
#define CMD_REQ_LOGON				1			//�����¼
#define CMD_ACK_LOGON				2			//Ӧ���¼
#define CMD_REQ_AV					3			//��������Ƶ
#define CMD_ACK_AUDIO				4			//Ӧ������
#define CMD_ACK_VIDEO				6			//Ӧ����Ƶ
#define CMD_REQ_SEND_AV				7			//��������Ƶ
#define CMD_ACK_SEND_AUDIO			8			//Ӧ������Ƶ

#define CMD_REQ_GET_PARA			11			//�����ȡ����
#define CMD_ACK_GET_PARA			12			//Ӧ���ȡ����
#define CMD_REQ_SET_PARA			13			//�������ò���
#define CMD_ACK_SET_PARA			14			//Ӧ�����ò���
#define CMD_REQ_PTZ					15			//����PTZ����
#define CMD_ACK_PTZ					16			//Ӧ��PTZ����
#define CMD_REQ_UPGRADE				17			//�����豸����
#define CMD_ACK_UPGRADE				18			//Ӧ���豸����
#define CMD_REQ_VIDEO_SHIFT			19			//������Ƶ�л�
#define CMD_ACK_VIDEO_SHIFT			20			//Ӧ����Ƶ�л�
#define CMD_REQ_3D					49

#define CMD_REQ_MDSET				55
#define CMD_BACK_MDSET				56
#define CMD_REQ_MDGET				57
#define CMD_BACK_MDGET				58

//�汾
#define IP_VERSION4					4			//IPV4
#define IP_VERSION6					6			//IPV6

//����Ƶ����
#define DATA_VIDEO					1			//��Ƶ��
#define DATA_AUDIO					2			//��Ƶ��
#define DATA_AV						3			//������

//��Ƶ��������
#define VIDEO_MPEG4_MAJOR			1			//MPEG4������
#define VIDEO_MPEG4_MINOR			2			//MPEG4������
#define VIDEO_MJPEG					3			//MJPEG����
#define VIDEO_H264_MAJOR			4			//H264������
#define VIDEO_H264_MINOR			5			//H264������
#define VIDEO_MJPEG2000				8			// yesun13

//��Ƶ��������
#define	AUDIO_G711_U				0x01		//G711_U
#define	AUDIO_G711_A				0x02		//G711_A
#define	AUDIO_ADPCM_A				0x03		//ADPCM_A
#define	AUDIO_G726					0x04		//G726
#define	AUDIO_G711_A_HI				0x05		//HI H264
#define	AUDIO_G711_U_HI				0x06		//HI H264
#define	AUDIO_G726_HI				0x07		//HI H264

//֡����
#define FRAME_VOL					0xD0		//VOL
#define FRAME_IVOP					0xD1		//I֡
#define FRAME_PVOP					0xD2		//P֡
#define FRAME_AUDIO					0xD3		//��Ƶ֡

//��¼���������
#define RE_SUCCESS					0			//�ɹ�
#define RE_USERNAME_ERROR			1			//�û�������
#define RE_PASSWORD_ERROR			2			//�������


//��Ƶ���������
#define RE_AV_SUCCESS               0           //����
#define RE_AV_FULL_ERROR            1           //��������
#define RE_AV_LOST_ERROR            2           //��Ƶ��ʧ
#define RE_AV_TYPE_ERROR            3           //������Ƶ����
#define RE_AV_NONSUPPORT_ERROR      4           //��֧�� 
#define RE_AV_NO_PRIVILEGE          5           //û��Ȩ��
#define RE_AV_UNREACH               6           //ǰ�����粻�ɴ�




#define TEXT_LENGTH					32

//��Ƶ��������
#define PLAY_AUDIO_SAMPLE_POOR		8000
#define PLAY_AUDIO_SAMPLE_LOW		11025
#define PLAY_AUDIO_SAMPLE_NORMAL	22050
#define PLAY_AUDIO_SAMPLE_HIGH		44100

//ת������ͻ�������
#define	CLIENT_DECODER				0x01		//DECODER
#define	CLIENT_LMC					0x02		//LMC
#define	CLIENT_SMT					0x03		//SMT
#define	CLIENT_NVR					0x04		//NVR
#define CLIENT_WEB					0x05		//Web 

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

typedef struct tagLOGON_REQ_INFO
{
	unsigned char	szUserName[TEXT_LENGTH];		//�û���
	unsigned char	szPassword[TEXT_LENGTH];		//����
}LOGON_REQ_INFO,*LPLOGON_REQ_INFO;

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
	unsigned long	dwFrameID;					//֡ID
	unsigned long   dwFrameSize;				//֡��С
	unsigned long   dwTimeStamp;				//ʱ���
	unsigned short	sErrorCode;					//�����
	unsigned short	sExtLength;					//��չ����	
}AV_AUDIO_INFO,*LPAV_AUDIO_INFO;

typedef struct tagPTZ_REQ_INFO
{
	unsigned char	cCommand;					//��������
	unsigned char	cPanSpeed;					//Pan�����ٶ�
	unsigned char	cTiltSpeed;					//Tilt�����ٶ�
	unsigned char	cReserved;					//Ԥ��
	unsigned short	sChannel;					//ͨ��
	unsigned short	sExtLength;					//��չ����
}PTZ_REQ_INFO, *LPPTZ_REQ_INFO;

typedef struct tagPTZ_ACK_INFO
{
	unsigned short	sErrorCode;					//�����
	unsigned short	sExtLength;					//��չ����
}PTZ_ACK_INFO, *LPPTZ_ACK_INFO;

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

#endif
