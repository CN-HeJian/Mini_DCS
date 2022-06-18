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

const std::unordered_set<std::string> Request::DEFAULT_HTML{
            "/index", "/welcome", "/video", "/picture"};

Request::Request(){
    init();
}

void Request::init(){
    method_  = path_ =version_ = body_ = "";
    state_ = REQUEST_LINE;
    header_.clear();
    post_.clear();
}

//是否为长连接!!!
bool Request::isKeepAlive() const{
    if(header_.count("Connection") == 1) {
        return header_.find("Connection")->second == "keep-alive" && version_ == "1.1";
    }
    return false;
}

bool Request::parse(Buffer& buff){
    const char CRLF[] = "\r\n";
    if(buff.readableBytes()<=0){
        return false;
    }

    while(buff.readableBytes() && state_!=FINISH){
        const char* lineEnd = std::search(buff.curReadPtr(),buff.curWritePtrConst(),CRLF,CRLF+2);
        std::string line(buff.curReadPtr(),lineEnd);
        
        switch(state_){
            case REQUEST_LINE:
                if(!parseRequestLine_(line)){
                    return false;
                }
                parsePath_();
                break;
            case HEADERS:
                parseRequestHeader_(line);
                if(buff.readableBytes()<=2){
                    state_ = FINISH;
                }
                break;
            case BODY:
                parseDataBody_(line);
                break;
            default:
                break;
        }
        if(lineEnd == buff.curWritePtr()){
            break;
        }
        buff.updateReadPtrUntilEnd(lineEnd+2);
    }
    return true;
}

/*解析需要获取的路径*/
void Request::parsePath_(){
    if(path_ == "/"){
        path_ = "/index.html";
    }else{
        for(auto &item:DEFAULT_HTML){
            if(item == path_){
                path_ += ".html";
                break;
            }
        }
    }
}

/*解析请求行*/
bool Request::parseRequestLine_(const std::string& line){
    std::regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch subMatch;
    if(regex_match(line, subMatch, patten)) {   
        method_ = subMatch[1];
        path_ = subMatch[2];
        version_ = subMatch[3];
        state_ = HEADERS;
        return true;
    }
    return false;
}

/*解析*/
void Request::parseRequestHeader_(const std::string& line) {
    std::regex patten("^([^:]*): ?(.*)$");
    std::smatch subMatch;
    if(regex_match(line, subMatch, patten)) {
        header_[subMatch[1]] = subMatch[2];
    }
    else {
        state_ = BODY;
    }
}

//一个字符解析欸!!!
void Request::parseDataBody_ (const std::string& line){
    body_ = line;
    parsePost_();
    state_ = FINISH;
}

//字符串转数字
int Request::convertHex(char ch) {
    if(ch >= 'A' && ch <= 'F') return ch -'A' + 10;
    if(ch >= 'a' && ch <= 'f') return ch -'a' + 10;
    return ch;
}


void Request::parsePost_() {
    if(method_ == "POST" && header_["Content-Type"] == "application/x-www-form-urlencoded") {
        if(body_.size() == 0) { return; }

        std::string key, value;
        int num = 0;
        int n = body_.size();
        int i = 0, j = 0;

        for(; i < n; i++) {
            char ch = body_[i];
            switch (ch) {
            case '=':
                key = body_.substr(j, i - j);
                j = i + 1;
                break;
            case '+':
                body_[i] = ' ';
                break;
            case '%':
                num = convertHex(body_[i + 1]) * 16 + convertHex(body_[i + 2]);
                body_[i + 2] = num % 10 + '0';
                body_[i + 1] = num / 10 + '0';
                i += 2;
                break;
            case '&':
                value = body_.substr(j, i - j);
                j = i + 1;
                post_[key] = value;
                break;
            default:
                break;
            }
        }
        assert(j <= i);
        if(post_.count(key) == 0 && j < i) {
            value = body_.substr(j, i - j);
            post_[key] = value;
        }
    }   
}

std::string Request::path() const{
    return path_;
}

std::string& Request::path(){
    return path_;
}

std::string Request::method() const {
    return method_;
}

std::string Request::version() const {
    return version_;
}

std::string Request::getPost(const std::string& key) const {
    assert(key != "");
    if(post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}

std::string Request::getPost(const char* key) const {
    assert(key != nullptr);
    if(post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}
