
#ifndef _IP_CAM_CGI_H_
#define _IP_CAM_CGI_H_

#include "curl.h"
#include "libxml/xmlmemory.h"
#include "libxml/tree.h"
#include "libxml/parser.h"
#include <iostream>
#include <string>

namespace iim_ego{
namespace  capturer {

typedef struct
{
	int exposureMode;  /*0 --zidongbaoguang */
	int scenceSelect;  /*1 --shinei   0 ---shiwai*/
	int slowShutter;
	int agcMax;
	int agcManual;
	int shutterMax;
	int shutterManual;
	int ICRSwitch;
	int ICREnable;
	int icrtTimer;
	int ICRC2BThr;
	int ICRB2CThr;
	int hlcSwitch;
	int elcLevel;
	int ColorMode;
	int BLCSwitch;
	
}CGICamExposureInfo;

typedef struct
{
	int MirrorHor;
	int MirrorVer;
	int WDRSwitch;
	int WDRLevel;
	int AFCSwitch;
	int AFGSwitch;
	int LSCSwitch;
	int LDCSwitch;
	int DISSwitch;
	int WBMode;
	int WBRGain;
	int WBBGain;
        int LDCLevel;	
}CGICamBasicInfo;
// http://ipaddr/cgi/camera_set?Channel=1&Group=BasicInfo&LDCSwitch=1&LDCLevel=130

typedef struct
{
	int BitRate;
	int BitType;
	int FrameRate;
	int IPRate;
	int Payload; /*0 --h264 1--h265*/
	int StreamRateCut;
	int VideoQuality;
	std::string Resolution;
}CGICamStreamInfo;


typedef struct
{
	int TextOSDStatus;
	int TextOSDStatus1;
	int TextOSDStatus2;
	int TextOSDStatus3;
	int TextOSDStatus4;
	int MultipleOSDStatus;
	int TimeOSDStatus;
}CGICamOSDInfo;

class IPcam_CGI
{
public:
    static bool getDynamicRange(const std::string &ipaddr,CGICamBasicInfo &info);
    static bool setDynamicRange(const std::string &ipaddr,const CGICamBasicInfo& info,const int nSelect[13]);
    static bool getExposureMsg(const std::string &ipaddr,CGICamExposureInfo &info);
    static bool setExposureMsg(const std::string &ipaddr,const CGICamExposureInfo& info,const int nSelect[16]);
    static bool getStreamInfoMsg(const std::string &ipaddr,CGICamStreamInfo &info);
    static bool setStreamInfoMsg(const std::string &ipaddr,const CGICamStreamInfo& info, const int nSelect[8]);
    
    static bool getDeviceInfo(std::string const& ipaddr);
    
    static bool getCamOSDInfo(const std::string &ipaddr,CGICamOSDInfo &info);
    static bool setCamOSDInfo(const std::string &ipaddr,const CGICamOSDInfo& info,const int nSelect[7]);
    static void log_params(const CGICamOSDInfo& OSDinfo);
//     static void config_log_stream(iim_ego::basis::logstream *plogstream);
    static void log_params(const CGICamBasicInfo& basicinfo);
    static void log_params(const CGICamExposureInfo& cgiInfo);
    static void log_params(const CGICamStreamInfo& streamInfo);
	
private:
   static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid);
   static bool http_get_xmldata(const std::string& url,std::string &rtn);
   static bool getDetailMegByNode(xmlNodePtr& node,const std::string& typeString, void *info);
   static bool xmlParseCameraMsg(const std::string &data,const std::string &typestring, bool if_parse, void* info);
   
//    static iim_ego::basis::logstream *logstream;
};


}
}


#endif
