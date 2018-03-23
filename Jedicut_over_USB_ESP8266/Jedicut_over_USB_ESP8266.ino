/* Copyright 2013 Martin
    Modified 2018 Javier Hernandez
    This file is part of jedicutplugin.
    Jedicut_over_USB_ESP8266.ino is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Jedicut_over_USB_ESP8266.ino is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.*/
    
/*
The jedicut communication configuration for Clock and Direction must be fixed set to the below values, 
only the wires to the specific board may be different -- wire to -->

Function               Number in jedicut        Arduino Pin            e.g. TB6560 SubD25 pin
                           configuration
                           (fixed !!)
EngineX1 Clock          2                                 D1      -- wire to -->       16   
EngineX2 Clock          3                                 D2     -- wire to -->        9
EngineY1 Clock          4                                 D3      -- wire to -->        14
EngineY2 Clock          5                                 D4     -- wire to -->        3
EngineX1 Direction     6                                 D5      -- wire to -->        1
EngineX2 Direction     7                                 D6     -- wire to -->        8
EngineY1 Direction     8                                 D7     -- wire to -->        7
EngineY2 Direction     9                                 D8      -- wire to -->        6
All Engines On/Off     -                                  D0      -- wire to -->       17; 4 and 5
Heating On/off         -                                   N/A     
Heating PWM            -                                  N/A    
Ground                     -                                  G        -- wire to -->  SubD 15 Pin 14
*/ 

////// This release is operative for TB6560 4 axis board and Wemos D1 mini ESP8266 based arduino IDE compatible board
////// Other motor controller board and  esp8266 board should be changed acordingly
////// No wire heating control
////// Todo: speed control thru USB


//int MICRODELAY=90; //   period of pulses in microsecond, change this to change desired speed, the limit: overlapping interrupts...
int tickPeriod=65;      //   motor pulses lenght, in microsecs, change this to suit your board performance
int stepmin_period = 200;              //microseconds, Fast Speed (here is 5.000Hz pulse rate)  change this to change desired speed, the lowest limit: overlapping interrupts, vibrations in the table... 
int stepmax_period = 500;           //microseconds,  Cut speed (here is 1.000Hz pulse rate)   change this to change desired speed, the limit: your patience as speed will go ... 
int step_period = stepmax_period;  //   period of pulses in microseconds, either the max or the min, as selected by Jedicut

#define CMD_BUFFER_SIZE 1200  // must be even !
volatile byte cmdArray[CMD_BUFFER_SIZE];
volatile int arrayIdxRead  = 0;
volatile int arrayIdxWrite = 0;
volatile int cmdCounter = 0;
volatile boolean ovf = false;

volatile bool isrActive = false;

unsigned int val = 0; // The command parameter value
int pines[]={D1, D2, D3, D4, D5, D6, D7, D8};
//unsigned char BufferRecep[2]={0};
int timemark=0;
