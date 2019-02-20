#pragma once

#include "Define.h"
/* 
 * Copyright (c) 2008-2018 HKVision corporation
 * Author: fire
 * Data: 2011.06
 * Description: 
 * 		   ��90�˿�Э��ӿ�ģ��
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */

typedef struct INF_AUDIO_STREAM_IN_PARAM
{
	const char *pServerAddr;			// �����ip��ַ
	int iAVType;				// ����Ƶ���ͣ�example:	DATA_VIDEO
	int iEncoderType;			// �������ͣ�example:	VIDEO_H264_MAJOR    
}INF_AUDIO_STREAM_IN_PARAM;

typedef struct tagThreadGetAudioStreamParam
{
	int iStreamID;//ͨ����
	INF_AUDIO_STREAM_IN_PARAM pThreadParam; /**< �������ͣ�0-��������1-������ */
	void * pUserData; /**< �������� */
}ThreadGetAudioStreamParam;

void * ThreadGetAudioStream(void* arg);
void * ThreadPlayAudioStream(void * arg);
BOOL ThreadStopListen();
