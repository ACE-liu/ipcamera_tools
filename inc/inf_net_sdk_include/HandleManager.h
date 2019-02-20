#pragma once
#include <pthread.h>
#include <map>
#include "Login.h"

class CHandleManager
{
public:
    CHandleManager(void);
    ~CHandleManager(void);

    BOOL Init();
    BOOL Cleanup();
    long Login(const char *sDevIP,const unsigned int nDevPort,const char *sUserName,const char *sPassword);
    BOOL Logout(long lLoginID);
    long StartRealData(long lLoginID,S_REALDATA_INFO *pRealDateParam,void *pUserData = NULL);
    BOOL StopRealData(long lRealHandle,int iStreamID);
    BOOL StopRealDataConnect(long lRealHandle,int iStreamID,int iSockfd);
    BOOL StartTalk(long lLoginID);
    void StopTalk();
    BOOL StartVoiceInput(long lRealHandle, BYTE *pFrameBuf, unsigned int iFrameSize, void *pUser);
	BOOL GetMDScope(long lLoginID,short sPort,int *format,MD_Scope_Info *scope);
	BOOL SetMDScope(long lLoginID,short sPort,MD_Scope_Info *scope);

private:
    BOOL IsRealHandleValid(long lRealHandle);
    CLogin* GetLoginInfo(long lLoginID);

    std::map<long,int> m_mapSocket;
    std::map<long,pthread_t> m_mapRealData;
    std::map<long,CLogin*> m_mapLoginInfo;

};
