EESchema Schematic File Version 2
LIBS:dc_proto
LIBS:w_connectors
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
LIBS:lm1086
LIBS:dc-cache
EELAYER 27 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Diving computer prototype"
Date "19 oct 2014"
Rev ""
Comp "MC JBF"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L STM32F4_DISCOVERY_HEADER J1
U 1 1 54386300
P 5200 2700
F 0 "J1" H 5200 4150 60  0000 C CNN
F 1 "STM32F4_DISCOVERY_HEADER" H 5200 4050 60  0000 C CNN
F 2 "stm32f4_discovery_header" H 5200 3050 60  0001 C CNN
F 3 "" H 5200 3050 60  0000 C CNN
	1    5200 2700
	1    0    0    -1  
$EndComp
NoConn ~ 4650 1550
NoConn ~ 4700 1600
NoConn ~ 4700 3800
$Comp
L GND #PWR01
U 1 1 54386C3D
P 5850 3850
F 0 "#PWR01" H 5850 3850 30  0001 C CNN
F 1 "GND" H 5850 3780 30  0001 C CNN
F 2 "" H 5850 3850 60  0000 C CNN
F 3 "" H 5850 3850 60  0000 C CNN
	1    5850 3850
	0    -1   -1   0   
$EndComp
NoConn ~ 5750 2450
$Comp
L GND #PWR02
U 1 1 54386DE2
P 4550 3850
F 0 "#PWR02" H 4550 3850 30  0001 C CNN
F 1 "GND" H 4550 3780 30  0001 C CNN
F 2 "" H 4550 3850 60  0000 C CNN
F 3 "" H 4550 3850 60  0000 C CNN
	1    4550 3850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR03
U 1 1 54386ECD
P 4550 2550
F 0 "#PWR03" H 4550 2550 30  0001 C CNN
F 1 "GND" H 4550 2480 30  0001 C CNN
F 2 "" H 4550 2550 60  0000 C CNN
F 3 "" H 4550 2550 60  0000 C CNN
	1    4550 2550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 54386EF7
P 4500 1450
F 0 "#PWR04" H 4500 1450 30  0001 C CNN
F 1 "GND" H 4500 1380 30  0001 C CNN
F 2 "" H 4500 1450 60  0000 C CNN
F 3 "" H 4500 1450 60  0000 C CNN
	1    4500 1450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 54386F84
P 6500 1650
F 0 "#PWR05" H 6500 1650 30  0001 C CNN
F 1 "GND" H 6500 1580 30  0001 C CNN
F 2 "" H 6500 1650 60  0000 C CNN
F 3 "" H 6500 1650 60  0000 C CNN
	1    6500 1650
	1    0    0    -1  
$EndComp
NoConn ~ 5750 1750
NoConn ~ 5700 1800
$Comp
L +3.3V #PWR06
U 1 1 543942EA
P 4200 7250
F 0 "#PWR06" H 4200 7210 30  0001 C CNN
F 1 "+3.3V" H 4200 7360 30  0000 C CNN
F 2 "" H 4200 7250 60  0000 C CNN
F 3 "" H 4200 7250 60  0000 C CNN
	1    4200 7250
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P1
U 1 1 543947F2
P 700 5900
F 0 "P1" V 650 5900 50  0000 C CNN
F 1 "CONN_4" V 750 5900 50  0000 C CNN
F 2 "ED10563-ND" H 700 5900 60  0001 C CNN
F 3 "" H 700 5900 60  0000 C CNN
	1    700  5900
	-1   0    0    -1  
$EndComp
$Comp
L +BATT #PWR07
U 1 1 54394816
P 1650 5750
F 0 "#PWR07" H 1650 5700 20  0001 C CNN
F 1 "+BATT" H 1650 5850 30  0000 C CNN
F 2 "" H 1650 5750 60  0000 C CNN
F 3 "" H 1650 5750 60  0000 C CNN
	1    1650 5750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5439481C
P 1500 6250
F 0 "#PWR08" H 1500 6250 30  0001 C CNN
F 1 "GND" H 1500 6180 30  0001 C CNN
F 2 "" H 1500 6250 60  0000 C CNN
F 3 "" H 1500 6250 60  0000 C CNN
	1    1500 6250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 54395CB8
P 1350 5750
F 0 "#FLG09" H 1350 5845 30  0001 C CNN
F 1 "PWR_FLAG" H 1350 5930 30  0000 C CNN
F 2 "" H 1350 5750 60  0000 C CNN
F 3 "" H 1350 5750 60  0000 C CNN
	1    1350 5750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG010
U 1 1 54395CC7
P 1350 6150
F 0 "#FLG010" H 1350 6245 30  0001 C CNN
F 1 "PWR_FLAG" H 1350 6330 30  0000 C CNN
F 2 "" H 1350 6150 60  0000 C CNN
F 3 "" H 1350 6150 60  0000 C CNN
	1    1350 6150
	-1   0    0    1   
$EndComp
$Comp
L +BATT #PWR011
U 1 1 543966DF
P 3550 6450
F 0 "#PWR011" H 3550 6400 20  0001 C CNN
F 1 "+BATT" H 3550 6550 30  0000 C CNN
F 2 "" H 3550 6450 60  0000 C CNN
F 3 "" H 3550 6450 60  0000 C CNN
	1    3550 6450
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR012
U 1 1 543966E5
P 3300 6950
F 0 "#PWR012" H 3300 6950 30  0001 C CNN
F 1 "GND" H 3300 6880 30  0001 C CNN
F 2 "" H 3300 6950 60  0000 C CNN
F 3 "" H 3300 6950 60  0000 C CNN
	1    3300 6950
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 5439673D
P 4200 6350
F 0 "#PWR013" H 4200 6440 20  0001 C CNN
F 1 "+5V" H 4200 6440 30  0000 C CNN
F 2 "" H 4200 6350 60  0000 C CNN
F 3 "" H 4200 6350 60  0000 C CNN
	1    4200 6350
	0    1    -1   0   
