# Copyright © 2017 Uisee Co., Ltd.

# 文件名： CMakeLists.txt
# 功能  ： CMake文件，管理整个工程
# 作者  ： JohnnyWang
# log   :   
#=======2017.06.14(星期三)=======创建文件

cmake_minimum_required(VERSION 2.8)
#工程名
PROJECT (crab)


#设置全局变量
set (EXTRA_LIBS ${EXTRA_LIBS} serial dealy thread control keyboard cv)
#注意，如果一个库要引用其他库的函数，需要将被引用的库放在后面
set (CMAKE_CXX_FLAGS "-std=c++11")
#添加c++11标准支持


find_package (OpenCV REQUIRED)
find_package (Threads)

include_directories( ${OpenCV_INCLUDE_DIRS})
#包含opencv的头文件


#添加库文件
add_library(serial   SHARED src/sys/serial/serial.c)
add_library(dealy    SHARED src/sys/dealy/dealy.c)
add_library(thread   SHARED src/sys/thread/thread.c)
add_library(control  SHARED src/control/control.c)
add_library(keyboard SHARED src/sensor/keyboard/keyboard.c)
add_library(cv       SHARED src/sensor/cv/cv.cpp)

#添加可执行文件
add_executable(crab src/main.c)

#链接
target_link_libraries(crab ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})
#   CMAKE_THREAD_LIBS_INIT 是pthread线程的动态库
#   OpenCV_LIBS              OpenCV
