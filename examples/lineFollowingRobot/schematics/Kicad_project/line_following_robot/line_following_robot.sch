EESchema Schematic File Version 4
LIBS:line_following_robot-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "lun. 30 mars 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8950 1450 1    60   ~ 0
Vin
Text Label 9350 1450 1    60   ~ 0
IOREF
Text Label 8900 2500 0    60   ~ 0
A0
Text Label 8900 2600 0    60   ~ 0
A1
Text Label 8900 2700 0    60   ~ 0
A2
Text Label 8900 2800 0    60   ~ 0
A3
Text Label 8900 2900 0    60   ~ 0
A4(SDA)
Text Label 8900 3000 0    60   ~ 0
A5(SCL)
Text Label 10550 3000 0    60   ~ 0
0(Rx)
Text Label 10550 2800 0    60   ~ 0
2
Text Label 10550 2900 0    60   ~ 0
1(Tx)
Text Label 10550 2700 0    60   ~ 0
3(**)
Text Label 10550 2600 0    60   ~ 0
4
Text Label 10550 2500 0    60   ~ 0
5(**)
Text Label 10550 2400 0    60   ~ 0
6(**)
Text Label 10550 2300 0    60   ~ 0
7
Text Label 10550 2100 0    60   ~ 0
8
Text Label 10550 2000 0    60   ~ 0
9(**)
Text Label 10550 1900 0    60   ~ 0
10(**/SS)
Text Label 10550 1800 0    60   ~ 0
11(**/MOSI)
Text Label 10550 1700 0    60   ~ 0
12(MISO)
Text Label 10550 1600 0    60   ~ 0
13(SCK)
Text Label 10550 1400 0    60   ~ 0
AREF
NoConn ~ 9400 1600
Text Label 10550 1300 0    60   ~ 0
A4(SDA)
Text Label 10550 1200 0    60   ~ 0
A5(SCL)
Text Notes 10850 1000 0    60   ~ 0
Holes
Text Notes 8550 750  0    60   ~ 0
Shield for Arduino that uses\nthe same pin disposition\nlike "Uno" board Rev 3.
$Comp
L Connector_Generic:Conn_01x08 P1
U 1 1 56D70129
P 9600 1900
F 0 "P1" H 9600 2350 50  0000 C CNN
F 1 "Power" V 9700 1900 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 9750 1900 20  0000 C CNN
F 3 "" H 9600 1900 50  0000 C CNN
	1    9600 1900
	1    0    0    -1  
$EndComp
Text Label 8650 1800 0    60   ~ 0
Reset
$Comp
L power:+3.3V #PWR01
U 1 1 56D70538
P 9150 1450
F 0 "#PWR01" H 9150 1300 50  0001 C CNN
F 1 "+3.3V" V 9150 1700 50  0000 C CNN
F 2 "" H 9150 1450 50  0000 C CNN
F 3 "" H 9150 1450 50  0000 C CNN
	1    9150 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 56D707BB
P 9050 1350
F 0 "#PWR02" H 9050 1200 50  0001 C CNN
F 1 "+5V" V 9050 1550 50  0000 C CNN
F 2 "" H 9050 1350 50  0000 C CNN
F 3 "" H 9050 1350 50  0000 C CNN
	1    9050 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 56D70CC2
P 9300 3150
F 0 "#PWR03" H 9300 2900 50  0001 C CNN
F 1 "GND" H 9300 3000 50  0000 C CNN
F 2 "" H 9300 3150 50  0000 C CNN
F 3 "" H 9300 3150 50  0000 C CNN
	1    9300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 56D70CFF
P 10300 3150
F 0 "#PWR04" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10300 3000 50  0000 C CNN
F 2 "" H 10300 3150 50  0000 C CNN
F 3 "" H 10300 3150 50  0000 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 P2
U 1 1 56D70DD8
P 9600 2700
F 0 "P2" H 9600 2300 50  0000 C CNN
F 1 "Analog" V 9700 2700 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 9750 2750 20  0000 C CNN
F 3 "" H 9600 2700 50  0000 C CNN
	1    9600 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 56D71177
P 10800 650
F 0 "P5" V 10900 650 50  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10721 724 20  0000 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 56D71274
P 10900 650
F 0 "P6" V 11000 650 50  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10900 650 20  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P7
U 1 1 56D712A8
P 11000 650
F 0 "P7" V 11100 650 50  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" V 11000 650 20  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P8
U 1 1 56D712DB
P 11100 650
F 0 "P8" V 11200 650 50  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 11024 572 20  0000 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10800 850 
NoConn ~ 10900 850 
NoConn ~ 11000 850 
NoConn ~ 11100 850 
$Comp
L Connector_Generic:Conn_01x08 P4
U 1 1 56D7164F
P 10000 2600
F 0 "P4" H 10000 2100 50  0000 C CNN
F 1 "Digital" V 10100 2600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 10150 2550 20  0000 C CNN
F 3 "" H 10000 2600 50  0000 C CNN
	1    10000 2600
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8525 825  9925 825 
Wire Notes Line
	9925 825  9925 475 
