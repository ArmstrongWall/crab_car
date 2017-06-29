/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： thread.c
 * 功能  ： 开辟线程的函数
 * 作者  ： JohnnyWang
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
        printf("I am ctrlcar\r\n");
        pthread_mutex_lock(&mux);
        pthread_cond_wait(&SCAN_OK,&mux);//等待被通知，这个函数会自动unlock互斥量,阻塞函数
        if(key_num == 119)
        {
            move_forward(serial_fd);
        }
        if(key_num == 113)
        {
            move_stop(serial_fd);
        }
        if(key_num == 115)
        {
            move_back(serial_fd);
        }
		if(key_num == 97)
        {
            move_left(serial_fd);
        }
		if(key_num == 100)
        {
            move_right(serial_fd);
        }
        pthread_mutex_unlock(&mux);
    }

}

void *cvprogress()
{
    get_and_save_video();
}

void thread_init()
{
    pthread_mutex_init(&mux,NULL);
    //初始化线程互斥锁
    pthread_create(&thread[0],NULL,getkey,NULL);
    pthread_create(&thread[1],NULL,ctrlcar,NULL);
    pthread_create(&thread[2],NULL,cvprogress,NULL);
    //创建线程

    pthread_join(&thread[0],NULL);
    pthread_join(&thread[1],NULL);
    pthread_join(&thread[2],NULL);
    //开始运行线程
    

}

