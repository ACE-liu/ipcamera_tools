#include "curl.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include "include/ip_cam_CGI.h"
#include <unistd.h>


#define GET_MSG 1

enum file_type
{
    IS_IFU=0,
    IS_BIN,
};
static std::string ip="192.168.10.18";
static file_type up_file_type;

size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
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

bool get_msg_bin(std::string const& url,bool status)
{
   if(url.empty())
    {
       std::cout<<"url or binName can not be empty."<<std::endl;
       return false;
    } 
    
    CURL *curl = NULL;  
    CURLcode code;  
   std::string response;
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
    }
    else
    {
// 	 (*logstream)(IIM_INFO)<<"curl init failed ."<<std::endl;
// 	 logstream->flush();
	 return false; 
    }  
    curl_easy_setopt(curl,CURLOPT_TCP_KEEPALIVE,1);
    
	 httpheaders = curl_slist_append(httpheaders, "Connection: Keep-Alive");
	 httpheaders = curl_slist_append(httpheaders, "Authorization: Basic YWRtaW46");
	 httpheaders = curl_slist_append(httpheaders, "Accept: text/plain, */*; q=0.01");
	 httpheaders = curl_slist_append(httpheaders, "X-Requested-With: XMLHttpRequest");
	 httpheaders = curl_slist_append(httpheaders, "User-Agent: Mozilla/5.0 (X11; Linux) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36");
         httpheaders = curl_slist_append(httpheaders, "Accept-Encoding: gzip, deflate");
         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheaders);
	 curl_easy_setopt(curl, CURLOPT_COOKIE ,"dev=188; BSDdev=0; ICEtype=0; SU=admin; jsLivePresetNo=0; jsLiveAutopanNo=0; jslivePatternNum=0; jsliveTourNum=0");
// 	 Referer: http://192.168.10.18/browse/top/roottop.asp?_=1550476848057
	 char referer[128]={0};
    if(status)	 
       sprintf(referer,"http://%s/browse/top/roottop.asp?_=1550476848057",ip.c_str());
    else
       sprintf(referer,"http://%s/browse/settings/sysInf.asp?_=1550476849606",ip.c_str());
    
    curl_easy_setopt (curl, CURLOPT_REFERER, referer); 

	 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData); 
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response); 
    code = curl_easy_perform(curl);  
    std::cout <<"response:\n"<<response<<std::endl;
    if (code != CURLE_OK)  
    {   
	 curl_easy_cleanup(curl);  
        return false;  
    }  
    curl_easy_cleanup(curl);  
      
    return true;  
    
}

