![Line following robot demo](videos/line_following_robot_sim.gif)

# README #

This code simulates mechanisms controlled by an Arduino and several standard electronic components. The simulator used is CoppeliaSim (which was known as Vrep before) and it should be installed in your computer. You can use the Arduino IDE to compile the code, but the generated program needs to be run from the terminal, see instructions bellow. Please, be aware that this program can have bugs. I programmed it fast as it is available for How To Make (Almost) Anything students. If you find a bug or something is not well modeled, please, fill a bug report or send me an email.

__Note: In this document, Vrep and CoppeliaSim are used interchangeably. I hope to update this documentation and remove all references to Vrep soon.__

## Features ##

The simulator is able to handle most common types of motors, sensors and standard electronic devices. 

Motors:

* DC Motors with transistors
* DC Motors with motor controllers (H-bridges) like the L298N
* Stepper motors with STEP/DIR interfaces 

Sensors:

* Proximity sensors like ultrasounds or Infrareds 
* Infrareds used as vision sensors to detect colors

Devices for user interfaces

* LEDs 
* Potentiometers
* Buttons (push button and toggle buttons) (momentary or matching)

TODO (not in this semester):

* Potentiometers for joint feedback
* Joysticks for user interface
* 7 segments displays for user interface


## Software ##

You can control your device by writing code for an Arduino board. Currently, only the Arduino Uno is supported. You can program and compile your code from the Arduino IDE. I ported the most common functions. These functions are listed below:

Time:

* delay
* delayMicroseconds
* millis
* micros

Servo:

* attach
* write

I/O:

* pinMode
* digitalRead
* digitalWrite
* analogWrite
* analogRead

Serial:

* begin
* write
* print
* println

TODO:

* ~~analogRead~~
* ~~analogWrite~~
* Serial.available
* Serial.read
* interrupts


## Installation ##

There is a virtual machine with all the software ready to use, you only need to install the CoppeliaSim simulator. If you prefer to install it in your machine, I provide detailed instructions. Take into account that the installation can be a bit tricky, if you are not used to install libraries and developing tools. 

See [Installation Instructions](docs/Installation.md)

## Using the simulator ##

First, open the CoppeliaSim and load an scene with the model of your machine. For this explanation, we will use the line following robot example. If you are using the virtual machine, you need to download the scene from the repository, you can find it [here](examples/lineFollowingRobot/line_following_robot.ttt).  If you downloaded the repository, you can find it in the folder "examples/lineFollowingRobot/". To load the scene, go toFile->Open Scene... in CoppeliaSim. You should select the file (line_following_robot.ttt). After this, you should see the black line on the floor and the robot. Then, you are ready to run your Arduino code. You don't need to touch anything in CoppeliaSim, the simulation will start automatically when you run your program. However, you can use your mouse to rotate (middle button of the mouse) and translate (left button of the mouse) the view in CoppeliaSim. 

Second, open the Arduino IDE and open the Test.ino sketch that comes with the repository (examples/lineFollowingRobot folder): If you are using the virtual machine, press in nine dots button at the bottom left corner ("Show Applications") and type Arduino. Then choose the Arduino icon and go to File->Open to locate the Test sketch in /home/htmaa/Arduino/hardware/arduino2vrepsim/Test/Test.ino. 

Third, select the Board ArduinoUno2Vrep in the Arduino IDE. Tools->Board->ArduinoUno2Vrep. It can be at the bottom, so maybe you have to scroll down in the Board menu. This will change the compiler and, instead of compiling your code for the microcontroller, it will compile the code to use the CoppeliaSim simulator.

Fourth, press verify. It should generate a few warnings but not errors. 

Now, we will run the program that we have generated. Please, be sure that you have CoppeliaSim simulator open and the scene loaded. Now, you have two options to initiate your program, but we will need a terminal in both of them. If you are using the virtual machine, you can open a terminal by clicking in nine dots button at the bottom left corner ("Show Applications") and type Terminal and select the terminal icon 

Option 1 (does not work in WSL):

In the Arduino IDE, press Sketch->Export compiled Binary. This moves the compiled binary to your sketch folder. Then in the terminal, go to your sketch folder. For example:

	cd /home/htmaa/Arduino/arduino2vrepsim/examples/lineFollowingRobot/Test

And run the compiled program:

	./Test.ino.exe

Option 2:

We should find the folder where Arduino compiles your program. You can find the folder in the last line that is shown when compiling. If you cannot find it, be sure that the option "Show verbose option during compilation" is checked in File->Preferences in the Arduino IDE. In Linux, this is done in the temp folder (/tmp usually), in Windows usually is C/:Users/user/Documents/AppData/. In the virtual machine is in /tmp/arduino_build_XXXXXX/, where XXXXXX are six numbers. Go to this folder and find the executable, which is the name of your sketch (Test.ino):

	cd /tmp/
	ls -l 
	(you will see a folder like arduino_build_XXXXXX, go to this folder)
	cd arduino_build_836444/
	./Test.ino


As soon as you initiate your program, the robot should move in the CoppeliaSim simulator. In this example, the robot will move in circles. In order to stop the program, press Ctr+C in the terminal. This will stop your program and reset the scene.

Now, you can program the Arduino so the robot follows the line, grasps the can and places it at the intersection. Yes, it is possible :-) 

Every time that you change your code:
* press verify in the Arduino IDE (or press "Export compiled Binary")
* change to the terminal that you used to run your program for the last time
* run your new program (./Test.ino.exe)

I recommend that your Arduino program is saved in /home/htmaa/Arduino. So you keep a clean copy of the repository files and you can upgrade the source code easily.

## Hardware setup ##

In order to be able to use you machine you should define the kind of electronics and motors and sensors that you will employ. This is done in the model and in the Ardiono code. 

In the model, the movements of your machine are defined by joints. Each joint represents a degree of freedom of your machine and they can be rotational or prismatic (linear). In addition, the vision sensors or proximity sensors should be in the model. All the sensors and joints have a name, which should be unique. 

In the Arduino code, you should specify the all electronic elements that you are going to use. This is done in a function called hardware_setup, see below an example:

	void hardware_setup(){
		new DCMotor_Transistor(11, "right_motor", 2.5, -4.1415, 1);
		new VisionSensor(9, "left_IR", 0.5);
		new Potentiometer_UI(A0, "pot 1", 0.3);
	}

In this example, we are using a DC motor controlled with a transistor, a vision sensor (IR sensor to detect colors) and a potentiometer that the user can control. Notice that the first parameter is the pin of the Arduino where these devices are connected (11, 9 and A0 respectively). The second argument is the name of the joint or sensor in CoppeliaSim or the user interface ("right_motor", "left_IR" and "pot 1"). If the names of the motors or sensors does not match any joint or sensor in CoppeliaSim, there will be an error. Be aware,that other devices need more that one pin (such as stepper drivers or H-bridge motor controllers).

For detailed documentation about how to define the electronic devices, check the [Hardware Setup page](docs/HardwareSetup.md)


## Creating a model of your machine ##

This course not focus on simulation techniques and we will create a basic model of your machine for you. Please, contact me by mail or in the forum.

If you are interested in learning how the model has been created or of you want to fine tune your model, a good tutorial can be found [in this link](https://www.coppeliarobotics.com/helpFiles/en/bubbleRobTutorial.htm). If you want to give your model a realistic appearance, you can use [this tutorial](https://www.coppeliarobotics.com/helpFiles/en/buildingAModelTutorial.htm). However, it can take a lot of time to prepare it and it is out of the scope of the course. I strongly recommend that you focus on the contents of the course.

## Questions? ##

Please, send me an email or (better) ask in the forum .

