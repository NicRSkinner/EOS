#include "ros/ros.h"
#include "eos_msgs/gamepad_output.h"
#include "eos_msgs/Motor.h"
#include <iostream>

ros::Publisher motor_publisher;

// The triggers need to have value remembered, so that it can't flop back and fourth
//      when both triggers are pressed.
void gamepadCallback(const eos_msgs::gamepad_output::ConstPtr &msg)
{
    // Right Trigger
    if (msg->id == 10)
    {
        eos_msgs::Motor out_msg;

        out_msg.id = 0;
        out_msg.name.data = "Motor Set";
        out_msg.speed = msg->value;
        out_msg.position = 0;
        out_msg.feedback = 0;

        motor_publisher.publish(out_msg);
    }
    // Left Trigger
    else if (msg->id == 9)
    {
        eos_msgs::Motor out_msg;

        out_msg.id = 0;
        out_msg.name.data = "Motor Set";
        out_msg.speed = -1 * msg->value;
        out_msg.position = 0;
        out_msg.feedback = 0;

        motor_publisher.publish(out_msg);
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "eos_core_main");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    ros::Subscriber sub = n.subscribe("gamepad", 1000, gamepadCallback);
    motor_publisher = n.advertise<eos_msgs::Motor>("motor_control_rear_drive", 1000);
    ros::spin();

    return 0;
}