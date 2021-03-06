#!/usr/bin/env python

# IMPORTANT: User MUST be part of the input group with rw permissions on the files.
#		Otherwise this program will not run. 
#		ROS doesn't easily allow the use of sudo permissions on programs.

# Format for the info published to the rostopic:
# Button Number, is_button, value

# If is_button is true, then value=1 is button down and value=0 is button up.

from evdev import InputDevice, categorize, ecodes
from enum import Enum
import argparse
import rospy
from eos_msgs.msg import gamepad_output

parser = argparse.ArgumentParser(description='Map Controller Inputs to ROS outputs.')
parser.add_argument('-i', '--input_event', type=str, default='/dev/input/event2',
	help='The event in /dev/input/ where the controller events come from')

LEFT_ACTION = 1
RIGHT_ACTION = 2
UP_ACTION = 3
DOWN_ACTION = 4

LEFT_DIRECTION = 5
RIGHT_DIRECTION = 6
UP_DIRECTION = 7
DOWN_DIRECTION = 8

LEFT_TRIGGER = 9
RIGHT_TRIGGER = 10
LEFT_BUMPER = 11
RIGHT_BUMPER = 12

START = 13
SELECT = 14

LEFT_STICK_MOVE_VERTICAL = 15
LEFT_STICK_MOVE_HORIZONTAL = 16
RIGHT_STICK_MOVE_VERTICAL = 17
	
RIGHT_STICK_MOVE_HORIZONTAL = 18
LEFT_STICK_PRESS = 19
RIGHT_STICK_PRESS = 20

def getGamepadOutputs():
	args = parser.parse_args()
	gamepad = InputDevice(args.input_event)
	pub = rospy.Publisher("gamepad", gamepad_output, queue_size=100)
	rospy.init_node('gamepad_publisher', anonymous=True)

	print(gamepad)

	sqBtn = 308
	xBtn = 304
	circBtn = 305
	triBtn = 307

	lBump = 310
	rBump = 311

	lTrig = 312
	rTrig = 313
	lTrigAbs = 5
	rTrigAbs = 2

	lStick = 317
	rStick = 318

	start = 315
	select = 314

	lStickUpDownAbs = 1
	lStickLeftRightAbs = 0

	rStickLeftRightAbs = 3
	rStickUpDownAbs = 4


	# updown and leftright are for the directional buttons, even though they don't have
	# values other than 255 and -255.
	# up is negative, down is positive, 0 is release.
	updown = 17

	# left is negative, right is positive, 0 is release.
	leftright = 16

	for event in gamepad.read_loop():
		eventmsg = (0, 0, 0)
		#print(categorize(event))
		if event.type == ecodes.EV_ABS:
			#print(event)
			if event.code == updown:
				if event.value < 0:
					eventmsg = (UP_DIRECTION, 1, event.value)
				elif event.value > 0:
					eventmsg = (DOWN_DIRECTION, 1, event.value)
			elif event.code == leftright:
				if event.value < 0:
					eventmsg = (LEFT_DIRECTION, 1, event.value)
				elif event.value > 0:
					eventmsg = (RIGHT_DIRECTION, 1, event.value)

			elif event.code == lTrigAbs:
				eventmsg = (RIGHT_TRIGGER, 0, event.value)
			elif event.code == rTrigAbs:
				eventmsg = (LEFT_TRIGGER, 0, event.value)

			elif event.code == lStickUpDownAbs:
				eventmsg = (LEFT_STICK_MOVE_VERTICAL, 0, event.value)
			elif event.code == lStickLeftRightAbs:
				eventmsg = (LEFT_STICK_MOVE_HORIZONTAL, 0, event.value)
			elif event.code == rStickUpDownAbs:
				eventmsg = (RIGHT_STICK_MOVE_VERTICAL, 0, event.value)
			elif event.code == rStickLeftRightAbs:
				eventmsg = (RIGHT_STICK_MOVE_HORIZONTAL, 0 , event.value)

		if event.type == ecodes.EV_KEY:
			if event.code == sqBtn:
				eventmsg = (LEFT_ACTION, 1, event.value)
			elif event.code == xBtn:
				eventmsg = (DOWN_ACTION, 1, event.value)
			elif event.code == circBtn:
				eventmsg = (RIGHT_ACTION, 1, event.value)
			elif event.code == triBtn:
				eventmsg = (UP_ACTION, 1, event.value)

			elif event.code == lBump:
				eventmsg = (LEFT_BUMPER, 1, event.value)
			elif event.code == rBump:
				eventmsg = (RIGHT_BUMPER, 1, event.value)

			elif event.code == lStick:
				eventmsg = (LEFT_STICK_PRESS, 1, event.value)
			elif event.code == rStick:
				eventmsg = (RIGHT_STICK_PRESS, 1, event.value)

			elif event.code == start:
				eventmsg = (START, 1, event.value)
			elif event.code == select:
				eventmsg = (SELECT, 1, event.value)

		if (eventmsg[0] != 0):
			newmsg = gamepad_output()
			newmsg.id = eventmsg[0]
			newmsg.is_button = eventmsg[1]
			newmsg.value = eventmsg[2]

			pub.publish(newmsg)


if __name__ == "__main__":
	try:
		getGamepadOutputs()
	except rospy.ROSInterruptException:
		pass
