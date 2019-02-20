#include "include/ip_cam_CGI.h"
#include <string.h>


namespace
{
    const char *new_ip="192.168.10.18";
    const char *gateway="192.168.10.1";
    const int  exposureMode=0;
    const int scenceSelect=1;
    const int FrameRate=15;
    const int WDRSwitch=1; //kuandongtai
    const int WDRLevel=50;
    const int LDCSwitch=1; //jibianjiaozheng
    const int LDCLevel=50;
    const int textstatus=0;
    const int timestatus=0;
    
    const int iprate=10;
}

static bool set_expos_ScenceSelect(const char *ipaddr,int exposureMode, int scenceSelect)
{
  iim_ego::capturer::CGICamExposureInfo cgiInfo;
  memset(&cgiInfo, 0x00, sizeof(iim_ego::capturer::CGICamExposureInfo));
  int nSlect[16] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
  cgiInfo.exposureMode=exposureMode;
  cgiInfo.scenceSelect = scenceSelect;
  return iim_ego::capturer::IPcam_CGI::setExposureMsg(ipaddr,cgiInfo,nSlect);  
}
static bool setFrameRate(const char *ipaddr,int frameRate)
{
  bool ret;
  iim_ego::capturer::CGICamStreamInfo cgiInfo;
  memset(&cgiInfo, 0x00, sizeof(iim_ego::capturer::CGICamStreamInfo));
  int nSlect[7] = {0,0,1,0,0,0,0};	
  cgiInfo.FrameRate = frameRate;
  return iim_ego::capturer::IPcam_CGI::setStreamInfoMsg(ipaddr,cgiInfo,nSlect);
}

static bool setWDRswitch_level(const char *ipaddr,int ldcswitch,int wdrSwitch, int value)
{
  bool ret;
  int data=value;
  iim_ego::capturer::CGICamBasicInfo basicInfo;
  memset(&basicInfo, 0x00, sizeof(iim_ego::capturer::CGICamBasicInfo));
  int nSlect[13] = {0,0,1,1,0,0,0,1,0,0,0,0,0};
  basicInfo.LDCSwitch=ldcswitch;
  basicInfo.WDRSwitch=wdrSwitch;
  if(data<0)
     data=0;
  if(data>255) 
     data=255;
  basicInfo.WDRLevel = data;
  return iim_ego::capturer::IPcam_CGI::setDynamicRange(ipaddr,basicInfo,nSlect);

}


static bool set_LDClevel(const char *ipaddr,const int LDClevel)
{
  bool ret;
  int data =LDClevel;
  iim_ego::capturer::CGICamBasicInfo basicInfo;
  memset(&basicInfo, 0x00, sizeof(iim_ego::capturer::CGICamBasicInfo));
  int nSlect[13] = {0,0,0,0,0,0,0,1,0,0,0,0,1};
  basicInfo.LDCSwitch=1;
  if(data<0)
     data=0;
  if(data>255) 
     data=255;
    basicInfo.LDCLevel=data;
  return iim_ego::capturer::IPcam_CGI::setDynamicRange(ipaddr,basicInfo,nSlect);
}
static bool setTextStatus(const char *ipaddr,int textstatus, int timestatus)
{
  bool ret;
  iim_ego::capturer::CGICamOSDInfo osdInfo;
  memset(&osdInfo, 0x00, sizeof(iim_ego::capturer::CGICamOSDInfo));
  int nSlect[7] = {1,0,0,0,0,0,1};	
  osdInfo.TextOSDStatus = textstatus;
  osdInfo.TimeOSDStatus= timestatus;
  return iim_ego::capturer::IPcam_CGI::setCamOSDInfo(ipaddr,osdInfo,nSlect);
}

static int curLDClevel=0;
static bool config_new_ip_camera()
{
   bool ret =true;
   if(!set_expos_ScenceSelect(new_ip,exposureMode,scenceSelect))
   {
	std::cout<<"设置相机曝光模式 和场景失败."<<std::endl;
	ret =false;
}
else
    std::cout<<"设置相机曝光模式 和场景成功."<<std::endl;
   if(!setFrameRate(new_ip,FrameRate))
   {
	std::cout<<"设置相机framerate失败."<<std::endl;
	ret =false;
}
else
    std::cout<<"设置相机framerate成功."<<std::endl;	
if(!setWDRswitch_level(new_ip,LDCSwitch,WDRSwitch,WDRLevel))
{
	std::cout<<"设置相机校正状态 宽动态失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机校正状态 宽动态成功."<<std::endl;
if(!setTextStatus(new_ip,textstatus,timestatus))
{
	std::cout<<"设置相机文字状态失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机文字状态成功."<<std::endl;

if(!set_LDClevel(new_ip,curLDClevel))
{
	std::cout<<"设置相机校正等级失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机校正等级成功."<<std::endl;

   return ret;
}




int main(int argc, char *argv[])
{
    curLDClevel=LDCLevel;
    if(argc>1)
    {
      int value =atoi(argv[1]);
      if(value>=0&&value<=255)
	  curLDClevel=value;    
}
    config_new_ip_camera();
    return 0;
}