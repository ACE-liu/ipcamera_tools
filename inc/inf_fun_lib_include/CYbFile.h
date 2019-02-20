/*********************************************************
** 文件名:CYbFile.h
** Copyright (c) 2008-2018 英飞拓公司技术开发部
** 创建人:bin yan
** 日 期: 2012.03
** 修改人:
** 日 期:
** 描 述:抓拍机库配置文件读写函数头文件
**
** 版 本:v1.0
*********************************************************/

#ifndef _CYbFile_H_
#define _CYbFile_H_
#pragma once

#include "linuxInclude.h"
#include "define.h"

class CYbFile
{
public:
	CYbFile();
	~CYbFile();

public:
	enum {MAX_STR_LENGHT = 255,FILE_BUF_SIZE=4096};

public:
	BOOL OpenFile(char* pFileName, char *pMode);
	void CloseFile();

	//BOOL WriteConfStr(char* pKeyName, const char* pString);
	BOOL WriteConfStr(char* pKeyName,char* pString);
	BOOL AddConfStr(char* str);

	char* ReadConfStr(char* pKeyName);
	int ReadConfInt(char* pKeyName);

	int FindKeyName(char* pKeyName);

private:
	FILE	*m_fp;
	char   m_fileBuf[FILE_BUF_SIZE];
	char	m_strBuf[MAX_STR_LENGHT];


};

#endif //#ifndef _CYbFile_H_





