/* 
 * Copyright (c) 2008-2009 HKVision corporation
 * Author: fire
 * Data: 2008.10
 * Description: 
 * 		function library
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */
 
#pragma once



#include "linuxInclude.h"
#include "define.h"

namespace Function
{
	// printf hexadecimal data
	void printHexData(unsigned char* buf, int len);

	/*  a c++ equivalent to the standard c routine "strdup()" */
	char* myStrDup(char const* str);

	/* like "strDup()", except that it doesn't copy the original.
	* (Instead, it just allocates a string of the same size as
	* the original.)
	*/  
	char* strDupSize(char const* str);

	/* handler routines for specific RTSP commands:
	* Generate a "Date:" header for use in a RTSP response:*/ 
	char const* dateHeader();

	/* returns a random sixteen bit value */
	u_int16_t GetRandom16();
	 
	/* returns a random thirty-two bit value */
	u_int32_t GetRandom32();


	// 在linux下产生min到max范围均匀分布的随机数
	int GetRandomInt(int iMin, int iMax);

	/* reports the error */
	void bail(const char *on_what);

	/* 改进的send 函数, 如果返回值是false, 则tcp链接可能断开*/
	BOOL mySend(int socketNum, unsigned char *sendBuf, int sendSize);

	/* 改进的 recv 函数*/
	BOOL myRecv(int socketNum, unsigned char *recvbuff, int recvSize);

	// printf hexadecimal short data
	void printHexShortData(unsigned short* buf, int len);

	// 延迟millisecond毫秒
	void myMDelay(int millisecond);

	// 延迟microsecond微秒
	void myUDelay(int microsecond);

	// 延迟nanosecond纳秒
	void myNDelay(int nanosecond);

                                       
	// 把数据大小字节顺序反转
	unsigned int FCC(unsigned int ch4);

	// 设置线程属性参数
	void SetThreadAttrParam(pthread_attr_t *pThr_attr, int iPriorty, int iStackSize, BOOL bScopeSys = FALSE,
							BOOL bIsDetached = FALSE);

}













