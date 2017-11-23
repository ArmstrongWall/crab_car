/*
 * Copyright © 2017 Uisee Co., Ltd.
 * File name： thread.c
 * Function  ： 开辟线程的函数
 * Author  ： JohnnyWang
 * log   :   
 * =======2017.06.20.16:06(星期二)======= 创建文

*/
#include "../../include.h"

pthread_t thread[3];//三个线程号
pthread_mutex_t mux;//线程互斥锁
pthread_cond_t SCAN_OK = PTHREAD_COND_INITIALIZER;//初始化一个线程条件变量


int key_num = 0;

void *getkey()
{
    int temp;
    while(1)
    {
        temp = scanKeyboard();
        if( temp> 1)
        {
            pthread_mutex_lock(&mux);
            key_num = temp;
            pthread_cond_signal(&SCAN_OK);//通知另一个线程
            pthread_mutex_unlock(&mux);
        }
    }
}

void *ctrlcar()
{
    while(1)
    {
       
    }

}

void *cvprogress()
{
    //get_and_save_video();
}

void thread_init()
{

    

}