Wire Wire Line
	9350 1450 9350 1700
Wire Wire Line
	9350 1700 9400 1700
Wire Wire Line
	9400 1900 9150 1900
Wire Wire Line
	9400 2000 9050 2000
Wire Wire Line
	9400 2300 8950 2300
Wire Wire Line
	9400 2100 9300 2100
Wire Wire Line
	9400 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	8950 2300 8950 1450
Wire Wire Line
	9050 2000 9050 1350
Wire Wire Line
	9150 1900 9150 1450
Wire Wire Line
	9400 2500 8900 2500
Wire Wire Line
	9400 2600 8900 2600
Wire Wire Line
	9400 2700 8900 2700
Wire Wire Line
	9400 2800 8900 2800
Wire Wire Line
	9400 2900 8900 2900
Wire Wire Line
	9400 3000 8900 3000
$Comp
L Connector_Generic:Conn_01x10 P3
U 1 1 56D721E0
P 10000 1600
F 0 "P3" H 10000 2150 50  0000 C CNN
F 1 "Digital" V 10100 1600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 10150 1600 20  0000 C CNN
F 3 "" H 10000 1600 50  0000 C CNN
	1    10000 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2100 10550 2100
Wire Wire Line
	10200 2000 10550 2000
Wire Wire Line
	10200 1900 10550 1900
Wire Wire Line
	10200 1800 10550 1800
Wire Wire Line
	10200 1700 10550 1700
Wire Wire Line
	10200 1600 10550 1600
Wire Wire Line
	10200 1400 10550 1400
Wire Wire Line
	10200 1300 10550 1300
Wire Wire Line
	10200 1200 10550 1200
Wire Wire Line
	10200 3000 10550 3000
Wire Wire Line
	10200 2900 10550 2900
Wire Wire Line
	10200 2800 10550 2800
Wire Wire Line
	10200 2700 10550 2700
Wire Wire Line
	10200 2600 10550 2600
Wire Wire Line
	10200 2500 10550 2500
Wire Wire Line
	10200 2400 10550 2400
Wire Wire Line
	10200 2300 10550 2300
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	10300 1500 10300 3150
Wire Wire Line
	9300 2100 9300 2200
Wire Wire Line
	9300 2200 9300 3150
Wire Notes Line
	8500 500  8500 3450
Wire Notes Line
	8500 3450 11200 3450
Wire Wire Line
	9400 1800 8650 1800
Text Notes 9700 1600 0    60   ~ 0
1
Wire Notes Line
	11200 1000 10700 1000
Wire Notes Line
	10700 1000 10700 500 
$Comp
L Transistor_BJT:PN2222A Q2
U 1 1 5E8A72EA
P 4275 2175
F 0 "Q2" H 4465 2221 50  0000 L CNN
F 1 "PN2222A" H 4465 2130 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4475 2100 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/PN/PN2222A.pdf" H 4275 2175 50  0001 L CNN
	1    4275 2175
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E8A7BA8
P 3800 2175
F 0 "R2" V 3593 2175 50  0000 C CNN
F 1 "R" V 3684 2175 50  0000 C CNN
F 2 "" V 3730 2175 50  0001 C CNN
F 3 "~" H 3800 2175 50  0001 C CNN
	1    3800 2175
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5E8A8749
P 4375 2425
F 0 "#PWR012" H 4375 2175 50  0001 C CNN
F 1 "GND" H 4380 2252 50  0000 C CNN
F 2 "" H 4375 2425 50  0001 C CNN
F 3 "" H 4375 2425 50  0001 C CNN
	1    4375 2425
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M2
U 1 1 5E8A91E2
P 4375 1575
F 0 "M2" H 4533 1571 50  0000 L CNN
F 1 "Motor_DC" H 4533 1480 50  0000 L CNN
F 2 "" H 4375 1485 50  0001 C CNN
F 3 "~" H 4375 1485 50  0001 C CNN
	1    4375 1575
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D2
U 1 1 5E8A9D53
P 5075 1625
F 0 "D2" V 5121 1497 50  0000 R CNN
F 1 "DIODE" V 5030 1497 50  0000 R CNN
F 2 "" H 5075 1625 50  0001 C CNN
F 3 "~" H 5075 1625 50  0001 C CNN
	1    5075 1625
	0    -1   -1   0   