$EndComp
Text GLabel 4550 2850 0    15   BiDi ~ 0
FSMC_D08
Text GLabel 4550 2900 0    15   BiDi ~ 0
FSMC_D09
Text GLabel 4550 2950 0    15   BiDi ~ 0
FSMC_D10
Text GLabel 4550 3000 0    15   BiDi ~ 0
FSMC_D11
Text GLabel 4550 3050 0    15   BiDi ~ 0
FSMC_D12
Text GLabel 4550 3400 0    15   BiDi ~ 0
FSMC_D13
Text GLabel 4550 3450 0    15   BiDi ~ 0
FSMC_D14
Text GLabel 4550 3500 0    15   BiDi ~ 0
FSMC_D15
Text GLabel 4550 3550 0    15   Output ~ 0
FSMC_A16
Text GLabel 5850 2900 2    15   Output ~ 0
FSMC_NWE
Text GLabel 5850 2950 2    15   Output ~ 0
FSMC_NOE
Text GLabel 5850 2800 2    15   Output ~ 0
FSMC_NE1
Text GLabel 4550 1700 0    15   Output ~ 0
RESET
$Comp
L NHD‐2.7‐12864UCY3 DISP1
U 1 1 54399449
P 850 5000
F 0 "DISP1" H 200 5000 30  0000 C CNN
F 1 "NHD‐2.7‐12864UCY3" H 875 5000 30  0000 C CNN
F 2 "NHD‐2.7‐12864UCY3" H 575 5025 60  0001 C CNN
F 3 "" H 575 5025 60  0000 C CNN
	1    850  5000
	0    -1   1    0   
$EndComp
Text GLabel 1200 4600 2    15   BiDi ~ 0
FSMC_D08
Text GLabel 1200 4650 2    15   BiDi ~ 0
FSMC_D09
Text GLabel 1200 4700 2    15   BiDi ~ 0
FSMC_D10
Text GLabel 1200 4750 2    15   BiDi ~ 0
FSMC_D11
Text GLabel 1200 4800 2    15   BiDi ~ 0
FSMC_D12
Text GLabel 1200 4850 2    15   BiDi ~ 0
FSMC_D13
Text GLabel 1200 4900 2    15   BiDi ~ 0
FSMC_D14
Text GLabel 1200 4950 2    15   BiDi ~ 0
FSMC_D15
Text GLabel 1200 5050 2    15   Input ~ 0
RESET
Text GLabel 1200 5100 2    15   Input ~ 0
FSMC_NE1
Text GLabel 1200 4500 2    15   Input ~ 0
FSMC_NWE
Text GLabel 1200 4550 2    15   Input ~ 0
FSMC_NOE
Text GLabel 1200 4450 2    15   Input ~ 0
FSMC_A16
Text GLabel 5850 3700 2    15   BiDi ~ 0
SDIO_D0
Text GLabel 5850 3650 2    15   BiDi ~ 0
SDIO_D1
Text GLabel 5850 3300 2    15   BiDi ~ 0
SDIO_D2
Text GLabel 5850 3250 2    15   BiDi ~ 0
SDIO_D3
Text GLabel 5850 3200 2    15   Output ~ 0
SDIO_CK
Text GLabel 5850 3050 2    15   Output ~ 0
SDIO_CMD
Text GLabel 4550 1900 0    15   Input ~ 0
SPI2_MISO
Text GLabel 4550 3350 0    15   Output ~ 0
SPI2_MOSI
Text GLabel 4550 3250 0    15   Output ~ 0
SPI2_SCK
$Comp
L SDCARD SD1
U 1 1 543AB537
P 1300 1500
F 0 "SD1" V 1600 600 60  0000 C CNN
F 1 "SDCARD" V 1600 1250 60  0000 C CNN
F 2 "101-00405-75-ND" H 1300 1500 60  0001 C CNN
F 3 "" H 1300 1500 60  0000 C CNN
	1    1300 1500
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 543AB757
P 2450 2800
F 0 "#PWR014" H 2450 2800 30  0001 C CNN
F 1 "GND" H 2450 2730 30  0001 C CNN
F 2 "" H 2450 2800 60  0000 C CNN
F 3 "" H 2450 2800 60  0000 C CNN
	1    2450 2800
	1    0    0    -1  
$EndComp
Text GLabel 2400 1850 2    40   BiDi ~ 0
SDIO_D0
Text GLabel 2400 1950 2    40   BiDi ~ 0
SDIO_D1
Text GLabel 2400 2050 2    40   BiDi ~ 0
SDIO_D2
Text GLabel 2400 2150 2    40   BiDi ~ 0
SDIO_D3
Text GLabel 2400 1700 2    40   Input ~ 0
SDIO_CK
Text GLabel 2400 1600 2    40   Input ~ 0
SDIO_CMD
$Comp
L +3.3V #PWR015
U 1 1 543AEFC8
P 2250 950
F 0 "#PWR015" H 2250 910 30  0001 C CNN
F 1 "+3.3V" H 2250 1060 30  0000 C CNN
F 2 "" H 2250 950 60  0000 C CNN
F 3 "" H 2250 950 60  0000 C CNN
	1    2250 950 
	0    1    1    0   
$EndComp
Text GLabel 5850 3600 2    15   Input ~ 0
SD_CD
Text GLabel 5850 3350 2    15   Input ~ 0
SD_WP
Text GLabel 2100 2750 2    40   Output ~ 0
SD_CD
Text GLabel 2100 2850 2    40   Output ~ 0
SD_WP
$Comp
L R R6
U 1 1 543AFD99
P 1850 3200
F 0 "R6" V 1930 3200 40  0000 C CNN
F 1 "100k" V 1857 3201 40  0000 C CNN
F 2 "SM0402" V 1780 3200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1850 3200 30  0001 C CNN
	1    1850 3200
	1    0    0    -1  
