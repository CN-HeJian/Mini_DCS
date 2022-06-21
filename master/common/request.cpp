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

#include "request.h"
#include "../common/json.h"
using json = nlohmann::json;

Request::Request(){
    init();
}

void Request::init(){

}

//需要判断能否解析成功
bool Request::parse(Buffer& buff){
    std::cout<<"Request::parse: "<<std::endl;
    buff.printContent();

    std::string s = buff.AlltoStr();
    json j = json::parse(s);
    req_data_ = j.get<req>();

    switch(req_data_.req_type){
        case CACHE_SERVER:
            request_cacheServer_();
            break;
        case CLIENT:
            request_client_();
            break; 
        case MASTER:
            request_master_();
            break;
        default:
            return false;
    }

    return true;
}

//处理缓存服务器请求
void Request::request_cacheServer_(){
    std::cout<<"Request::request_cacheServer_: "<<std::endl;
}

//处理客户端请求
void Request::request_client_(){
    std::cout<<"Request::request_client_: "<<std::endl;
}

//从masster
void Request::request_master_(){
    std::cout<<"Request::request_client_: "<<std::endl;
}
