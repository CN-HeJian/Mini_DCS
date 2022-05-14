#include "../common/consistentHash.h"

#include <iostream>
#include <vector>
using namespace std;

class Manager{
public:
    Manager(){}

    //一致性缓存 根据key获取到ip_port
    string getWhichCacheServer(string key);

private:
    vector<string> cacheServers;
    ConsistentHash* conHash;

};
