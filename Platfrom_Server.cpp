//
// Created by Administrator on 2020/1/17.
//
#include "include/Platfrom_Server.h"
#include <iostream>
#include <functional>
using namespace std;
Platfrom_Server* Platfrom_Server::m_this=NULL;
bool Autostream =false; //false为手动暂停拉流线程，true为将停止的拉流线程启动
Platfrom_Server::Platfrom_Server() {
    m_this=this;
    m_chanel_rtsp.clear();
    m_rtsp_thred.clear();

# if 1
    p_SDK_base = std::make_shared<Sdk_Base>();
    if(0!=p_SDK_base->sdk_HikPt_Init()){
        printf("sdk_HikPt_Init failed!\n");
        exit(-1);
    }
    if (0!=p_SDK_base->sdk_HikPt_Login()){
        printf("sdk_HikPt_Login failed!\n");
        exit(-1);
    }
    //获取组织架构
    m_Orgnazition_json =cJSON_CreateObject();
    if(0!= p_SDK_base->Sdk_Get_Orgnization(m_Orgnazition_json)){
        printf("sdk_QueryCamResource  failed!\n");
    }
    //获取状态
    m_chanel_status = p_SDK_base->Get_status_map();
#endif
}
void Platfrom_Server::Server_start()
{
    printf("server listening....\n");
    event_init();
    http_server = evhttp_start(m_http_addr.c_str(),m_http_port);
    if(http_server == NULL){
        printf("====line:%d,%s\n",__LINE__,"http server start failed.");
        exit(-1);
    }
    //设置请求超时时间(s)
    evhttp_set_timeout(http_server,5);
    //循环监听
    evhttp_set_cb(http_server,"/image_upload",Platfrom_Server::wrap_http_post,NULL);
    evhttp_set_cb(http_server,"/image_get",Platfrom_Server::wrap_http_get,NULL);
    event_dispatch();
    cout<<"event_dispatch\n"<<endl;
    evhttp_free(http_server);
}

Platfrom_Server::~Platfrom_Server() {
    if(m_this!=NULL){
        delete m_this;
        printf("delete m_this!\n");
    }
    p_SDK_base->sdk_Destory();
}

void Platfrom_Server::wrap_http_get(struct evhttp_request *req, void *arg) {
    m_this->http_handler_get_msg(req,arg);
}
void Platfrom_Server::wrap_http_post(struct evhttp_request *req, void *arg) {
    m_this->http_handler_post_msg(req,arg);
}
int Platfrom_Server::watch_rtsp2hls(std::map<std::string, bool> m_rtsp_thred) {
    //遍历map
    while(1)
    {
        sleep(m_sleep_s);
        std::map<std::string, bool>::iterator  it =m_rtsp_thred.begin();
        for(;it!=m_rtsp_thred.end();it++){
            if(it->second==false){
                //拉流thred
                std::thread start_thread(Platfrom_Server::wrap_run_rtsp2hls,it->first);
                start_thread.detach();
            }
        }
    }
}
int Platfrom_Server::wrap_watch_rtsp2hls(std::map<std::string, bool> m_rtsp_thred) {
    m_this->watch_rtsp2hls(m_rtsp_thred);
}
void Platfrom_Server::http_handler_get_msg(struct evhttp_request *req, void *arg)
{
     if(req == NULL){
         printf("====line:%d,%s\n",__LINE__,"input param req is null.");
         return;
     }
     msg_data msg_data_tmp;
     char *data = NULL;
     char *channel = NULL;
     struct evkeyvalq sign_params = {0};
     data = find_http_header(req,&sign_params,"cmd");//获取get请求uri中的cmd参数
     channel = find_http_header(req,&sign_params,"channel");
     cmd_data m_cmd_data;
     strcpy(m_cmd_data.chanel,channel);
     strcpy(m_cmd_data.cmd,data);
     printf("data form cmd is %s,channel=%s\n",data,channel);
     if(data == NULL){
         printf("====line:%d,%s\n",__LINE__,"request uri no param data.");
         return;
     }else{

         Parse_Cmd(m_cmd_data,msg_data_tmp);
     }
     //回响应
     Response(req,msg_data_tmp);
     static bool watch_flag =false;
     //开启守护线程
     if(!watch_flag){
         std::thread watch_thread(Platfrom_Server::wrap_watch_rtsp2hls,m_rtsp_thred);
         watch_thread.detach();
     }
}

