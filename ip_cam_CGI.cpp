#include "include/ip_cam_CGI.h"


// iim_ego::basis::logstream*
// iim_ego::capturer::IPcam_CGI::logstream =NULL;

bool iim_ego::capturer::IPcam_CGI::getDynamicRange(const std::string &ipaddr,CGICamBasicInfo &info)
{
   if(ipaddr.empty())
      return false;
   std::string data;  
   std::string url ="http://"+ipaddr+"/cgi/camera_get?Channel=1&Group=BasicInfo";
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed. getDynamicRange"<<std::endl;
//       logstream->flush();
      return false;
    }
    return xmlParseCameraMsg(data,"BasicInfo",true,(void*)&info);
	
}

// WDRSwitch 为
// 数字宽动态,WDRLevel 为宽动态等级,AFCSwitch 为伪彩消除状态,AFGSwitch
// 为透雾功能状态,LSCSwitch 为阴影校正状态,LDCSwitch 为畸变校正状态,
// DISSwitch 为数字防抖状态

bool iim_ego::capturer::IPcam_CGI::setDynamicRange(const std::string& ipaddr, const CGICamBasicInfo& info, const int nSlect[13])
{
   if(ipaddr.empty())
      return false;   
    std::string data;
   std::string url="http://"+ipaddr+"/cgi/camera_set?Channel=1&Group=BasicInfo";
    if(nSlect[0]==1)
   {
     url.append("&MirrorHor=");
     url+=std::to_string(info.MirrorHor);    
   }
    if(nSlect[1]==1)
   {
     url.append("&MirrorVer=");
     url+=std::to_string(info.MirrorVer);    
   }
    if(nSlect[2]==1)
   {
     url.append("&WDRSwitch=");
     url+=std::to_string(info.WDRSwitch);    
   }
    if(nSlect[3]==1)
   {
     url.append("&WDRLevel=");
     url+=std::to_string(info.WDRLevel);    
   }
    if(nSlect[4]==1)
   {
     url.append("&AFCSwitch=");
     url+=std::to_string(info.AFCSwitch);    
   }
    if(nSlect[5]==1)
   {
     url.append("&AFGSwitch=");
     url+=std::to_string(info.AFGSwitch);    
   }
    if(nSlect[6]==1)
   {
     url.append("&LSCSwitch=");
     url+=std::to_string(info.LSCSwitch);    
   }
    if(nSlect[7]==1)
   {
     url.append("&LDCSwitch=");
     url+=std::to_string(info.LDCSwitch);    
   }
    if(nSlect[8]==1)
   {
     url.append("&DISSwitch=");
     url+=std::to_string(info.DISSwitch);    
   }
    if(nSlect[9]==1)
   {
     url.append("&WBMode=");
     url+=std::to_string(info.WBMode);    
   }
    if(nSlect[10]==1)
   {
     url.append("&WBRGain=");
     url+=std::to_string(info.WBRGain);    
   }
    if(nSlect[11]==1)
   {
     url.append("&WBBGain="); 
     url+=std::to_string(info.WBBGain);    
   }
   if(nSlect[12]==1)
   {
     url.append("&LDCLevel="); 
     url+=std::to_string(info.LDCLevel);    
   }
    bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    if(!xmlParseCameraMsg(data,"BasicInfo",false, NULL))
    {
       std::cout<<"set dynamic range failed: "<<std::endl;
       return false;
//        logstream->flush();
    }
    return true;
}

bool iim_ego::capturer::IPcam_CGI::getCamOSDInfo(const std::string& ipaddr, iim_ego::capturer::CGICamOSDInfo& info)
{
   if(ipaddr.empty())
      return false;
   std::string data;
   std::string url ="http://"+ipaddr+"/cgi/image_get?Channel=1&Group=OSDInfo";
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    return xmlParseCameraMsg(data,"OSDInfo",true,(void*)&info);
}

