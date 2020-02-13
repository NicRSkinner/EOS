cmake_minimum_required(VERSION 2.8.3)
project(motor_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  eos_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}  
)

link_directories(include)

add_executable(motor_driver src/motordriver.cpp src/DRF0601.cpp)
target_link_libraries(motor_driver
  ${catkin_LIBRARIES}
  wiringPi)

add_dependencies(motor_driver
  eos_msgs_generate_messages
  eos_msgs_gencpp
  eos_msgs_genpy
)
