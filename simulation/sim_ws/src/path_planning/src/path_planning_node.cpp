//
// Created by chrisliu on 2020/6/1.
//
#include "ros/ros.h"
#include <iostream>
#include <nav_msgs/OccupancyGrid.h>
#include <Eigen/Eigen>

//#include "Astar_searcher.h"

using namespace std;
using namespace Eigen;

void rcvMapCallBack(const nav_msgs::OccupancyGridConstPtr &map);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "SteeringWheel");//初始化ROS节点
    ros::NodeHandle n;

    ros::Subscriber _map_sub = n.subscribe("/map", 1, rcvMapCallBack);

    while (ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}

void rcvMapCallBack(const nav_msgs::OccupancyGridConstPtr &map)
{
//     The map resolution [m/cell]
    float _resolution = map->info.resolution;
//    Map width [cells]
    uint32_t MAP_WIDTH = map->info.width;
//    Map height [cells]
    uint32_t MAP_HEIGHT = map->info.height;

//     The origin of the map [m, m, rad].  This is the real-world pose of the
//       cell (0,0) in the map.
    float _origin_x = map->info.origin.position.x;
    float _origin_y = map->info.origin.position.y;

    int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT;

    Eigen::MatrixXd MAP_DATA = Eigen::MatrixXd::Zero(MAP_HEIGHT,MAP_WIDTH);

    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
//        只要概率不是0我都认为他是障碍物
            if (map->data[i*MAP_WIDTH+j] != 0)
                MAP_DATA(i,j) = 1;
        }
    }
    cout<<MAP_DATA<<endl;


}