$EndComp
NoConn ~ 5750 1850
NoConn ~ 5700 1900
NoConn ~ 5750 1950
NoConn ~ 5700 2100
NoConn ~ 5750 2150
NoConn ~ 5700 2200
NoConn ~ 5750 2250
NoConn ~ 5700 2300
NoConn ~ 5750 2350
NoConn ~ 5700 2500
NoConn ~ 5700 2400
NoConn ~ 5750 2550
NoConn ~ 5700 2600
NoConn ~ 5750 2650
NoConn ~ 5700 2700
NoConn ~ 5750 2750
NoConn ~ 5750 2850
NoConn ~ 5700 3000
NoConn ~ 5700 3100
NoConn ~ 5700 3400
NoConn ~ 5750 3450
NoConn ~ 5700 3500
NoConn ~ 5750 3550
NoConn ~ 5750 3750
NoConn ~ 5700 3800
NoConn ~ 4650 3750
NoConn ~ 4700 3700
NoConn ~ 4650 3650
NoConn ~ 4700 3600
NoConn ~ 4700 3200
NoConn ~ 4650 3150
NoConn ~ 4700 3100
NoConn ~ 4700 2800
NoConn ~ 4650 2750
NoConn ~ 4700 2700
NoConn ~ 4650 2650
NoConn ~ 4700 2600
NoConn ~ 4700 2500
NoConn ~ 4700 2400
NoConn ~ 4700 2300
NoConn ~ 4650 2250
NoConn ~ 4700 2200
NoConn ~ 4650 2150
NoConn ~ 4700 2100
NoConn ~ 4700 2000
NoConn ~ 4650 1850
NoConn ~ 4700 1800
NoConn ~ 4650 1750
NoConn ~ 5750 3150
$Comp
L +3.3V #PWR016
U 1 1 543AF720
P 2000 3450
F 0 "#PWR016" H 2000 3410 30  0001 C CNN
F 1 "+3.3V" H 2000 3560 30  0000 C CNN
F 2 "" H 2000 3450 60  0000 C CNN
F 3 "" H 2000 3450 60  0000 C CNN
	1    2000 3450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR017
U 1 1 543B2144
P 1850 4850
F 0 "#PWR017" H 1850 4850 30  0001 C CNN
F 1 "GND" H 1850 4780 30  0001 C CNN
F 2 "" H 1850 4850 60  0000 C CNN
F 3 "" H 1850 4850 60  0000 C CNN
	1    1850 4850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR018
U 1 1 543B3051
P 1950 4350
F 0 "#PWR018" H 1950 4310 30  0001 C CNN
F 1 "+3.3V" H 1950 4460 30  0000 C CNN
F 2 "" H 1950 4350 60  0000 C CNN
F 3 "" H 1950 4350 60  0000 C CNN
	1    1950 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 3850 5750 3900
Wire Wire Line
	5750 3900 5700 3900
Connection ~ 5750 3900
Wire Wire Line
	5750 3850 5850 3850
Wire Wire Line
	4650 3850 4550 3850
Wire Wire Line
	4700 3900 4650 3900
Wire Wire Line
	4650 3900 4650 3850
Wire Wire Line
	4550 2550 4650 2550
Wire Wire Line
	4500 1450 4650 1450
Wire Wire Line
	4700 1500 4600 1500
Wire Wire Line
	4600 1450 4600 1650
Connection ~ 4600 1450
Wire Wire Line
	4600 1650 4650 1650
Connection ~ 4600 1500
Wire Wire Line
	1050 5750 1650 5750
Wire Wire Line
	1500 6150 1500 6250
Connection ~ 1500 5750
Connection ~ 1350 6150
Connection ~ 1350 5750
Wire Wire Line
	4550 2850 4650 2850
Wire Wire Line
	4550 2900 4700 2900
Wire Wire Line
	4550 2950 4650 2950
Wire Wire Line
	4550 3000 4700 3000
Wire Wire Line
	4550 3050 4650 3050
Wire Wire Line
	4550 3400 4700 3400
Wire Wire Line
	4550 3450 4650 3450
Wire Wire Line
	4550 3500 4700 3500
Wire Wire Line
	4550 3550 4650 3550
Wire Wire Line
	5700 2900 5850 2900
Wire Wire Line
	5750 2950 5850 2950
Wire Wire Line
	5700 2800 5850 2800
Wire Wire Line
	4550 1700 4700 1700
Wire Wire Line
	1400 4350 1400 5250
Wire Wire Line
	1400 5250 1150 5250
Wire Wire Line
	1150 5200 1400 5200
Connection ~ 1400 5200
Wire Wire Line
	1150 4600 1200 4600
Wire Wire Line
	1150 4650 1200 4650
Wire Wire Line
	1150 4700 1200 4700
Wire Wire Line
	1150 4750 1200 4750
Wire Wire Line
	1150 4800 1200 4800
Wire Wire Line
	1150 4850 1200 4850
Wire Wire Line
	1150 4900 1200 4900
Wire Wire Line
	1150 4950 1200 4950
Wire Wire Line
	1200 5050 1150 5050
Wire Wire Line
	1150 5100 1200 5100
Wire Wire Line
	1200 4500 1150 4500
Wire Wire Line
	1200 4550 1150 4550
Wire Wire Line
	1150 4450 1200 4450
Wire Wire Line
	5700 3700 5850 3700
Wire Wire Line
	5750 3650 5850 3650
Wire Wire Line
	5700 3300 5850 3300
Wire Wire Line
	5750 3250 5850 3250
Wire Wire Line
	5700 3200 5850 3200
Wire Wire Line
	5750 3050 5850 3050
Wire Wire Line
	4550 1900 4700 1900
Wire Wire Line
	4550 3350 4650 3350
Wire Wire Line
	4550 3250 4650 3250
Connection ~ 2600 2300
Wire Wire Line
	2450 2700 2850 2700
Wire Wire Line
	2450 2400 2450 2800
Wire Wire Line
	1600 2500 2450 2500
Connection ~ 2600 2700
Wire Wire Line
	1600 2400 2450 2400
Connection ~ 2450 2500
Connection ~ 2450 2700
Wire Wire Line
	1600 1850 2400 1850
Wire Wire Line
	1600 1950 2400 1950
Wire Wire Line
	1600 2050 2400 2050
Wire Wire Line
	1600 2150 2400 2150
Wire Wire Line
	1600 1700 2400 1700
Wire Wire Line
	1600 1600 2400 1600
Connection ~ 2450 2650
Wire Wire Line
	1600 2300 3100 2300
Connection ~ 1700 1850
Wire Wire Line
	1700 1450 1700 1850
Wire Wire Line
	1850 1450 1850 1950
Connection ~ 1850 1950
Wire Wire Line
	2000 1450 2000 2050
Connection ~ 2000 2050
Wire Wire Line
	2150 1450 2150 2150
Connection ~ 2150 2150
Wire Wire Line
	1700 950  2250 950 
Connection ~ 1850 950 
Connection ~ 2000 950 
Connection ~ 2150 950 
Connection ~ 1700 950 
Wire Wire Line
	5850 3600 5700 3600
Wire Wire Line
	5850 3350 5750 3350
Wire Wire Line
	1600 2650 2450 2650
