//
// Created by chrisliu on 2019/9/25.
//

#include "ros/ros.h"
#include <iostream>
#include "steeringwheel.h"
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float32MultiArray.h>
//时间戳近似同步订阅
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace std;

ros::Publisher S0;
ros::Publisher M0;
ros::Publisher S1;
ros::Publisher M1;
ros::Publisher S2;
ros::Publisher M2;
ros::Publisher S3;
ros::Publisher M3;


std_msgs::Float32MultiArray wheelAngles;

void wheelangles_callback(const std_msgs::Float32MultiArray::ConstPtr &wheelangles_msg) {
    wheelAngles = *wheelangles_msg;
}

void keyboard_callback(const geometry_msgs::Twist::ConstPtr &keyboard) {
    float vel = sqrt(pow(keyboard->linear.x, 2) + pow(keyboard->linear.y, 2));
    if (vel == 0.0) {
        std_msgs::Float32 speedStop;
        speedStop.data = 0;
        M0.publish(speedStop);
        M1.publish(speedStop);
        M2.publish(speedStop);
        M3.publish(speedStop);
    } else {
        float angle = atan2(keyboard->linear.y, keyboard->linear.x) + PI / 2;
        cout << angle * 180 / PI << endl;

        fwc(vel, angle, keyboard->angular.z);
        std_msgs::Float32 speed[4], steer[4];
        for (int i = 0; i < 4; i++) {
            if (wheelAngles.data.empty() == false) {
                adjustSteerAngle(wheel.vol[i], wheel.angle[i], wheelAngles.data[i]);
            } else {
                cout << "No feedback!" << endl;
            }
            speed[i].data = wheel.vol[i];
            steer[i].data = wheel.angle[i];

        }

        M0.publish(speed[0]);
        S0.publish(steer[0]);
        M1.publish(speed[1]);
        S1.publish(steer[1]);
        M2.publish(speed[2]);
        S2.publish(steer[2]);
        M3.publish(speed[3]);
        S3.publish(steer[3]);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "SteeringWheel");//初始化ROS节点
    ros::NodeHandle n;

    ros::Subscriber sub_wheelangles = n.subscribe("/wheel_angles", 1, wheelangles_callback);
    ros::Subscriber sub_keyboard = n.subscribe("/cmd_vel", 1, keyboard_callback);

    S0 = n.advertise<std_msgs::Float32>("/FrontRight_SteerMotor", 1);
    M0 = n.advertise<std_msgs::Float32>("/FrontRight_MoveMotor", 1);
    S1 = n.advertise<std_msgs::Float32>("/BackRight_SteerMotor", 1);
    M1 = n.advertise<std_msgs::Float32>("/BackRight_MoveMotor", 1);
    S2 = n.advertise<std_msgs::Float32>("/BackLeft_SteerMotor", 1);
    M2 = n.advertise<std_msgs::Float32>("/BackLeft_MoveMotor", 1);
    S3 = n.advertise<std_msgs::Float32>("/FrontLeft_SteerMotor", 1);
    M3 = n.advertise<std_msgs::Float32>("/FrontLeft_MoveMotor", 1);


    while (ros::ok()) {
        ros::spinOnce();
    }
    return 0;
}

