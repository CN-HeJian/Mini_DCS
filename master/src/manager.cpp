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
            m_SingleInstance->server = new NetServer(1316, 3, 10000, false, 1);        
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

void Manager::cacheServerKeepAlive(const struct sockaddr_in &_addr){
    
}