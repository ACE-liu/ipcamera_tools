/************************************************************

Copyright (C), 2008-2011, HKVision. Co., Ltd.

*************************************************************

File Name     : RingBuffer.h
Version       : V1.0 
Author        : HKVision RD3
Last Modified : 2008-12-9
Description   : 具有音视频功能的RingBuff
Function List : 
History       :

************************************************************/

#include <stdio.h>
typedef enum tag_MODULE
{
    MODULE_GENERAL = 0,
    MODULE_SYS     = 1 ,  /*系统模块*/           
    MODULE_DRV     = 2 ,  /*驱动模块*/
    MODULE_MMF     = 3,   /*MultiMedia Frame*/
    MODULE_APP     = 4,   /*应用模块*/

    MODULE_BUTT         /*结束标志*/
}MODULE_E;

typedef enum tag_SYS_SUB_MODULE
{
    SYS_SUB_MODULE_AZ   = 1, /*Arm ZSP Message Communication*/
    SYS_SUB_MODULE_RB   = 2, /*Ring Buffer */
    SYS_SUB_MODULE_BM   = 3, /*Buffer Manager*/
    SYS_SUB_MODULE_MQ   = 4, /*Message Queue*/
    SYS_SUB_MODULE_THREAD = 5,
    SYS_SUB_MODULE_BUTT
}SYS_SUB_MODULE;


#define HI_SUCCESS                    0

#define ERR_NUMBER(err, base)          ( (base) | (err) ) 
#define ERR_SUB_MODULE_BASE(module, submodule)    \
                (( module << 24 ) | ( submodule << 16 )) 
                
#define ERR_SYS_RB_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_RB)


/*0x00XX*/
#define ERR_GENERAL_BASE      ERR_SUB_MODULE_BASE(MODULE_GENERAL, 0)

#define ERR_GEN_NOT_ENOUGH_MEMORY ERR_NUMBER(2, ERR_GENERAL_BASE) /*0x0002*/
#define ERR_GEN_INVALID_POINTER   ERR_NUMBER(3, ERR_GENERAL_BASE) /*0x0003*/
#define ERR_GEN_OVERFLOW          ERR_NUMBER(4, ERR_GENERAL_BASE) /*0x0004*/
#define ERR_GEN_OUT_OF_BOUND      ERR_NUMBER(5, ERR_GENERAL_BASE) /*0x0004*/
#define ERR_GEN_INVALID_FP        ERR_NUMBER(6, ERR_GENERAL_BASE) /*0x0004*/

#define ERR_GEN_TIMEOUT           ERR_NUMBER(7, ERR_GENERAL_BASE) /*0x0007*/
#define ERR_GEN_INVALID_PARAMETER ERR_NUMBER(8, ERR_GENERAL_BASE) /*0x0008*/


#define ERR_RB_ERROR               ERR_NUMBER(0, ERR_SYS_RB_BASE) /*0x1201*/
#define ERR_RB_INIT                ERR_NUMBER(1, ERR_SYS_RB_BASE) /*0x1201*/
#define ERR_RB_OVERFLOW            ERR_NUMBER(2, ERR_SYS_RB_BASE) /*0x1202*/
#define ERR_RB_READ_NOTENOGH       ERR_NUMBER(3, ERR_SYS_RB_BASE) /*0x1203*/
#define ERR_RB_WRITE_NOTENOGH      ERR_NUMBER(4, ERR_SYS_RB_BASE) /*0x1204*/
#define ERR_RB_NULL_BUF            ERR_NUMBER(5, ERR_SYS_RB_BASE) /*0x1205*/
#define ERR_RB_DAMAGE              ERR_NUMBER(6, ERR_SYS_RB_BASE) /*0x1206*/


/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后的起始地址
 * 如4byte对齐, 0x80001232 ALIGN_START(0x80001232,4) = 0x80001230
 */
#define ALIGN_START(v,a) (((v)) & (~((a)-1)))

/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后的结束地址地址
 * 如4byte对齐, 0x80001232 ALIGN_END(0x80001232,4) = 0x80001233
 */
#define ALIGN_END(v,a) (((v) & ~((a)-1)) + ((a)-1) ) 
/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后下一地址的开始地址
 * 如4byte对齐, 0x80001232 ALIGN_NEXT(0x80001232,4) = 0x80001234
 */

#define ALIGN_NEXT(v,a) ((((v) + ((a)-1)) & (~((a)-1))))

#define ALIGN_LENGTH(l, a) ALIGN_NEXT(l, a)

#define ALIGNTYPE_1BYTE  1
/*zsp*/
#define ALIGNTYPE_2BYTE  2
/*x86... default*/
#define ALIGNTYPE_4BYTE  4

#define ALIGNTYPE_8BYTE  8
/*1 Page*/
#define ALIGNTYPE_4K     4096

#define ALIGNTYPE_ZSP    ALIGNTYPE_2BYTE

#define ALIGNTYPE_VIDEO  ALIGNTYPE_8BYTE


#define RB_LEN_BYTES 4

typedef enum RB_STAT_ENUM
{
	E_RB_TotalReadError,
	E_RB_TotalWriteError,
		
	E_RB_TotalWriteSize,
	E_RB_TotalReadSize,
		
	E_RB_TotalReadTimes,
	E_RB_TotalWriteTimes,
		
	E_RB_STAT_END
}RB_STAT_E;

typedef struct RingBuffer
{
	unsigned int  m_ulSize;			/*Buffer的总长度*/    
	unsigned char   *m_pRB;				/*Buffer的开始地址*/
	unsigned int  m_ulWritePos;		/*写的位置, 偏移位*/
	unsigned int  m_ulReadPos;		/*读的位置, 偏移位*/
	unsigned long long  m_stat[E_RB_STAT_END];
	unsigned short  m_usMediaType; 	    /*媒体类型*/ 
}RingBuffer_t;

void RB_Init_Stat(RingBuffer_t *RingBuf);
void RB_Do_Stat(RB_STAT_E, unsigned long long value,RingBuffer_t *RingBuf);
void RB_Disp_Stat(RingBuffer_t *RingBuf);

unsigned int RB_MaxReadSize(RingBuffer_t *RingBuf);
unsigned int RB_MaxWriteSize(RingBuffer_t *RingBuf);
unsigned int RB_MAXSize(RingBuffer_t *RingBuf);

int RB_Init (unsigned int ulSize,RingBuffer_t *RingBuf);

void RB_Clear(RingBuffer_t *RingBuf);
void RB_Destroy(RingBuffer_t *RingBuf);

int RB_Write(unsigned char *pData, unsigned int ulLen, unsigned int *pulWriteLen,RingBuffer_t *RingBuf);
int RB_Read(unsigned char *pData, unsigned int ulLen, unsigned int *pulRead,RingBuffer_t *RingBuf);

int RB_Write_X(unsigned char *pData, unsigned int ulDataLen, unsigned int *pulWriteLen,RingBuffer_t *RingBuf);
int RB_Read_X(unsigned char *pData, unsigned int *pulData,RingBuffer_t *RingBuf);

unsigned int RB_GetLen_X(RingBuffer_t *RingBuf);
unsigned char RB_GetFirstHI_U8(RingBuffer_t *RingBuf);   /*从Read指针读取值*/
unsigned short RB_GetFirstHI_U16(RingBuffer_t *RingBuf); /*2Byte*/
unsigned int RB_GetFirstHI_U32(RingBuffer_t *RingBuf);

unsigned int RB_GetMaxWritePercent(RingBuffer_t *RingBuf);
unsigned int RB_GetMaxReadPercent(RingBuffer_t *RingBuf);

