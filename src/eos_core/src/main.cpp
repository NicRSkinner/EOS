#include "ros/ros.h"
#include "eos_msgs/gamepad_output.h"
#include <iostream>

void motorCallback(const eos_msgs::gamepad_output::ConstPtr &msg)
{
    std::cout << msg->id << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "eos_core_main");

    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    ros::Subscriber sub = n.subscribe("gamepad_output", 1000, motorCallback);

    ros::spin();

    return 0;
}