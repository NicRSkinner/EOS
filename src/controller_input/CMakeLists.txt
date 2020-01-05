cmake_minimum_required(VERSION 2.8.3)
project(controller_input)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  eos_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_dependencies(
  eos_msgs_generate_messages
  eos_msgs_gencpp
  eos_msgs_genpy  
)