bool iim_ego::capturer::IPcam_CGI::setCamOSDInfo(const std::string& ipaddr, const iim_ego::capturer::CGICamOSDInfo& info, const int nSelect[7])
{
   if(ipaddr.empty())
      return false;   
    std::string data;
   std::string url="http://"+ipaddr+"/cgi/image_set?Channel=1&Group=OSDInfo";
   if(nSelect[0]==1)
   {
     url.append("&TextOSDStatus=");
     url+=std::to_string(info.TextOSDStatus);    
   }
   if(nSelect[1]==1)
   {
     url.append("&TextOSDStatus1=");
     url+=std::to_string(info.TextOSDStatus1);    
   }
      if(nSelect[2]==1)
   {
     url.append("&TextOSDStatus2=");
     url+=std::to_string(info.TextOSDStatus2);    
   }
      if(nSelect[3]==1)
   {
     url.append("&TextOSDStatus3=");
     url+=std::to_string(info.TextOSDStatus3);    
   }
      if(nSelect[4]==1)
   {
     url.append("&TextOSDStatus4=");
     url+=std::to_string(info.TextOSDStatus4);    
   }
      if(nSelect[5]==1)
   {
     url.append("&MultipleOSDStatus=");
     url+=std::to_string(info.MultipleOSDStatus);    
   }
      if(nSelect[6]==1)
   {
     url.append("&TimeOSDStatus=");
     url+=std::to_string(info.TimeOSDStatus);    
   }
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    if(!xmlParseCameraMsg(data,"OSDInfo",false,NULL))
    {
         std::cout<<"set OSDInfo failed: "<<std::endl;
// 	 logstream->flush();
	 return false;
    }
//     else 
//         std::cout<<"set OSDInfo success."<<std::endl;
    return true;
}

bool iim_ego::capturer::IPcam_CGI::getExposureMsg(const std::string& ipaddr, CGICamExposureInfo& info)
{
   if(ipaddr.empty())
      return false;
   std::string data;
   std::string url ="http://"+ipaddr+"/cgi/camera_get?Channel=1&Group=ExposureInfo";
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    return xmlParseCameraMsg(data,"ExposureInfo",true,(void*)&info);
}

bool iim_ego::capturer::IPcam_CGI::getDeviceInfo(const std::__cxx11::string& ipaddr)
{
   if(ipaddr.empty())
      return false;
   std::string data;
   std::string url ="http://"+ipaddr+"/cgi/sys_get?Group=DeviceInfo";
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    std::cout<<data<<std::endl;
    return true;
}


// void iim_ego::capturer::IPcam_CGI::config_log_stream(iim_ego::basis::logstream* plogstream)
// {
//     iim_ego::capturer::IPcam_CGI::logstream =plogstream;
// }


// ExposureMode 为曝光模式取值 0—2;ScenceSelect 为场景选择,取
// 值 0 和 1;SlowShutter 为慢快门模式, 取值 1—25;AGCMax 为最大增益,取值  
// 1—64;AGCManual 为手动增益,取值 1—64;ShutterMax 为快门速度,取值为
// 25—8000;ShutterManual 为手动快门速度,取值为 25—8000,和 ShutterMax 不
// 能同时设置;ICREnable 为红外灯使能,取值为 0 和 1;ICRTimer 为切换时间,
// 取值为 1 到 15;HLCSwitch 为强光抑制;取值为 0—3;ELCLevel 为曝光补偿,
// 第 14 页取值为 0—255;ColorMode 为图像色彩,取值 0—2;ICRSwitch 为彩黑转换,取
// 值为 0—3;ICRC2BThr 和 CRB2CThr 分别为彩转黑阈值和黑转彩阈值,取值为
// 0—255

