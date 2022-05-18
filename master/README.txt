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
3) safeQueue
    1、https://www.freeaihub.com/post/93796.html    
    1、环形数组
    2、线程函数
4) json
5) threadPool
6）log
    1、