$EndComp
$Comp
L power:+6V #PWR011
U 1 1 5E8AB3AC
P 4375 1275
F 0 "#PWR011" H 4375 1125 50  0001 C CNN
F 1 "+6V" H 4390 1448 50  0000 C CNN
F 2 "" H 4375 1275 50  0001 C CNN
F 3 "" H 4375 1275 50  0001 C CNN
	1    4375 1275
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M3
U 1 1 5E8AC350
P 7225 1600
F 0 "M3" H 7557 1665 50  0000 L CNN
F 1 "Motor_Servo" H 7557 1574 50  0000 L CNN
F 2 "" H 7225 1410 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 7225 1410 50  0001 C CNN
	1    7225 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4375 2425 4375 2375
Wire Wire Line
	4075 2175 3950 2175
Wire Wire Line
	4375 1975 4375 1925
Wire Wire Line
	4375 1925 5075 1925
Wire Wire Line
	5075 1925 5075 1825
Connection ~ 4375 1925
Wire Wire Line
	4375 1925 4375 1875
Wire Wire Line
	5075 1425 5075 1325
Wire Wire Line
	5075 1325 4375 1325
Wire Wire Line
	4375 1325 4375 1275
Wire Wire Line
	4375 1375 4375 1325
Connection ~ 4375 1325
$Comp
L power:GND #PWR014
U 1 1 5E8B3AA1
P 6400 1700
F 0 "#PWR014" H 6400 1450 50  0001 C CNN
F 1 "GND" H 6405 1527 50  0000 C CNN
F 2 "" H 6400 1700 50  0001 C CNN
F 3 "" H 6400 1700 50  0001 C CNN
	1    6400 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5E8B43F7
P 6400 1500
F 0 "#PWR013" H 6400 1350 50  0001 C CNN
F 1 "+5V" H 6415 1673 50  0000 C CNN
F 2 "" H 6400 1500 50  0001 C CNN
F 3 "" H 6400 1500 50  0001 C CNN
	1    6400 1500
	1    0    0    -1  
$EndComp
$Comp
L Interface_Optical:QSE159 U2
U 1 1 5E8B654F
P 4100 5075
F 0 "U2" H 3838 5075 50  0000 R CNN
F 1 "QSE159" H 3838 5030 50  0001 R CNN
F 2 "OptoDevice:ONSemi_QSE15x" H 4100 4675 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QSE159-D.pdf" H 4750 5375 50  0001 C CNN
	1    4100 5075
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:PN2222A Q1
U 1 1 5E8BCCA4
P 1825 2150
F 0 "Q1" H 2015 2196 50  0000 L CNN
F 1 "PN2222A" H 2015 2105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2025 2075 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/PN/PN2222A.pdf" H 1825 2150 50  0001 L CNN
	1    1825 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E8BCCAA
P 1350 2150
F 0 "R1" V 1143 2150 50  0000 C CNN
F 1 "R" V 1234 2150 50  0000 C CNN
F 2 "" V 1280 2150 50  0001 C CNN
F 3 "~" H 1350 2150 50  0001 C CNN
	1    1350 2150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E8BCCB0
P 1925 2400
F 0 "#PWR06" H 1925 2150 50  0001 C CNN
F 1 "GND" H 1930 2227 50  0000 C CNN
F 2 "" H 1925 2400 50  0001 C CNN
F 3 "" H 1925 2400 50  0001 C CNN
	1    1925 2400
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M1
U 1 1 5E8BCCB6
P 1925 1550
F 0 "M1" H 2083 1546 50  0000 L CNN
F 1 "Motor_DC" H 2083 1455 50  0000 L CNN
F 2 "" H 1925 1460 50  0001 C CNN
F 3 "~" H 1925 1460 50  0001 C CNN
	1    1925 1550
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D1
U 1 1 5E8BCCBC
P 2625 1600
F 0 "D1" V 2671 1472 50  0000 R CNN
F 1 "DIODE" V 2580 1472 50  0000 R CNN
F 2 "" H 2625 1600 50  0001 C CNN
F 3 "~" H 2625 1600 50  0001 C CNN
	1    2625 1600
	0    -1   -1   0   
$EndComp
$Comp
L power:+6V #PWR05
U 1 1 5E8BCCC2
P 1925 1250
F 0 "#PWR05" H 1925 1100 50  0001 C CNN
F 1 "+6V" H 1940 1423 50  0000 C CNN
F 2 "" H 1925 1250 50  0001 C CNN
F 3 "" H 1925 1250 50  0001 C CNN
	1    1925 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1925 2400 1925 2350
Wire Wire Line
	1625 2150 1500 2150
Wire Wire Line
	1925 1950 1925 1900
Wire Wire Line
	1925 1900 2625 1900
Wire Wire Line
	2625 1900 2625 1800