bool iim_ego::capturer::IPcam_CGI::setExposureMsg(const std::string& ipaddr, const CGICamExposureInfo& info, const int nSlect[16])
{
   if(ipaddr.empty())
      return false;   
    std::string data;
   std::string url="http://"+ipaddr+"/cgi/camera_set?Channel=1&Group=ExposureInfo";
   if(nSlect[0]==1)
   {
     url.append("&ExposureMode=");
     url+=std::to_string(info.exposureMode);    
   }
   if(nSlect[1]==1)
   {
     url.append("&ScenceSelect=");
     url+=std::to_string(info.scenceSelect);    
   }
   if(nSlect[2]==1)
   {
     url.append("&SlowShutter=");
     url+=std::to_string(info.slowShutter);    
   }
   if(nSlect[3]==1)
   {
     url.append("&AGCMax=");
     url+=std::to_string(info.agcMax);    
   }
   if(nSlect[4]==1)
   {
     url.append("&AGCManual=");
     url+=std::to_string(info.agcManual);    
   }
   if(nSlect[5]==1)
   {
     url.append("&ShutterMax=");
     url+=std::to_string(info.shutterManual);    
   }
   if(nSlect[6]==1)
   {
     url.append("&ShutterManual=");
     url+=std::to_string(info.shutterManual);    
   }
   if(nSlect[7]==1)
   {
     url.append("&ICREnable=");
     url+=std::to_string(info.ICREnable);    
   }
   if(nSlect[8]==1)
   {
     url.append("&ICRTimer=");
     url+=std::to_string(info.icrtTimer);    
   }
   if(nSlect[9]==1)
   {
     url.append("&HLCSwitch=");
     url+=std::to_string(info.hlcSwitch);    
   }
   if(nSlect[10]==1)
   {
     url.append("&ELCLevel=");
     url+=std::to_string(info.elcLevel);    
   }
   if(nSlect[11]==1)
   {
     url.append("&ColorMode=");
     url+=std::to_string(info.ColorMode);    
   }
   if(nSlect[12]==1)
   {
     url.append("&ICRSwitch=");
     url+=std::to_string(info.ICRSwitch);    
   }
   if(nSlect[13]==1)
   {
     url.append("&ICRC2BThr=");
     url+=std::to_string(info.ICRC2BThr);    
   }
   if(nSlect[14]==1)
   {
     url.append("&ICRB2CThr=");
     url+=(info.ICRB2CThr);    
   }
   if(nSlect[15]==1)
   {
     url.append("&BLCSwitch=");
     url+=std::to_string(info.BLCSwitch);    
   }
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    if(!xmlParseCameraMsg(data,"ExposureInfo",false,NULL))
    {
         std::cout<<"set exposureMsg failed: "<<std::endl;
// 	 logstream->flush();
	 return false;
    }
//     else 
//         std::cout<<"set exposureMsg success."<<std::endl;
    return true;
}

bool iim_ego::capturer::IPcam_CGI::getStreamInfoMsg(const std::string& ipaddr, iim_ego::capturer::CGICamStreamInfo& info)
{
   if(ipaddr.empty())
      return false;
   std::string data;
   std::string url ="http://"+ipaddr+"/cgi/major_stream_get?Channel=1&Group=StreamInfo";
   bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    return xmlParseCameraMsg(data,"StreamInfo",true,(void*)&info);

}

bool iim_ego::capturer::IPcam_CGI::setStreamInfoMsg(const std::string& ipaddr, const iim_ego::capturer::CGICamStreamInfo& info, const int nSlect[7])
{
    if(ipaddr.empty())  
      return false;   
    std::string data;
   std::string url="http://"+ipaddr+"/cgi/major_stream_set?Channel=1&Group=StreamInfo";
   if(nSlect[0]==1)
   {
     url.append("&BitRate=");
     url+=std::to_string(info.BitRate);    
   }
   if(nSlect[1]==1)
   {
     url.append("&BitType=");
     url+=std::to_string(info.BitType);    
   }
   if(nSlect[2]==1)
   {
     url.append("&FrameRate=");
     url+=std::to_string(info.FrameRate);    
   }
   if(nSlect[3]==1)
   {
     url.append("&IPRate=");
     url+=std::to_string(info.IPRate);    
   }
   if(nSlect[4]==1)
   {
     url.append("&Payload=");
     url+=std::to_string(info.Payload);    
   }
   if(nSlect[5]==1)
   {
     url.append("&StreamRateCut=");
     url+=std::to_string(info.StreamRateCut);    
   }
   if(nSlect[6]==1)
   {
     url.append("&VideoQuality=");
     url+=std::to_string(info.VideoQuality);    
   }
    bool ret=http_get_xmldata(url, data);
    if(!ret)
    {
//       (*logstream)(IIM_INFO) <<"http get failed."<<std::endl;
//       logstream->flush();
      return false;
    }
    if(!xmlParseCameraMsg(data,"StreamInfo",false,NULL))
    {
      std::cout<<"set streaminfo failed: "<<std::endl;
// 	  logstream->flush();
      return false;
    }
    return true;
}

