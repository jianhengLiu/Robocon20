//
// Created by chrisliu on 2019/9/25.
//

#include "ros/ros.h"
#include <iostream>
#include <algorithm>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

using namespace std;

ros::Publisher pub_AllMoveMotorSpeed;
ros::Publisher M0;
ros::Publisher M1;
ros::Publisher M2;
ros::Publisher M3;

float robot_radius=0.205;

void keyboard_callback(const geometry_msgs::Twist::ConstPtr &keyboard)
{
//    fwc(0,1,2);
//    wheel.w_vol[1];
//    std_msgs::Float32 speed,steer;
//    speed.data = keyboard->linear.x/10;

    float vel_x  = -1*keyboard->linear.x;
    float vel_y  = keyboard->linear.y;
    float omega_z = robot_radius*keyboard->angular.z;
    std_msgs::Float32 speed[4];

    for(int i=0;i<4;i++)
    {
        speed[i].data=vel_x*0.707+vel_y*0.707*pow(-1,i);
        if(i==0||i==3)
            speed[i].data+=omega_z;
        else
            speed[i].data-=omega_z;
    }

//    float vel=sqrt(pow(keyboard->linear.x,2)+pow(keyboard->linear.y,2));
//    float angular = atan2(keyboard->linear.y,keyboard->linear.x)+PI/2;
//
//    fwc(vel,angular,keyboard->angular.z);
//    std_msgs::Float32 speed[4];
//    for(int i=0;i<4;i++)
//    {
//
//        speed[i].data = wheel.w_vol[i];//keyboard->linear.x;
//        cout<<wheel.w_vol[i]<<"//vol"<<endl;
//        cout<<wheel.w_angle[i]<<"//angle"<<endl;
//    }
//
    M0.publish(speed[0]);
    M1.publish(speed[1]);
    M2.publish(speed[2]);
    M3.publish(speed[3]);
//    pub_AllMoveMotorSpeed.publish(speed);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "OmniWheel");//初始化ROS节点
    ros::NodeHandle n;

    ros::Subscriber sub_keyboard = n.subscribe("/cmd_vel",1,keyboard_callback);

    pub_AllMoveMotorSpeed = n.advertise<std_msgs::Float32>("/All_MoveMotor", 1);

    M0 = n.advertise<std_msgs::Float32>("/FrontLeft_MoveMotor", 1);
    M1 = n.advertise<std_msgs::Float32>("/FrontRight_MoveMotor", 1);
    M2 = n.advertise<std_msgs::Float32>("/BackRight_MoveMotor", 1);
    M3 = n.advertise<std_msgs::Float32>("/BackLeft_MoveMotor", 1);


    while (ros::ok()) {

        ros::spinOnce();
//		loop_rate.sleep();

    }
    return 0;
}