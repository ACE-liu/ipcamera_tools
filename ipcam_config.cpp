#include "include/ipcam_config.h"
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "include/ip_cam_CGI.h"
#include <string.h>

int ipcam_config::count =0;
char ipcam_config::old_ip[20]={0};
int ipcam_config::curLdclevel=50;
bool ipcam_config::need_update_up=false;
int ipcam_config::cur_http_port=80;
// ipcam_settings* ipcam_config::settings=NULL;
namespace
{
    const int http_port =80;
    char new_ip[64]="192.168.10.18";
    char gateway[64]="192.168.10.1";
    int  exposureMode=0;
    int scenceSelect=1;
    int FrameRate=15;
    int WDRSwitch=1; //kuandongtai
    int WDRLevel=80;
    int LDCSwitch=1; //jibianjiaozheng
    int LDCLevel=50;
    
    int textstatus=0;
    int timestatus=0;
    int iprate=10;
    std::string resolution ="1280x720";
    int payload =1;
}

// void ipcam_config::load_settings()
// {
//    std::string fileName="./ipcamera_cfg.xml";
//    settings=new ipcam_settings(fileName);
//    strcpy(new_ip,settings->new_ip.c_str());
//    strcpy(gateway,settings->gateway.c_str());
//    exposureMode=settings->exposureMode;
//    scenceSelect=settings->scenceSelect;
//    FrameRate=settings->FrameRate;
//    WDRSwitch=settings->WDRSwitch;
//    WDRLevel=settings->WDRLevel;
//    LDCSwitch=settings->LDCSwitch;
//    LDCLevel=settings->LDCLevel;
//    textstatus=settings->textstatus;
//    timestatus=settings->timestatus;
//    iprate=settings->iprate;
//    resolution=settings->resolution;
//    payload=settings->payload;
// }
void ipcam_config::dealloc()
{
//  if(settings!=NULL)
//  {
//     delete settings;
//     settings=NULL;
// }
}

bool ipcam_config::config_one_ipCam(int setLDClevel)
{
//   if(settings==NULL)
//      load_settings();
    
  if(setLDClevel>=0&&setLDClevel<=255)	
	  curLdclevel=setLDClevel;
  else
	  curLdclevel=LDCLevel;
  if(!ipcam_config_default_ipaddr())
  {
      return false;
  }
  if(need_update_up)
  {
    bool rtn=iim_ego::capturer::IPcam_CGI::set_defaultPortMsg(old_ip,cur_http_port);
    if(rtn)
	std::cout<<"配置http端口为 80成功！"<<std::endl;
}
else
{	
  bool status=on_config_ipcam_params(old_ip);
  on_config_ipcam_ip(old_ip,new_ip);
  after_config_one_ipCam(status);
  return true;
}
}




bool ipcam_config::on_config_ipcam_params(const char* ip,const int port)
{
   bool ret =true;
   
   //log
   log_camera_msg(ip);
   
   if(!set_expos_ScenceSelect(ip,exposureMode,scenceSelect))
   {
// 	std::cout<<"设置相机曝光模式 和场景失败."<<std::endl;
	ret =false;
	return ret;
}
else
    std::cout<<"设置相机曝光模式 和场景成功."<<std::endl;
   if(!setstreamMsg(ip,resolution,iprate,payload,FrameRate))
   {
// 	std::cout<<"设置相机rtsp流相关失败.."<<std::endl;
	ret =false;
	return ret;
}
else
    std::cout<<"设置相机rtsp流相关成功.."<<std::endl;	
if(!setWDRswitch_level(ip,LDCSwitch,WDRSwitch,WDRLevel))
{
// 	std::cout<<"设置相机校正状态 宽动态失败."<<std::endl;
	ret=false;
	return ret;
}
else
   std::cout<<"设置相机校正状态 宽动态成功."<<std::endl;
if(!setTextStatus(ip,textstatus,timestatus))
{
// 	std::cout<<"设置相机文字状态失败."<<std::endl;
	ret=false;
	return ret;
}
else
   std::cout<<"设置相机文字状态成功."<<std::endl;
if(!set_LDClevel(ip,curLdclevel))
{
// 	std::cout<<"设置相机校正等级失败."<<std::endl;
	ret=false;
	return ret;
}
else
   std::cout<<"设置相机校正等级成功."<<std::endl;

if(ret)
{
    std::cout <<"版本信息: "<<std::endl;
    iim_ego::capturer::IPcam_CGI::getDeviceInfo(ip);
}
        return ret;
}

bool ipcam_config::on_config_ipcam_ip(const char* oldip,const char* newip)
{
	bool ret=true;
  int result = NET_IPC_Modify_DeviceIP(oldip,newip,gateway,"255.255.255.0");
	       if(result == -1)
	      {
		   printf("Modify device ip address Error !\n");
		  ret=false;
	       }		
	NET_IPC_StopSearch();
	NET_IPC_Search_Cleanup();
	std::cout<<"---------------------配置ip成功---------------------------"<<std::endl;
        return ret;
}


bool ipcam_config::set_expos_ScenceSelect(const char *ipaddr,int exposureMode, int scenceSelect)
{
  iim_ego::capturer::CGICamExposureInfo cgiInfo;
  memset(&cgiInfo, 0x00, sizeof(iim_ego::capturer::CGICamExposureInfo));
  int nSlect[16] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
  cgiInfo.exposureMode=exposureMode;
  cgiInfo.scenceSelect = scenceSelect;
  return iim_ego::capturer::IPcam_CGI::setExposureMsg(ipaddr,cgiInfo,nSlect);  
}

