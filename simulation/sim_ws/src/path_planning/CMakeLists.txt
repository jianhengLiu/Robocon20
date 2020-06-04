cmake_minimum_required(VERSION 2.8.3)
project(path_planning)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        nav_msgs
        )
find_package(Eigen3 REQUIRED)
set(Eigen3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

catkin_package(
        INCLUDE_DIRS include
        #  LIBRARIES path_planning
        #  CATKIN_DEPENDS roscpp std_msgs
        #  DEPENDS system_lib
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${Eigen3_INCLUDE_DIRS}
)

add_executable(path_planning_node
        src/path_planning_node.cpp
        #        src/Astar_searcher.cpp
        )
target_link_libraries(path_planning_node
        ${catkin_LIBRARIES}
        )