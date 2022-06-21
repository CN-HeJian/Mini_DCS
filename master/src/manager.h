#ifndef MANAGER
#define MANAGER

#include "nodeConHash.h"
#include "netServer.h"


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
    //处理客户端的心跳包
    void cacheServerKeepAlive(const struct sockaddr_in &_addr);
    

private:
    Manager(){};
    ~Manager(){};
    Manager(const Manager &signal);
    const Manager &operator = (const Manager&signal);

    static Manager* m_SingleInstance;
    static std::mutex m_mutex;
private:

    vector<string> ipPortLs;
    vector<string> ipLs;
    vector<int>    portLs;

    NetServer *server;
};

#endif
