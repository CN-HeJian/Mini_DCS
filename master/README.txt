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



技术点:
1)  一致性哈希
2)  套接字
3)  状态机回复
4)  日志模块

功能划分:
1)  主动扩容
2)  主动缩容
3)  被动缩容
4)  Master容灾

公有模块
1) consistentHash
    1、哈希函数
    2、增加虚拟节点，防止雪崩效应
    3、增加一个机器
    4、删除一个机器
    5、依据key得到在哪个机器对应的ipPort
2) epoll
    1、读取数据
    2、发送数据
3) safeQueue
    1、https://www.freeaihub.com/post/93796.html    
    1、环形数组
    2、线程函数
4) json
    1、直接传递json类型的数据包
5) threadPool
    1、addTask 即可!!!
6) log
    1、异步读写!

Master与哪些机器进行交互？
1) cacheServer:
    1)KEEP_ALIVE:
        判断是不是更新了???
        1)  删除之前新建的定时任务
        2)  新建一个定时任务....

2) Master:master容灾
    
3) client:Master


下一步计划：
1) 将日志模块添加到现有系统中
2) 研究定时器模块，添加定时任务
3) 绑定cache_server,确定交互逻辑
4) 需要确定发送函数!!!

js[machine]
js[type]
js["data"]["iplist"]

MASTER
    ADD_CACHE_SERVER(扩容)---iplist
        1)处理备份LRU
        2)处理主体LRU
    SHUTDOWN_CACHE(主动)---iplist
        1)处理备份LRU
        2)处理主体LRU
        3)关闭当前机器,暂停心跳包的发送，不行这样子就会触发REFLESH_IP
    REFLESH_IP(被动)---iplist
        1)处理主体LRU
        2)处理备份LRU

client
    GET
        1)缓存中查找并返回
    SET
        1)set lru
        2)发送对应数据到备份服务器

CACHE_SERVER
    KEY_VALUE_RESPONCE:
        1)写入到主体LRU
    KEY_VALUE_RESPONCE_BACK
        2)写入到备份LRU

FELESH_MASTER
    REFLESH MASTER_IP
        1)更换master_ip
        2)







异常：
--------------------------------------------------
Q：
    1) test_client.cpp 中 多次send 不能多次捕获读事件
    2) 调用了send不能捕获close()

A:上面两个问题都需要通过重置标志位来解决
--------------------------------------------------
Q:
    3) buffer_->readv(fd,iov,2)会一次读完所有的数据?
    
A：
    不会，会将readv中的缓冲区都读满，如果缓冲区长度大于iov的长度的话，这个时候就需要扩容了！
--------------------------------------------------

Q: cacheServer Master节点挂掉，心跳包发送失败，CacheServer程序自动退出...


Q: CacheServer 收不到Master的回复信息


Q: CacheServer 客户端关闭没有把iplist更新!!!

//...关闭连接需要更新iplist//---这儿称为主动掉线？？
不对，掉线是通过心跳包来检测的!!!

Q: epoll_wait(timeOut)有什么作用？
    

