#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include "../common/json.h"
using json = nlohmann::json;


struct req_key{
    std::string value;
};

// person -> json
void to_json(json& j, const req_key& p) {
    j = json{{"value", p.value}};
}

// json -> person
void from_json(const json& j, req_key& p) {
    j.at("value").get_to(p.value);
}


int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
 
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1316);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    struct linger optLinger  = {0};
    optLinger.l_onoff = 1;
    optLinger.l_linger = 1;

    int ret = setsockopt(sock,SOL_SOCKET,SO_LINGER,&optLinger,sizeof(optLinger));
    if(ret<0){
        close(sock);
        std::cout<<"init linger erroe!"<<std::endl;
    }
    
    req_key kv={"3.14"};

    json j=kv;

    auto p = j.get<req_key>();
 
    //添加一个存储为double的数字
    // std::string ss="";
    // for(int i=0;i<500;i++){
    //     ss += std::to_string(i);
    // }

    //std::cout<<ss<<std::endl;


    //j["pi"] = 3.144;

    std::string s = j.dump();
    const char *sendData;
    sendData = s.c_str();
    
    char buffer[4000];
    // for(int i=0;i<10;i++){
    //     buffer[i] = 'a'+i;
    // }
    buffer[10] = '\0';

    int count = 0;
    while(count<1){
        sleep(2);
        std::cout<<"send buffer..."<<strlen(sendData)<<std::endl;
        int len = send(sock,sendData,strlen(sendData),0);
        //std::cout<<"send length: "<<len<<std::endl;
        count++;
    }
    //读取服务器传回的数据
    // char buffer[40];
    // read(sock, buffer, sizeof(buffer)-1);
    sleep(1);
    // printf("Message form server: %s\n", buffer);
   
    //关闭套接字
    std::cout<<"close: "<<std::endl;
    close(sock);
    
    while(1){

    }

    //sleep(1);
 
    return 0;
}
