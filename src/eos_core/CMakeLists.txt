cmake_minimum_required(VERSION 2.8.3)
project(eos_core)

find_package(catkin REQUIRED COMPONENTS
  eos_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(eos_main src/main.cpp)
target_link_libraries(eos_main ${catkin_LIBRARIES})