/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.03
 * Description: 
 * 		��·����select ��
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
	int		m_iSec;		// ��
	int		m_iuSec;	// ΢��
	char	m_cDbInfo[DB_INFO_MAX_LEN];


};




















