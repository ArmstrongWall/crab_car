/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： serial.h
 * 功能  ： serial.h
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.14(星期三)=======创建文件
 *
 */
#ifndef SERIAL_H_
#define SERIAL_H_
int open_port(); 
int set_opt();
int serial_init(int baurdrate);
#endif
