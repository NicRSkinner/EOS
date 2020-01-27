#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ros/ros.h"
#include "escdriver.h"
#include "eos_msgs/Motor.h"

// Check to make sure this works.
ESCDriver rwMotor(0, 500000lu, 1500000lu, 2000000lu, false);

void rearWheelInputCallback(const eos_msgs::Motor::ConstPtr &msg)
{
    std::cout << msg->speed << std::endl;

    rwMotor.send(msg->speed, 0, 255);
}

void steeringInputCallback(const eos_msgs::Motor::ConstPtr &msg)
{

}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "motor_driver");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    // Initialize the ESC driver, needs a HIGH signal to init.
    rwMotor.start();
    rwMotor.send(255, 0, 255);
    sleep(2);
    rwMotor.send(0, 0, 255);


    ros::Subscriber rw_input_sub = n.subscribe("motor_control_rear_drive", 1000, rearWheelInputCallback);
    ros::Subscriber sw_input_sub = n.subscribe("motor_control_steering", 1000, steeringInputCallback);
    
    ros::spin();
}