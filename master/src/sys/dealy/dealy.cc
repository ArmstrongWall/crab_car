/*
 * Copyright © 2017 Uisee Co., Ltd.
 * File name： dealy.c
 * Function  ： 延时函数
 * Author  ： JohnnyWang
 * log   :   
 * =======2017.06.20.16:06(星期二)======= 创建文

*/
#include "../../include.h"
/*
 *函数Function：精准延时
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


