//
// Created by chrisliu on 2019/9/25.
//


//#include <cmath>
#include "steeringwheel.h"
#include <algorithm>
#include <math.h>

wheel_t wheel;
float delta[4]={3*PI/4, PI/4, 7*PI/4, 5*PI/4};
void fwc(float V, float theta, float Omega)
{
    for(int i=0;i<4;i++)
    {
        wheel.angle[i] = atan2((Omega*AFA*sin(delta[i])+V*sin(theta)) ,(Omega*AFA*cos(delta[i])+V*cos(theta)));
        //获得的速度永远>=0
        wheel.vol[i] = sqrt(pow(Omega*AFA,2)+V*V+ 2*V*Omega*AFA*cos(delta[i]-theta));
    }

}

void adjustSteerAngle(float &targetVel, float &targetAngle_rad, float currentAngle_rad) {
//    输入输出：
//                          x+
//                          前
//                          90
//              y-  左 180        0 右  y+
//                          -90
//                          后
//                          x-
    float targetAngle_1 = targetAngle_rad * 180 / PI;
    float targetAngle_2 = targetAngle_1 + 180;
    if (targetAngle_2 > 180) {
        targetAngle_2 -= 360;
    }

    float currentAngle_degree = currentAngle_rad * 180 / PI;

    float delta_1 = targetAngle_1 - currentAngle_degree;
    float delta_2 = targetAngle_2 - currentAngle_degree;
    float delta_1_abs = abs(delta_1);
    float delta_2_abs = abs(delta_2);
    if (delta_1_abs > 180) {
        delta_1_abs = 360 - delta_1_abs;
    }
    if (delta_2_abs > 180) {
        delta_2_abs = 360 - delta_2_abs;
    }
    if (delta_1_abs < delta_2_abs) {
        targetAngle_rad = targetAngle_1 / 180 * PI;
//        targetVel = targetVel;
    } else {
        targetAngle_rad = targetAngle_2 / 180 * PI;
        targetVel = -targetVel;
    }
}