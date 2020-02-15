//
// Created by chrisliu on 2019/9/25.
//

#ifndef VREP_PKG_FWC_H
#define VREP_PKG_FWC_H
struct wheel_t{
    float vol[4];
    float angle[4];
};
const float PI = 3.1415;
const float AFA = 0.141;         //轮子到底盘中心距离(m)
extern wheel_t wheel;
void fwc(float V, float theta, float Omega);
void adjustSteerAngle(float &targetVel, float &targetAngle_rad, float currentAngle_rad);
#endif //VREP_PKG_FWC_H