Wire Wire Line
	1600 2750 2100 2750
Wire Wire Line
	1600 2850 2100 2850
Wire Wire Line
	1700 2750 1700 2950
Connection ~ 1700 2750
Wire Wire Line
	1850 2850 1850 2950
Connection ~ 1850 2850
Wire Wire Line
	1700 3450 2000 3450
Connection ~ 1850 3450
Connection ~ 2850 2300
Connection ~ 2850 2700
Connection ~ 1600 4350
Connection ~ 1400 4350
Wire Wire Line
	1850 4750 1850 4850
Wire Wire Line
	1450 4800 1850 4800
Wire Wire Line
	1450 4800 1450 4300
Wire Wire Line
	1450 4300 1150 4300
Connection ~ 1850 4800
$Comp
L C C3
U 1 1 543C1CFB
P 2850 2500
F 0 "C3" H 2850 2600 40  0000 L CNN
F 1 "10uF" H 2856 2415 40  0000 L CNN
F 2 "SM0603_Capa" H 2888 2350 30  0001 C CNN
F 3 "490-3340-1-ND" H 2850 2500 60  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 543C24BD
P 3850 6650
F 0 "C7" H 3900 6750 50  0000 L CNN
F 1 "1uF" H 3900 6550 50  0000 L CNN
F 2 "SM0402_c" H 3850 6650 60  0001 C CNN
F 3 "490-1320-1-ND" H 3850 6650 60  0001 C CNN
	1    3850 6650
	-1   0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 543C24CE
P 1600 4550
F 0 "C4" H 1650 4650 50  0000 L CNN
F 1 "1uF" H 1650 4450 50  0000 L CNN
F 2 "SM0402_c" H 1600 4550 60  0001 C CNN
F 3 "490-1320-1-ND" H 1600 4550 60  0001 C CNN
	1    1600 4550
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 543C24D4
P 3550 6650
F 0 "C6" H 3600 6750 50  0000 L CNN
F 1 "1uF" H 3600 6550 50  0000 L CNN
F 2 "SM0402_c" H 3550 6650 60  0001 C CNN
F 3 "490-1320-1-ND" H 3550 6650 60  0001 C CNN
	1    3550 6650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1150 4350 1950 4350
$Comp
L +3.3V #PWR019
U 1 1 543C2A85
P 3100 2300
F 0 "#PWR019" H 3100 2260 30  0001 C CNN
F 1 "+3.3V" H 3100 2410 30  0000 C CNN
F 2 "" H 3100 2300 60  0000 C CNN
F 3 "" H 3100 2300 60  0000 C CNN
	1    3100 2300
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 543C2BD7
P 1700 3200
F 0 "R5" V 1780 3200 40  0000 C CNN
F 1 "100k" V 1707 3201 40  0000 C CNN
F 2 "SM0402" V 1630 3200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1700 3200 30  0001 C CNN
	1    1700 3200
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 543C2BDD
P 2000 1200
F 0 "R3" V 2080 1200 40  0000 C CNN
F 1 "100k" V 2007 1201 40  0000 C CNN
F 2 "SM0402" V 1930 1200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 2000 1200 30  0001 C CNN
	1    2000 1200
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 543C2BE3
P 2150 1200
F 0 "R4" V 2230 1200 40  0000 C CNN
F 1 "100k" V 2157 1201 40  0000 C CNN
F 2 "SM0402" V 2080 1200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 2150 1200 30  0001 C CNN
	1    2150 1200
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 543C2BE9
P 1850 1200
F 0 "R2" V 1930 1200 40  0000 C CNN
F 1 "100k" V 1857 1201 40  0000 C CNN
F 2 "SM0402" V 1780 1200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1850 1200 30  0001 C CNN
	1    1850 1200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 543C2BEF
P 1700 1200
F 0 "R1" V 1780 1200 40  0000 C CNN
F 1 "100k" V 1707 1201 40  0000 C CNN
F 2 "SM0402" V 1630 1200 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1700 1200 30  0001 C CNN
	1    1700 1200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 543C2EF3
P 6500 1400
F 0 "C1" H 6500 1500 40  0000 L CNN
F 1 "10uF" H 6506 1315 40  0000 L CNN
F 2 "SM0603_Capa" H 6538 1250 30  0001 C CNN
F 3 "490-3340-1-ND" H 6500 1400 60  0001 C CNN
	1    6500 1400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C15
U 1 1 543C3067
P 1500 5950
F 0 "C15" H 1550 6050 50  0000 L CNN
F 1 "150uF" H 1550 5850 39  0000 L CNN
F 2 "c_elec_6.3x5.7" H 1500 5950 60  0001 C CNN
F 3 "493-9778-1-ND" H 1500 5950 60  0001 C CNN
	1    1500 5950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C5
U 1 1 543C306D
P 1850 4550
F 0 "C5" H 1900 4650 50  0000 L CNN
F 1 "150uF" H 1900 4450 39  0000 L CNN
F 2 "c_elec_6.3x5.7" H 1850 4550 60  0001 C CNN
F 3 "493-9778-1-ND" H 1850 4550 60  0001 C CNN
	1    1850 4550
	1    0    0    -1  
$EndComp
$Comp
L CP1 C8
U 1 1 543C3073
P 4200 6650
F 0 "C8" H 4250 6750 50  0000 L CNN
F 1 "150uF" H 4250 6550 39  0000 L CNN
F 2 "c_elec_6.3x5.7" H 4200 6650 60  0001 C CNN
F 3 "493-9778-1-ND" H 4200 6650 60  0001 C CNN
	1    4200 6650
	-1   0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 543C307F
P 2600 2500
F 0 "C2" H 2650 2600 50  0000 L CNN
F 1 "150uF" H 2650 2400 39  0000 L CNN
F 2 "c_elec_6.3x5.7" H 2600 2500 60  0001 C CNN
F 3 "493-9778-1-ND" H 2600 2500 60  0001 C CNN
	1    2600 2500
	1    0    0    -1  
$EndComp
$Comp
L CONN_4X2 P2
U 1 1 543C46D5
P 9100 5400
F 0 "P2" H 9100 5650 50  0000 C CNN
F 1 "CONN_4X2" V 9100 5400 40  0000 C CNN
F 2 "pin_array_4x2" H 9100 5400 60  0001 C CNN
F 3 "" H 9100 5400 60  0000 C CNN
	1    9100 5400
	1    0    0    -1  
