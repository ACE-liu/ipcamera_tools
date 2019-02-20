/*******************************************************************************
Copyright (c) HKVision Tech. Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------

Date Created: 2012-2-13
Author: wuxiaofan
Description: Interface for HKVision device search

--------------------------------------------------------------------------------
Modification History
DATE          AUTHOR          DESCRIPTION
--------------------------------------------------------------------------------
2012-05-15	 wuxiaofan	 Add search type parameter,usually search for that devices whose ip 
												 are not in local subnet

*******************************************************************************/

#ifndef _INF_SDK_SEARCHDEVICE_H_
#define _INF_SDK_SEARCHDEVICE_H_

#define YS_WEAK __attribute__((weak))
#define INADDR_NONE             0xffffffff
#define SOCKET_ERROR            (-1)

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef NULL
#define	   NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

//return value
#define RET_SUCCEED           		0  	/**< Success */
#define RET_FAIL             			-1 	/**< Failure */
#define RET_ERR_IPADDR        		1  	/**< Incorrect IP address, causes: illegal IP address; range from the Start IP address to End IP address exceeding 256*256, or the End IP < Start IP */
#define RET_ERR_OPENSOCKET    	2  	/**< Network Connections Creation Error, causes: 5050 port may be occupied */
#define RET_ERR_INVALIDPARAM  	3  	/**< Invalid parameter*/


typedef struct 
{
	unsigned char iIpAddr[6];		/**<IPV4 使用前4字节，设定6字节是为IPV6考虑*/
	unsigned char iGateWay[4];	/**<网关*/
	unsigned char iMask[4];		/**<子网掩码*/
	unsigned char iMac[6];		/**<mac 地址*/
	unsigned int 	iHttpPort;		/**<http 端口*/
	unsigned int 	iTcpPort;		/**<video 端口*/
	unsigned int 	iRtspPort;		/**<rtsp 端口*/
}DETECT_SHOW_INFO, *PDETECT_SHOW_INFO;


/**
* @brief - Interface for init search
* @param void
* @return RET_FAIL:failure ; RET_SUCCEED:success
*/
int NET_IPC_Search_Init();


/**
* Search device interface
* @param [IN] strStartIP   search the start IP address
* @param [IN] strEndIP     search the End IP address
* @param [IN] fSearchData  call-back function of the search result
* @param [IN] iType        search type.0(default): Normal search,peer to peer or broadcast search;
                                       1: Special search,broadcast send and device receive use broadcast,usually search for that devices who are in local subnet,but whose ip are not in local subnet;
                                       others: reserved.
* @param [IN] pUserData    user defined data, callback function returned with original value.
* @return  Return result as follows:
* - TURE: RET_SUCCEED
* - FALSE: Refer to the return value definition
* @note If the Start IP and the End IP are set as "0", then execute broadcast searching in the current network segment; 
*       if the Start IP is the same as the End IP, and the value is not "0", then search the Start IP only. 
*/
int NET_IPC_SearchDevice (const char*strStartIP, const char*strEndIP, int iType = 0, char *ethName = NULL, void*pUserData = NULL);

/**
* Interface for searching progress
* @param  Void
* @return Return the search progress, 0-100 represents the searching progress and 100 represents the search result. 
*         In broadcast searching, the interface callback is ineffective and "100" will be returned.
*/
int NET_IPC_GetSearchPos();

/**
* @brief - Interface for get search info
* @param[out] dShowInfo 	the information you search and show
* @param[out] searchNum 	the device number you search
* @return 	RET_FAIL:failure ;RET_SUCCEED:success
*/
int NET_IPC_GetSearchInfo(char *dShowInfo, int *searchNum);


/**
* Interface for stop searching
* @param  Void
* @return  Return result as follows:
* - TURE: RET_SUCCEED
* - FALSE: Refer to the return value definition
*/
int NET_IPC_StopSearch();

/**
* @brief - Interface for modify ip, you can call this function after calling INFNET_SearchDevice interface.
* @param [in] oldIP 		old ip address
* @param [in] newIP 		set ip address
* @param [in] szGateway	gateway
* @param [in] szNetmask 	mask
* @return 0 and -1: failure ; 1: success
*/
int NET_IPC_Modify_DeviceIP(const char *oldIP, const char *newIP, const char *szGateway, const char *szNetmask);

/**
* @brief - Interface for modify ip, you can call this function after calling INFNET_SearchDevice interface.
* @param [in] newIP 		set ip address
* @param [in] szGateway	gateway
* @param [in] szNetmask 	mask
* @param [in] Mac 			device mac address
* @param [in] ethName 	net card interface name
* @return 0 and -1: failure ; 1: success
*/
int NET_IPC_Modify_DeviceIP_ByMac(const char *newIP, const char *szGateway, const char *szNetmask, const char *Mac,char *ethName);

/**
* @brief - Interface for release source
* @param void
* @return 0: success ; -1: failure
*/
int NET_IPC_Search_Cleanup();


#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif //#ifndef _INF_SDK_SEARCHDEVICE_H_
