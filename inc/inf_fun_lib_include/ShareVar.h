/* 
 * Copyright (c) 2010-2013 HKVision corporation
 * Author: fire
 * Data: 2010.01
 * Description: 
 * 		share variable Function
   * 		
 * Modify by:
 * Date:
 * Description: 
 * Version: V1.0
 * 
 */



#pragma once

#include "linuxInclude.h"
#include "AutoMutex.h"

template <typename T> 
class CShareVar
{
public:
	CShareVar();
	~CShareVar();
	
public:
	void SetShareVar(T shareVar);		// 把m_shareVar设置为shareVar
	T GetShareVar();					// 获取m_shareVar的值

	void AddShareVar(T add);			// 把m_shareVar加add
	void SubtractShareVar(T sub);		// 把m_shareVar减少sub

public:
// 以下函数提供不上锁的接口，以便可以更灵活调用，但要谨慎使用
	void SetShareVarNoLock(T shareVar) {m_shareVar = shareVar;}
	T GetShareVarNoLock() {return m_shareVar;}			

	void AddShareVarNoLock(T add) {m_shareVar += add;}			// 把m_shareVar加add
	void SubtractShareVarNoLock(T sub) {m_shareVar -= sub;}		// 把m_shareVar减少sub

	void Lock() {pthread_mutex_lock(&m_mutex);}
	void UnLock() {pthread_mutex_unlock(&m_mutex);}

private:
	T m_shareVar;
	pthread_mutex_t			m_mutex;

};

template <typename T> 
CShareVar<T>::CShareVar()
{
	pthread_mutex_init(&m_mutex, NULL);
}


template <typename T> 
CShareVar<T>::~CShareVar()
{
	pthread_mutex_destroy(&m_mutex);
}


template <typename T> 
void CShareVar<T>::SetShareVar(T shareVar)
{
	pthread_mutex_lock(&m_mutex);
	m_shareVar = shareVar;
	pthread_mutex_unlock(&m_mutex);	
}

template <typename T>
T CShareVar<T>::GetShareVar()
{
	CAutoMutexPtr lock(&m_mutex);

	return m_shareVar;
}


template <typename T> 
void CShareVar<T>::AddShareVar(T add)
{
	pthread_mutex_lock(&m_mutex);
	m_shareVar += add;
	pthread_mutex_unlock(&m_mutex);	

}


template <typename T>
void CShareVar<T>::SubtractShareVar(T sub)
{
	pthread_mutex_lock(&m_mutex);
	m_shareVar -= sub;
	pthread_mutex_unlock(&m_mutex);	

}


