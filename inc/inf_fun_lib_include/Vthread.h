/*
 * Vthread.h
 *
 */

#ifndef VTHREAD_H_
#define VTHREAD_H_

#include <pthread.h>
#include <unistd.h>


typedef enum
{
	SINGLE = 0,
	MULTIPLE,
	WAITING
}EventPostType;

typedef enum
{
	LOW = 0,
	NORMAL,
	HIGH
}ThreadPriority;


typedef void* (*TH_FN)(void *arg1);


typedef void* (*TH_FN_ARG)(void *arg1);

typedef struct THREAD_TYPE
{
	pthread_attr_t attr;
	pthread_t thread;
	struct sched_param param;
}v_thread;

typedef struct MUTEX_TYPE
{
	pthread_attr_t attr;
	pthread_mutex_t mutex;
}v_mutex;

typedef struct EVENT_TYPE
{
	pthread_cond_t event;
	int refCnt;
	int post_type;
}v_event;

typedef struct TIME_TYPE
{
	int tSec;
	int tMsec;
}v_time;

int v_thread_init(v_thread *threadPtr, TH_FN_ARG thFunc, void *thData, 
		ThreadPriority prtyVal);

int v_mutex_init(v_mutex *mutex_lock);
int v_mutex_lock(v_mutex *mutex_lock);
int v_mutex_unlock(v_mutex *mutex_lock);


int v_event_init(v_event *eventPtr, EventPostType postType);
int v_event_wait(v_event *eventPtr, v_mutex *mutexPtr);
int v_event_post(v_event *eventPtr);
int v_mutex_tryLock(v_mutex *mutex_lock);
int v_event_timed_wait(v_event *eventPtr, v_mutex *mutexPtr, v_time tWait);

int v_mutex_destroy(v_mutex *mutexPtr);
int v_event_destroy(v_event *eventPtr);

void v_sleep(int milliSec);
#endif /* VTHREAD_H_ */
