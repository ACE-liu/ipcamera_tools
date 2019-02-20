#pragma once

#include "Define.h"
/* 
 * Copyright (c) 2008-2018 HKVision corporation
 * Author: fire
 * Data: 2011.06
 * Description: 
 * 		   简单90端口协议接口模块
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */

typedef struct INF_AUDIO_STREAM_IN_PARAM
{
	const char *pServerAddr;			// 摄像机ip地址
	int iAVType;				// 音视频类型，example:	DATA_VIDEO
	int iEncoderType;			// 编码类型，example:	VIDEO_H264_MAJOR    
}INF_AUDIO_STREAM_IN_PARAM;

typedef struct tagThreadGetAudioStreamParam
{
	int iStreamID;//通道号
	INF_AUDIO_STREAM_IN_PARAM pThreadParam; /**< 码流类型，0-主码流，1-子码流 */
	void * pUserData; /**< 编码类型 */
}ThreadGetAudioStreamParam;

void * ThreadGetAudioStream(void* arg);
void * ThreadPlayAudioStream(void * arg);
BOOL ThreadStopListen();
