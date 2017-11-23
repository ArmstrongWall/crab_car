/*
 * Copyright © 2017 Uisee Co., Ltd.
 * File name： robot.cc
 * Function ： robot class
 * Author   ： JohnnyWang
 * log   :   
 * 
 *
 */
#include "robot.h"


Eigen::Vector3d three_omni_wheel_robot::wheel_velocity_decode()
{ 
    dewheel_velocity  = solve_convert * robot_velocity;
    return dewheel_velocity;
}



int three_omni_wheel_robot::robot_move()
{
    Eigen::Vector3i dwv= dewheel_velocity.cast<int>();
    
    for(int i = 0; i < 3 ; i++)
    {
        dwv(i) = dwv(i) + 32767;
        instruction_message[i*2+1] = (dwv(i) & 0x0000ff00) >> 8;
        instruction_message[i*2+2] = (dwv(i) & 0x000000ff);
    }
    //nread=read(fd,buff,8);//读串口 
    write(serial_fd,instruction_message,sizeof(instruction_message));//读串口 
    //printf("nread=%d,%s\n",nread,buff); 
    //printf("nwrite=%d,%s\n",nwrite,buff);
    //close(fd);

    //printf("move_forward\r\n");
}

















