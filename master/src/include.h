/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： include.h
 * 功能  ： 该头文件包含了工程中所有的头文件
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.14(星期三)=======创建文件
 *
 */
#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "control/control.h"
#include "sensor/keyboard/keyboard.h"
#include "sys/serial/serial.h"
#include "sys/thread/thread.h"
#include "sys/dealy/dealy.h"
//#include "sensor/cv/cv.h"

extern int serial_fd;

#endif
