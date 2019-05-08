
#include "include/ip_cam_CGI.h"
#include <string.h>

static std::string new_ip ="192.168.10.18";











static void log_camera_msg()
{
   iim_ego::capturer::CGICamExposureInfo exposureInfo;
    iim_ego::capturer::CGICamBasicInfo basicInfo;
    iim_ego::capturer::CGICamStreamInfo streamInfo;
     iim_ego::capturer::CGICamOSDInfo osdInfo;

    if(iim_ego::capturer::IPcam_CGI::getExposureMsg(new_ip,exposureInfo))
        iim_ego::capturer::IPcam_CGI::log_params(exposureInfo);
    else
	std::cout<<"获取相机曝光信息失败，请检查相机是否接好..."<<std::endl;
    
    if(iim_ego::capturer::IPcam_CGI::getStreamInfoMsg(new_ip,streamInfo))
       iim_ego::capturer::IPcam_CGI::log_params(streamInfo);
    else
       std::cout<<"获取相机流信息失败，请检查相机是否接好..."<<std::endl;
     if(iim_ego::capturer::IPcam_CGI::getDynamicRange(new_ip,basicInfo))
        iim_ego::capturer::IPcam_CGI::log_params(basicInfo);
     else
	std::cout<<"获取相机宽动态相关信息失败，请检查相机是否接好..."<<std::endl;
     if(iim_ego::capturer::IPcam_CGI::getCamOSDInfo(new_ip,osdInfo))
        iim_ego::capturer::IPcam_CGI::log_params(osdInfo);
     iim_ego::capturer::IPcam_CGI::getDeviceInfo(new_ip);
}


int main(int argc,char *argv[])
{
   log_camera_msg();
   return 0;
}