bool post_killapp(const std::string &url)
{
    if(url.empty())
    {
       std::cout<<"url or binName can not be empty."<<std::endl;
       return false;
    } 
    CURL *curl = NULL;  
    CURLcode code;  
   std::string response;
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
    }
    else
    {
// 	 (*logstream)(IIM_INFO)<<"curl init failed ."<<std::endl;
// 	 logstream->flush();
	 return false; 
    }
    curl_easy_setopt(curl,CURLOPT_TCP_KEEPALIVE,1);
     curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);
    char host_str[64]={0};
    char origin[64]={0};
    char referer[128]={0};
    sprintf(host_str,"Host: %s",ip.c_str());
    sprintf(origin,"Origin: http://%s",ip.c_str());
    sprintf(referer,"http://%s/browse/settings/sysInf.asp?_=1548319075062",ip.c_str());
     httpheaders = curl_slist_append(httpheaders, "Connection: Keep-Alive");
     httpheaders = curl_slist_append(httpheaders, host_str);
     httpheaders = curl_slist_append(httpheaders, "Authorization: Basic YWRtaW46");
     httpheaders = curl_slist_append(httpheaders, "Accept: text/plain, */*; q=0.01");
     httpheaders = curl_slist_append(httpheaders, origin);
     httpheaders = curl_slist_append(httpheaders, "X-Requested-With: XMLHttpRequest");
     httpheaders = curl_slist_append(httpheaders, "Accept-Encoding: gzip, deflate");
     httpheaders = curl_slist_append(httpheaders, "Content-Length: 0");
     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheaders);

    curl_easy_setopt (curl, CURLOPT_REFERER, referer); 
    curl_easy_setopt(curl, CURLOPT_COOKIE ,"dev=188; BSDdev=0; ICEtype=0; SU=admin; jsLivePresetNo=0; jsLiveAutopanNo=0; jslivePatternNum=0; jsliveTourNum=0");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData); 
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response); 

      curl_easy_setopt(curl, CURLOPT_POST, 1); 
      std::cout <<"at kill form ....beform perform"<<std::endl;
       code = curl_easy_perform(curl);  
    std::cout <<"response:\n"<<response<<std::endl;
    if (code != CURLE_OK)  
    {  
	 curl_easy_cleanup(curl);  
        return false;  
    }  
    curl_easy_cleanup(curl);  
      
    return true;     
}
bool update_bin(const std::string &url,const std::string &binName)
{
   if(url.empty()||binName.empty())
    {
       std::cout<<"url or binName can not be empty."<<std::endl;
       return false;
    } 
    
    CURL *curl = NULL;  
    CURLcode code;  
   std::string response;
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
    }
    else
    {
// 	 (*logstream)(IIM_INFO)<<"curl init failed ."<<std::endl;
// 	 logstream->flush();
	 return false; 
    }
    
    struct curl_httppost* post =NULL;
    struct curl_httppost* last=NULL;
    

    
    //curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);  
   // curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0); 
      //curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl,CURLOPT_TCP_KEEPALIVE,1);
       curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2);
    char host_str[64]={0};
    char origin[64]={0};
    char referer[128]={0};
    sprintf(host_str,"Host: %s",ip.c_str());
    sprintf(origin,"Origin: http://%s",ip.c_str());
    sprintf(referer,"http://%s/browse/settings/sysInf.asp?_=1548319075062",ip.c_str());
	 //httpheaders = curl_slist_append(httpheaders, "Cache-Control: no-cache");
	 httpheaders = curl_slist_append(httpheaders, "Cache-Control: max-age=0");
	 httpheaders = curl_slist_append(httpheaders, "Connection: Keep-Alive");
      httpheaders = curl_slist_append(httpheaders, host_str);
	 httpheaders = curl_slist_append(httpheaders, origin);
	 httpheaders = curl_slist_append(httpheaders, "X-Requested-With: XMLHttpRequest");
	 httpheaders = curl_slist_append(httpheaders, "Accept-Encoding: gzip, deflate");
	 //httpheaders = curl_slist_append(httpheaders, "Expect: ");
	 // httpheaders = curl_slist_append(httpheaders, "Authorization: Basic YWRtaW46YWRtaW4=");
	 httpheaders = curl_slist_append(httpheaders, "Authorization: Basic YWRtaW46");
	 httpheaders = curl_slist_append(httpheaders, "Upgrade-Insecure-Requests: 1");
     httpheaders = curl_slist_append(httpheaders, "content-type: multipart/form-data"); 
         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheaders);

       curl_easy_setopt (curl, CURLOPT_REFERER, referer);  
       curl_easy_setopt(curl, CURLOPT_COOKIE ,"dev=188; BSDdev=0; ICEtype=0; SU=admin; jsLivePresetNo=0; jsLiveAutopanNo=0; jslivePatternNum=0; jsliveTourNum=0");
     
//      curl_easy_setopt(curl, CURLOPT_ENCODING, 'gzip,deflate');
     
   //  curl_easy_setopt(curl, CURLOPT_POST, true);
     
     curl_formadd(&post, &last, CURLFORM_PTRNAME, "language", CURLFORM_PTRCONTENTS, "cn", CURLFORM_END);
     if(up_file_type==IS_BIN)
         curl_formadd(&post, &last, CURLFORM_COPYNAME, "type",  CURLFORM_COPYCONTENTS, "bin", CURLFORM_END);
     else if(up_file_type==IS_IFU)
         curl_formadd(&post, &last, CURLFORM_COPYNAME, "type",  CURLFORM_COPYCONTENTS, "ifu", CURLFORM_END);
      curl_formadd(&post, &last, CURLFORM_COPYNAME, "reset", CURLFORM_COPYCONTENTS, "0", CURLFORM_END);
      curl_formadd(&post, &last, CURLFORM_PTRNAME, "fileName", CURLFORM_FILE, binName.c_str(), CURLFORM_END);  
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData); 
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response); 
      curl_easy_setopt(curl, CURLOPT_HTTPPOST,post);

 
    code = curl_easy_perform(curl);  
    std::cout <<"response:\n"<<response<<std::endl;
    if (code != CURLE_OK)  
    { 
	 curl_easy_cleanup(curl);
        return false;  
    }  
    curl_easy_cleanup(curl);  
      
    return true;   
}

