#include "include/ipcam_settings.h"
#include <opencv2/core/persistence.hpp>
#include <iostream>

ipcam_settings::ipcam_settings(const std::string& fileName)
{
   load(fileName);
}

ipcam_settings::ipcam_settings()
{
    new_ip="192.168.10.18";
     gateway="192.168.10.1";
     exposureMode=0;
     scenceSelect=1;
     FrameRate=15;
     WDRSwitch=1; //kuandongtai
     WDRLevel=50;
     LDCSwitch=1; //jibianjiaozheng
     LDCLevel=50;
    
     textstatus=0;
     timestatus=0;
     iprate=10;
     resolution ="1280x720";
     payload =1;
}


void ipcam_settings::load(const std::string& fileName)
{
   bool file_access=true;
   if(fileName.empty())
	file_access=false;
    cv::FileStorage fs(fileName.c_str(), cv::FileStorage::FORMAT_XML);
    if (!fs.isOpened())
    {
        file_access=false;
    }
    
    if(file_access)
    {
	   
     fs["new_ip"] >> new_ip;

    if (new_ip.length() > 0 && new_ip[0] == '"')
        new_ip = new_ip.substr(1, new_ip.length() - 2); 
    fs["gateway"] >> gateway;

    if (gateway.length() > 0 && gateway[0] == '"')
        gateway = gateway.substr(1, gateway.length() - 2); 
    fs["exposureMode"] >> exposureMode;
    fs["scenceSelect"] >> scenceSelect;
    fs["FrameRate"] >> FrameRate;
    fs["WDRSwitch"] >> WDRSwitch;
    fs["WDRLevel"] >> WDRLevel;
    fs["LDCSwitch"] >> LDCSwitch;
    fs["LDCLevel"] >> LDCLevel;
    fs["textstatus"] >> textstatus;
    fs["timestatus"] >> timestatus;
    fs["iprate"] >> iprate;
    fs["resolution"] >> resolution;
      if (resolution.length() > 0 && resolution[0] == '"')
        resolution = resolution.substr(1, resolution.length() - 2); 
    fs["payload"] >> payload;
     std::cout <<"配置文件存在，参数配置为：\n"<<*this<<std::endl;    
}
else
{ 
    new_ip="192.168.10.18";
     gateway="192.168.10.1";
     exposureMode=0;
     scenceSelect=1;
     FrameRate=15;
     WDRSwitch=1; //kuandongtai
     WDRLevel=50;
     LDCSwitch=1; //jibianjiaozheng
     LDCLevel=50;
    
     textstatus=0;
     timestatus=0;
     iprate=10;
     resolution ="1280x720";
     payload =1;
     std::cout <<"配置文件不存在，使用默认参数配置：\n"<<*this<<std::endl;
}
}

std::ostream& operator<<(std::ostream& os, const ipcam_settings& data)
{
   os<<"====================================================="<<std::endl;
   os << "相机ip: " <<data.new_ip<< std::endl;
    os << "相机网关: " <<data.gateway<< std::endl;
     os << "相机曝光模式: " <<data.exposureMode<< std::endl;
    os << "场景选择: " <<data.scenceSelect<< std::endl;
     os << "相机帧率: " <<data.FrameRate<< std::endl;
    os << "宽动态开关: " <<data.WDRSwitch<< std::endl;
    os << "宽动态等级: " <<data.WDRLevel<< std::endl;
     os << "畸变矫正开关: " <<data.LDCSwitch<< std::endl;
    os << "畸变矫正等级: " <<data.LDCLevel<< std::endl;
     os << "文字显示开关: " <<data.textstatus<< std::endl;
     os << "时间显示开关: " <<data.timestatus<< std::endl;
    os << "i帧p帧比率: " <<data.iprate<< std::endl;
     os << "图像分辨率: " <<data.resolution<< std::endl;
    os << "rtsp流编码格式: ";
    std::string type=data.payload==0?"h264":"h265";
    os<<type<<std::endl;
    os<<"====================================================="<<std::endl;
     return os;
}
