[http://wiki.ros.org/navigation/Tutorials/Writing%20A%20Global%20Path%20Planner%20As%20Plugin%20in%20ROS](http://wiki.ros.org/navigation/Tutorials/Writing A Global Path Planner As Plugin in ROS)

https://www.youtube.com/watch?v=We1gGDXAO_o&list=PL93n88K6Qpb63pyaaPaOTudQB30Z2Qn4r

https://www.youtube.com/watch?v=t4A_niNlDdg

## 1.待更

## 2.将自己的路径规划器设置成插件（plugin）

1. 先编译好工作空间，此时会在`devel/lib`文件夹下生成之前我们自己的库文件

2. 在包下添加`relaxed_astar_planner_plugin.xml`文件

   写入

   ```xml
   <library path="lib/librelaxed_astar_lib">
   <!--    上面这个路径是catkin_make生成的库文件-->
       <class name="RAstar_planner/RAstarPlannerROS" type="RAstar_planner::RAstarPlannerROS" base_class_type="nav_core::BaseGlobalPlanner">
           <description>This is Relaxed Astar global planner plugin by iroboapp project.</description>
       </class>
   </library>
   ```

3. 为插件在ROS系统中进行注册，在自己包的`package.xml`文件中，添加
  ```xml
    <export>
      <nav_core plugin="${prefix}/relaxed_astar_planner_plugin.xml"/>
    </export>
  ```
  ```

  同时应该确保包时依赖与`nav_core`的，即在该文件中必须包含

  ```xml
  <build_depend>nav_core</build_depend>
  <exec_depend>nav_core</exec_depend>
  ```

4. 检查是否注册成功

   ```bash
   catkin_make
   source devel/setup.zsh
   rospack plugins --attrib=plugin nav_core
   ```

   输出

   ```bash
   move_slow_and_clear /opt/ros/kinetic/share/move_slow_and_clear/recovery_plugin.xml
   carrot_planner /opt/ros/kinetic/share/carrot_planner/bgp_plugin.xml
   teb_local_planner /opt/ros/kinetic/share/teb_local_planner/teb_local_planner_plugin.xml
   global_planner /opt/ros/kinetic/share/global_planner/bgp_plugin.xml
   rotate_recovery /opt/ros/kinetic/share/rotate_recovery/rotate_plugin.xml
   navfn /opt/ros/kinetic/share/navfn/bgp_plugin.xml
   clear_costmap_recovery /opt/ros/kinetic/share/clear_costmap_recovery/ccr_plugin.xml
   dwa_local_planner /opt/ros/kinetic/share/dwa_local_planner/blp_plugin.xml
   base_local_planner /opt/ros/kinetic/share/base_local_planner/blp_plugin.xml
   trajectory_planning /home/chrisliu/Robocon20/simulation/sim_ws/src/trajectory_planning/relaxed_astar_planner_plugin.xml
   ```

   可以看到最后一行即为我们要注册的插件

## 3.使用自己写的规划器

在启动`move_base`节点的launch文件中，设置全局规划器为自己在先前所定义的名字如下

```xml
<node pkg="move_base" type="move_base" respawn="false" name="move_base" output="screen">
        <rosparam file="$(find mapping)/config/costmap_common_params.yaml" command="load" ns="global_costmap"/>
        <rosparam file="$(find mapping)/config/costmap_common_params.yaml" command="load" ns="local_costmap"/>
        <rosparam file="$(find mapping)/config/local_costmap_params.yaml" command="load"/>
        <rosparam file="$(find mapping)/config/global_costmap_params.yaml" command="load"/>
        <rosparam file="$(find mapping)/config/teb_local_planner_params.yaml" command="load"/>

        <param name="base_global_planner" value="RAstar_planner/RAstarPlannerROS"/>

        <param name="base_local_planner" value="teb_local_planner/TebLocalPlannerROS"/>
    </node>
```