Connection ~ 1925 1900
Wire Wire Line
	1925 1900 1925 1850
Wire Wire Line
	2625 1400 2625 1300
Wire Wire Line
	2625 1300 1925 1300
Wire Wire Line
	1925 1300 1925 1250
Wire Wire Line
	1925 1350 1925 1300
Connection ~ 1925 1300
$Comp
L power:GND #PWR010
U 1 1 5E8BDFBB
P 4200 5450
F 0 "#PWR010" H 4200 5200 50  0001 C CNN
F 1 "GND" H 4205 5277 50  0000 C CNN
F 2 "" H 4200 5450 50  0001 C CNN
F 3 "" H 4200 5450 50  0001 C CNN
	1    4200 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5E8BE4E7
P 4200 4725
F 0 "#PWR09" H 4200 4575 50  0001 C CNN
F 1 "+5V" H 4215 4898 50  0000 C CNN
F 2 "" H 4200 4725 50  0001 C CNN
F 3 "" H 4200 4725 50  0001 C CNN
	1    4200 4725
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5075 4825 5075
Wire Wire Line
	4200 5450 4200 5375
Wire Wire Line
	4200 4775 4200 4725
$Comp
L Interface_Optical:QSE159 U1
U 1 1 5E8CA1E7
P 1850 5100
F 0 "U1" H 1588 5100 50  0000 R CNN
F 1 "QSE159" H 1588 5055 50  0001 R CNN
F 2 "OptoDevice:ONSemi_QSE15x" H 1850 4700 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QSE159-D.pdf" H 2500 5400 50  0001 C CNN
	1    1850 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E8CA1F1
P 1950 5475
F 0 "#PWR08" H 1950 5225 50  0001 C CNN
F 1 "GND" H 1955 5302 50  0000 C CNN
F 2 "" H 1950 5475 50  0001 C CNN
F 3 "" H 1950 5475 50  0001 C CNN
	1    1950 5475
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5E8CA1FB
P 1950 4750
F 0 "#PWR07" H 1950 4600 50  0001 C CNN
F 1 "+5V" H 1965 4923 50  0000 C CNN
F 2 "" H 1950 4750 50  0001 C CNN
F 3 "" H 1950 4750 50  0001 C CNN
	1    1950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5100 2575 5100
Wire Wire Line
	1950 5475 1950 5400
Wire Wire Line
	1950 4800 1950 4750
$Comp
L Interface_Optical:QSE159 U3
U 1 1 5E8D0A4E
P 6675 5175
F 0 "U3" H 6413 5175 50  0000 R CNN
F 1 "QSE159" H 6413 5130 50  0001 R CNN
F 2 "OptoDevice:ONSemi_QSE15x" H 6675 4775 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QSE159-D.pdf" H 7325 5475 50  0001 C CNN
	1    6675 5175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5E8D0A58
P 6775 5550
F 0 "#PWR016" H 6775 5300 50  0001 C CNN
F 1 "GND" H 6780 5377 50  0000 C CNN
F 2 "" H 6775 5550 50  0001 C CNN
F 3 "" H 6775 5550 50  0001 C CNN
	1    6775 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 5E8D0A62
P 6775 4825
F 0 "#PWR015" H 6775 4675 50  0001 C CNN
F 1 "+5V" H 6790 4998 50  0000 C CNN
F 2 "" H 6775 4825 50  0001 C CNN
F 3 "" H 6775 4825 50  0001 C CNN
	1    6775 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	6975 5175 7400 5175
Wire Wire Line
	6775 5550 6775 5475
Wire Wire Line
	6775 4875 6775 4825
Text Notes 3375 4325 0    129  ~ 0
IR sensor right
Text Notes 3850 900  0    129  ~ 0
DC Motor right
Text Notes 1375 925  0    129  ~ 0
DC Motor left
Text Label 3400 2175 0    129  ~ 0
11
Wire Wire Line
	3400 2175 3650 2175
Text Label 900  2150 0    129  ~ 0
10
Wire Wire Line
	1200 2150 900  2150
Text Label 6675 1500 0    129  ~ 0
3
Wire Wire Line
	6675 1500 6925 1500
Wire Wire Line
	6925 1600 6400 1600
Wire Wire Line
	6400 1600 6400 1500
Wire Wire Line
	6925 1700 6400 1700
Text Notes 6475 950  0    129  ~ 0
Servo (Gripper)
Text Notes 1225 4275 0    129  ~ 0
IR sensor left
Text Label 2575 5100 2    129  ~ 0
9
Text Label 4825 5075 2    129  ~ 0
8
Text Label 7400 5175 2    129  ~ 0
7
Text Notes 5850 4450 0    129  ~ 0
IR sensor front \n   (gripper)
$EndSCHEMATC
