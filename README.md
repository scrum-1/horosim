![Line following robot demo](videos/line_following_robot_sim.gif)

# HoRoSim #

HoRoSim (Holistic Robotic Simulator) allows you to simulate physical devices controlled by Arduino code. The user defines standard electronic circuits that are employed in the Arduino code (see [Hardware Setup function](#markdown-header-hardware_setup)) and a robot simulator, CoppeliaSim, simulates the physics of the device. Thus, HoRoSim simulates Arduino code with a physics engine and based on the electronic circuits defined. You can use the Arduino IDE to compile the code and run it, see instructions bellow. Please, be aware that this program can have bugs. I programmed it fast as it is available for "How To Make (Almost) Anything" students at the IT University of Copenhagen. If you find a bug or something is not well modeled, please, fill a bug report or send me an email.

The simulator has been described in this [article](docs/faina2021RIE_HoRoSim_postprint.pdf), which has been published on the 13th International Conference on 2021 Robotics in Education conference. Cite:

Faiña A. (2022) HoRoSim, a Holistic Robot Simulator: Arduino Code, Electronic Circuits and Physics. In: Merdan M., Lepuschitz W., Koppensteiner G., Balogh R., Obdržálek D. (eds) Robotics in Education. RiE 2021. Advances in Intelligent Systems and Computing, vol 1359. Springer, Cham. https://doi.org/10.1007/978-3-030-82544-7_24


## Features ##

The simulator is able to handle most common types of motors, sensors and standard electronic devices. 

Motors:

* DC Motors with transistors
* DC Motors with motor controllers (H-bridges) like the L298N
* Stepper motors with STEP/DIR interfaces 

Sensors:

* Proximity sensors like ultrasounds or Infrareds 
* Infrareds used as vision sensors to detect colors
* Potentiometers connected to a joint in CoppeliaSim

Devices for user interfaces

* LEDs 
* Potentiometers
* Buttons (push button and toggle buttons) (momentary or matching)

TODO:

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
* writeMicroseconds
* read
* attached
* detach

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
* available
* read

Others:

* map

TODO:

* interrupts
* I2C (Wire)
* SPI


## Installation ##

See [Installation Instructions](docs/Installation.md)

## Testing the simulator ##

First, open the CoppeliaSim and load an scene with the model of your machine. For this explanation, we will use the line following robot example. You need to download the scene from the repository, you can find it [here](examples/lineFollowingRobot/line_following_robot.ttt).  If you downloaded the repository, you can find it in the folder "examples/lineFollowingRobot/". To load the scene, go to File->Open Scene... in CoppeliaSim. You should select the file (line_following_robot.ttt). After this, you should see the black line on the floor and the robot. Then, you are ready to run your Arduino code. You don't need to touch anything in CoppeliaSim, the simulation will start automatically when you run your program. However, you can use your mouse to rotate (middle button of the mouse) and translate (left button of the mouse) the view in CoppeliaSim. 

Second, open the Arduino IDE and open the robot_with_dc_motors.ino sketch that comes with the repository (examples/lineFollowingRobot/robot_with_dc_motors folder). To do that, open the Arduino IDE and press File->Open and locate the robot_with_dc_motors sketch in HoRoSim/examples/lineFollowingRobot/robot_with_dc_motors/robot_with_dc_motors.ino. 

Third, select the Board ArduinoUno_HoRoSim in the Arduino IDE. Tools->Board->ArduinoUno_HoRoSim. It can be at the bottom, so maybe you have to scroll down in the Board menu. This will change the compiler and, instead of compiling your code for the microcontroller, it will compile the code to use the CoppeliaSim simulator.

Fourth, press verify. It should generate a few warnings but not errors. 

Now, we will run the program that we have generated. Please, be sure that you have CoppeliaSim simulator open and the scene loaded. Now, you have three options to initiate your program.

Option 1

This is the easiest way to run a program. Just press the upload button of the IDE and the code will run. The output of you program can be seen at the bottom of the Arduino IDE (where the messages and errors appear). To stop the program, just close the user interface window.

**Note for Windows users: the Arduino IDE cannot show the output of your program (Serial.write/print). If you need it, use the option 2 or 3 to debug your code using Serial.write/print.** 
**Note for Linux users: the Arduino IDE shows the output (Serial.write/print) in chunks and you will not see a smooth output. So, it is better to use the option 2 or 3 to debug your code using Serial.write/print.** 


Option 2 (does not work in WSL):

For option 2 and 3, we will need a terminal. In the Arduino IDE, press Sketch->Export compiled Binary. This moves the compiled binary to your sketch folder. Then in the terminal, go to your sketch folder. You can press Sketch->Show Sketch Folder to open a file explorer at the sketch folder to check its path. For example:

	cd [PATH_TO_SKETCH_FOLDER, such as /home/htmaa/Arduino/arduino2vrepsim/examples/lineFollowingRobot/Test]

And run the compiled program. 

In Linux:

	./robot_with_dc_motors.ino.exe

In Windows:

	robot_with_dc_motors.ino.exe

Option 3:

The third option is to run the program from the folder where Arduino compiles your program. You can find the folder in the last line that is shown when compiling. If you cannot find it, be sure that the option "Show verbose option during compilation" is checked in File->Preferences in the Arduino IDE. In Linux, this is done in the temp folder (/tmp usually), in Windows usually is C/:Users/user/Documents/AppData/. In the virtual machine is in /tmp/arduino_build_XXXXXX/, where XXXXXX are six numbers. Go to this folder and find the executable, which is the name of your sketch (Test.ino):

In Linux and MacOS:

	cd [PATH_TO_TEMP_FOLDER, such as /tmp/]
	ls -l | grep "arduino_build*"
	(you will see one or more folders like arduino_build_XXXXXX, go to the more recent folder)
	cd arduino_build_836444/
	./robot_with_dc_motors.ino

In Windows: open a command prompt window (Press Windows+R to open "Run", type "cmd" and then click "OK") 

	cd [PATH_TO_TEMP_FOLDER, such as C:\Users\anfv\AppData\Local\Temp]
	dir arduino_*
	(you will see a folder like arduino_build_XXXXXX, go to the more recent folder)
	cd arduino_build_836444/
	robot_with_dc_motors.ino

As soon as you initiate your program, the robot should move in the CoppeliaSim simulator. In this example, the robot will move in circles. In order to stop the program, press Ctr+C in the terminal. This will stop your program and reset the scene.

Now, you can program the Arduino so the robot follows the line, grasps the can and places it at the intersection. Yes, it is possible :-) 

Every time that you change your code:
* press verify in the Arduino IDE (or press "Export compiled Binary")
* change to the terminal that you used to run your program for the last time
* run your new program (./robot_with_dc_motors.ino)

I recommend that your Arduino program is saved in /home/htmaa/Arduino. So you keep a clean copy of the repository files and you can upgrade the source code easily.

#### Examples

I provide with three different examples. The first one is the line following robot. The second one is an example of the user interface (buttons, potentiometers and LEDs). The third one is a proportinal controller. For more information about the examples, check the [examples page](docs/Examples.md)

## Hardware setup ##

In order to be able to use you machine you should define the kind of electronics and motors and sensors that you will employ. This is done in the model and in the Arduino code. 

In the model, the movements of your machine are defined by joints. Each joint represents a degree of freedom of your machine and they can be rotational or prismatic (linear). In addition, the vision sensors or proximity sensors should be in the model. All the sensors and joints have a name, which should be unique. 

In the Arduino code, you should specify the all electronic elements that you are going to use. This is done in a function called hardware_setup, see below an example:

	void hardware_setup(){
		new DCMotor_Transistor(11, "right_motor", 2.5, -4.1415, 1);
		new VisionSensor(9, "left_IR", 0.5);
		new Potentiometer_UI(A0, "pot 1", 0.3);
	}

In this example, we are using a DC motor controlled with a transistor, a vision sensor (IR sensor to detect colors) and a potentiometer that the user can control. Notice that the first parameter is the pin of the Arduino where these devices are connected (11, 9 and A0 respectively). The second argument is the name of the joint or sensor in CoppeliaSim or the user interface ("right_motor", "left_IR" and "pot 1"). If the names of the motors or sensors does not match any joint or sensor in CoppeliaSim, there will be an error. Be aware,that other devices need more that one pin (such as stepper drivers or H-bridge motor controllers).

For detailed documentation about how to define the electronic devices, check the [Hardware Setup page](docs/HardwareSetup.md)


## Creating a model of your robot/machine/device) ##

If you are interested in learning how the model has been created or of you want to fine tune your model, a good tutorial can be found [in this link](https://www.coppeliarobotics.com/helpFiles/en/bubbleRobTutorial.htm). If you want to give your model a realistic appearance, you can use [this tutorial](https://www.coppeliarobotics.com/helpFiles/en/buildingAModelTutorial.htm). 

Some videos explaining how to create your models in CoppeliaSim can be found [here](https://www.youtube.com/watch?v=wHrgG9ZYh24) or [here](https://www.youtube.com/playlist?list=PLjzuoBhdtaXOoqkJUqhYQletLLnJP8vjZ).

For the sake of completeness, a very brief explanation about how to modify the provided examples is given below.

### Fine tuning your model

Maybe you just want to adjust the model a bit to add a new sensor or a new feature. You are welcome to modify your model.

#### Adding an physical object

In order to add a physical object you have to load your initial model and go to Add->Primitive Shape->Cuboid or Add->Primitive Shape->Sphere or Add->Primitive Shape->Cylinder. Then, a new object will be in the Scene hierarchy (the left panel where you can see the scene objects). The object will be free and will react to forces caused by your motors or the gravity. If it needs to be fixed to another object you have two options: (1) Add a force sensor (Add-Force Sensor) or (2) group your object with the other object.

Option 1: Move the sensor, press the "Object/item shift" button  in the button menu (a cube with four small arrows). A menu will show up. Put the sensor close to the object that is already in your model by dragging it with the mouse or by giving a specific position. Then, repeat the process with the new object and rotate it if it is necessary ("Object/item rotate" button, which is next to the move object button). Now, the sensor and object are in place but they will behave as independent objects. To attach them to the object, drag the force sensor to the object that is in your model in the Scene hierarchy. Then, drag the new object to the force sensor in the Scene hierarchy. Now, both objects are linked during the simulation.

Option 2: You can select the two objects (using control and clicking them) and then do a right click and select the option "Edit->Grouping/Merging->Group Selected Shapes". This will probably change the hierarchy that you had before. You need restore it by dragging the objects in the Scene hierarchy. You can press Control+Z to undo the changes and see the previous hierarchy. 

#### Adding a sensor

In order to add a sensor you have to load your initial model and go to Add->Vision Sensor->Orthographic type or Add->Proximity Sensor->Ray type. As soon as you do this, a sensor will be added to the the scene. For proximity sensors, you need to adjust the range of the sensor. Double click on its icon in the Scene hierarchy (the left panel where you can see the scene objects) and a menu will pop up. Press "show volume parameters" and in that menu set the offset to 0 and set range to an appropriate value for your sensor (a few cm for IRs and up to 2 or 3 meters for US). remember the range to set this parameter in the hardware setup function. When the sensor is configured, it needs to be placed as a child of a physical object of your model. Then the sensor will be attached to this object. To do this, drag the sensor to the object in the scene hierarchy. The sensor will probably need to be move to its right position. To do that, use the "object/item shift" in the button menu (see the previous section for more info). Finally, the objects that the the proximity sensors are going to detect need to be modified. Double click on this object in the scene hierarchy and press the common tab. Here check the checkbox called "detectable". Then, this object will be detected by the proximity sensors.

Remember to rename the sensor to use it as parameter in the hardware_setup function. You can rename it by double clicking **on the text** of the sensor in the Scene hierarchy.

#### Adding a motor

This follows the same procedure as for the sensors and objects. First, add a joint (Add->Joint->Revolute or Add->Joint->Prismatic). Then move it to the right place. Finally, drag it to its parent object and drag another object to be its child in the Scene hierarchy. Note that this is a physics simulation. The parameters of the motors are set through the hardware_setup function and they do not need to be changed in CoppeliaSim.

## Known issues

## Changelog

HoRoSim 0.1.2

* Fixed issue (UI was not shown in Arduino IDE 2.0)

HoRoSim 0.1.1

 * Added a Serial Monitor.
 * Implemented Serial available and read.
 * Changed Serial print and write to use standard Arduino functions.
 * The Arduino sketch is run in its own thread, this fixed the issues with big delays.
 * Added more examples

HoRoSim 0.1.0 

 * First release of the software.
 * Added a Windows Installer
 * Fixed bug with negative values in analogWrite
 * Implemented map function
  

## Questions? ##

Please, send me an email.

