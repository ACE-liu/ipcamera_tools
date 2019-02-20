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
}


bool ipcam_config::config_one_ipCam(int setLDClevel)
{
  if(setLDClevel>=0&&setLDClevel<=255)	
	  curLdclevel=setLDClevel;
  else
	  curLdclevel=LDCLevel;
  if(!ipcam_config_default_ipaddr())
  {
      return false;
  }
  bool status=on_config_ipcam_params();
  after_config_one_ipCam(status);
  return true;
}



bool ipcam_config::on_config_ipcam_params()
{
   bool ret =true;
   
   //log
   log_camera_msg();
   
   if(!set_expos_ScenceSelect(old_ip,exposureMode,scenceSelect))
   {
	std::cout<<"设置相机曝光模式 和场景失败."<<std::endl;
	ret =false;
}
else
    std::cout<<"设置相机曝光模式 和场景成功."<<std::endl;
   if(!setFrameRate(old_ip,FrameRate))
   {
	std::cout<<"设置相机framerate失败."<<std::endl;
	ret =false;
}
else
    std::cout<<"设置相机framerate成功."<<std::endl;	
if(!setWDRswitch_level(old_ip,LDCSwitch,WDRSwitch,WDRLevel))
{
	std::cout<<"设置相机校正状态 宽动态失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机校正状态 宽动态成功."<<std::endl;
if(!setTextStatus(old_ip,textstatus,timestatus))
{
	std::cout<<"设置相机文字状态失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机文字状态成功."<<std::endl;
if(!set_LDClevel(old_ip,curLdclevel))
{
	std::cout<<"设置相机校正等级失败."<<std::endl;
	ret=false;
}
else
   std::cout<<"设置相机校正等级成功."<<std::endl;
  int result = NET_IPC_Modify_DeviceIP(old_ip,new_ip,gateway,"255.255.255.0");
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

bool ipcam_config::setFrameRate(const char *ipaddr,int frameRate)
{
  bool ret;
  iim_ego::capturer::CGICamStreamInfo cgiInfo;
  memset(&cgiInfo, 0x00, sizeof(iim_ego::capturer::CGICamStreamInfo));
  int nSlect[7] = {0,0,1,0,0,0,0};	
  cgiInfo.FrameRate = frameRate;
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


void ipcam_config::log_camera_msg()
{
   iim_ego::capturer::CGICamExposureInfo exposureInfo;
    iim_ego::capturer::CGICamBasicInfo basicInfo;
    iim_ego::capturer::CGICamStreamInfo streamInfo;
     iim_ego::capturer::CGICamOSDInfo osdInfo;
     iim_ego::capturer::IPcam_CGI::getExposureMsg(old_ip,exposureInfo);
     iim_ego::capturer::IPcam_CGI::log_params(exposureInfo);
     iim_ego::capturer::IPcam_CGI::getStreamInfoMsg(old_ip,streamInfo);
     iim_ego::capturer::IPcam_CGI::log_params(streamInfo);
     iim_ego::capturer::IPcam_CGI::getDynamicRange(old_ip,basicInfo);
     iim_ego::capturer::IPcam_CGI::log_params(basicInfo);
     iim_ego::capturer::IPcam_CGI::getCamOSDInfo(old_ip,osdInfo);
     iim_ego::capturer::IPcam_CGI::log_params(osdInfo);
}

bool ipcam_config::ipcam_config_default_ipaddr()
{
   	int ret = 0;
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
// 	printf("\n======== searchNum = %d ========\n",searchNum);
// 	for(i=0; i<searchNum; i++)
// 	{
// 		ptr += i*sizeof(DETECT_SHOW_INFO);	
		sprintf(old_ip,"%d.%d.%d.%d",ptr->iIpAddr[0],ptr->iIpAddr[1],ptr->iIpAddr[2],ptr->iIpAddr[3]);

		
// 	}
	free(detectData);
        return true;
}


void ipcam_config::after_config_one_ipCam(bool config_status)
{
    if(config_status)
	count++;
    std::cout<<"已经成功配置: "<<count<<"台ip相机!"<<std::endl;
}
