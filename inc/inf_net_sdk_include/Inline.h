/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.02
 * Description: 
 * 		��������
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */

#pragma once

#include "Function.h"

// ���iRet != iValue, ���ӡ������Ϣ��on_what�� ���˳�����
inline void BailIfNotEqual(const char *on_what, int iRet, const int iValue = 0)
{
	if(iRet != iValue)
	{
		Function::bail(on_what);
	}		
}
