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
    if(argc>1)
    {
       LDClevel=atoi(argv[1]);
}
    struct timeval start, end;
    gettimeofday(&start ,NULL);
    while(!ctrl_c_captured)
    {
        status=ipcam_config::config_one_ipCam(LDClevel);
// 	break;
	sleep(1);
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
    ipcam_config::dealloc();
    std::cout<<"退出！"<<std::endl;
    return 0;
}
