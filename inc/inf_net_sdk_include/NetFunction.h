/* 
 * Copyright (c) 2008-2018 HKVision corporation
 * Author: fire
 * Data: 2011.06
 * Description: 
 * 	
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

#include "linuxInclude.h"
#include "IPCNetSDK.h"



// 关掉TCP连接
BOOL inf_DisConnect(int iSocket);

/* increase send Buffer to */
unsigned int inf_increaseSendBufferTo(int socket, unsigned requestedSize);


//返回根据addr和port构建的网络地址
struct sockaddr_in inf_make_sockaddr_in(int addr, short port);


/* setup stream socket */
int inf_setupStreamSocket(short port, int reuseFlag, int addr);



/* 改进的 send 函数, 如果返回值是false, 则tcp链接可能断开*/
BOOL inf_Send(int socketNum, unsigned char *sendBuf, int sendSize);

/* 改进的 recv 函数*/
BOOL inf_Recv(int socketNum, unsigned char *recvbuff, int recvSize);




// printf hexadecimal data
void inf_printHexData(unsigned char* buf, int len);


BOOL NetDataInit(const char *pServerAddr, int *pSocket, struct sockaddr_in *pRemoteName);

BOOL NetRealPlaySocketCreate(const char *pServerAddr, int *pSocket);

BOOL ConnectServer(int iSocket, struct sockaddr_in remoteName);

#ifdef __cplusplus
}
#endif

