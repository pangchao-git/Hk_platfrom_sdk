//
// Created by Administrator on 2020/1/17.
//
#ifndef HIK_SDK_PLATFORM_PLATFROM_SERVER_H
#define HIK_SDK_PLATFORM_PLATFROM_SERVER_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <evhttp.h>
#include <event.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <map>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_compat.h>
#include <event2/http_struct.h>
#include <event2/http_compat.h>
#include <event2/util.h>
#include <event2/listener.h>
#include<memory>
#include <thread>
#include <atomic>
#include "Cjson.h"
#include "Sdk_Base.h"
using namespace std;
#define BUF_MAX 1024*16
#define MAX_LINE 100
#define MYHTTPD_SIGNATURE   "MoCarHttpd v0.1"
using namespace std;
typedef struct tag_cmd_data{
    char cmd[100]={0};
    char chanel[100]={0};
}cmd_data;
typedef struct tag_msg_data{
    int status;
    char *p_result;
}msg_data;
class Platfrom_Server {
public:
    Platfrom_Server();
    ~Platfrom_Server();
    //post请求处理函数
    void http_handler_post_msg(struct evhttp_request *req,void *arg);
    //get请求处理
    void http_handler_get_msg(struct evhttp_request *req,void *arg);
    int run_rtsp2hls(std::string channal);
    int watch_rtsp2hls(std::map<std::string,bool> m_rtsp_thred);
    int Parse_Cmd(const cmd_data &cmd_data_tmp,msg_data  &msg_data_tmp);
    //wrap for callback;
    static void wrap_http_get(struct evhttp_request *req,void *arg);
    static void wrap_http_post(struct evhttp_request *req,void *arg);
    static int wrap_run_rtsp2hls(std::string channal);
    static int wrap_watch_rtsp2hls(std::map<std::string,bool> m_rtsp_thred);
    void Server_start();
    void Get_snapimg(std::string channel,int img_w,int img_h,std::string save_path );
    struct evhttp *http_server = NULL;
private:
    std::shared_ptr<Sdk_Base> p_SDK_base;
    void get_post_message(struct evhttp_request *req);
    char *find_http_header(struct evhttp_request *req,
            struct evkeyvalq *params,const char *query_char);
    void Read_config(const char *path,char*buffer);
    std::string Channal2cmd(const std::string channal);
    std::string Channal2rtsp(const std::string channal);
    char file_name[100] ={0};
    char net_mac[100] ={0};
    char response_data[20]={0};
    //服务的ip和端口
    short m_http_port =56789;
    void Response(struct evhttp_request *req,msg_data &msg_data_tmp);
    void Set_json(cJSON *root,const msg_data &msg_data_tmp);
    int Mkdir_path(const string path);
    std::string m_http_addr = "0.0.0.0";
    static Platfrom_Server *m_this;
    cJSON *root=NULL;
    cJSON *m_Orgnazition_json=NULL;

    const char *m_cmd_data[4]={"Get_Orgnazition",
                             "Get_channel_status",
                             "Start_stream",
                             "Stop_stream"
                             };
    std::map<std::string,std::string> m_chanel_status;//通道号。在线状态
    std::map<std::string,std::string> m_chanel_rtsp;//通道号，rtsp命令
    std::map<std::string,bool> m_rtsp_thred;//通道号，rtsp2hls
    std::string m_rtsp_pre="rtsp://61.153.55.146:554/pag://172.26.15.15:7302:";
    std::string m_rtsp_end=":0:MAIN:TCP?cnid=1&pnid=1&auth=50";
    std::string m_Rtsp2Hls_cmd_start = "ffmpeg -y -loglevel quiet -rtsp_transport tcp -re -i";
    std::string m_Rtsp2Hls_cmd_end = "-codec copy -f hls -hls_flags delete_segments ";
    std::string m_save_pic_root = "D:/tmp/";
    int m_sleep_s = 5;
};


#endif //HIK_SDK_PLATFORM_PLATFROM_SERVER_H