int Platfrom_Server::run_rtsp2hls(std::string channal)
{
    bool isrun_rtsp2hls=true;
    std::string Rtsp2Hls_cmd = Channal2cmd(channal);
    std::cout<<"run_rtsp2hls Rtsp2Hls_cmd="<<Rtsp2Hls_cmd<<std::endl;
    m_chanel_rtsp.insert(std::make_pair(channal,Rtsp2Hls_cmd));
    m_rtsp_thred.insert(std::make_pair(channal,isrun_rtsp2hls));
    system(Rtsp2Hls_cmd.c_str());
    isrun_rtsp2hls=false;//执行到这一步说明cmd命令已经退出，没有在循环，转码程序结束
    m_rtsp_thred[channal]=isrun_rtsp2hls;
}

int Platfrom_Server::wrap_run_rtsp2hls(std::string channal) {
    m_this->run_rtsp2hls(channal);
    return 0;

}
int Platfrom_Server::Parse_Cmd(const cmd_data &cmd_data_tmp,msg_data  &msg_data_tmp) {
    const char *cmd=cmd_data_tmp.cmd;
    const char *chanel=cmd_data_tmp.chanel;
   if(0==strcmp(cmd,m_cmd_data[0]))
   {
#if 1
       std::string json_data_tmp=cJSON_PrintUnformatted(m_Orgnazition_json);
       //解决中文乱码
       const char* json_data = json_data_tmp.c_str();
       int data_len=strlen(json_data)+1;
       msg_data_tmp.p_result=(char*)malloc(sizeof(char)*data_len);
       if(NULL == msg_data_tmp.p_result){
           perror("malloc msg_data_tmp.p_result is failed!\n ");
           msg_data_tmp.status=-1;
           msg_data_tmp.p_result=NULL;
           return -1;
       }else{
           msg_data_tmp.status=0;
           memcpy(msg_data_tmp.p_result,json_data,data_len);
           return 0;
       }
#endif
   }
   else if(0==strcmp(cmd,m_cmd_data[1])){
       //通道状态
   }
   else if(0==strcmp(cmd,m_cmd_data[2])){
        //拉流
        //判断状态
       std::map<std::string, std::string>::iterator iter;
       iter = m_chanel_status.find(std::string(chanel));
       if(iter != m_chanel_status.end()){
           if("0" == iter->second){
               msg_data_tmp.status=-2;
               string reply_data="Channal  not Found!";
               int json_data = strlen(reply_data.c_str())+1;
               msg_data_tmp.p_result=(char*)malloc(json_data);
               memcpy(msg_data_tmp.p_result,reply_data.c_str(),json_data);
               cout<<"Do not Find"<<endl;
               return -1;
           }else{
               //创建线程
               cout<<"Find,the channel is "<<iter->first<<endl;
               std::thread rtsp_thread(Platfrom_Server::wrap_run_rtsp2hls,iter->first);
               std::cout<<"Rtsp2Hls_cmd_end"<<std::endl;
               rtsp_thread.detach();
               msg_data_tmp.status=0;
               string reply_data=Channal2cmd(iter->first);
               int json_data = strlen(reply_data.c_str())+1;
               msg_data_tmp.p_result=(char*)malloc(json_data);
               memcpy(msg_data_tmp.p_result,reply_data.c_str(),json_data);

               return 0;
           }

       }else{
           msg_data_tmp.status=-2;
           string reply_data="Channal  not Found!";
           int json_data = strlen(reply_data.c_str())+1;
           msg_data_tmp.p_result=(char*)malloc(json_data);
           memcpy(msg_data_tmp.p_result,reply_data.c_str(),json_data);
           cout<<"Do not Find"<<endl;
           return -1;
       }
   }
    else if(0==strcmp(cmd,m_cmd_data[3])){
        //暂停拉流
    }else{

    }
}
void Platfrom_Server::Read_config(const char *path,char*buffer){
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if((fp = fopen(path,"r")) == NULL)
    {
        perror("fail to read");
        exit (1) ;
    }
    while(fgets(buffer,MAX_LINE,fp) != NULL)
    {

#ifdef WIN32

#else
        len = strlen(buffer);
        buffer[len-1] = '\0';  /*去掉换行符*/
#endif
    }
    fclose(fp);
}

