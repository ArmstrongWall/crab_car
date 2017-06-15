/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： main.c
 * 功能  ： 螃蟹车控制主程序
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.14(星期三)=======创建文件,
 */
#include "include.h"
void mysleep(int isec,int iusec)
{
    struct timeval timer;
    timer.tv_sec  = isec;
    timer.tv_usec = iusec;
    select(0,NULL,NULL,NULL,&timer);
}

int main(void)  
{ 
    int fd; 
    int nread,nwrite,i; 
    char buff[]="go20;ss"; 
 
    if((fd=open_port(fd,1))<0){//打开串口 
        perror("open_port error"); 
        return; 
    } 
    if((i=set_opt(fd,9600,8,'N',1))<0){//设置串口 
        perror("set_opt error"); 
        return; 
    } 
    printf("fd=%d\n",fd); 
    fd=3;
    mysleep(3,0);
    //nread=read(fd,buff,8);//读串口 
    //printf("nread=%d,%s\n",nread,buff); 
    nwrite=write(fd,buff,8);//写串口 
    printf("nwrite=%d,%s\n",nwrite,buff);
    close(fd); 
    return; 
} 








