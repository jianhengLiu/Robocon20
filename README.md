# 1.文件结构



# 2.使用方法

## 2.0. 仿真场景

`~/Robocon20/simulation/scenes/RaceSceneWithOmniwheel.ttt`

`~/Robocon20/simulation/scenes/RaceSceneWithSteerwheel.ttt`



## 2.1. 建图

`cartographer`进行建图

```bash
roslaunch cartographer_ros omni_lds.launch
```

保存地图

```bash
rosservice call /write_state /home/chrisliu/ROS/cartographer_ws/RaceMap.pbstream true
rosrun cartographer_ros cartographer_pbstream_to_ros_map -pbstream_filename /home/chrisliu/ROS/cartographer_ws/RaceMap.pbstream -map_filestem /home/chrisliu/ROS/cartographer_ws/RaceMap
```

然后将`RaceMap.yaml`和`RaceMap.pgm`放置在`～/Robocon20/simulation/sim_ws/src/mapping/maps`下

可能需要修改`.yaml`文件内的路径信息

## 2.2. 导航定位

```bash
roslaunch mapping nav_omni.launch
roslaunch mapping nav_steer.launch
```

# 3. 参数配置

