/*
 * Copyright © 2017 Uisee Co., Ltd.
 * 文件名： control.h
 * 功能  ： 控制函数头文件
 * 作者  ： JohnnyWang
 * log   :   
 * =======2017.06.15.10:19(星期四)=======创建文件
 *
 */
#ifndef CONTROL_H_
#define CONTROL_H_

#include <Eigen/Core>
#include <Eigen/Geometry>

class wheel_robot
{
public:
    wheel_robot() = default;
    wheel_robot(Eigen::Vector3d speed): robot_speed(speed){};
    virtual void motion_model() const{};
    virtual ~wheel_robot() = default;
    
public:
    Eigen::Vector3d  robot_speed;

//     robot_pose --   V_X   -- 
//                |           |
//                |    V_Y    |
//                |           |
//                --  omega  --
    
};

class three_omni_wheel_robot : public wheel_robot
{
public:
    three_omni_wheel_robot() = default;
    three_omni_wheel_robot( Eigen::Vector3d speed ) : wheel_robot(speed)
    {
        speed_solve<<   -0.5d , -0.866d , 1.0d
                        -0.5d , -0.866d , 1.0d
                        -0.5d ,  0.0d   , 1.0d ;
    };
    void motion_model() const override;


private:
    Eigen::Matrix3d speed_solve;
   
};




int move_forward(int fd);
int move_stop(int fd);
int move_back(int fd);
int move_left(int fd);
int move_right(int fd);


#endif