$EndComp
Text GLabel 8600 5250 0    40   Input ~ 0
SPI2_SCK
NoConn ~ 9500 5350
$Comp
L GND #PWR020
U 1 1 543C46E7
P 9600 5250
F 0 "#PWR020" H 9600 5250 30  0001 C CNN
F 1 "GND" H 9600 5180 30  0001 C CNN
F 2 "" H 9600 5250 60  0000 C CNN
F 3 "" H 9600 5250 60  0000 C CNN
	1    9600 5250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9500 5250 9600 5250
Wire Wire Line
	8600 5250 8700 5250
Text GLabel 8600 5350 0    40   Input ~ 0
DEPTH_CS
Wire Wire Line
	8600 5350 8700 5350
Wire Wire Line
	9550 5450 9500 5450
Wire Wire Line
	9550 5000 9550 5450
Connection ~ 9550 5250
$Comp
L +3.3V #PWR021
U 1 1 543C4963
P 8600 5450
F 0 "#PWR021" H 8600 5410 30  0001 C CNN
F 1 "+3.3V" H 8600 5560 30  0000 C CNN
F 2 "" H 8600 5450 60  0000 C CNN
F 3 "" H 8600 5450 60  0000 C CNN
	1    8600 5450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8600 5450 8700 5450
Text GLabel 8600 5550 0    40   Input ~ 0
SPI2_MOSI
Wire Wire Line
	8600 5550 8700 5550
Text GLabel 9500 5550 2    40   Output ~ 0
SPI2_MISO
Text GLabel 4550 3300 0    15   Output ~ 0
DEPTH_CS
Wire Wire Line
	4550 3300 4700 3300
$Comp
L C C9
U 1 1 543C5A4E
P 9100 5000
F 0 "C9" H 9100 5100 40  0000 L CNN
F 1 "10uF" H 9106 4915 40  0000 L CNN
F 2 "SM0603_Capa" H 9138 4850 30  0001 C CNN
F 3 "490-3340-1-ND" H 9100 5000 60  0001 C CNN
	1    9100 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9550 5000 9300 5000
Wire Wire Line
	8900 5000 8650 5000
Wire Wire Line
	8650 5000 8650 5450
Connection ~ 8650 5450
$Comp
L CONN_4X2 P3
U 1 1 543C5FB1
P 8400 6300
F 0 "P3" H 8400 6550 50  0000 C CNN
F 1 "CONN_4X2" V 8400 6300 40  0000 C CNN
F 2 "pin_array_4x2" H 8400 6300 60  0001 C CNN
F 3 "" H 8400 6300 60  0000 C CNN
	1    8400 6300
	1    0    0    -1  
$EndComp
$Comp
L MS5803 BARO1
U 1 1 543C5FDC
P 9600 6050
F 0 "BARO1" H 9750 6250 60  0000 C CNN
F 1 "MS5803" H 9800 6150 60  0000 C CNN
F 2 "MS5803" H 9600 6050 60  0001 C CNN
F 3 "MS5803-05BA" H 9600 6050 60  0001 C CNN
	1    9600 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 6150 8000 6050
Wire Wire Line
	8000 6050 9300 6050
Wire Wire Line
	8800 6150 9300 6150
Wire Wire Line
	8000 6250 7900 6250
Wire Wire Line
	7900 6250 7900 5950
Wire Wire Line
	8800 6350 9100 6350
Wire Wire Line
	9100 6350 9100 6550
Wire Wire Line
	9100 6550 9300 6550
Wire Wire Line
	8000 6350 7900 6350
Wire Wire Line
	7900 6350 7900 6600
Wire Wire Line
	7900 6600 9200 6600
Wire Wire Line
	9200 6600 9200 6450
Wire Wire Line
	9200 6450 9300 6450
Wire Wire Line
	8000 6450 8000 6650
Wire Wire Line
	8000 6650 9300 6650
Wire Wire Line
	8800 6450 8800 6750
Wire Wire Line
	8800 6750 9300 6750
$Comp
L C C13
U 1 1 543C6794
P 9050 6950
F 0 "C13" H 9050 7050 40  0000 L CNN
F 1 "10uF" H 9056 6865 40  0000 L CNN
F 2 "SM0603_Capa" H 9088 6800 30  0001 C CNN
F 3 "490-3340-1-ND" H 9050 6950 60  0001 C CNN
	1    9050 6950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR022
U 1 1 543C679C
P 9250 7050
F 0 "#PWR022" H 9250 7050 30  0001 C CNN
F 1 "GND" H 9250 6980 30  0001 C CNN
F 2 "" H 9250 7050 60  0000 C CNN
F 3 "" H 9250 7050 60  0000 C CNN
	1    9250 7050
	1    0    0    -1  
$EndComp
Connection ~ 9250 6950
Wire Wire Line
	8850 6600 8950 6600
Wire Wire Line
	8850 6950 8850 6600
Connection ~ 8850 6600
Wire Wire Line
	8850 6200 9300 6200
Wire Wire Line
	8850 6200 8850 5950
Wire Wire Line
	8850 5950 7900 5950
Wire Wire Line
	9300 6200 9300 6250
Wire Wire Line
	9250 6150 9250 7050
Connection ~ 9250 6150
Wire Wire Line
	1050 5850 1250 5850
$Comp
L +5V #PWR023
U 1 1 543D9CE9
P 6500 1150
F 0 "#PWR023" H 6500 1240 20  0001 C CNN
F 1 "+5V" H 6500 1240 30  0000 C CNN
F 2 "" H 6500 1150 60  0000 C CNN
F 3 "" H 6500 1150 60  0000 C CNN
	1    6500 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1150 6500 1200
Wire Wire Line
	6500 1600 6500 1650
Wire Wire Line
	6500 1200 6300 1200
Wire Wire Line
	6300 1200 6300 1550
Wire Wire Line
	6300 1550 5750 1550
Wire Wire Line
	5750 1600 5700 1600
Wire Wire Line
	5750 1550 5750 1600
Wire Wire Line
	5850 1600 6750 1600
Wire Wire Line
	5850 1600 5850 1450
Wire Wire Line
	5850 1450 5750 1450
Wire Wire Line
	5750 1450 5750 1500
Wire Wire Line
	5750 1500 5700 1500
Wire Wire Line
	5750 1650 5750 1700