bool ipcam_config::setstreamMsg(const char *ipaddr,std::string resolution,int iprate,int payload, int frameRate)
{
  bool ret;
  iim_ego::capturer::CGICamStreamInfo cgiInfo;
  memset(&cgiInfo, 0x00, sizeof(iim_ego::capturer::CGICamStreamInfo));
  int nSlect[8] = {0,0,1,1,1,0,0,1};	
  cgiInfo.FrameRate = frameRate;
  cgiInfo.Payload=payload;
  cgiInfo.IPRate=iprate;
  cgiInfo.Resolution=resolution;
  return iim_ego::capturer::IPcam_CGI::setStreamInfoMsg(ipaddr,cgiInfo,nSlect);
}


bool ipcam_config::setWDRswitch_level(const char *ipaddr,int ldcswitch,int wdrSwitch, int value)
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

bool ipcam_config::set_LDClevel(const char *ipaddr,const int LDClevel)
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

// http://ipaddr/cgi/camera_set?Channel=1&Group=BasicInfo&LDCSwitch=1&LDCLevel=130
bool ipcam_config::setTextStatus(const char *ipaddr,int textstatus, int timestatus)
{
  bool ret;
  iim_ego::capturer::CGICamOSDInfo osdInfo;
  memset(&osdInfo, 0x00, sizeof(iim_ego::capturer::CGICamOSDInfo));
  int nSlect[7] = {1,0,0,0,0,0,1};	
  osdInfo.TextOSDStatus = textstatus;
  osdInfo.TimeOSDStatus= timestatus;
  return iim_ego::capturer::IPcam_CGI::setCamOSDInfo(ipaddr,osdInfo,nSlect);
}


void ipcam_config::log_camera_msg(const char *ip)
{
   iim_ego::capturer::CGICamExposureInfo exposureInfo;
    iim_ego::capturer::CGICamBasicInfo basicInfo;
    iim_ego::capturer::CGICamStreamInfo streamInfo;
     iim_ego::capturer::CGICamOSDInfo osdInfo;
     if(iim_ego::capturer::IPcam_CGI::getExposureMsg(ip,exposureInfo))
          iim_ego::capturer::IPcam_CGI::log_params(exposureInfo);
     else
	  return;
     if(iim_ego::capturer::IPcam_CGI::getStreamInfoMsg(ip,streamInfo))
          iim_ego::capturer::IPcam_CGI::log_params(streamInfo);
     else 
	 return;
     if(iim_ego::capturer::IPcam_CGI::getDynamicRange(ip,basicInfo))
          iim_ego::capturer::IPcam_CGI::log_params(basicInfo);
     else
	  return;
     if(iim_ego::capturer::IPcam_CGI::getCamOSDInfo(ip,osdInfo))
          iim_ego::capturer::IPcam_CGI::log_params(osdInfo);
     else 
	     return;
      iim_ego::capturer::IPcam_CGI::getDeviceInfo(ip);
}

bool ipcam_config::ipcam_config_default_ipaddr()
{
   	int ret = 0;
	std::cout<<"开始搜索1网段相机..."<<std::endl;
	ret = NET_IPC_Search_Init();
	if(ret != RET_SUCCEED)
	{
		printf("Init Search Error !\n");
		return false;
	}
	/*send udp broadcast and receive udp broadcast*/
	NET_IPC_SearchDevice ("192.168.1.1", "192.168.1.255", 0);

	do
	{
		ret = NET_IPC_GetSearchPos();
// 		printf("\n======== ret = %d ========\n",ret);
		sleep(1);
	} while(ret != 100);	
	int searchNum = 0;
	DETECT_SHOW_INFO *ptr = NULL;

	char *detectData = NULL;
	detectData = (char *)malloc(10*sizeof(DETECT_SHOW_INFO));
	if(detectData == NULL)
	    return false;

	ptr = (DETECT_SHOW_INFO *)detectData;
	ret = NET_IPC_GetSearchInfo(detectData, &searchNum);
	if(ret != RET_SUCCEED||searchNum==0)
	{
		std::cout <<"未搜索到设备，请检查相机是否接好,机器ip是否在1网段！"<<std::endl;
		NET_IPC_Search_Cleanup();
		return false;
	}
	int i;
	memset(old_ip,0,sizeof(old_ip));
	std::cout<<"搜索到相机，ip为： "<<old_ip<<std::endl;
// 	printf("\n======== searchNum = %d ========\n",searchNum);
// 	for(i=0; i<searchNum; i++)
// 	{
// 		ptr += i*sizeof(DETECT_SHOW_INFO);	
		sprintf(old_ip,"%d.%d.%d.%d",ptr->iIpAddr[0],ptr->iIpAddr[1],ptr->iIpAddr[2],ptr->iIpAddr[3]);

		
// 	}
	if(ptr->iHttpPort!=http_port)
	{
	   std::cout<<"搜索到相机端口为： "<<ptr->iHttpPort<<std::endl;	
	   need_update_up=true;
	   cur_http_port=ptr->iHttpPort;
	}
	else
	   need_update_up=false;
	free(detectData);
        return true;
}


void ipcam_config::after_config_one_ipCam(bool config_status)
{
    if(config_status)
	count++;
    std::cout<<"已经成功配置: "<<count<<"台ip相机!"<<std::endl;
}
