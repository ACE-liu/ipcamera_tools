/* 
 * Copyright (c) 2010-2011 HKVision corporation
 * Author: fire
 * Data: 2010.01
 * Description: 
 * 		Auto Mutex Function
   * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */



#pragma once

#include "linuxInclude.h"

class CMutex
{
public:
	CMutex()
	{
		pthread_mutex_init(&m_mutex, NULL);
	};

	~CMutex()
	{
		pthread_mutex_destroy(&m_mutex);
	};

	void Lock() 
	{
		pthread_mutex_lock(&m_mutex);
	};

	void Unlock() 
	{
		pthread_mutex_unlock(&m_mutex);
	};

private:
	pthread_mutex_t			m_mutex;

};



class CAutoMutex
{
public:
	CAutoMutex(CMutex *pMutex)
	{
		m_pMutex = pMutex;
		m_pMutex->Lock();
	};

	~CAutoMutex()
	{
		m_pMutex->Unlock();
	};

private:
	CMutex *m_pMutex;

};

class CAutoMutexPtr
{
public:
	CAutoMutexPtr(pthread_mutex_t *pMutex)
	{
		m_pMutex = pMutex;
		pthread_mutex_lock(m_pMutex);

	};

	~CAutoMutexPtr()
	{
		pthread_mutex_unlock(m_pMutex);
	};

private:
	pthread_mutex_t			*m_pMutex;

};






