Wire Wire Line
	5750 1700 5700 1700
$Comp
L C C14
U 1 1 543DA2E1
P 6750 1400
F 0 "C14" H 6750 1500 40  0000 L CNN
F 1 "10uF" H 6756 1315 40  0000 L CNN
F 2 "SM0603_Capa" H 6788 1250 30  0001 C CNN
F 3 "490-3340-1-ND" H 6750 1400 60  0001 C CNN
	1    6750 1400
	1    0    0    -1  
$EndComp
Connection ~ 6500 1600
Wire Wire Line
	6750 1200 6750 1000
Wire Wire Line
	6000 1000 6850 1000
Wire Wire Line
	6000 1000 6000 1650
Wire Wire Line
	6000 1650 5750 1650
Text GLabel 6850 1000 2    60   Output ~ 0
STM_3V
Connection ~ 6750 1000
Text GLabel 2150 7000 2    60   Output ~ 0
STM_3V
$Comp
L R R7
U 1 1 543DA997
P 1800 7000
F 0 "R7" V 1880 7000 40  0000 C CNN
F 1 "100k" V 1807 7001 40  0000 C CNN
F 2 "SM0402" V 1730 7000 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1800 7000 30  0001 C CNN
	1    1800 7000
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 543DA99D
P 1800 7150
F 0 "R8" V 1880 7150 40  0000 C CNN
F 1 "100k" V 1807 7151 40  0000 C CNN
F 2 "SM0402" V 1730 7150 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1800 7150 30  0001 C CNN
	1    1800 7150
	0    1    -1   0   
$EndComp
Wire Wire Line
	2150 7000 2050 7000
$Comp
L PWR_FLAG #FLG024
U 1 1 543DAEAB
P 7900 6600
F 0 "#FLG024" H 7900 6695 30  0001 C CNN
F 1 "PWR_FLAG" H 7900 6780 30  0000 C CNN
F 2 "" H 7900 6600 60  0000 C CNN
F 3 "" H 7900 6600 60  0000 C CNN
	1    7900 6600
	-1   0    0    1   
$EndComp
NoConn ~ 8800 6250
Text GLabel 1300 7200 1    40   Output ~ 0
WATER
Text GLabel 4550 1950 0    15   Input ~ 0
WATER
Wire Wire Line
	4550 1950 4650 1950
NoConn ~ 5750 2050
NoConn ~ 5700 2000
Connection ~ 1500 6150
$Comp
L C C16
U 1 1 543DBDC2
P 1450 7550
F 0 "C16" H 1500 7650 50  0000 L CNN
F 1 "1uF" H 1500 7450 50  0000 L CNN
F 2 "SM0402_c" H 1450 7550 60  0001 C CNN
F 3 "490-1320-1-ND" H 1450 7550 60  0001 C CNN
	1    1450 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 6150 1750 6150
Wire Wire Line
	1250 5850 1250 6150
$Comp
L GND #PWR025
U 1 1 543DD393
P 1450 7850
F 0 "#PWR025" H 1450 7850 30  0001 C CNN
F 1 "GND" H 1450 7780 30  0001 C CNN
F 2 "" H 1450 7850 60  0000 C CNN
F 3 "" H 1450 7850 60  0000 C CNN
	1    1450 7850
	1    0    0    -1  
$EndComp
Connection ~ 1450 7300
Text GLabel 4550 2050 0    15   Input ~ 0
SW1
Text GLabel 4550 2450 0    15   Input ~ 0
SW3
Text GLabel 4550 2350 0    15   Input ~ 0
SW2
Wire Wire Line
	4550 2450 4650 2450
Wire Wire Line
	4550 2350 4650 2350
Wire Wire Line
	4550 2050 4650 2050
Text GLabel 10150 2000 2    40   Output ~ 0
SW2
$Comp
L SW_PUSH SW2A1
U 1 1 543F85AF
P 9150 2300
F 0 "SW2A1" H 9300 2410 50  0000 C CNN
F 1 "SW_PUSH" H 9150 2220 50  0000 C CNN
F 2 "P8008S-ND" H 9150 2300 60  0001 C CNN
F 3 "~" H 9150 2300 60  0000 C CNN
	1    9150 2300
	0    -1   -1   0   
$EndComp
$Comp
L C C20
U 1 1 543FA0AC
P 10000 2200
F 0 "C20" H 10050 2300 50  0000 L CNN
F 1 "1uF" H 10050 2100 50  0000 L CNN
F 2 "SM0402_c" H 10000 2200 60  0001 C CNN
F 3 "490-1320-1-ND" H 10000 2200 60  0001 C CNN
	1    10000 2200
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 543FA0B5
P 9650 2000
F 0 "R14" V 9730 2000 40  0000 C CNN
F 1 "100k" V 9657 2001 40  0000 C CNN
F 2 "SM0402" V 9580 2000 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 2000 30  0001 C CNN
	1    9650 2000
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 543FA0BB
P 9650 1850
F 0 "R13" V 9730 1850 40  0000 C CNN
F 1 "100k" V 9657 1851 40  0000 C CNN
F 2 "SM0402" V 9580 1850 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 1850 30  0001 C CNN
	1    9650 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 2000 9400 1850
Connection ~ 9400 2000
Wire Wire Line
	9400 2600 9400 2650
Wire Wire Line
	9900 2000 10150 2000
Connection ~ 10000 2000
$Comp
L +3.3V #PWR026
U 1 1 543FA0C9
P 9950 1850
F 0 "#PWR026" H 9950 1810 30  0001 C CNN
F 1 "+3.3V" H 9950 1960 30  0000 C CNN
F 2 "" H 9950 1850 60  0000 C CNN
F 3 "" H 9950 1850 60  0000 C CNN
	1    9950 1850
	0    1    1    0   
$EndComp
Connection ~ 9400 2600
$Comp
L GND #PWR027
U 1 1 543FA0D0
P 9400 2650
F 0 "#PWR027" H 9400 2650 30  0001 C CNN
F 1 "GND" H 9400 2580 30  0001 C CNN
F 2 "" H 9400 2650 60  0000 C CNN
F 3 "" H 9400 2650 60  0000 C CNN
	1    9400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1850 9950 1850
Wire Wire Line
	10000 2600 10000 2400
