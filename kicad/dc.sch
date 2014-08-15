EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:TEENSYPP2
LIBS:LM2937
LIBS:dc-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "15 aug 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 6750 2250 2    60   Input ~ 0
TVCC
$Comp
L TEENSYPP2 U1
U 1 1 53EBF821
P 5300 3200
F 0 "U1" H 5300 3100 50  0000 C CNN
F 1 "TEENSYPP2" H 5300 3300 50  0000 C CNN
F 2 "MODULE" H 5300 3200 50  0001 C CNN
F 3 "DOCUMENTATION" H 5300 3200 50  0001 C CNN
	1    5300 3200
	1    0    0    -1  
$EndComp
Text GLabel 6750 3250 2    60   Input ~ 0
GND
Text GLabel 3850 2250 0    60   Input ~ 0
GND
Wire Wire Line
	6750 3250 6650 3250
Wire Wire Line
	3850 2250 3950 2250
Wire Wire Line
	6650 2250 6750 2250
$Comp
L R R1
U 1 1 53EBFE16
P 4950 5050
F 0 "R1" V 5030 5050 40  0000 C CNN
F 1 "10k" V 4957 5051 40  0000 C CNN
F 2 "~" V 4880 5050 30  0000 C CNN
F 3 "~" H 4950 5050 30  0000 C CNN
	1    4950 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4650 4950 4800
Text GLabel 4950 5400 3    60   Input ~ 0
5V
Wire Wire Line
	4950 5300 4950 5400
$Comp
L CRYSTAL X1
U 1 1 53EBFFDC
P 5750 1350
F 0 "X1" H 5750 1500 60  0000 C CNN
F 1 "32.768 kHz" H 5750 1200 60  0000 C CNN
F 2 "~" H 5750 1350 60  0000 C CNN
F 3 "~" H 5750 1350 60  0000 C CNN
	1    5750 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 1650 5750 1750
Wire Wire Line
	5750 1050 5850 1050
Wire Wire Line
	5850 1050 5850 1750
$Comp
L LM2937ES-3.3 IC2
U 1 1 53EC034F
P 4050 6650
F 0 "IC2" H 4000 6600 50  0000 L BNN
F 1 "LM2937ES-3.3" H 3750 6350 50  0000 L BNN
F 2 "lm2937-TO263" H 4050 6800 50  0001 C CNN
F 3 "" H 4050 6650 60  0000 C CNN
	1    4050 6650
	1    0    0    1   
$EndComp
Wire Wire Line
	3350 6750 3450 6750
Wire Wire Line
	3450 6750 3550 6750
Text GLabel 5050 7350 2    60   Input ~ 0
GND
$Comp
L C C4
U 1 1 53EC04AD
P 4550 7050
F 0 "C4" H 4550 7150 40  0000 L CNN
F 1 "10 uF" H 4556 6965 40  0000 L CNN
F 2 "~" H 4588 6900 30  0000 C CNN
F 3 "~" H 4550 7050 60  0000 C CNN
	1    4550 7050
	1    0    0    1   
$EndComp
$Comp
L C C3
U 1 1 53EC04BC
P 3550 7050
F 0 "C3" H 3550 7150 40  0000 L CNN
F 1 "0.1 uF" H 3556 6965 40  0000 L CNN
F 2 "~" H 3588 6900 30  0000 C CNN
F 3 "~" H 3550 7050 60  0000 C CNN
	1    3550 7050
	1    0    0    1   
$EndComp
Wire Wire Line
	4550 6750 4550 6850
Wire Wire Line
	3550 6750 3550 6850
Wire Wire Line
	4550 6550 4950 6550
Text GLabel 4650 6750 2    60   Input ~ 0
3.3V
Wire Wire Line
	4650 6750 4550 6750
$Comp
L LM2937ES-5.0 IC1
U 1 1 53EC0D05
P 1950 6650
F 0 "IC1" H 1900 6600 50  0000 L BNN
F 1 "LM2937ES-5.0" H 1650 6350 50  0000 L BNN
F 2 "lm2937-TO263" H 1950 6800 50  0001 C CNN
F 3 "" H 1950 6650 60  0000 C CNN
	1    1950 6650
	1    0    0    1   
$EndComp
Text GLabel 1350 6750 0    60   Input ~ 0
BATT
Wire Wire Line
	1350 6750 1450 6750
$Comp
L C C2
U 1 1 53EC0E4A
P 2450 7050
F 0 "C2" H 2450 7150 40  0000 L CNN
F 1 "10 uF" H 2456 6965 40  0000 L CNN
F 2 "~" H 2488 6900 30  0000 C CNN
F 3 "~" H 2450 7050 60  0000 C CNN
	1    2450 7050
	1    0    0    1   
$EndComp
$Comp
L C C1
U 1 1 53EC0E50
P 1450 7050
F 0 "C1" H 1450 7150 40  0000 L CNN
F 1 "0.1 uF" H 1456 6965 40  0000 L CNN
F 2 "~" H 1488 6900 30  0000 C CNN
F 3 "~" H 1450 7050 60  0000 C CNN
	1    1450 7050
	1    0    0    1   
$EndComp
Wire Wire Line
	1450 7350 2450 7350
Wire Wire Line
	2450 7350 2850 7350
Wire Wire Line
	2850 7350 3550 7350
Wire Wire Line
	3550 7350 4550 7350
Wire Wire Line
	4550 7350 4950 7350
Wire Wire Line
	4950 7350 5050 7350
Wire Wire Line
	2850 6550 2850 7350
Wire Wire Line
	2450 6750 2450 6850
Wire Wire Line
	2450 6550 2850 6550
Connection ~ 2850 7350
Wire Wire Line
	2950 6750 2450 6750
$Comp
L DIODE D1
U 1 1 53EC0EDF
P 3150 6750
F 0 "D1" H 3150 6850 40  0000 C CNN
F 1 "DIODE" H 3150 6650 40  0000 C CNN
F 2 "~" H 3150 6750 60  0000 C CNN
F 3 "~" H 3150 6750 60  0000 C CNN
	1    3150 6750
	1    0    0    -1  
$EndComp
Text GLabel 3350 6350 0    60   Input ~ 0
TVCC
Wire Wire Line
	3450 6350 3350 6350
Text GLabel 3450 6250 1    60   Input ~ 0
5V
Connection ~ 3450 6350
Connection ~ 1450 6750
Wire Wire Line
	2450 7250 2450 7350
Connection ~ 2450 7350
Wire Wire Line
	1450 7250 1450 7350
Wire Wire Line
	1450 6750 1450 6850
Wire Wire Line
	4550 7250 4550 7350
Connection ~ 4550 7350
Wire Wire Line
	3550 7250 3550 7350
Connection ~ 3550 7350
Connection ~ 4950 7350
Wire Wire Line
	4950 6550 4950 7350
Wire Wire Line
	4950 7350 5000 7350
Wire Wire Line
	3450 6250 3450 6350
Wire Wire Line
	3450 6350 3450 6750
Connection ~ 3450 6750
Text Notes 2650 6150 0    20   ~ 0
Cut the trace between USB VCC and MCU VCC\nand put a diode between the pads.
$EndSCHEMATC
