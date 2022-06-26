#include "heart_beat.h"
#include "manager.h"
#include <fcntl.h>       // fcntl()
#include <pthread.h>

//ms定时器
void sleep(int n) {
  struct timeval delay;
  delay.tv_sec = 0;
  delay.tv_usec = n * 1000;
  select(0, NULL, NULL, NULL, &delay);
}

//线程执行函数
void* start(void* arg){
    HeartBeat* ht = (HeartBeat*)arg;
    //连接
    ht->connectTask(get_ipport(ht->master_ipport),ht->masterfd_);
    //定时发送
    ht->heartBeatSend();
}

//开启线程
HeartBeat::HeartBeat(){
    pthread_create(&m_thread,0,start,this);
}

//向cfd写入json文件
int HeartBeat::WriteData(int& cfd,json js){
    int nwrite;
    int j = 0;
    string buf = js.dump();
    buf+='\0';
    nwrite = Write(cfd,(char*)buf.data(),buf.length()+1);
    return nwrite;
}

//没有连接成功则一直重复连接，超过了3次数退出
int HeartBeat::connectTask(ipport_pair oneip,int &cfd){
    int tryCount = 0;
    cfd = Socket(AF_INET,SOCK_STREAM,0);
    int ret  = setsockopt(cfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
    
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET,(oneip.ip.c_str()),&serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(oneip.port);

    //连接成功
    int n = connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(n<0){
        do{
            Close(cfd);
            cfd = Socket(AF_INET,SOCK_STREAM,0);
            ret = setsockopt(cfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
            n = connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
            sleep(1);
            if(n>0){
                break;
            }
            tryCount++;
            if(tryCount>3){
                //std::cout<<"connect master failed"<<std::endl;
                break;
            }
        }while(tryCount<=3);
    }

    return n;
}

//发送心跳包
void HeartBeat::heartBeatSend(){
    for(;;){
        json js;
        js["machineType"] = CACHE_SERVER;
        js["req_type"] = KEEP_ALIVE;
        js["data"] = json::object();
        string msg = js.dump();

        int tryCount  = 0;

        int ret = WriteData(masterfd_,js);
        if(ret<0){
                //std::cout<<"send failed"<<std::endl;
        }

        if(ret<0){
            std::cout<<"start Try reconnect"<<std::endl;
            int n = connectTask(get_ipport(master_ipport),masterfd_);
            ret = WriteData(masterfd_,js);
            if(ret<0){
                //std::cout<<"try send failed"<<std::endl;
            }
        }

        sleep(50);
    }
}

void HeartBeat::HeartStop(){
    pthread_join(m_thread,0);
}