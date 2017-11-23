/*
 *
 * Copyright © 2017 Uisee Co., Ltd.
 * File name： cv.cpp
 * Function  ： 基于OpenCV-3.2.0的图像处理
 * Author  ： JohnnyWang
 * log   :   
 =======2017.06.21.17:29(星期三)======= create file
 =======2017.06.22.11:19(星期四)======= 添加图像采集 
 *
 */
#if 0
#include <stdio.h>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "cv.h"

using namespace cv;
using namespace std;

/*
 *函数Function：打开视频流并且保存图像
 *参数说明：
                   ：
                   ：
  返回值 ：
            成功： 0
            失败：-1
 * */
int  get_and_save_video()
{
    char s[] = "img000.jpg";
    int picture_count=0;
    
    Mat frame;//定义一桢图片的存储结构

    VideoCapture cap;//初始化图像捕获对象
    int deviceID = 0;//默认的相机号为0
    int apiID = cv::CAP_ANY;//自动获取现在机器的相机号
    //打开摄像头
    cap.open(deviceID + apiID); 

    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }//检查是否打开摄像头

  while(1)
  {
        cap.read(frame);
        //检查图像是否为空
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        //显示图像，有按键按下就退出
        imshow("Live", frame);
        if (waitKey(5) == 113)
            break;
        imwrite(s,frame);
 

        *(s+3) = (char)  (picture_count/100+48);
        *(s+4) = (char)  (picture_count%100/10+48);
        *(s+5) = (char)  (picture_count%10+48);
      //sprintf(s,"%d.ipg",picture_count);
      //strcat(s,"\0");
      //cvSaveImage(s, pFrame, 0);
      //printf("%s\r\n",s);
        picture_count ++;
        if(picture_count == 999)
          picture_count = 0;

  }
  return 0;

}
#endif
