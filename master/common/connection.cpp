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

#include "connection.h"

std::atomic<int> Connection::userCount;
bool Connection::isET;

Connection::Connection(){
    fd_ = -1;
    addr_ = {0};
    isClose_ = true;
}

Connection::~Connection(){
    closeConnect();
}

void Connection::initConnection(int sockFd,const sockaddr_in & addr){
    assert(sockFd>0);
    userCount++;
    addr_ = addr;
    fd_ = sockFd;
    readBuffer_.initPtr();
    writeBuffer_.initPtr();
    isClose_ = true;
}

void Connection::closeConnect(){
    //TODO: 需要关闭映射的文件
    if(isClose_ == false){
        isClose_ = true;
        userCount--;
        close(fd_);
    }
}

int Connection::getFd()const{
    return fd_;
}

struct sockaddr_in Connection::getAddr() const{
    return addr_;
}

const char* Connection::getIp()const{
    return inet_ntoa(addr_.sin_addr);
}

int Connection::getPort() const{
    return addr_.sin_port;
}

ssize_t Connection::readBuffer(int *saveErrno){
    ssize_t len = -1;
    do{
        len = readBuffer_.readFd(fd_,saveErrno);
        if(len<=0){ 
            break;
        }
    }while(isET);
    return len;
}

ssize_t Connection::writeBuffer(int *saveErrno){
    ssize_t len = -1;
    do{
         len = writev(fd_, iov_, iovCnt_);
        if(len <= 0) {
            *saveErrno = errno;
            break;
        }
        if(iov_[0].iov_len + iov_[1].iov_len  == 0) { break; } /* 传输结束 */
        else if(static_cast<size_t>(len) > iov_[0].iov_len) {
            iov_[1].iov_base = (uint8_t*) iov_[1].iov_base + (len - iov_[0].iov_len);
            iov_[1].iov_len -= (len - iov_[0].iov_len);
            if(iov_[0].iov_len) {
                writeBuffer_.initPtr();
                iov_[0].iov_len = 0;
            }
        }
        else {
            iov_[0].iov_base = (uint8_t*)iov_[0].iov_base + len; 
            iov_[0].iov_len -= len; 
            writeBuffer_.updateReadPtr(len);
        }
    }while(isET||writeBytes()>10240);
    return len;
}


bool Connection::handleConnec(){
    std::cout<<"handleConnec "<<std::endl;
    // request_.init();
    // if(readBuffer_.readableBytes() <= 0) {
    //     //std::cout<<"readBuffer is empty!"<<std::endl;
    //     return false;
    // }
    // else if(request_.parse(readBuffer_)) {
    //     response_.init(srcDir, request_.path(), request_.isKeepAlive(), 200);
    // }else {
    //     std::cout<<"400!"<<std::endl;
    //     //readBuffer_.printContent();
    //     response_.init(srcDir, request_.path(), false, 400);
    // }

    // response_.makeResponse(writeBuffer_);
    // /* 响应头 */
    // iov_[0].iov_base = const_cast<char*>(writeBuffer_.curReadPtr());
    // iov_[0].iov_len = writeBuffer_.readableBytes();
    // iovCnt_ = 1;

    // /* 文件 */
    // if(response_.fileLen() > 0  && response_.file()) {
    //     iov_[1].iov_base = response_.file();
    //     iov_[1].iov_len = response_.fileLen();
    //     iovCnt_ = 2;
    // }
    return true;
}

