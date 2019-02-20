/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.03
 * Description: 
 * 		多路复用select 类
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

class CSelect
{
public:
	CSelect();
	~CSelect();


public:
	enum {DB_INFO_MAX_LEN = 256};

public:
	int SelectWait();


	BOOL IsReadEvent();
	BOOL IsWriteEvent();
                     
public:
	BOOL SetFdNum(int iFdNum) {m_iFdNum = iFdNum;};                    
	BOOL SetDbName(char* pName = "name");
	BOOL SetTimeOut(int iSec, int iuSec);


private:
	fd_set m_fdread;
	fd_set m_fdwrite;

  	struct timeval timeout;           // Timeout struct for select
                               
private:
	int		m_iFdNum;   
	int		m_iSec;		// 秒
	int		m_iuSec;	// 微秒
	char	m_cDbInfo[DB_INFO_MAX_LEN];


};




















