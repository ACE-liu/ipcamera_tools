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
	void SetShareVar(T shareVar);		// ��m_shareVar����ΪshareVar
	T GetShareVar();					// ��ȡm_shareVar��ֵ

	void AddShareVar(T add);			// ��m_shareVar��add
	void SubtractShareVar(T sub);		// ��m_shareVar����sub

public:
// ���º����ṩ�������Ľӿڣ��Ա���Ը������ã���Ҫ����ʹ��
	void SetShareVarNoLock(T shareVar) {m_shareVar = shareVar;}
	T GetShareVarNoLock() {return m_shareVar;}			

	void AddShareVarNoLock(T add) {m_shareVar += add;}			// ��m_shareVar��add
	void SubtractShareVarNoLock(T sub) {m_shareVar -= sub;}		// ��m_shareVar����sub

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


