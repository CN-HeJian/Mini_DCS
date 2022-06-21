// Copyright 2022 icf
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef REQUEST_H
#define REQUEST_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <arpa/inet.h>

#include "buffer.h"
#include "../common/json.h"


class Manager;
using json = nlohmann::json;

/*
    machineType 
        0：cacheServer
        1：client
        2：master
*/

/*
    req_type
        0： keepAlive
        1：
*/

struct req{
    int machineType;
    int req_type;
};

class Request{    
public:
    enum MACHINE_TYPE{
        CACHE_SERVER,
        CLIENT,
        MASTER,
    };

    enum REQ_TYPE{
        KEEP_ALIVE,
        //CLIENT,
        //MASTER,
    };

    Request();
    ~Request()=default;

    void init();
    bool parse(Buffer& buff,const struct sockaddr_in &_addr);

    bool request_cacheServer_();

    void cacheServer_KeepAlive();

    bool request_client_();
    bool request_master_();

private:
    req req_data_;
    struct sockaddr_in addr_;
};

// person -> json
static void to_json(json& j, const req& p) {
    j = json{{"req_type", p.req_type}};
}

// json -> person
static void from_json(const json& j, req& p) {
    j.at("req_type").get_to(p.req_type);
}

#endif // !REQUEST_H
