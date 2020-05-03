# Hardware setup #

This section explains how to configure the hardware_setup function. This function needs to be in your sketch. For example, in the line following robot looks like this:

	void hardware_setup(){
		new DCMotor_Transistor(11, "right_motor", 2.5, -2.1415, 1);
		new DCMotor_Transistor(10, "left_motor", 2.5, -2.1415, 1);
		new ServoMotor(3, "servo_joint", 2.5, -2.1415, 1);
		new VisionSensor(9, "left_IR", 0.5);
		new VisionSensor(8, "right_IR", 0.5);
		new ProximitySensor(7, "front_IR", 0.16, 0.3);
	}

## Table of contents
1. [Motors](##motors)
	1. [DCMotor_Transistor](####dcmotor_transistor)
2. [Sensors in CoppeliaSim](##sensorsincoppeliasim)
    1. [ProximitySensor](####proximitysensor)
3. [Sensors and LEDs in the User Interface](##sensorsandledsintheuserinterface)

## Motors ##

Each motor is needs some standard arguments:

* an string_id
* one or more pins of the Arduino
* max torque of the motor in Nm
* max speed of the motor in rad/s
* a reduction parameter

The string_id needs to match with the name of a joint in the CoppeliaSim model. The max force of the motor should be found in the datasheet of the motor. The max speed should be also found in the datasheet if it is available. If not, you can use an approximate value.  The reduction parameter is the reduction rate of the motor to the joint that is moving. For example, in the line following robot, there are two DC motor and each motor is connected to the wheels of the robot directly. Therefore, the reduction parameter is one on both cases. If there were a reduction 1:2 (motor gear of 8 teeth and wheel gear of 16 teeth), the reduction parameter would be 0.5. In the case of the servo motor, the servo is connected to a linkage that transforms the rotation of the servo into linear movement. 90 degrees (1.57 radians) of servo rotation produce 25mm (0.025m) of motion. Then the reduction parameter is 0.016 (0.025/1.57).

Currently, there are three motors supported (DC motors, stepper motors and servo motors) and the DC motors can be controlled with a transistor or with a motor controller (H-bridge). The constructors (the function that creates an object in C++) should be called with the word "new" before the constructor. And of course, end the call with a semicolon. The syntax is as follow.

#### DCMotor_Transistor ####

	new DCMotor_Transistor(arduino_pin, "name_joint", torque, speed, reduction);

** Parameters **

* pin: the Arduino pin number where the hardware is connected to the driver of the motor.
* name_joint: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_motor").
* torque: The torque of the motor from the datasheet in Nm.
* speed: The nominal speed of the motor in rad/s
* reduction: The reduction ratio between the motor and the axis of movement. This value represents the transmission (gears, belts, lead-screw) and it will reduce the speed the axis and increase its force/torque.

** Notes: **

This motor, controlled by a transistor, can only turn in one direction. In the hardware, you can change the rotation direction by wiring the motor in the opposite polarity. To imitate this behavior in the simulator, just give a positive or negative speed value.

#### DCMotor_Hbridge ####

	new DCMotor_Hbridge(in1_pin, in2_pin, en_pin, "name_joint", torque, speed, reduction);

** Parameters: **

* in1_pin: the Arduino pin number where the hardware is connected to in1 of the driver.
* in2_pin: the Arduino pin number where the hardware is connected to the in2 of the driver.
* en_pin: the Arduino pin number where the hardware is connected to the enable pin in driver.
* name_joint: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_motor").
* torque: The torque of the motor from the datasheet in Nm.
* speed: The nominal speed of the motor in rad/s
* reduction: The reduction ratio between the motor and the axis of movement. This value represents the transmission (gears, belts, lead-screw) and it will reduce the speed the axis and increase its force/torque.

** Notes: **

The in1 and in2 signals decide the direction of the turning or if the motor is stopped. The enable pin shutdowns the motor independently of the values in in1 and in2. This enable pin is used to control the speed of the motor by generating a PWN signal.  

#### ServoMotor ####

	new ServoMotor(arduino_pin, "name_joint", torque, speed, reduction);

** Parameters **

* pin: the Arduino pin number where the hardware is connected to the driver of the motor.
* name_joint: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_motor").
* torque: The torque of the motor from the datasheet in Nm.
* speed: The nominal speed of the motor in rad/s
* reduction: The reduction ratio between the motor and the axis of movement. This value represents the transmission (gears, belts, lead-screw) and it will reduce the speed the axis and increase its force/torque.

** Notes: **

This motor has a feedback loop and it will try to reach a target position. The servo always starts at its center position. Therefore, the axis in the model should be centered too.
	
#### StepperMotor ####

	new StepperMotor(dir_pin, step_pin, "name_joint", torque, speed, reduction);

** Parameters **

* dir_pin: the Arduino pin number that is connected to the direction pin in the stepper driver. It controls the turning direction.
* step_pin: the Arduino pin number that is connected to the step pin in the stepper driver. 
* name_joint: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_motor").
* torque: The torque of the motor from the datasheet in Nm.
* speed: The nominal speed of the motor in rad/s
* reduction: The reduction ratio between the motor and the axis of movement. This value represents the transmission (gears, belts, lead-screw) and it will reduce the speed the axis and increase its force/torque.

** Notes: **

To generate movement, you need to select a turning direction with the dir pin and generate s a sequence of steps in the step pin. The motor moves one step at every rising edge (LOW to HIGH transition). Currently, only 200 steps/revolution servos are implemented. Only full step is implemented.  

## Sensors (in CoppeliaSim) ##

Each sensor needs some standard arguments:

* an string_id
* one pin of the Arduino, where the sensor is connected.

The string_id needs to match with the name of a sensor in the CoppeliaSim model. Currently, there are two sensors supported (proximity sensors and vision sensors) The constructors (the function that creates an object in C++) should be called with the word "new" before the constructor. And of course, end the call with a semicolon. The syntax is as follow.

#### ProximitySensor ####

	ProximitySensor(pin, "name_sensor", range,  threshold);

** Parameters **

* pin: the Arduino pin number where the sensor is connected. 
* name_sensor: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_proximity_sensor").
* range: The maximum range that the proximity sensor is able to detect
* threshold: A value between 0 and 1 that determines the digital value of the output.

** Notes: **

These sensors simulate infrared (IR), ultrasound (US) and laser sensors. It can also be used to simulate a switch or a pushbutton in the simulation if it is used as digital sensor.

These sensors can be used as analog or digital sensors. If it is used as an analog sensor, it should be connected to a analog input and the threshold value is ignored. If it used as a digital sensor, the threshold value imitates the potentiometer that is usually found in these devices.

**Important: The sensor in CoppeliaSim needs to have the same range as in his function. Additionally, the offset of the sensor in CoppeliaSim needs to be set to 0. If not, the sensor will not work properly.** 

#### VisonSensor ####

	VisionSensor(pin, "name_sensor", threshold);

** Parameters **

* pin: the Arduino pin number where the sensor is connected. 
* name_sensor: the name of the joint in CoppeliaSim. This parameter should go between "" (for example: "left_vision_sensor").
* threshold: A value between 0 and 1 that determines the digital value of the output.

** Notes: **

These sensors simulate an infrared (IR) sensor that is placed to detect colors. Usually, they are used to detect a transition wrom white to back in line following robots or in encoders. 

These sensors can be used as analog or digital sensors. If it is used as an analog sensor, it should be connected to a analog input and the threshold value is ignored. If it used as a digital sensor, the threshold value imitates the potentiometer that is usually found in these devices.

## Sensors and LEDs in the User Interface ##

In most projects, there is a user who interacts with the machine. This interaction is usually performed with different kind of buttons and potentiometers. In addition, there are LEDs to provide feedback to the user. You can use these kinds of hardware in the simulator. However, they are not part of the physical simulation in CoppeliaSim. Instead, they are just created in an user interface. 

The constructors (the function that creates an object in C++) should be called with the word "new" before the constructor. And of course, end the call with a semicolon. The syntax is as follow.

** The names of the user interface elements should be uniques, if not they will not work properly! **

#### Led_UI ####

	new Led_UI(pin, "name", color);
	new Led_UI(pin, "name");

** Parameters **

* pin: the Arduino pin number where the LED is connected. 
* name: the name of the LED for identification. This parameter should go between "" (for example: "left_vision_sensor").
* color (optional): The color of the LED: LED_RED or LED_GREEN (without ""). The default color is LED_RED.

** Notes: **

Currently the anode of the LED is connected to the Arduino and the cathode to ground (of course, with a resistor to limit the current). This means that the LED will be on if the pin of the Arduino is a HIGH. The brightness of the LED can be controlled through PWM if configured correctly.


#### Potentiometer_UI ####

	new Potentiometer_UI(pin, "name", init_state);

** Parameters **

* pin: the Arduino pin number where the wiper of the potentiometer is connected. 
* name: the name of the potentiometer for identification. This parameter should go between "" (for example: "potentiometer 1").
* init_state: A value from 0 to 1 that represents the position of the knob of the servo (for example, 0: left, 0.5: center, 1:right)

** Notes: **

The other two ends of the potentiometer are connected to Ground and 5V respectively. As in real life, the potentiometer can be connected to analog or digital inputs.

#### PushButton_Momentary_UI ####

	new PushButton_Momentary_UI(pin, "name", type);

** Parameters **

* pin: the Arduino pin number where the push button is connected. 
* name: the name of the push button for identification. This parameter should go between "" (for example: "potentiometer 1").
* type: PULL_UP or PULL_DOWN. 

** Notes: **

This button will not latch. 

#### ToggleButton_Latching_UI ####

	new ToggleButton_Latching_UI(pin, "name", type);

** Parameters **

* pin: the Arduino pin number where the toggle button is connected. 
* name: the name of the toggle button for identification. This parameter should go between "" (for example: "potentiometer 1").
* type: PULL_UP or PULL_DOWN. 

** Notes: **

This button will latch. 