bool iim_ego::capturer::IPcam_CGI::getDetailMegByNode(xmlNodePtr& node, const std::string& typeString, void* info)
{
      unsigned char* con;
      if(typeString=="ExposureInfo")
      {
	 CGICamExposureInfo *data =static_cast<CGICamExposureInfo*>(info);
         while(node!=NULL)
        {
	  if(xmlStrcasecmp(node->name,BAD_CAST"ExposureMode")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->exposureMode= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"ScenceSelect")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->scenceSelect= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"SlowShutter")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->slowShutter= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"AGCMax")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->agcMax= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"AGCManual")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->agcManual= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ShutterMax")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->shutterMax= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ShutterManual")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->shutterManual= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ICRSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->ICRSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ICREnable")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->ICREnable= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ICRTimer")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->icrtTimer= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ICRC2BThr")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->ICRC2BThr= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ICRB2CThr")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->ICRB2CThr=atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"ColorMode")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->ColorMode= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"HLCSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->hlcSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"BLCSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->BLCSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"ELCLevel")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->elcLevel= atoi(reinterpret_cast<char *>(con));
	  }
// 	  else 
// 	  {
// 	     (*logstream)(IIM_INFO)<<"xml parse --"<<typeString<<" get unexpected value:"<<node->name<<std::endl;
// 	     logstream->flush();
// 	  }
	  node=node->next;     
        }
      }	
      else if(typeString=="BasicInfo")
      {
	 CGICamBasicInfo *data =static_cast<CGICamBasicInfo*>(info);
         while(node!=NULL)
        {
            if(xmlStrcasecmp(node->name,BAD_CAST"MirrorHor")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->MirrorHor= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"MirrorVer")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->MirrorVer= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"WDRSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->WDRSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"WDRLevel")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->WDRLevel= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"AFCSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->AFCSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"AFGSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->AFGSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"LSCSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->LSCSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"LDCSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->LDCSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"DISSwitch")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->DISSwitch= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"WBMode")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->WBMode= atoi(reinterpret_cast<char *>(con));
	  }
	   else if(xmlStrcasecmp(node->name,BAD_CAST"WBRGain")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->WBRGain= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"WBBGain")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->WBBGain= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"LDCLevel")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->LDCLevel= atoi(reinterpret_cast<char *>(con));
	  }
// 	  else 
// 	  {
// 	     (*logstream)(IIM_INFO)<<"xml parse --"<<typeString<<" get unexpected value:"<<node->name<<std::endl;
// 	     logstream->flush();
// 	  }
	  node=node->next;  
	} 
      }
      else if(typeString=="StreamInfo")
      {
	 CGICamStreamInfo *data =static_cast<CGICamStreamInfo*>(info);
	 while(node!=NULL)
        {
	  if(xmlStrcasecmp(node->name,BAD_CAST"BitRate")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->BitRate= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"BitType")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->BitType= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"FrameRate")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->FrameRate= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"IPRate")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->IPRate= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"Payload")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->Payload= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"StreamRateCut")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->StreamRateCut= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"VideoQuality")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->VideoQuality= atoi(reinterpret_cast<char *>(con));
	  }
	  node=node->next; 
	}
      }
      else if(typeString=="OSDInfo")
      {
	 CGICamOSDInfo *data =static_cast<CGICamOSDInfo*>(info);    
       while(node!=NULL)
        {
	  if(xmlStrcasecmp(node->name,BAD_CAST"TextOSDStatus")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TextOSDStatus= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"TextOSDStatus1")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TextOSDStatus1= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"TextOSDStatus2")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TextOSDStatus2= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"TextOSDStatus3")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TextOSDStatus3= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"TextOSDStatus4")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TextOSDStatus4= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"MultipleOSDStatus")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->MultipleOSDStatus= atoi(reinterpret_cast<char *>(con));
	  }
	  else if(xmlStrcasecmp(node->name,BAD_CAST"TimeOSDStatus")==0)
	  {
	      con=xmlNodeGetContent(node);
	      data->TimeOSDStatus= atoi(reinterpret_cast<char *>(con));
	  }
	   node=node->next; 
	}
}
      return true;
}

