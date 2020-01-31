//
// Created by chrisliu on 2019/9/25.
//

#include "ros/ros.h"
#include <iostream>
#include <algorithm>
#include "steeringwheel.h"
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float32MultiArray.h>
//时间戳近似同步订阅
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <math.h>

using namespace std;

ros::Publisher S0;
ros::Publisher M0;
ros::Publisher S1;
ros::Publisher M1;
ros::Publisher S2;
ros::Publisher M2;
ros::Publisher S3;
ros::Publisher M3;

void vector_control(float &vel_target, float &theta_target_rad, float theta_now_rad) {
    int theta_target = theta_target_rad * 180 / PI;
    int theta_now_degree = theta_now_rad * 180 / PI;
    int delta1 = theta_target - theta_now_degree;
    int delta2 = (theta_target + 180) % (360) - theta_now_degree;
    int delta1_abs = abs(delta1);
    int delta2_abs = abs(delta2);
    if (delta1_abs > 180) {
        delta1_abs = 360 - delta1_abs;
    }
    if (delta2_abs > 180) {
        delta2_abs = 360 - delta2_abs;
    }
    if (delta1_abs < delta2_abs) {
        theta_target_rad = (float) theta_target / 180 * PI;
        vel_target = vel_target;
    } else {
        theta_target_rad = (float) ((theta_target + 180) % (360)) / 180 * PI;
        vel_target = -vel_target;
    }
}

std_msgs::Float32MultiArray wheel_angles;
void wheelangles_callback(const std_msgs::Float32MultiArray::ConstPtr &wheelangles_msg) {
        wheel_angles = *wheelangles_msg;
}

void keyboard_callback(const geometry_msgs::Twist::ConstPtr &keyboard) {
    float vel = sqrt(pow(keyboard->linear.x, 2) + pow(keyboard->linear.y, 2));
    float angle = atan2(keyboard->linear.y, keyboard->linear.x) + PI / 2;

    fwc(vel, angle, keyboard->angular.z);
    std_msgs::Float32 speed[4], steer[4];
    for (int i = 0; i < 4; i++) {
        //vector_control(wheel.w_vol[i], wheel.w_angle[i], wheel_angles.data[i]);
        speed[i].data = wheel.w_vol[i];
        steer[i].data = wheel.w_angle[i];
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

