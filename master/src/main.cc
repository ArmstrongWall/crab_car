/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： main.c
 * 功能  ： 螃蟹车控制主程序
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.14.09:50(星期三)======= 创建文件,成功配置串口，并发出数据
 * =======2017.06.15.09:18(星期四)======= 添加键盘遥控
 * =======2017.06.20.15:19(星期二)======= 添加遥控采集图像
 */
#include "include.h"
int serial_fd;

int main(void)  
{
    
     
                    
    serial_fd = serial_init(115200);

    if( serial_fd == -1)
    {
        printf("serial init failed\r\n");
        exit(-1);
    }
    
    mysleep(3,0);//串口初始化完成后需要等待一段时间

    thread_init();


    return 0; 
} 