bool iim_ego::capturer::IPcam_CGI::http_get_xmldata(const std::string& url, std::string& rtn)
{
   if(url.empty())
    {
       std::cout<<"url can not be empty."<<std::endl;
       return false;
    } 
    
    CURL *curl = NULL;  
    CURLcode code;  
    struct curl_slist* httpheaders = NULL;
    curl_global_init(CURL_GLOBAL_DEFAULT);  
     curl = curl_easy_init();    
    if (curl)
    {
	code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  
        if (code != CURLE_OK)  
        {  
//            (*logstream)(IIM_INFO) << " Failed to set URL "  << std::endl;  
// 	   logstream->flush();
            return false;  
        }
        code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
       if (code != CURLE_OK)  
       {  
//           (*logstream)(IIM_INFO) << " Failed to set redirect option "  << std::endl;  
// 	  logstream->flush();
          return false;  
       }
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&rtn); 
    }
    else
    {
// 	 (*logstream)(IIM_INFO)<<"curl init failed ."<<std::endl;
// 	 logstream->flush();
	 return false; 
    }
    
     httpheaders = curl_slist_append(httpheaders, "Authorization: Basic YWRtaW46YWRtaW4=");
     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheaders);
    
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);  
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2); 
     curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
 
    code = curl_easy_perform(curl);  
    if (code != CURLE_OK)  
    {         
        return false;  
    }  
    curl_easy_cleanup(curl);  
      
    return true;  
}

void iim_ego::capturer::IPcam_CGI::log_params(const iim_ego::capturer::CGICamOSDInfo& OSDinfo)
{
  printf("======== TextOSDStatus = %d \n",OSDinfo.TextOSDStatus);
  printf("======== TextOSDStatus1 = %d \n",OSDinfo.TextOSDStatus1);	
  printf("======== TextOSDStatus2 = %d \n",OSDinfo.TextOSDStatus2);
  printf("======== TextOSDStatus3 = %d \n",OSDinfo.TextOSDStatus3);
  printf("======== TextOSDStatus4 = %d \n",OSDinfo.TextOSDStatus4);	
  printf("======== MultipleOSDStatus = %d \n",OSDinfo.MultipleOSDStatus);	
  printf("======== TimeOSDStatus = %d \n",OSDinfo.TimeOSDStatus);	
}


void iim_ego::capturer::IPcam_CGI::log_params(const CGICamExposureInfo& cgiInfo)
{
  printf("\n======== exposureMode = %d \n",cgiInfo.exposureMode);	
  printf("======== scenceSelect = %d \n",cgiInfo.scenceSelect);	
    printf("======== slowShutter = %d \n",cgiInfo.slowShutter);	
  printf("======== agcMax = %d \n",cgiInfo.agcMax);	
  printf("======== agcManual = %d \n",cgiInfo.agcManual);	
  printf("======== shutterMax = %d \n",cgiInfo.shutterMax);	
  printf("======== shutterManual = %d \n",cgiInfo.shutterManual);	
  printf("======== icrtSwitch = %d \n",cgiInfo.ICRSwitch);	
  printf("======== ICREnable = %d \n",cgiInfo.ICREnable);
  printf("======== icrtTimer = %d \n",cgiInfo.icrtTimer);	
  printf("======== ICRC2BThr = %d \n",cgiInfo.ICRC2BThr);
  printf("======== ICRB2CThr = %d \n",cgiInfo.ICRB2CThr);
  printf("======== blcSwitch = %d \n",cgiInfo.BLCSwitch);	
  printf("======== hlcSwitch = %d \n",cgiInfo.hlcSwitch);	
  printf("======== elcLevel = %d \n",cgiInfo.elcLevel);	
   printf("======== ColorMode = %d \n",cgiInfo.ColorMode);	
}

