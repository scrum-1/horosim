# Installation #

The installation can be a bit tricky, specially if you are not used to install libraries and developing tools. However, I have tried to give step by step instructions and there is a windows installer. 

## Introduction ##

HoRoSim uses differents programs to work:

1. CoppeliaSim simulator
2. Arduino IDE (>1.5.0)
3. c++ compiler (g++) and glut libraries
4. The HoRoSim source code

## Windows installation

### Step 1: CoppeliaSim Simulator

Install the CoppeliaSim simulator for your operating system. Link: [CoppeliaSim simulator](https://www.coppeliarobotics.com/). 

### Step 2: Arduino IDE (>1.5.0 and <2.0)

Download the Arduino IDE from the [Arduino website](https://www.arduino.cc/en/software) and install it in you system. The Arduino IDE 1.8.14 is the last stable version. **Do not download the Arduino 2.0, which is still in beta and uses a completely new system** 

### Step 3: HoRoSim source code, g++ and glut libraries

The recommended installation is to use the provided installer, only attempt to follow the advanced installation if you are a developer.

#### Basic installation
Doanload the installer from [here](https://www.dropbox.com/s/i1m1ydk95hfnojd/HoRoSim_Installer.exe?dl=0). Before running the installer, be sure that the Arduino IDE is installed. Follow the installer, which will install a g++ compiler, HoRoSim source files and the glut libraries. Be sure to select the Arduino´s sketchbook folder as installation directory, and press yes to install the compiler and to add it to the PATH environmental variable. **Do not modify the g++ installer options. If you change the architecture or the installation folder, HoRoSim will not work!** 

#### Advanced installation (not recommended)

This section provides the steps to install and c++ compiler, glut libraries and the HoRoSim source code in Windows. Another option would be to use the WSL. If you do that, install WSL and follow the linux instructions. [Here](https://docs.microsoft.com/en-us/windows/wsl/install-win10) you have a guide to install WSL. **Note: WSL2 will not work! The programs communicate through TCP/IP communications and all of them need to run in the same IP).**  

If you prefer to install the compiler and libraries in Windows, follow the following steps.

Install MingW-W64-builds, which provides a g++ for Windows. It is available for download [here](https://sourceforge.net/projects/mingw-w64/). Select the MingW-W64-builds option, download it and install it. Use the default options. 

**Note: I tried Visual Studio, but you cannot use it from a normal terminal (you need to use a special terminal). Thus, you can use Visual studio, but then you cannot use the Arduino IDE to compile it. There is no support for Visual Studio** 

**Note: MinGW will not work as it does not provide POSIX support.** 

Now, you need to add the path of the folder where the binaries of the compiler are installed to the %PATH% environment variable. Press in the START icon, type "Edit the system environment variables", and click on the icon that appears. In that menu, click on "Environment Variables...". In the next menu, select the Path variable under "System variables" and click on edit. Now, press the New button and type the path to the folder where the binaries or the compiler are. Im my system, it looks like: C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin

Click on the OK button three times to close the three windows. Now, you could check that everything went well by checking the version of the compiler. Press START button, type "cmd" and press on the Command Promt app that appears. In that window, type

	g++ --version 

You should see something like:

	C:\Users\anfv>g++ --version
	g++ (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0
	Copyright (C) 2018 Free Software Foundation, Inc.
	This is free software; see the source for copying conditions.  There is NO
	warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

If so, the compiler is installed and it can be found by the system. Well done!


Now, it is time to get the HoRoSim source code. When the Arduino IDE is installed, run it. In the Arduino IDE, go to File-> Preferences and locate the Sketchbook location. In my case, it is in C:\fai\documents\Arduino. Go to this folder and check if there is a folder called "hardware". If not, create it. 

If you know how to use git, clone the HoRoSim repository in the hardware folder. If not, you can download the source code from the [HoRoSim repository](https://bitbucket.org/afaina/horosim/src/master/). To do that, open the repository in a web browser and click on the "..." button next to the clone button. Then, select "Download repository". Extract the zip file and copy the horosim folder in the hardware folder.

In my case, the structure is C:\fai\documents\Arduino\hardware\HoRoSim.


Now we need to install the OpenGL and GLUT libraries (Yes, they are very old but they are easy to use and install). 

The easiest option is to download them already compiled. They are available [here](https://www.transmissionzero.co.uk/software/freeglut-devel/). Select the "Download freeglut 3.0.0 for MinGW" option, download the zip file. Create a folder redist inside the HoRoSim folder and extract the glut libraries there. In my case, the libraries are in "C:\fai\documents\Arduino\hardware\HoRoSim\redist\freeglut". Note that the if you have installer a x64 compiler, you should replace the libraries of freeglut by the x64 libraries (they are in a folder called x64).  


HoRoSIm is installed!


## MacOs installation

### Step 1: CoppeliaSim Simulator

Install the CoppeliaSim simulator for your operating system. Link: [CoppeliaSim simulator](https://www.coppeliarobotics.com/). 

### Step 2: Arduino IDE (>1.5.0 and <2.0)

Download the Arduino IDE from the [Arduino website](https://www.arduino.cc/en/software) and install it in you system. The Arduino IDE 1.8.14 is the last stable version. **Do not download the Arduino 2.0, which is still in beta and uses a completely new system** 

### Step 3: HoRoSim source code, g++ and glut libraries

In MacOS, the installation of the compiler and the libraries is straight forward. Simply, open a terminal and type these commands:

	sudo apt-get update
	sudo apt-get install g++
	(type "Y" when asked)

Now, the compiler is installed and we just need the libraries to create the graphical user interface (OpenGL and GLUT). Yes, they are very old but they are easy to use and install. To install them, just type:

	sudo apt-get install freeglut3-dev
	(type "Y" when asked)

The compiler and the libraries are installed.

#### HoRoSim source code without git

When the Arduino IDE is installed, run it. In the Arduino IDE, go to File-> Preferences and locate the Sketchbook location. In my case, it is in C:\fai\documents\Arduino. Go to this folder and check if there is a folder called "hardware". If not, create it. 

If you know how to use git, clone the HoRoSim repository in the hardware folder. If not, you can download the source code from the [HoRoSim repository](https://bitbucket.org/afaina/horosim/src/master/). To do that, open the repository in a web browser and click on the "..." button next to the clone button. Then, select "Download repository". Extract the zip file and copy the horosim folder in the hardware folder.

#### HoRoSim source code with git

You could also clone the HoRoSim repository inside the hardware folder inside the Arduino´s sketchbook folder. See Linux installation for reference.


## Linux

## Step 1: CoppeliaSim Simulator (All OS) ##

Install the CoppeliaSim simulator for your operating system. Link: [CoppeliaSim simulator](https://www.coppeliarobotics.com/). 

### Step 2: Arduino IDE (>1.5.0 and <2.0)

Unfortunately, the Arduino IDE in the Ubuntu repositories is too old. We need to download and install it from the web. Use the following commands:

	wget https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz
	tar -xvf arduino-1.8.12-linux64.tar.xz
	cd arduino-1.8.12/
	sudo ./install.sh 

If you are in Windows using WSL, you need to install a X server to be able to run the Arduino IDE. I use [Xming](https://sourceforge.net/projects/xming/). Install it in Windows and run it, you will see a new icon in the system tray. In the terminal in WSL, you need to set a display, run:

	export DISPLAY=:0

Now, you should be able to run the Arduino IDE by typing:

	arduino

### Step 3: HoRoSim source code, g++ and glut libraries

In Linux, the installation of the compiler and the libraries is straight forward. Simply, open a terminal and type these commands:

	sudo apt-get update
	sudo apt-get install g++
	(type "Y" when asked)

Now, the compiler is installed and we just need the libraries to create the graphical user interface (OpenGL and GLUT). Yes, they are very old but they are easy to use and install. To install them, just type:

	sudo apt-get install freeglut3-dev
	(type "Y" when asked)

The compiler and the libraries are installed.

When the Arduino IDE is installed, run it. In the Arduino IDE, go to File-> Preferences and locate the Sketchbook location. In my case, it is /mnt/c/fai/documents/Arduino in WSL and /home/htmaa/Arduino in the Ubuntu virtual machine. Go to this folder and check if there is a folder called "hardware". If not, create it. 


	cd /mnt/c/fai/documents/Arduino
	ls -l

If there is no hardware folder, create it:

	mkdir hardware

Go to the hardware folder:
	
	cd hardware 

Then, clone the HoRoSim repository in the hardware folder (or copy all the files there). In my case, the structure is /mnt/c/fai/documents/Arduino/hardware/HoRoSim/.

If you don't have installed git, you need to install it:
	
	sudo apt-get install git
	(type "Y" when asked)

Then, clone the repository of the Arduino2Vrep:

	git clone https://bitbucket.org/afaina/horosim.git

HoRoSim is installed!


## Test the installation

The installation is completed. Follow the instructions in [Testing the simulator](../README.md). But basically, it consists on opening a scene in CoppeliaSim and press the upload button in the Arduino IDE. Enjoy it!

## Updating the software ##

If you used git, you can update the software easily. Use you the method that you prefer or open a terminal and type these commands in the terminal:

	cd [PATH_TO_HOROSIM such as /home/htmaa/Arduino/hardware/HoRoSim/]
	git pull

If you have not used git, remove the HoRoSim folder that is contained in Arduino´sSketchbookFolder/hardware and replace it with the new version. 

## Troubleshooting ##

#### If CoppeliaSim does not load on linux ####

If this error occurs:  

"terminate called after throwing an instance of 'std::runtime_error' 
what():  locale::facet:: \_S\_create\_c\_locale name not valid". Type in terminal: 	
	
	export LC_ALL=C; unset LANGUAGE

and run CoppeliaSim again.


#### Test the IP of the host machine form the virtual machine ####

Try this command in the terminal of the virtual machine

	ip route show default

The result should be something like:
	
	default via 10.0.2.2 dev enp0s3 proto dhcp metric 100

The IP shown needs to be 10.0.2.2. If not, try to change the network adapter in the virtual machine to NAT.

#### Try to see that the port in CoppeliaSim is open ####

You can check the CoppeliaSim port if you go to Tools->User settings and uncheck the option "Hide console window". On macOS, in order to see the CoppeliaSim console, you have to open the app from the terminal with coppeliaSim.app/Contents/MacOS/coppeliaSim. Then, in the console, you can find something like: 

	Plugin 'RemoteApi': loading...
	Starting a remote API server on port 19997
	Plugin 'RemoteApi': load succeeded.

#### Try to change the port ####

The program tries to find CoppeliaSim in the port 19997. If it is not found, it automatically tries the port 10000. Try to set the CoppeliaSim port to 10000 (in the remoteApiConnections.txt file). To do that, go to the folder where CoppeliaSim is installed (in my case C:\Program Files\CoppeliaRobotics\CoppeliaSimEdu ) and open the remoteApiConnections.txt file.  On MacOS, this file is in the package bundle (/.../CoppeliaRobotics/coppeliaSim.app/Contents/MacOS/remoteApiConnections.txt). In this file, change the port to 10000. It should look like this:

	portIndex1_port             = 10000
	portIndex1_debug            = false
	portIndex1_syncSimTrigger   = true

restart CoppeliaSim and run your program.

If it still does not work, try to change the port to a bigger number instead that the default 19997 (like 25876 for example). You have to change the port in line 211 of main.cpp (in folder HoRoSim\horosim\cores\horosim_corefiles) and in CoppeliaSim (remoteApiConnections.txt file, and restart CoppeliaSim).

#### CoppeliaSim crashes on MacOS ####

Try to run this command in Terminal in the directory where the coppeliaSim app is. 

	sudo xattr -r -d com.apple.quarantine *

And then try to run it from the terminal.

#### CoppeliaSim problems ####

Ask in the [CoppeliaSim forum](https://forum.coppeliarobotics.com/), they reply very fast. 

#### Try to test the CoppeliaSim examples ####

Please, try to run the example that coppelia provides, for example the python one. You have to go to CoppeliaSim folder/CoppeliaSimEdu/programming/remoteApiBindings/python/python

Copy to this directory the simulator library for your OS. You can find in CoppeliaSim folder/CoppeliaSimEdu/programming/remoteApiBindings/lib/lib/MacOS

Then, try to run the simpleTest.py
	
	python simpleTest.py

You should see something like:

	Program started
	Connected to remote API server
	('Number of objects in the scene: ', 16)
	('Mouse position x: ', 1128)
