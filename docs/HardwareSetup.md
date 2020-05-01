# Hardware setup #

This section explains how to configure the hardware_setup function.

## Motors ##

Each motor is needs some standard arguments:

* an string_id
* one or more pins of the Arduino
* max torque of the motor in Nm
* max speed of the motor in rad/s
* a reduction parameter

The string_id needs to match with the name of a joint in the CoppeliaSim model. The max force of the motor should be found in the datasheet of the motor. The max speed should be also found in the datasheet if it is available. If not, you can use an approximate value.  The reduction parameter is the reduction rate of the motor to the joint that is moving.



## Sensors (in CoppeliaSim) ##

## Sensors and LEDs in the User Interface ##