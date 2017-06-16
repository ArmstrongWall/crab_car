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
set (EXTRA_LIBS ${EXTRA_LIBS} serial keyboard)
#添加库文件
add_library(serial SHARED src/serial/serial.c)
add_library(keyboard SHARED src/sensor/keyboard/keyboard.c)
#添加可执行文件
add_executable(crab src/main.c)
#链接
target_link_libraries(crab ${EXTRA_LIBS})
