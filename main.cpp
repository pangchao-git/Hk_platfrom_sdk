#include <iostream>
#include <fstream>
#define example_sdk_base 0
#define example_plat_from_server 1
#if example_sdk_base
#include "include/Sdk_Base.h"
#endif
#if example_plat_from_server
#include "include/Platfrom_Server.h"
#endif
#include "windows.h"
#include "winsock2.h"


int main() {
    printf("test_start!\n");
    std::ofstream OutFile("camera_list1.txt",std::ios::trunc);
    OutFile<<"hello world!\n"<<std::endl;
    OutFile.close();
#if 1
#ifdef WIN32
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
#endif
# if example_sdk_base
    cJSON* root=NULL;
    root =cJSON_CreateObject();
    Sdk_Base sdk_base;
    sdk_base.sdk_HikPt_Init();
    if(0!= sdk_base.sdk_HikPt_Login()){
        printf("sdk login failed!\n");
        return -1;
    }
    if(0!=sdk_base.Sdk_Get_Orgnization(root)){
        printf("sdk_QueryCamResource  failed!\n");
        return -1;
    }
#endif
#if example_plat_from_server
    Platfrom_Server plat_server;
    plat_server.Server_start();

#endif
    return 0;
}