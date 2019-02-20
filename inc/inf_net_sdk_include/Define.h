/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.02
 * Description: 
 * 		ºê¶¨Òåº¯Êý
 * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */

#pragma once


#ifndef DB
#define DB(x)				\
	printf("%s\n", x);
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE( x )	\
	if (NULL != x)			\
	{						\
		delete x;			\
		x = NULL;			\
	}
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE( x )	\
	if (NULL != x)				\
	{							\
		delete[] x;				\
		x = NULL;				\
	}
#endif

#ifndef SAFE_FREE
#define SAFE_FREE( x )		\
	if (NULL != x)			\
	{						\
		free(x);			\
		x = NULL;			\
	}
#endif



#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#define WEAK __attribute__((weak))


