/* 
 * Copyright (c) 2008-2009 HKVision corporation
 * Author: fire
 * Data: 2008.10
 * Description: 
 * 		net function library
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

#define DEFAULT_NETWORK_CARD "eth0"

namespace netFunction
{
	/* setup stream socket */
	int setupStreamSocket(u_int16_t port, int reuseFlag, u_int32_t addr);

	/* setup datagram socket */
	int setupDatagramSocket(u_int16_t port, int reuseFlag, u_int32_t addr);

    /* setup datagram socket */
	int setupBroadcastSocket(u_int16_t port, int reuseFlag, u_int32_t addr);

	/* Create a socket address */
	struct sockaddr_in make_sockaddr_in(u_int32_t addr, u_int16_t port);

	/* get buffer size */
	unsigned getBufferSize(int bufOptName, int socket);

	/* get send buffer size */
	unsigned getSendBufferSize(int socket);

	/* get receive buffer size */
	unsigned getReceiveBufferSize(int socket);

	/* increase buffer to */
	unsigned increaseBufferTo(int bufOptName, int socket, unsigned requestedSize);


	/* increase send Buffer to */
	unsigned increaseSendBufferTo(int socket, unsigned requestedSize);

	/* increase receive buffer to */
	unsigned increaseReceiveBufferTo(int socket, unsigned requestedSize);

	/* read date from socket */
	int readSocket(int socket, unsigned char* buffer,
		unsigned bufferSize, struct sockaddr_in* fromAddress);

	/* write socket */
	BOOL writeSocket(int socket, struct in_addr address, 
		u_int16_t port, unsigned char* buffer, unsigned bufferSize);


	/* get local ip address */
	struct in_addr GetLocalIp(char *pNetworkCard = DEFAULT_NETWORK_CARD);

	/* get local mask address */
	struct in_addr GetLocalMask(char *pNetworkCard = DEFAULT_NETWORK_CARD);

	/* get local mac address */
	unsigned char* GetLocalMac(char *pNetworkCard = DEFAULT_NETWORK_CARD);

	/* get local ip info address */
	struct in_addr GetLocalIpInfo(char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// set local ip address
	void SetLocalIp(char *ip, char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// set local mask address
	BOOL SetLocalMask(char *maskStr, char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// set local broadcast address
	void SetLocalBroadAdr(char *broadStr, char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// set local mac address
	void SetLocalMac(char *macStr, char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// set local gateway
	void SetLocalGateway(char *cmdType, char *gateWayStr, char *pNetworkCard = DEFAULT_NETWORK_CARD);

	// 增加组播路由
	void AddMulticastRoute(char *pNetworkCard = DEFAULT_NETWORK_CARD);

	/* get multicast address */
	void GetMulticastAddr(char multicastAddr[40], int iChan);


	/* 检查端口有没有被使用，并自动使port为未被使用的端口 */
	BOOL CheckPortHaveBeenUse(int *pPort);

	/* 往pBoardAddr发送广播包 */
	void SendBoardPacket(char *pBoardAddr);

}
			
				






 
