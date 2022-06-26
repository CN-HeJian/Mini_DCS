#ifndef MANAGER
#define MANAGER

#include "nodeConHash.h"
#include "netServer.h"

#include <fcntl.h>       
#include <iostream>
#include <vector>
#include <unordered_map>
#include <mutex>

using namespace std;

class Manager{
public:
    static Manager* GetInstance();
    static void deleteInstance();
    
    void init();
    //一致性缓存 根据key获取到ip_port
    string getWhichCacheServer(string key);
    //处理cacheServer的心跳包
    void cacheServerKeepAlive(struct sockaddr_in &_addr);
    //处理client的分布请求
    void clientGetDistribution(struct sockaddr_in &_addr);
    //发送缓存服务器列表
    void notifyCacheServer();
    //超时未收到心跳包,则认为需要更新
    void someCacheServerLost(struct sockaddr_in&_addr);
    //主动关闭服务器
    void shutDownOneMachine(struct sockaddr_in&addr);
    

private:
    Manager(){};
    ~Manager(){};
    Manager(const Manager &signal);
    const Manager &operator = (const Manager&signal);

    static Manager* m_SingleInstance;
    static std::mutex m_mutex;
private:

    std::mutex                  m_sourceMutex;

    vector<string>              ipPortLs;
    vector<string>              ipLs;
    vector<int>                 portLs;
    unordered_map<string,int>   cacheServersMp;

    NetServer *server;
};

#endif
