/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： keyboard.c
 * 功能  ： 按键扫描
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.15.10:22(星期四)======= 创建文

*/
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>  
/*函数功能：扫描键盘按下的键值
 *参数说明：
  返回值 ：
            成功： 按键对应的ASCII码
            失败：-1
  * */
int scanKeyboard()  
{  
    int in;  
    struct termios new_settings;  
    struct termios stored_settings;  
    tcgetattr(0,&stored_settings);  
    new_settings = stored_settings;  
    new_settings.c_lflag &= (~ICANON);  
    new_settings.c_cc[VTIME] = 0;  
    tcgetattr(0,&stored_settings);  
    new_settings.c_cc[VMIN] = 1;  
    tcsetattr(0,TCSANOW,&new_settings);  
      
    in = getchar(); 

    printf("you press key num is %d",in);
      
//这个方法就可以，返回值是该键的ASCII码值，不需要回车的，  
    tcsetattr(0,TCSANOW,&stored_settings);  
    
    return in;  
}  
