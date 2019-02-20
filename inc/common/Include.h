/* 
 * Copyright (c) 2008-2009 hankvision corporation
 * Author: fire
 * Data: 2013.12.28
 * Description: 
 * 		include header
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */
 
 
#pragma once

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netdb.h>
#include <linux/types.h>
#include <linux/if_ether.h>

#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX 终端控制定义*/
#include <errno.h>      /*错误号定义*/
#include <unistd.h>     /*Unix 标准函数定义*/
#include <arpa/inet.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <resolv.h>
#include <dirent.h>
#include <math.h>

typedef unsigned char  INT8U;
typedef signed   char  INT8S;
typedef unsigned short INT16U;
typedef signed   short INT16S;
typedef unsigned int  INT32U;
typedef signed   int  INT32S;

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