Text GLabel 10150 1050 2    40   Output ~ 0
SW1
$Comp
L SW_PUSH SW1B1
U 1 1 543FB3EA
P 9150 1350
F 0 "SW1B1" H 9300 1460 50  0000 C CNN
F 1 "SW_PUSH" H 9150 1270 50  0000 C CNN
F 2 "REED" H 9150 1350 60  0001 C CNN
F 3 "~" H 9150 1350 60  0000 C CNN
	1    9150 1350
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW1A1
U 1 1 543FB3F0
P 8850 1350
F 0 "SW1A1" H 9000 1460 50  0000 C CNN
F 1 "SW_PUSH" H 8850 1270 50  0000 C CNN
F 2 "P8008S-ND" H 8850 1350 60  0001 C CNN
F 3 "~" H 8850 1350 60  0000 C CNN
	1    8850 1350
	0    -1   -1   0   
$EndComp
$Comp
L C C19
U 1 1 543FB3F6
P 10000 1250
F 0 "C19" H 10050 1350 50  0000 L CNN
F 1 "1uF" H 10050 1150 50  0000 L CNN
F 2 "SM0402_c" H 10000 1250 60  0001 C CNN
F 3 "490-1320-1-ND" H 10000 1250 60  0001 C CNN
	1    10000 1250
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 543FB3FC
P 9650 1050
F 0 "R12" V 9730 1050 40  0000 C CNN
F 1 "100k" V 9657 1051 40  0000 C CNN
F 2 "SM0402" V 9580 1050 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 1050 30  0001 C CNN
	1    9650 1050
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 543FB402
P 9650 900
F 0 "R11" V 9730 900 40  0000 C CNN
F 1 "100k" V 9657 901 40  0000 C CNN
F 2 "SM0402" V 9580 900 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 900 30  0001 C CNN
	1    9650 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 1050 9400 900 
Connection ~ 9400 1050
Wire Wire Line
	9400 1650 9400 1700
Wire Wire Line
	9900 1050 10150 1050
Connection ~ 10000 1050
Wire Wire Line
	8850 1650 10000 1650
$Comp
L +3.3V #PWR028
U 1 1 543FB40E
P 9950 900
F 0 "#PWR028" H 9950 860 30  0001 C CNN
F 1 "+3.3V" H 9950 1010 30  0000 C CNN
F 2 "" H 9950 900 60  0000 C CNN
F 3 "" H 9950 900 60  0000 C CNN
	1    9950 900 
	0    1    1    0   
$EndComp
Connection ~ 9400 1650
$Comp
L GND #PWR029
U 1 1 543FB415
P 9400 1700
F 0 "#PWR029" H 9400 1700 30  0001 C CNN
F 1 "GND" H 9400 1630 30  0001 C CNN
F 2 "" H 9400 1700 60  0000 C CNN
F 3 "" H 9400 1700 60  0000 C CNN
	1    9400 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 900  9950 900 
Wire Wire Line
	8850 1050 9400 1050
Connection ~ 9150 1050
Wire Wire Line
	10000 1650 10000 1450
Connection ~ 9150 1650
Text GLabel 10150 2950 2    40   Output ~ 0
SW3
$Comp
L SW_PUSH SW3B1
U 1 1 543FB421
P 9150 3250
F 0 "SW3B1" H 9300 3360 50  0000 C CNN
F 1 "SW_PUSH" H 9150 3170 50  0000 C CNN
F 2 "REED" H 9150 3250 60  0001 C CNN
F 3 "~" H 9150 3250 60  0000 C CNN
	1    9150 3250
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW3A1
U 1 1 543FB427
P 8850 3250
F 0 "SW3A1" H 9000 3360 50  0000 C CNN
F 1 "SW_PUSH" H 8850 3170 50  0000 C CNN
F 2 "P8008S-ND" H 8850 3250 60  0001 C CNN
F 3 "~" H 8850 3250 60  0000 C CNN
	1    8850 3250
	0    -1   -1   0   
$EndComp
$Comp
L C C21
U 1 1 543FB42D
P 10000 3150
F 0 "C21" H 10050 3250 50  0000 L CNN
F 1 "1uF" H 10050 3050 50  0000 L CNN
F 2 "SM0402_c" H 10000 3150 60  0001 C CNN
F 3 "490-1320-1-ND" H 10000 3150 60  0001 C CNN
	1    10000 3150
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 543FB433
P 9650 2950
F 0 "R16" V 9730 2950 40  0000 C CNN
F 1 "100k" V 9657 2951 40  0000 C CNN
F 2 "SM0402" V 9580 2950 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 2950 30  0001 C CNN
	1    9650 2950
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 543FB439
P 9650 2800
F 0 "R15" V 9730 2800 40  0000 C CNN
F 1 "100k" V 9657 2801 40  0000 C CNN
F 2 "SM0402" V 9580 2800 30  0001 C CNN
F 3 "1276-4424-1-ND" H 9650 2800 30  0001 C CNN
	1    9650 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 2950 9400 2800
Connection ~ 9400 2950
Wire Wire Line
	9400 3550 9400 3600
Wire Wire Line
	9900 2950 10150 2950
Connection ~ 10000 2950
Wire Wire Line
	8850 3550 10000 3550
$Comp
L +3.3V #PWR030
U 1 1 543FB445
P 9950 2800
F 0 "#PWR030" H 9950 2760 30  0001 C CNN
F 1 "+3.3V" H 9950 2910 30  0000 C CNN
F 2 "" H 9950 2800 60  0000 C CNN
F 3 "" H 9950 2800 60  0000 C CNN
	1    9950 2800
	0    1    1    0   
$EndComp
Connection ~ 9400 3550
$Comp
L GND #PWR031
U 1 1 543FB44C
P 9400 3600
F 0 "#PWR031" H 9400 3600 30  0001 C CNN
F 1 "GND" H 9400 3530 30  0001 C CNN
F 2 "" H 9400 3600 60  0000 C CNN
F 3 "" H 9400 3600 60  0000 C CNN
	1    9400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 2800 9950 2800
Wire Wire Line
	8850 2950 9400 2950
Connection ~ 9150 2950
Wire Wire Line
	10000 3550 10000 3350
Connection ~ 9150 3550
Wire Wire Line
	9150 2000 9400 2000
Wire Wire Line
	9150 2600 10000 2600
