#ifndef _IPCAM_CONFIG_H_
#define _IPCAM_CONFIG_H_

#include <string>
#include "inf_search_include/SearchDevice.h"
// #include "ipcam_settings.h"

class ipcam_config 
{
public:
   static bool config_one_ipCam(int setLDClevel=-1);
   static void dealloc();
   static bool on_config_ipcam_params(const char *ip,const int port=80);

private:
   static bool ipcam_config_default_ipaddr();
   static void after_config_one_ipCam(bool config_status);
   
   static bool on_config_ipcam_ip(const char* oldip,const char* newip);
   
   static bool set_expos_ScenceSelect(const char * ipaddr,int exposureMode, int scenceSelect);
   static bool setstreamMsg(const char *ipaddr,std::string resolution,int iprate,int payload, int frameRate);
   static bool setWDRswitch_level(const char *ipaddr,int ldcswitch,int wdrSwitch, int value);
   static bool set_LDClevel(const char *ipaddr,const int LDClevel);
   
   static bool setTextStatus(const char *ipaddr,int textstatus, int timestatus);
   
//    static void load_settings();

   
   
   static void log_camera_msg(const char *ip);
   static int count;
   static char old_ip[20];
   static int curLdclevel;
   static bool need_update_up;
   static int cur_http_port;
//    static ipcam_settings* settings;	
};


#endif