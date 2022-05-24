cmake_minimum_required (VERSION 3.8)
project (demo)

set(CMAKE_CXX_STANDARD 11)

set(SRC_LIST
        main.cpp
        #./src/nodeConHash.cpp
        #./src/manager.cpp
        #./common/consistentHash.cpp
        )
add_executable(master ${SRC_LIST})





#consistentHash
add_executable(testConsistentHash ./test/test_consistentHash.cpp ./src/nodeConHash.cpp ./common/consistentHash.cpp)

#log
add_executable(testlog ./test/test_log.cpp  ./common/log.cpp)
TARGET_LINK_LIBRARIES( testlog pthread)

#safeQueue
add_executable(testSafeQueue ./test/test_safeQueue.cpp ./common/safeQueue.h)
TARGET_LINK_LIBRARIES( testSafeQueue pthread)

#threadPool


#cmd
#g++ test_consistentHash.cpp  ../src/nodeConHash.cpp ../common/consistentHash.cpp  -o conff
#g++ test_log.cpp  ../common/log.cpp  -o log -pthread
#g++ test_safeQueue.cpp ../common/safeQueue.h  -o safeQueue  -pthread
