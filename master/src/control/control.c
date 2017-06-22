/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： control.c
 * 功能  ： 实现底盘速度的解析
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.15.10:22(星期四)======= 创建文件
 *
 */

int move_forward(int fd)
{
    
    char buff[]="go20;aa"; 
    //nread=read(fd,buff,8);//读串口 
    write(fd,buff,sizeof(buff));//读串口 
    //printf("nread=%d,%s\n",nread,buff); 
    //printf("nwrite=%d,%s\n",nwrite,buff);
    //close(fd);

    printf("move_forward\r\n");
}

int move_stop(int fd)
{
    
    char buff[]="ss"; 
    //nread=read(fd,buff,8);//读串口 
    write(fd,buff,sizeof(buff));//读串口 
    //printf("nread=%d,%s\n",nread,buff); 
    //printf("nwrite=%d,%s\n",nwrite,buff);
    //close(fd);

    printf("move_forward\r\n");
}

int move_back(int fd)
{
    
    char buff[]="bb"; 
    //nread=read(fd,buff,8);//读串口 
    write(fd,buff,sizeof(buff));//读串口 
    //printf("nread=%d,%s\n",nread,buff); 
    //printf("nwrite=%d,%s\n",nwrite,buff);
    //close(fd);

    printf("move_forward\r\n");
}
