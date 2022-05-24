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

#ifndef CONNEXTION_H
#define CONNEXTION_H

#include "buffer.h"

#include <arpa/inet.h>
#include <iostream>
#include <assert.h>
#include <sys/types.h>

class Connection{
public:
    Connection();
    ~Connection();

    void initConnection(int socketFd,const sockaddr_in&addr);

    ssize_t readBuffer(int *saveErrno);
    ssize_t writeBuffer(int* saveErrno);

    void closeConnect();
    bool handleConnec();

    const char* getIp()const;
    int getPort()const;
    int getFd()const;
    sockaddr_in getAddr() const;


    int writeBytes(){
        return iov_[1].iov_len+iov_[0].iov_len;
    }

    // bool isKeepLive(){
    //     //return false;
    // }

    static bool isET;

    //static const char* srcDir

    static std::atomic<int> userCount;

private: 
    int fd_;//连接对应的描述符
    struct sockaddr_in addr_;
    bool isClose_;

    int iovCnt_;
    struct iovec iov_[2];

    Buffer readBuffer_; //读缓冲区
    Buffer writeBuffer_;//写缓冲区
};


#endif