# Install script for directory: /home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/chrisliu/Robocon20/simulation/sim_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/chrisliu/Robocon20/simulation/sim_ws/build/teb_local_planner_tutorials/catkin_generated/installspace/teb_local_planner_tutorials.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/teb_local_planner_tutorials/cmake" TYPE FILE FILES
    "/home/chrisliu/Robocon20/simulation/sim_ws/build/teb_local_planner_tutorials/catkin_generated/installspace/teb_local_planner_tutorialsConfig.cmake"
    "/home/chrisliu/Robocon20/simulation/sim_ws/build/teb_local_planner_tutorials/catkin_generated/installspace/teb_local_planner_tutorialsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/teb_local_planner_tutorials" TYPE FILE FILES "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/teb_local_planner_tutorials" TYPE DIRECTORY FILES
    "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/launch"
    "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/cfg"
    "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/maps"
    "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/stage"
    "/home/chrisliu/Robocon20/simulation/sim_ws/src/teb_local_planner_tutorials/scripts"
    REGEX "/\\.svn$" EXCLUDE)
endif()

