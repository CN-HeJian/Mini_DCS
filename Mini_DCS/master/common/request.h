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
#include <regex>

#include "buffer.h"
#include "../common/json.h"
using json = nlohmann::json;

//using namespace std;

struct req_key{
    std::string value;
};

class Request{    
public:
    // //
    // enum PARSE_STATE{
    //     REQUEST_LINE,
    //     HEADERS,
    //     BODY,
    //     FINISH,
    // };

    // enum HTTP_CODE {
    //     // NO_REQUEST = 0,
    //     // GET_REQUEST,
    //     // BAD_REQUEST,
    //     // NO_RESOURCE,
    //     // FORBIDDENT_REQUEST,
    //     // FILE_REQUEST,
    //     // INTERNAL_ERROR,
    //     // CLOSED_CONNECTION,
    // };

    Request();
    ~Request()=default;

    void init();
    bool parse(Buffer& buff);

    // std::string path()const;
    // std::string &path();
    // std::string method();
    // std::string version();
    // std::string getPost(const std::string& key) const;
    // std::string getPost(const char* key) const;

    //bool isKeepAlive() const;

private:

    // request line
    /*  请求方法  URL  协议版本  换行符  */
    /*  GET  /mix/76.html?name=kelvin&password=123456 HTTP/1.1  */

    // request header 
    /*  请求头部  */

    //bool parseRequestLine_(const std::string& line);
    //void parseRequestHeader_(const std::string& line);
    //void parseDataBody_(const std::string& line);

    //void parsePath_();
    //void parsePost_();

    //static int convertHex(char ch);

    //std::string method() const;
    //std::string version() const;
    
    //当前报文解析进度curState
    //PARSE_STATE state_;
    //方法:get/post
    //std::string method_;
    //所需资源的路径!!!
    //std::string path_;
    //版本号Version_number
    //std::string version_;
    //内容Content
    //std::string body_;

    //std::unordered_map<std::string,std::string> header_;
    
    //std::unordered_map<std::string,std::string> post_;

    //static const std::unordered_set<std::string> DEFAULT_HTML;
};

#endif // !REQUEST_H
