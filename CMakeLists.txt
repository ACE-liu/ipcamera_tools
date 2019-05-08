cmake_minimum_required(VERSION 2.8.3)
set(prj_name "ipcam_config")
project(${prj_name})
add_compile_options(-std=c++11)

include_directories(inc/)
include_directories(include/)

INCLUDE_DIRECTORIES(/usr/include/curl)
INCLUDE_DIRECTORIES(/usr/include/libxml2)

set(head_libs "")


link_directories(lib)
set(inflib "libSearchDevice.a")

file(GLOB srcs
     ipcam_config.cpp
     ip_cam_CGI.cpp
#      ipcam_settings.cpp
 )
 list(APPEND inflib "curl;xml2")
 add_library(${prj_name} ${srcs})
target_link_libraries(${prj_name} ${inflib} ${head_libs} pthread)

add_executable(${prj_name}ip main.cpp)
target_link_libraries(${prj_name}ip ${prj_name} ${inflib} pthread)


add_executable(${prj_name}update main_update.cpp ip_cam_CGI.cpp)
target_link_libraries(${prj_name}update ${head_libs} curl xml2)


add_executable(bin_update main_bin_update.cpp ip_cam_CGI.cpp)
target_link_libraries(bin_update curl xml2)


add_executable(camera_msg main_msg.cpp ip_cam_CGI.cpp)
target_link_libraries(camera_msg curl xml2)

# add_executable(${prj_name}params main_config.cpp)
# target_link_libraries(${prj_name}params ${prj_name} ${inflib} pthread)