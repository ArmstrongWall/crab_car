/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： dealy.c
 * 功能  ： 延时函数
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.20.16:06(星期二)======= 创建文

*/
#include "../../include.h"
/*
 *函数功能：精准延时
 *参数说明：
            isec  ： 秒
            iusec ： 微秒
  返回值 ：
            成功： 
            失败：
 * */
void mysleep(int isec,int iusec)
{
    struct timeval timer;
    timer.tv_sec  = isec;
    timer.tv_usec = iusec;
    select(0,NULL,NULL,NULL,&timer);
}


