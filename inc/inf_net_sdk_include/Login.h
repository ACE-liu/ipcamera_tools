#pragma once
#include <string>
#include "linuxInclude.h"
#include "IPCNetSDK.h"

class CLogin
{
public:
    CLogin(const char *sDevIP,const unsigned short nDevPort,const char *sUserName,const char *sPassword);
    ~CLogin(void);
    BOOL Login();
    //BOOL PTZControl(unsigned int nChannel,E_PTZ_COMMAND ePTZCommand,int iParam1 = 6,int iParam2 = 0,BOOL bStop = false);
public:
    std::string m_sDevIP;
    unsigned short m_nDevPort;
    std::string m_sUserName;
    std::string m_sPassword;
private:
    BOOL Connect();
    BOOL LogOn();
    int  m_iSocketFD;

    //CThreadPtz *m_pThreadPtz;
};
