#pragma once

#include "InfiStreamProtocol.h"
#include "linuxInclude.h"
#include "IPCNetSDK.h"

typedef struct INF_AUDIO_STREAM_OUT_PARAM
{
	const char *pServerAddr;			// �����ip��ַ
	int iAVType;				// ����Ƶ���ͣ�example:	DATA_VIDEO
	int iEncoderType;			// �������ͣ�example:	VIDEO_H264_MAJOR    
}INF_AUDIO_STREAM_OUT_PARAM;

typedef struct tagThreadSendAudioStreamParam
{
	int iStreamID;//ͨ����
	INF_AUDIO_STREAM_OUT_PARAM pThreadParam; /**< �������ͣ�0-��������1-������ */
}ThreadSendAudioStreamParam;

typedef struct{
	const char *pServerAddr;
	short sPort;
	int iSocket;
	int iAVType;
	int iEncoderType;
}INTER_AUDIO_IN_PARAM;

typedef struct{
	int iChannel;
	INTER_AUDIO_IN_PARAM interAudioInParam;
	void * pUserData;
}InterSendAudioStreamParam;

BOOL VoiceDataWrite(BYTE *pFrameBuf, unsigned int iFrameSize);

void * ThreadVoiceDataInput(void* arg);

void * ThreadSendAudioStream(void* arg);

BOOL ThreadStopTalk();

BOOL VoiceFrameWriteShareBuffer(BYTE *pFrameBuf, unsigned int iFrameSize);



