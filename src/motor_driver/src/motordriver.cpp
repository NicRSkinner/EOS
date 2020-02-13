#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ros/ros.h"
#include "DRF0601.h"
#include "eos_msgs/Motor.h"

// Check to make sure this works.
DRF0601 rwMotor(1, 4, 5, 255);

void rearWheelInputCallback(const eos_msgs::Motor::ConstPtr &msg)
{
    std::cout << msg->speed << std::endl;

    // After testing, change speed to be always positive, but a reverse flag in the message.
    if (msg->speed >= 0)
    {
        rwMotor.send(msg->speed, false);
    }
    else
    {
        rwMotor.send(msg->speed * -1, true);
    }
}

void steeringInputCallback(const eos_msgs::Motor::ConstPtr &msg)
{

}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "motor_driver");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    rwMotor.start();

    ros::Subscriber rw_input_sub = n.subscribe("motor_control_rear_drive", 1000, rearWheelInputCallback);
    ros::Subscriber sw_input_sub = n.subscribe("motor_control_steering", 1000, steeringInputCallback);
    
    ros::spin();
}