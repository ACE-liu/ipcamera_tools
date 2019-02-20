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


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "InfiStreamProtocol.h"
#include "linuxInclude.h"
#include "IPCNetSDK.h"


typedef struct INF_VIDEO_STREAM_IN_PARAM
{
	const char *pServerAddr;			// �����ip��ַ
	int iAVType;				// ����Ƶ���ͣ�example:	DATA_VIDEO
	int iEncoderType;			// �������ͣ�example:	VIDEO_H264_MAJOR    
}INF_VIDEO_STREAM_IN_PARAM;

typedef struct tagThreadGetVideoStreamParam
{
	int iStreamID;//ͨ����
	INF_VIDEO_STREAM_IN_PARAM pThreadParam; /**< �������ͣ�0-��������1-������ */
	CBRealData CallBack; 
	void * pUserData; /**< �������� */
}ThreadGetVideoStreamParam;


void * ThreadGetVideoStream(void * arg);

BOOL StopGetVideoStream();

BOOL GetVideoDataEnd(int iSocket);

void *ThreadGetRealPlayStream(void *arg);

BOOL StartGetRealPlayStream(INTER_STREAM_IN_PARAM *pInParam,CBRealData fRealData,void *pUserData);

BOOL SetMDScopeFun(int iSocket,MD_Scope_Info *scope);

BOOL GetMDScopeFun(int iSocket,int *format,MD_Scope_Info *scope);

#ifdef __cplusplus
}
#endif
