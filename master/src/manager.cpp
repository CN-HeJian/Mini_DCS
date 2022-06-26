//
// Created by admin on 2022/5/13.
//

#include "manager.h"

Manager * Manager::m_SingleInstance = NULL;
std::mutex Manager::m_mutex;

string Manager::getWhichCacheServer(string key){
    return "";
}

void Manager::init(){
    server->start();
}

Manager* Manager::GetInstance(){
    if(m_SingleInstance==NULL){
        std::unique_lock<std::mutex> lock(m_mutex);
        if(m_SingleInstance==NULL){
            m_SingleInstance = new Manager();
            m_SingleInstance->server = new NetServer(7000, 3, 2000, false, 1);        
        }
    }
    return m_SingleInstance;
}

void Manager::deleteInstance(){
    std::unique_lock<std::mutex> lock(m_mutex);
    if(m_SingleInstance){
        delete m_SingleInstance;
        m_SingleInstance = NULL;
    }
}

//===================================================================client===========================================================//
void Manager::clientGetDistribution(struct sockaddr_in &_addr){
    json j;
    j["machineType"] = MASTER;
    j["req_type"] = DISTRIBUTION_RESPONSE;
    vector<string> allIpPorts;
    for (size_t i = 0; i < ipPortLs.size(); i++){
        string oneCacheServer = ipLs[i]+":"+to_string(portLs[i]);
        allIpPorts.push_back(oneCacheServer);
    }
    j["data"]["iplist"] = allIpPorts;
    //std::cout<<"clientGetDistribution"<<std::endl;
    std::string s = j.dump();
    for(auto &c:server->users_){
        if(c.second.getAddr().sin_port==_addr.sin_port && c.second.getAddr().sin_addr.s_addr == _addr.sin_addr.s_addr){
            c.second.connnectionSend(s);
        }
    }
}


//===========================================cacheServer==========================================//

//处理心跳包
void Manager::cacheServerKeepAlive(struct sockaddr_in &_addr){
    char * client_ip = inet_ntoa(_addr.sin_addr);
    string strIp = client_ip;
    int client_port = ntohs(_addr.sin_port);
    string strPort = std::to_string(client_port);
    string ipPortStr = strIp+":"+strPort;

    unique_lock<mutex> lock(m_sourceMutex);
    int fd = findFdAcrAddr(_addr);
    
    //已经建立连接的心跳包!!!
    if(cacheServersMp.find(ipPortStr)!=cacheServersMp.end()){
        //重置定时器
        server->timer_->update(fd,150);
    }else{
        ipPortLs.push_back(ipPortStr);
        ipLs.push_back(strIp);
        portLs.push_back(client_port);
        cacheServersMp.insert({ipPortStr,0});
        //添加定时器
        server->timer_->addTimer(fd,150,std::bind(&Manager::someCacheServerLost,this,_addr));
        //通知CacheServer
        notifyCacheServer();
    }
}

//根据地址获取这个连接的文件描述符
int Manager::findFdAcrAddr(struct sockaddr_in & _addr){
    for(auto &c:server->users_){
        if(c.second.getAddr().sin_port==_addr.sin_port && c.second.getAddr().sin_addr.s_addr == _addr.sin_addr.s_addr){
            return c.second.getFd();
        }
    }
    return -1;
}

//主动关闭一个服务器！！！
void Manager::shutDownOneMachine(struct sockaddr_in& _addr){

}

//有一个缓存服务器掉线了
void Manager::someCacheServerLost(struct sockaddr_in&_addr){
    //超时就需要移除
    std::cout<<"Manager::someCacheServerLost: "<<std::endl;
    exit(-1);
}

//通知其他服务器缓存服务器更新
void Manager::notifyCacheServer(){
    json j;
    for(int i=0;i<ipLs.size();i++){
        j.push_back({ipLs[i], portLs[i]});
    }
    std::string s = j.dump();
    for(auto &c:server->users_){
        std::cout<<"notifyCacheServer"<<std::endl;
        c.second.connnectionSend(s);
    }
}