$Comp
L LP38692 U1
U 1 1 54418EEC
P 3000 6250
F 0 "U1" H 3125 5850 60  0000 C CNN
F 1 "5V" H 3125 6350 60  0000 C CNN
F 2 "SOT-223-5" H 3025 5750 60  0001 C CNN
F 3 "LP38692MP-5.0/NOPBCT-ND" H 3125 5850 60  0001 C CNN
	1    3000 6250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3300 6850 4200 6850
Connection ~ 3850 6850
Wire Wire Line
	3300 6550 3300 6950
Connection ~ 3550 6850
Wire Wire Line
	3300 6450 3550 6450
Wire Wire Line
	3300 6250 3400 6250
Wire Wire Line
	3400 6250 3400 6450
Connection ~ 3400 6450
Wire Wire Line
	3300 6350 4200 6350
Wire Wire Line
	4200 6350 4200 6450
Wire Wire Line
	3850 6450 3850 6350
Connection ~ 3850 6350
Connection ~ 3300 6850
$Comp
L +BATT #PWR032
U 1 1 54419D7C
P 3550 7350
F 0 "#PWR032" H 3550 7300 20  0001 C CNN
F 1 "+BATT" H 3550 7450 30  0000 C CNN
F 2 "" H 3550 7350 60  0000 C CNN
F 3 "" H 3550 7350 60  0000 C CNN
	1    3550 7350
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR033
U 1 1 54419D82
P 3300 7850
F 0 "#PWR033" H 3300 7850 30  0001 C CNN
F 1 "GND" H 3300 7780 30  0001 C CNN
F 2 "" H 3300 7850 60  0000 C CNN
F 3 "" H 3300 7850 60  0000 C CNN
	1    3300 7850
	-1   0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 54419D8E
P 3850 7550
F 0 "C11" H 3900 7650 50  0000 L CNN
F 1 "1uF" H 3900 7450 50  0000 L CNN
F 2 "SM0402_c" H 3850 7550 60  0001 C CNN
F 3 "490-1320-1-ND" H 3850 7550 60  0001 C CNN
	1    3850 7550
	-1   0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 54419D94
P 3550 7550
F 0 "C10" H 3600 7650 50  0000 L CNN
F 1 "1uF" H 3600 7450 50  0000 L CNN
F 2 "SM0402_c" H 3550 7550 60  0001 C CNN
F 3 "490-1320-1-ND" H 3550 7550 60  0001 C CNN
	1    3550 7550
	-1   0    0    -1  
$EndComp
$Comp
L CP1 C12
U 1 1 54419D9A
P 4200 7550
F 0 "C12" H 4250 7650 50  0000 L CNN
F 1 "150uF" H 4250 7450 39  0000 L CNN
F 2 "c_elec_6.3x5.7" H 4200 7550 60  0001 C CNN
F 3 "493-9778-1-ND" H 4200 7550 60  0001 C CNN
	1    4200 7550
	-1   0    0    -1  
$EndComp
$Comp
L LP38692 U2
U 1 1 54419DA0
P 3000 7150
F 0 "U2" H 3125 6750 60  0000 C CNN
F 1 "3.3V" H 3125 7250 60  0000 C CNN
F 2 "SOT-223-5" H 3025 6650 60  0001 C CNN
F 3 "LP38692MP-3.3/NOPBCT-ND" H 3125 6750 60  0001 C CNN
	1    3000 7150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3300 7750 4200 7750
Connection ~ 3850 7750
Wire Wire Line
	3300 7450 3300 7850
Connection ~ 3550 7750
Wire Wire Line
	3300 7350 3550 7350
Wire Wire Line
	3300 7150 3400 7150
Wire Wire Line
	3400 7150 3400 7350
Connection ~ 3400 7350
Wire Wire Line
	3300 7250 4200 7250
Wire Wire Line
	4200 7250 4200 7350
Wire Wire Line
	3850 7350 3850 7250
Connection ~ 3850 7250
Connection ~ 3300 7750
Wire Wire Line
	1600 4750 1600 4800
Connection ~ 1600 4800
Connection ~ 1850 4350
$Comp
L R R9
U 1 1 5441C1D6
P 1800 7300
F 0 "R9" V 1880 7300 40  0000 C CNN
F 1 "100k" V 1807 7301 40  0000 C CNN
F 2 "SM0402" V 1730 7300 30  0001 C CNN
F 3 "1276-4424-1-ND" H 1800 7300 30  0001 C CNN
	1    1800 7300
	0    1    -1   0   
$EndComp
Wire Wire Line
	2050 7150 2100 7150
Wire Wire Line
	2100 7150 2100 7300
Wire Wire Line
	2100 7300 2050 7300
Wire Wire Line
	1550 7000 1500 7000
Wire Wire Line
	1500 7000 1500 7150
Wire Wire Line
	1500 7150 1550 7150
Wire Wire Line
	1450 7850 1450 7750
Wire Wire Line
	1200 7300 1550 7300
Wire Wire Line
	1450 7300 1450 7350
Wire Wire Line
	1200 7400 1300 7400
Wire Wire Line
	1300 7400 1300 7750
Wire Wire Line
	1300 7750 1450 7750
Wire Wire Line
	1300 7200 1300 7300
Connection ~ 1300 7300
$Comp
L CONN_4 P4
U 1 1 543DD38D
P 850 7450
F 0 "P4" V 800 7450 50  0000 C CNN
F 1 "CONN_4" V 900 7450 50  0000 C CNN
F 2 "ED10563-ND" H 850 7450 60  0001 C CNN
F 3 "" H 850 7450 60  0000 C CNN
	1    850  7450
	-1   0    0    1   
$EndComp
NoConn ~ 1200 7500
NoConn ~ 1200 7600
$Comp
L +3.3V #PWR034
U 1 1 544314FA
P 1050 5950
F 0 "#PWR034" H 1050 5910 30  0001 C CNN
F 1 "+3.3V" H 1050 6060 30  0000 C CNN
F 2 "" H 1050 5950 60  0000 C CNN
F 3 "" H 1050 5950 60  0000 C CNN
	1    1050 5950
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR035
U 1 1 54431500
P 1050 6050
F 0 "#PWR035" H 1050 6140 20  0001 C CNN
F 1 "+5V" H 1050 6150 30  0000 C CNN
F 2 "" H 1050 6050 60  0000 C CNN
F 3 "" H 1050 6050 60  0000 C CNN
	1    1050 6050
	0    1    -1   0   
$EndComp
$EndSCHEMATC
