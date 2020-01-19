#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ros/ros.h"
#include "escdriver.h"
#include "eos_msgs/gamepad_output.h"

void inputCallback(const eos_msgs::gamepad_output::ConstPtr &msg)
{
    std::cout << msg->id << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "motor_driver");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    // Check to make sure this works.
    ESCDriver rwMotor(0, 500000lu, 1500000lu, 2000000lu, false);

    // Initialize the ESC driver, needs a HIGH signal to init.
    rwMotor.start();
    rwMotor.send(255, 0, 255);
    sleep(2);
    rwMotor.send(0, 0, 255);


    ros::Subscriber input_sub = n.subscribe("motor_control", 1000, inputCallback);

    ros::spin();
}