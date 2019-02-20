#ifndef _IPCAM_CONFIG_H_
#define _IPCAM_CONFIG_H_

#include <string>
#include "inf_search_include/SearchDevice.h"

class ipcam_config 
{
public:
   static bool config_one_ipCam(int setLDClevel=-1);


private:
   static bool ipcam_config_default_ipaddr();
   static void after_config_one_ipCam(bool config_status);
   static bool on_config_ipcam_params();
   
   static bool set_expos_ScenceSelect(const char * ipaddr,int exposureMode, int scenceSelect);
   static bool setFrameRate(const char *ipaddr,int frameRate);
   static bool setWDRswitch_level(const char *ipaddr,int ldcswitch,int wdrSwitch, int value);
   static bool set_LDClevel(const char *ipaddr,const int LDClevel);
   
   static bool setTextStatus(const char *ipaddr,int textstatus, int timestatus);
   
   
   static void log_camera_msg();
   static int count;
   static char old_ip[20];
   static int curLdclevel;
	
};


#endif