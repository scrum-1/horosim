# Installation #

There is a virtual machine with all the software ready to use, you only need to install the CoppeliaSim simulator. If you prefer to install it in your machine, I provide detailed instructions. Take into account that the installation can be a bit tricky, specially if you are not used to install libraries and developing tools. 


There are a couple of requirements:

* g++ compiler
* Arduino IDE (>1.5.0)
* CoppeliaSim simulator

If you do not want to install g++ or the Arduino IDE(see below, it is tricky in Windows), you can use the virtual machine that I created [Download Ubuntu Virtual Machine](https://owncloud.itu.dk/index.php/s/orL1ETlNlpRN8B8). Thus, you only need to install the CoppeliaSim simulator. 

## CoppeliaSim Simulator (Mandatory) ##

Install the CoppeliaSim simulator for your operating system. Link: [CoppeliaSim simulator](https://www.coppeliarobotics.com/). 

Once is installed, go to the folder where is installed (in my case C:\Program Files\V-REP3\V-REP_PRO_EDU ) and open the remoteApiConnections.txt file.  On MacOS, this file is in the package bundle (/.../V-REP/vrep.app/Contents/MacOS/remoteApiConnections.txt). In this file, change the port to 19997. It should look like this:

	portIndex1_port             = 19997
	portIndex1_debug            = false
	portIndex1_syncSimTrigger   = true


## Option 1: Virtual Machine with everything installed ##

I created a virtual machine in VirtualBox. First, install virtualBox from [here](https://www.virtualbox.org/). Then, download the [Ubuntu Virtual Machine](https://owncloud.itu.dk/index.php/s/orL1ETlNlpRN8B8) and extract it. Then, start the virtual machine by opening through VirtualBox. The login is "htmaa" and the password is "htmaa". You still need to install the CoppeliaSim simulator in your computer (not in the virtual machine). 

## Option 2: Install all the software in your machine ##

#### g++ compiler and libraries

We need to use a c compiler. In Linux, you can use g++. In Windows it is a bit more complicated. I tried to use the MinGW compiler and it did not work as it does not provide a POSIX runtime environment. I tried Visual Studio, but you cannot use it from the terminal (you need to use a special terminal). You can try to use Visual studio, but then you cannot use the Arduino IDE to compile it. I ended up using the g++ through the WSL. [Here](https://docs.microsoft.com/en-us/windows/wsl/install-win10) you have a guide to install it. Then, launch a Linux terminal and install a g++ compiler using the following commands: 

	sudo apt-get update
	sudo apt-get install g++
	(type "Y" when asked)

The libraries to create the graphical user interface are OpenGL and GLUT. Yes, they are very old but they are easy to use and install. To install them, just type:

	sudo apt-get install freeglut3-dev
	(type "Y" when asked)

#### Arduino IDE (>1.5.0)

Now we need to install the Arduino IDE in WSL. Unfortunately, the Arduino IDE in the Ubuntu repositories is too old. We need to download and install it from the web. Use the following commands:

	wget https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz
	tar -xvf arduino-1.8.12-linux64.tar.xz
	cd arduino-1.8.12/
	sudo ./install.sh 

If you are using WSL, you need to install a X server to be able to run the Arduino IDE. I use [Xming](https://sourceforge.net/projects/xming/). Install it in Windows and run it, you will see a new icon in the system tray. In the terminal in WSL, you need to set a display, run:
export DISPLAY=:0

Now, you should be able to run the Arduino IDE by typing:
	arduino

#### Source code 

When the Arduino IDE is installed, you can run it using a terminal. Go to File-> Preferences and locate the Sketchbook location. In my case, it is /mnt/c/fai/documents/Arduino and /home/htmaa/Arduino in the Ubuntu virtual machine. Go to this folder and check if there is a folder called "hardware". If not, create it. 

	cd /mnt/c/fai/documents/Arduino
	ls -l

If there is no hardware folder. create it:
	mkdir hardware

Go to the hardware folder:
	
	cd hardware 

Then clone this repository in the hardware folder (or copy all the files there). In my case, the structure is /mnt/c/fai/documents/Arduino/hardware/Arduino2VrepSim/.

If you don't have installed git, you need to install it:
	
	sudo apt-get install git
	(type "Y" when asked)

Then, clone the repository of the Arduino2Vrep:

	git clone https://bitbucket.org/afaina/arduino2vrepsim.git

Removed as I think it is not necessary:
~~You are almost ready to run your sketches. We only need to setup the path for the libraries of the CoppeliaSim. Close the Arduino IDE. Find the right version of the CoppeliaSim libraries. They are in VREP_INSTALL_DIR/V-REP_PRO_EDU/programming/remoteApiBindings/lib/lib...
Then, type in your terminal:~~

~~export PATH=$PATH:PATH_TO_VREP_LIB ~~

~~In my case:~~
	
~~export PATH=$PATH:/mnt/c/Program\ Files/V-REP3/V-REP_PRO_EDU/programming/remoteApiBindings/lib/lib/Linux/64Bit/~~

You are done. Now, open the Arduino IDE and press verify. It should work.


## Updating the software ##

You can update the software by using these commands in the terminal:

	cd /home/htmaa/Arduino/hardware/arduino2vrepsim/
	git pull

## Troubleshooting ##

### If CoppeliaSim does not load on linux

If this error occurs:  

"terminate called after throwing an instance of 'std::runtime_error' 
what():  locale::facet:: \_S\_create\_c\_locale name not valid". Type in terminal: 	
	
	export LC_ALL=C; unset LANGUAGE

and run CoppeliaSim again.


### Test the ip of the host machine form the virtual machine ###
Try this command in the terminal of the virtual machine

	ip route show default

The result should be something like:
	
	default via 10.0.2.2 dev enp0s3 proto dhcp metric 100

The ip shown needs to be 10.0.2.2. If not, thry to change the network adapter in the virtual machine to NAT.

### Try to see that the port in CoppeliaSim (Vrep) is open ###

You can check the CoppeliaSim port if you go to Tools->User settings and uncheck the option "Hide console window". On macOS, in order to see the V-REP console, you have to open the app from the terminal with vrep.app/Contents/MacOS/vrep. Then, in the console, you can find something like: 

	Plugin 'RemoteApi': loading...
	Starting a remote API server on port 19997
	Plugin 'RemoteApi': load succeeded.

### Try to change the port ###

The program tries to find CoppeliaSim in the port 19997. If it is not found, it automatically tries the port 10000. Try to set the CoppeliaSim port to 10000 (in the remoteApiConnections.txt file), restart CoppeliaSim and run your program.

If it still does not work, try to change the port to a bigger number instead that the default 19997 (like 25876 for example). You have to change the port in line 83 of main.cpp (in folder Arduino2VrepSim\vrep\cores\VrepSim_corefiles) and in CoppeliaSim (remoteApiConnections.txt file, and restart CoppeliaSim).

### Try to test the CoppeliaSim examples ###

Please, try to run the example that coppelia provides, for example the python one. You have to go to CoppeliaSim folder/CoppeliaSimEdu/programming/remoteApiBindings/python/python

Copy to this directory the simulator library for your OS. You can find in CoppeliaSim folder/CoppeliaSimEdu/programming/remoteApiBindings/lib/lib/MacOS

Then, try to run the simpleTest.py
	
	python simpleTest.py

You should see something like:

	Program started
	Connected to remote API server
	('Number of objects in the scene: ', 16)
	('Mouse position x: ', 1128)
