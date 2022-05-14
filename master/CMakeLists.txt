cmake_minimum_required (VERSION 2.8)

project (demo)

aux_source_directory(. SRC_LIST)
add_compile_options(-std=c++11 -lpthread)
add_executable(master ${SRC_LIST})

find_package(Threads)
target_link_libraries(master ${CMAKE_THREAD_LIBS_INIT})
