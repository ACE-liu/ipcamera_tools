#include <iostream>
#include "include/ipcam_config.h"
#include "signal.h"
#include <unistd.h>
#include <sys/time.h>


static bool ctrl_c_captured=false;

static void signal_callback(int sig)
{
   switch(sig)
   {
	   case SIGINT:
	   case SIGTERM:
		   ctrl_c_captured=true;
		   break;
}
}

static int checktime =300;
// int main(int argc, char **argv) {
//     bool status=false;
//     std::cout<<"--------设置相机ip-----------";
//     status=ipcam_config::config_one_ipCam();
//     if(status)
// 	 return 0;
//     else
// 	 return 1;
// }

int main(int argc, char **argv) {
    signal(SIGINT,signal_callback);
    signal(SIGTERM, signal_callback);
    bool status=false;
    double freeTime;
    int LDClevel=-1;
    int ifbreak=1;
    if(argc>1)
    {
       ifbreak=atoi(argv[1]);
}
    struct timeval start, end;
    gettimeofday(&start ,NULL);
    std::cout<<"配置ip为192.168.10.18的相机时请将本机ip切到10网段\n配置ip为192.168.1.18的相机时请将本机ip切到1网段\n"<<std::endl;
    char ip[32]="192.168.10.18";
    while(!ctrl_c_captured)
    {   
	std::cout<<"查找192.168.10.18相机..."<<std::endl;
	status =ipcam_config::on_config_ipcam_params(ip);
	if(!status)
	{
	    std::cout<<"查找192.168.1.18相机..."<<std::endl;
            status=ipcam_config::config_one_ipCam(LDClevel);
	}
	else
	   std::cout<<"配置相机参数成功..."<<std::endl;
// 	break;
	sleep(1);
	if(ifbreak==1)
	   break;
	if(status)
	    gettimeofday(&start ,NULL);
	gettimeofday(&end,NULL);
	freeTime=end.tv_sec-start.tv_sec;
	if(freeTime>checktime)
	{
	   std::cout<<"超过5分钟未进行检测，退出！"<<std::endl;
	   break;
	}
    }
    if(status)
       std::cout<<"配置成功..."<<std::endl;
    else
       std::cout<<"配置失败..."<<std::endl;
	    
    sleep(3);
    std::cout<<"退出！"<<std::endl;
    sleep(5);
    ipcam_config::dealloc();
    return 0;
}
