# README #

This code simulates a line following robot controlled by an Arduino and connected as specified in the schematics document. The simulator used is Vrep and it should be installed in your computer. You can use the Arduino IDE to compile the code, but the generated program needs to be run from the terminal, see instructions bellow. Please, be aware that this program can have bugs. I programmed it fast as it is avalaible for How To Make (Almost) Anything students. If you find a bug or something is not well modelled, please, fill a bug report or send me an email.

### Hardware ###

The robot is a line following robot with two DC motors with wheels (left and right), which are connected to the base of the robot. The base contains two infrared sensors facing towards the ground that detect a black line on the floor. In addition, there is a IR sensor facing forwards that can be used to detect a can. A gripper at the front can grasp the can of the circuit. This gripper is controlled by a servomotor.

### Electronics ###

The robot contains a breadboard with two transistors to control the two DC motors. The 3 IR sensors are digital. The schematics of these devices and the Arduin are in the schematics folder. Please, check them to know which pins of the Arduino you should use.

### Software ###

You are programming an Arduino uno. I only ported a very small set of functions that you can use. These functions are listed below:

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

Serial:
* begin
* write
* print
* println

TODO:
* analogRead
* analogWrite

### Installation ###

There are a couple of requirements:

* g++ compiler
* Arduino IDE (>1.5.0)
* Vrep simulator



#### Vrep Simulator ####

Install the Vrep simulator for your operating system. Link: [Vrep simulator](https://www.coppeliarobotics.com/). 

Once is installed, go to the folder where is installed (in my case C:\Program Files\V-REP3\V-REP_PRO_EDU ) and open the remoteApiConnections.txt file. in this file, change the port to 19997. It should look like this:
portIndex1_port             = 19997
portIndex1_debug            = false
portIndex1_syncSimTrigger   = true

Now, open the vrep and load the scene from the folder scene_model_robot (File->Open Scene...). You should select the file (line_fllowing_robot.ttt). After this, you should see the circuit and the robot. Then, you are ready to run your Arduino code.

#### g++ compiler and Arduino IDE (>1.5.0)####

We need to use a c compiler. In linux, you can use g++. In Windows it is a bit more complicated. I tried to use the MinGW compiler and it did not work as it does not provide a POSIX runtime environment. I tried Visual Studio, but you cannot use it from the terminal (you need to use a special terminal). You can try to use Visual studio, but then you cannot use the Arduino IDE to compile it. I ended up using the g++ through the WSL. [Here](https://docs.microsoft.com/en-us/windows/wsl/install-win10) you have a guide to install it. Then, launch a linux terminal and install a g++ compiler using the following commands: 

sudo apt-get update
apt-get install g++

Now we need to install the Arduino IDE in WSL. Unfortunately, the Arduino IDE in the Ubuntu repositories is too old. We need to download and install it from the web. Ue the folowing commands:

wget https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz
tar -xvf arduino-1.8.12-linux64.tar.xz
cd arduino-1.8.12/
sudo ./install.sh 

If you are using WSL, you need to install a X server to be able to run the Arduino IDE. I use [Xming](https://sourceforge.net/projects/xming/). Install it in Windows and run it, you will see a new icon in the system tray. In the terminal in WSL, you need to set a display, run:
export DISPLAY=:0

Now, yuo should be able to run the Arduino IDE by typing:
arduino


#### Code ####

When the Arduino IDE is intalled, you can run it using a terminal. Go to File-> Preferences and locate the Skechbook location. In my case, it is /mnt/c/fai/documents/Arduino. Go to this folder and check if there is a folder called "hardware". If not, create it. Then clone this repository in the hardware folder (or coppy all the files there). In my case, the structure is /mnt/c/fai/documents/Arduino/hardware/Arduino2VrepSim/

You are almost ready to run your sketches. We only need to setup the path for the libraries of the vrep. Close the arduino IDE. Find the right version of the vrep libraries. They are in VREP_INSTALL_DIR/V-REP_PRO_EDU/programming/remoteApiBindings/lib/lib...
Then, type in your terminal:
export PATH=$PATH:PATH_TO_VREP_LIB 
In my case:
export PATH=$PATH:/mnt/c/Program\ Files/V-REP3/V-REP_PRO_EDU/programming/remoteApiBindings/lib/lib/Linux/64Bit/

You are done. Now, open the arduino IDE and press verify. It sould work.

### Use ###

Open the Arduino IDE and open the Test.ino sketch that comes with the repository. Press verify and it should generate a few warnings but not errors. Be sure that you have vrep open and the scene loaded. Now, open a terminal and we should go to the folder where Arduino compiles your program. In linux is where your temp foder is (/tmp usually), in Windows usually is C/:Users/user/Documents/AppData/. You can find the folder in the last line that is shown when compiling. If you cannot find it, be sure that the option "Show vervose option during compilation" is checked in File->Preferences. In my case this folder is: /tmp/arduino_build_836444/ Go to this folder and find the executable, which is the name of your sketch (Test.ino):

cd /tmp/arduino_build_836444/
./Test.ino

The robot should move in the Vrep simulator.

### Questions? ###

Please, send me an email or ask in the forum (better).

