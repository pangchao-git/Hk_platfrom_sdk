//
// Created by Administrator on 2020/1/17.
//

#ifndef HIK_SDK_PLATFORM_SDK_BASE_H
#define HIK_SDK_PLATFORM_SDK_BASE_H

#include "HikPlatformSDK.h"
#include "HikPtSDK_define.h"
#include "cJSON.h"
#include <map>
#include <time.h>
class Sdk_Base {
public:
    Sdk_Base();
    ~Sdk_Base();
    int Sdk_Get_Orgnization( cJSON *p_root);
    int sdk_HikPt_Init();
    int sdk_HikPt_Login();
    int sdk_Destory();
    std::map<std::string,std::string> Get_status_map();
private:
    int sdk_QueryCamResource(cJSON *p_root);
    int sdk_HikPt_GetUserCellList(cJSON *p_root);
    void AddItemToJson(cJSON *p_root, cJSON **p_item, const char *bodyname);
    std::map<std::string,std::string> m_channel_status; // channel and status;
    HikLoginInfo  pLoginInfo ;
    HikCellInfo* pCellList = NULL;
    HikCameraInfo* pCameraList=NULL;
    HikUserOrg** pUserCellList=NULL;
};

#endif //HIK_SDK_PLATFORM_SDK_BASE_H
