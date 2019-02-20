/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.02
 * Description: 
 * 		内联函数
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */

#pragma once

#include "Function.h"

// 如果iRet != iValue, 则打印错误信息：on_what， 并退出程序
inline void BailIfNotEqual(const char *on_what, int iRet, const int iValue = 0)
{
	if(iRet != iValue)
	{
		Function::bail(on_what);
	}		
}