void iim_ego::capturer::IPcam_CGI::log_params(const CGICamBasicInfo& basicinfo)
{
  printf("\n======== MirrorHor = %d \n",basicinfo.MirrorHor);	
  printf("======== MirrorVer = %d \n",basicinfo.MirrorVer);	
  printf("======== WDRSwitch = %d \n",basicinfo.WDRSwitch);	
  printf("======== WDRLevel = %d \n",basicinfo.WDRLevel);	
  printf("======== AFCSwitch = %d \n",basicinfo.AFCSwitch);	
  printf("======== AFGSwitch = %d \n",basicinfo.AFGSwitch);	
  printf("======== LSCSwitch = %d \n",basicinfo.LSCSwitch);	
  printf("======== LDCSwitch = %d \n",basicinfo.LDCSwitch);	
  printf("======== LDCLevel = %d \n",basicinfo.LDCLevel);
  printf("======== DISSwitch = %d \n",basicinfo.DISSwitch);
  printf("======== WBMode = %d \n",basicinfo.WBMode);	
  printf("======== WBRGain = %d \n",basicinfo.WBRGain);
  printf("======== WBBGain = %d \n",basicinfo.WBBGain);
   
}

void iim_ego::capturer::IPcam_CGI::log_params(const iim_ego::capturer::CGICamStreamInfo& streamInfo)
{
  printf("\n======== BitRate = %d \n",streamInfo.BitRate);	
  printf("======== BitType = %d \n",streamInfo.BitType);	
  printf("======== FrameRate = %d \n",streamInfo.FrameRate);	
  printf("======== IPRate = %d \n",streamInfo.IPRate);	
  printf("======== Payload = %d \n",streamInfo.Payload);	
  printf("======== StreamRateCut = %d \n",streamInfo.StreamRateCut);	
  printf("======== VideoQuality = %d \n",streamInfo.VideoQuality);	
}

bool iim_ego::capturer::IPcam_CGI::xmlParseCameraMsg(const std::string& data, const std::string& typestring, bool if_parse, void* info)
{
    xmlDocPtr doc=NULL;
    xmlNodePtr node = NULL;
    xmlKeepBlanksDefault(0);
    doc = xmlParseMemory(data.c_str(),data.size());  
  
    if(NULL  == doc) {  
//       (*logstream)(IIM_INFO)<<"doc is nullptr parse error\n";  
//       logstream->flush();
      return false;
    }  
    node =xmlDocGetRootElement(doc);
    if(node == NULL) {  
//         (*logstream)(IIM_INFO)<<"root error!\n";
// 	logstream->flush();
        xmlFreeDoc(doc);  
        return false;  
    }  
    bool ifok=false;
    
    node = node->children;  
    while(node != NULL) {  
	   if(!ifok&&xmlStrcasecmp(node->name,BAD_CAST"result")==0)
	   {		  
	      xmlChar* pro=xmlGetProp(node,BAD_CAST"code");
	      xmlChar* con =xmlNodeGetContent(node);
	      if(!pro&&xmlStrcasecmp(con,BAD_CAST"Successfully")!=0)
	      {
		      break;
	      }
	      if(xmlStrcasecmp(pro,BAD_CAST"200")==0)
	      {
		  ifok=true; 
		  if(!if_parse)
		     break;
		  node=node->next;
                  
	      }
	      else
	      {
		     ifok=false;
		     break;
	      }
	   }
	  else if(ifok&&xmlStrcasecmp(node->name,BAD_CAST(typestring.c_str()))==0)
	  {
	      node=node->children;	      
	      ifok=getDetailMegByNode(node,typestring,info);
	      break;
	  }
	  else
            node = node->next;  
    }
    xmlFreeDoc(doc);    
    return ifok;	
}

size_t iim_ego::capturer::IPcam_CGI::OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = static_cast<std::string*>(lpVoid);  
    if( NULL == str || NULL == buffer )  
    {  
        return -1;  
    }  
  
    char* pData = (char*)buffer;  
    str->append(pData, size * nmemb);  
    return nmemb; 
}