std::string Platfrom_Server::Channal2cmd(const std::string channal) {

    std::string rtsp_cmd=m_rtsp_pre+channal +m_rtsp_end+" transportmode=unicast";
    string hls_dir=m_save_pic_root+channal+"/";
    Mkdir_path(m_save_pic_root);
    Mkdir_path(hls_dir);
    std::string Rtsp2Hls_cmd=m_Rtsp2Hls_cmd_start+" "+"\""+rtsp_cmd+"\""+" "+m_Rtsp2Hls_cmd_end
                             +" "+"\""+hls_dir+"1.m3u8"+"\"";
    return Rtsp2Hls_cmd;
}
std::string Platfrom_Server::Channal2rtsp(const std::string channal) {
    std::string rtsp_cmd="\""+m_rtsp_pre+channal +m_rtsp_end+"\"";
    return rtsp_cmd;
}
void Platfrom_Server::Get_snapimg(std::string channel, int img_w, int img_h, std::string save_path) {
    //ffmpeg -i "rtsp://61.153.55.146:554/pag://172.26.15.15:7302:001774:0:MAIN:TCP?cnid=1&pnid=1&auth=50" -y -f image2 -t 0.001 -s 1280x720 test.jpg
    std::string size = std::to_string(img_w)+"x"+std::to_string(img_w);
    std::string current_time =";";
    std::string img_name = channel+"_"+current_time;
    std::string img_path = save_path+"/"+img_name;
    std::string cmd ="ffmpeg -i "+ Channal2rtsp(channel) + " -y -f image2 -t " + "0.001 "+ " -s " +size+" " +img_path;
    system(cmd.c_str());
}
void Platfrom_Server::http_handler_post_msg(struct evhttp_request *req, void *arg) {
    if(req == NULL)
    {
        printf("%s---->line:%d,%s\n",__FUNCTION__,__LINE__,"input param req is null.");
        return;
    }
    get_post_message(req);//获取请求数据，一般是json格式的数据
}
char* Platfrom_Server::find_http_header(struct evhttp_request *req, struct evkeyvalq *params, const char *query_char) {

    static int num=0;
    if(req == NULL || params == NULL || query_char == NULL)
    {
        printf("====line:%d,%s\n",__LINE__,"input params is null.");
        return NULL;
    }

    struct evhttp_uri *decoded = NULL;
    char *query = NULL;
    char *query_result = NULL;
    const char *path;
    const char *uri = evhttp_request_get_uri(req);//获取请求uri
    if(uri == NULL){
        printf("====line:%d,evhttp_request_get_uri return null\n",__LINE__);
        return NULL;
    }
    else{
        printf("Got a GET request:%s,the count=%d\n",uri,num);
    }
     num++;
    //解码uri
    decoded = evhttp_uri_parse(uri);
    if (!decoded){
        printf("====line:%d,It's not a good URI. Sending BADREQUEST\n",__LINE__);
        evhttp_send_error(req, HTTP_BADREQUEST, 0);
        return NULL;
    }

    //获取uri中的path部分
//    path = evhttp_uri_get_path(decoded);
//    if (path == NULL){
//        path = "/";
//    }
//    else{
//        printf("====line:%d,path is:%s\n",__LINE__,path);
//    }
    //获取uri中的参数部分
    query = (char*)evhttp_uri_get_query(decoded);
    if(query == NULL){
        printf("====line:%d,evhttp_uri_get_query return null\n",__LINE__);
        return NULL;
    }
    //查询指定参数的值
    evhttp_parse_query_str(query, params);
    query_result = (char*)evhttp_find_header(params, query_char);
    return query_result;
}
void Platfrom_Server::Set_json(cJSON *root,const msg_data &msg_data_tmp) {
    cJSON_AddNumberToObject(root, "status", msg_data_tmp.status);
    cJSON_AddStringToObject(root, "result", msg_data_tmp.p_result);
}
int Platfrom_Server::Mkdir_path(const string root_ts) {
    if(access(root_ts.c_str(),0)!=0){
        int ret = mkdir(root_ts.c_str());
        if(ret!=0){
            perror("mkdir failed!\n");
            return -1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}
void Platfrom_Server::Response(struct evhttp_request *req, msg_data &msg_data_tmp) {
    struct evbuffer *retbuff = NULL;
    retbuff = evbuffer_new();
    if(retbuff == NULL){
        printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
        return;
    }//获取json
    root = cJSON_CreateObject();
    Set_json(root,msg_data_tmp);
    char* reply_str = cJSON_Print(root);
//    char* reply_str = cJSON_Print(m_Orgnazition_json);
    evbuffer_add_printf(retbuff,reply_str);
    evhttp_send_reply(req,HTTP_OK,"Client",retbuff);
    evbuffer_free(retbuff);
    cJSON_Delete(root);
    root = NULL;
    //释放开辟的空间
    if(NULL!=msg_data_tmp.p_result){
        free(msg_data_tmp.p_result);
        msg_data_tmp.p_result=NULL;
    }
}
void Platfrom_Server::get_post_message(struct evhttp_request *req) {

    memset(file_name,0, sizeof(file_name)/sizeof(char));
    memset(net_mac,0, sizeof(net_mac)/sizeof(char));
    memset(response_data,0, sizeof(response_data)/sizeof(char));
    struct evkeyvalq *headers;
    struct evkeyval *header;
    struct evbuffer *evb = NULL;
    const char *uri = evhttp_request_get_uri(req);
    struct evhttp_uri *decoded = NULL;
    char *request_data_buf=NULL;
    headers = evhttp_request_get_input_headers(req);
    int i=0;
    //获取post的head信息
    for (header = headers->tqh_first; header; header = header->next.tqe_next)
    {
        if(i==3){
            memcpy(file_name ,header->value,strlen(header->value));
        }
        if(i==4){
            memcpy(net_mac ,header->value,strlen(header->value));
        }
        i++;
    }

    struct evkeyvalq sign_params = {0};
    char reply[100]={0};

    //判断此URI是否合法
    decoded = evhttp_uri_parse (uri);
    if (! decoded)
    {
        printf ("It's not a good URI. Sending BADREQUEST\n");
        evhttp_send_error (req, HTTP_BADREQUEST, 0);
        return;
    }
    //获取客户端上传的数据信息和大小
    struct evbuffer *buf_tmp = evhttp_request_get_input_buffer (req);
    char *payload = (char *) evbuffer_pullup (buf_tmp, -1);
    int post_data_len = evbuffer_get_length(buf_tmp);

    if(post_data_len<0){
        printf("upload_failed ,send masg to client\n");
        memset(response_data,0,strlen(response_data));
        memcpy(response_data,"postfile_failed",strlen("postfile_failed"));
    }else{
        request_data_buf = (char*)malloc(post_data_len);
        if(NULL==request_data_buf){
            perror("malloc error!\n");
            return ;
        }else{
            memset(response_data,0, sizeof(response_data));
            const char *reply =std::string("postfile_ok").c_str();
            memcpy(response_data,reply,strlen(reply));
        }
    }
    //保存http客户端上传的信息
    memcpy(request_data_buf, payload, post_data_len);
    /******
     进行业务逻辑开发
     * ***/
    evb = evbuffer_new ();
    printf("response_data=%s\n",response_data);
    evbuffer_add_printf(evb, response_data);
    //给客客户端发送响应
    evhttp_send_reply(req, HTTP_OK, "OK", evb);

    if (decoded)
        evhttp_uri_free (decoded);
    if (evb)
        evbuffer_free (evb);
    free(request_data_buf);
}