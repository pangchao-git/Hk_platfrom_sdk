//
// Created by Administrator on 2020/1/17.
//

#include "include/Sdk_Base.h"
#include <iostream>
#include<fstream>
using namespace std;
Sdk_Base::Sdk_Base() {
    m_channel_status.clear();
    printf("sdk create!\n");
}
Sdk_Base::~Sdk_Base() {

}
int Sdk_Base::sdk_HikPt_Init() {

    int ret = HikPt_Init();
    if(ret==0){
        printf("sdk init successful!\n");
    }else{
        printf("sdk init failed!\n");
    }
    char msg[512]={0};
    long ret_error =HikPt_GetLastError(msg,512);
    printf("init_error_code=%d\n",ret_error);
    printf("msg=%s\n",msg);
    return ret ;
}
int Sdk_Base::sdk_HikPt_Login() {

    strcpy(pLoginInfo.szServerUrl,"61.153.55.146");
    pLoginInfo.uServerPort = 8090;
    strcpy(pLoginInfo.szUserName,"admin");
    strcpy(pLoginInfo.szPassword,"sykj12345");
    int ret = HikPt_Login(&pLoginInfo);
    printf("ret=%d\n",ret);
    if(ret!=0){
        printf("login error,!\n");
    }
    return ret;

}
void Sdk_Base::AddItemToJson(cJSON *p_root, cJSON **p_item, const char *bodyname) {

        *p_item= cJSON_CreateObject();
        cJSON_AddItemToObject(p_root, bodyname,*p_item );
}
//获取用户组织树列表
int Sdk_Base::sdk_HikPt_GetUserCellList(cJSON *p_root) {
    int iErrNum = 0;
    HikUserOrg* pUserCellList = NULL;

    if (HikPt_GetUserCellList(&pUserCellList,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK && pUserCellList != NULL)
    {
        HikUserOrg* pTemp = pUserCellList;
        while (NULL != pTemp)
        {
            int Id = pTemp->nID;
            std::string Name = pTemp->szOrgName;
            int high = pTemp->nParentID;

            HikPlatformUser* pUserList = NULL;
            if(HikPt_GetUserListByCellId(&pUserList,pTemp->nID) == HIKPT_E_OK && pUserList != NULL)
            {
                HikPlatformUser* pTempU = pUserList;
                while(pTempU != NULL)
                {
                    int Id = pTempU->nId;
                    std::string Name = pTempU->szName;
                    pTempU = pTempU->pNext;
                }
                HikPt_FreeUserList(pUserList);
            }
            pTemp = pTemp->pNext;
        }
    }
    else
    {
        iErrNum = HikPt_GetLastError(NULL,512);
    }

    if(pUserCellList != NULL)
    {
        HikPt_FreeUserCellList(pUserCellList);
    }
}
int Sdk_Base::sdk_QueryCamResource(cJSON *p_root) {
    m_channel_status.clear();
    ofstream OutFile("camera_list.txt",std::ios::trunc);
    ofstream OutFile_Json("camera_list_json.txt",std::ios::trunc);
    //组装复杂json
    cJSON *p_body;
    cJSON *p_body_child;
    int iErrNum = 0;
    HikCellInfo* pCellList = NULL;
    if (HikPt_GetResCellList(&pCellList,HIK_WBS_OPCODE_PLAYVIEW,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK)
    {
        HikCellInfo* pTemp = pCellList;//组织树信息
        while (NULL != pTemp)
        {
            int Id = pTemp->nId;
            std::string Name = pTemp->szCellName;
            printf("parent_name=%s\n",pTemp->szCellName);
            printf("centor_name=%s\n",pTemp->szCascCode);
            AddItemToJson(p_root,&p_body,pTemp->szCellName);//添加parent,
            int high = pTemp->nParentId;
            HikCameraInfo* pCameraList = NULL;
            if(HikPt_GetCameraListByCellId(&pCameraList,pTemp->nId,HIK_WBS_OPCODE_PLAYVIEW) == HIKPT_E_OK && pCameraList != NULL)
            {
                HikCameraInfo* pTempc = pCameraList;
                while(NULL != pTempc)
                {
                    int Id = pTempc->nCamId;
                    std::string Name = pTempc->szCameraName;
                    int high = pTempc->nCellId;
                    printf("pTempc->name=%s\n",Name.c_str());
                   //通道 在线状态判断
                   bool online = pTempc->bOnlineStatus;
                   string online_str;
                   online ==false? online_str="0":online_str="1";
                   auto status = std::make_pair(pTempc->szIndexCode,online_str);
                   m_channel_status.insert(status);
                   OutFile<<Id<<":"<<pTemp->szCellName<<":"<<pTempc->szCameraName<<":"<<pTempc->szIndexCode<<":"<<online_str<<endl;
                   AddItemToJson(p_body,&p_body_child,pTempc->szCameraName);//添加parent,
                   cJSON_AddNumberToObject(p_body_child,"Id",pTempc->nCamId);
//                   cJSON_AddStringToObject(p_body,"Child_name",pTempc->szCameraName);
                   cJSON_AddStringToObject(p_body_child,"Channal_num",pTempc->szIndexCode);
                   cJSON_AddStringToObject(p_body_child,"online_status",online_str.c_str());
                   pTempc = pTempc->pNext;
                }
                HikPt_FreeCameraList(pCameraList);
            }
            pTemp = pTemp->pNext;
        }
    }
    else
    {
        iErrNum = HikPt_GetLastError(NULL, 512);
        return -1;

    }
    if(pCellList != NULL)
    {
        HikPt_FreeResCellList(pCellList);
    }
    char *json_data = cJSON_PrintUnformatted(p_root);
    OutFile_Json<<json_data<<endl;
    OutFile_Json.close();
    OutFile.close();
    printf("get camera list end!\n");
    return 0;
}

int Sdk_Base::Sdk_Get_Orgnization(cJSON *p_root) {
    clock_t   start,   finish;
    printf("start to count time\n");
    start =clock();
    if(0!=sdk_QueryCamResource(p_root)){
        perror("sdk_QueryCamResource!\n");
        return -1;
    }
    finish = clock();
    printf("%f seconds\n",((double)(finish-start)/CLOCKS_PER_SEC)/60);
    return 0;
}
std::map<std::string,std::string> Sdk_Base::Get_status_map() {
    return m_channel_status;
}

int Sdk_Base::sdk_Destory() {
    if(0!=HikPt_Logout()){
        return -1;
    }
    if(0!=HikPt_Uninit()){
        return -1;
    }
    return -1;
}