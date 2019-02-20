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


	// ��linux�²���min��max��Χ���ȷֲ��������
	int GetRandomInt(int iMin, int iMax);

	/* reports the error */
	void bail(const char *on_what);

	/* �Ľ���send ����, �������ֵ��false, ��tcp���ӿ��ܶϿ�*/
	BOOL mySend(int socketNum, unsigned char *sendBuf, int sendSize);

	/* �Ľ��� recv ����*/
	BOOL myRecv(int socketNum, unsigned char *recvbuff, int recvSize);

	// printf hexadecimal short data
	void printHexShortData(unsigned short* buf, int len);

	// �ӳ�millisecond����
	void myMDelay(int millisecond);

	// �ӳ�microsecond΢��
	void myUDelay(int microsecond);

	// �ӳ�nanosecond����
	void myNDelay(int nanosecond);

                                       
	// �����ݴ�С�ֽ�˳��ת
	unsigned int FCC(unsigned int ch4);

	// �����߳����Բ���
	void SetThreadAttrParam(pthread_attr_t *pThr_attr, int iPriorty, int iStackSize, BOOL bScopeSys = FALSE,
							BOOL bIsDetached = FALSE);

}