const static int http_port =80;

int main(int argc, char **argv)
{

   std::string fileName;
   if(argc<=1)
   {
	std::cout<<"-i ipaddr  输入相机的ip地址，默认192.168.10.18\n"
	         <<"-f fileName 输出需要升级的.bin或.ifu文件的路径\n"
		 <<"-p port 输出相机http端口，默认80"
		 <<std::endl;
	return -1;
}
std::string cur_arg;

int port =80;
bool findip=false,findfile=false,get_file=false,findport=false;;
for(int i =1;i<argc;++i)
{
   cur_arg=argv[i];
   if(findip&&cur_arg!="-f"&&cur_arg!="-p")
   {
     ip=cur_arg; 
     findip=false;
     continue;
}
   else if(findfile&&cur_arg!="-i"&&cur_arg!="-p")
   {
      fileName=cur_arg;
      get_file=true;
      findfile=false;
      continue;
}
   else if(findport&&cur_arg!="-i"&&cur_arg!="-f")
   {
      port=atoi(cur_arg.c_str());
      findport=false;
      continue;
}
findip=false;
findfile=false; 
findport=false;
   if(cur_arg=="-i")
   {
    findip=true;
}
else if(cur_arg=="-f")
{
   findfile=true;	
}
else if(cur_arg=="-p")
{
   findport=true;	
}
}

if(!get_file)
{
   std::cout<<"未输入固件文件路径，升级失败."<<std::endl;
   return -1;
}

std::cout<<"ip: "<<ip<<"\nfile: "<<fileName<<"\nport: "<<port<<std::endl;

 
//  std::string url="http://192.168.10.18";
 // std::string url="http://192.168.10.18/browse/settings/sysInfC.asp?_=1548319075062";
  std::string url="http://"+ip+":"+std::to_string(port)+"/form/upload";
//  std::string url="http://192.168.10.18/browse/index.asp?id=1548831083055";
// std::string url ="127.0.0.1"
  std::string substr =fileName.substr(fileName.size()-4);
  std::cout <<"substr:  "<<substr<<std::endl;
  if(substr==".bin")
  {
    up_file_type=IS_BIN;
}
else if(substr==".ifu")
{
   std::cout<<"at form kill app form"<<std::endl;
    up_file_type=IS_IFU;
   std::string url1="http://"+ip+":"+std::to_string(port)+"/form/killAppForm";
   post_killapp(url1);
}
else
{
    std::cout <<"file is not a bin file."<<std::endl;
    return -1;
}
std::cout <<"固件升级中，请等待..."<<std::endl;
 if(update_bin(url,fileName)) 
	 std::cout <<"update success."<<std::endl;
 else
 {
	 std::cout <<"update failed."<<std::endl;
	 sleep(2);
	 return -1;
 }
 
#if GET_MSG
  get_msg_bin("http://"+ip+":"+std::to_string(port)+"/cgi/GetCameraTime?_=1550476909583",true);
  get_msg_bin("http://"+ip+":"+std::to_string(port)+"/cgi/modeCallStatus?_=1550476910089",true);
  get_msg_bin("http://"+ip+":"+std::to_string(port)+"/cgi/GetCameraTime?_=1550476911115",false);
#endif
  std::cout<<"固件上传成功！ 请等待..."<<std::endl;
  sleep(130);
  std::cout<<"升级结束，新的固件版本信息:"<<std::endl;
  iim_ego::capturer::IPcam_CGI::getDeviceInfo(ip,port);
  sleep(8);
  if(port!=80)
  {
     iim_ego::capturer::IPcam_CGI::set_defaultPortMsg(ip,port);
  }
 std::cout<<"设置端口完成,请将相机断电重启再使用...."<<std::endl;
 sleep(3);
  std::cout<<"退出..."<<std::endl;
  sleep(5);
 return 0;
}
