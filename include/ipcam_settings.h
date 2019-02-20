#ifndef _IPCAM_SETTINGS_H_
#define _IPCAM_SETTINGS_H_

#include <string>
#include <ostream>

class ipcam_settings 
{
public:
   ipcam_settings();
   ipcam_settings(const std::string &fileName);
   friend std::ostream &operator<<(std::ostream& os,ipcam_settings const& data);
   
private:
   void load(const std::string & fileName);
public:
     std::string new_ip;
     std::string gateway;
     int  exposureMode=0;
     int scenceSelect=1;
     int FrameRate=15;
     int WDRSwitch=1; //kuandongtai
     int WDRLevel=50;
     int LDCSwitch=1; //jibianjiaozheng
     int LDCLevel=50;
    
     int textstatus=0;
     int timestatus=0;
     int iprate=10;
     std::string resolution;
     int payload =1;
};


std::ostream & operator<<(std::ostream& os, ipcam_settings const& data);




#endif