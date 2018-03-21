# Jedicut_over_USB_ESP8266
Extension pluging to use Jedicut with SerialUSB.dll and an Arduino ESP8266

ESP8266 chip has brought to Arduino world a new perspective for connectivity.
I have been a user of JEDICUT since 2011, very successfully, for hot wire cutting the foam wings of my aeromodels. Most of CNC controllers, and Jedicut was, only had a parallel port I/F and that is the way I connected my board... It has been since summer 2015 that I bumped somehow to the ESP8266 environment.
I was just starting to use Arduino Uno as a curiosity then I found ESP8266 environment that was fast developing by then, I felt dizzy on what was coming and that has became much reality.
So I did develop for myself and friends several nice applications, but I had to keep alive my XP computer and every day I crossed my fingers nothing happened to its motherboard... and when I returned by Jedicut pages I discovered that a USB interface was available and an aplication was done for Arduino!
Unfortunately I discovered that since the Source code Martin kindly shared was written for "genuine" Arduinos both the pinout and the way interrupts were handled were different.
So this is why I am sharing this adaptation for the ESP8266 processor.

# Hardware requirements

You will need a Personal computer, a CNC Foam Cutting Table, a suitable to your table stepper motor controller board and the Jedicut software.
See:
https://www.jedicut.com/

where a lot of advise can be found on this. Note there is a English version in this page.
Since most modern computers do not feature an LPT parallel port, the native interface for Jedicut and the controller board, several alternatives have been developed successfully to use different boards and in particular the universally accepted USB port of most of computers nowadays.
See Jedicut extensions:
https://github.com/jedicut/jedicut-devices-extensions
The extension I used was the USBSerial.dll as the Jedicut extension. By Using it Jedicut will output to a Serial port the stram of comands for controlling the board and then the table movements.

# Jedicut Configuration
The folowing paragraph aply to my own table configuration and pinout and most of them. Obviously you will need to acomodate to your board and table peculiars.

Jedicut/Tools/Comunication:
First Select "USBSerial.dll" as 'Comunication Mode'.

Parallel Port configuration is to be set to the following: NO MATER WHAT PINOUT your table has.

Function        Number in jedicut        
                configuration
                (fixed !!)
                           
MotorX1 Clock     2   

MotorX2 Clock     3      

MotorY1 Clock     4 

MotorY2 Clock     5  

MotorX1 Direction 6  

MotorX2 Direction 7    

MotorY1 Direction 8 

MotorY2 Direction 9 

This is because Jedicut is just transmiting this commands over the Serial and it is the Arduino that decodes these commands in the  phisical motors connections.

The rest of parameters in this page can be ignored.

Jedicut/Tools/CNC:

-Set the mm per step of your motors, mine are 0,000625 mm/step, that equals 1600 steps per mm (or turn in my case since I use a M6 threaded bar as spindle screw.

-Set cut Speed to "255"
-Set fast speed to "1"

USBserial provides a stream of commands in the foemat A,M,H,F and a byte like A1 (enable motors) or M35 (step in the direction desired) or F1 (fast speed).
I have noticed the USB driver does only command F values (frequency) toggling between the fast and cut values and only when a speed change is needed. As well surprisingly I realizaed that a "266-n" was transmited as an F command when a PAUSE was needed in the Cycle Cut Manager.
This is implemented in the arduino code so when a Fx when x is between 2 and 254 a pause of x tenths of second is done by the table. Do not place Pauses higher than 254 or less than 2 (tenths os seconds) or maybe the cut speed could change!

In this area configue the dimensions of your table acordingly, mine is hot wire length 912 mm and Length of X axis 400 mm.

First of all is my board never had a heating control so I cannot advise here very much on Jedicut Heating control. I set my table speed and tune manually the wire intensity. I control the wire intensity because I think it will control the wire temperature more acurately.... And is much to write about this. On the other hand the electronics you need for it is more complicated.
Function               Number in jedicut        Arduino Pin            e.g. TB6560 SubD25 pin
                           configuration
                           (fixed !!)
EngineX1 Clock               2                               D1      -- wire to -->       16   
EngineX2 Clock               3                                 D2     -- wire to -->        9
EngineY1 Clock               4                                 D3      -- wire to -->        14
EngineY2 Clock          5                                 D4     -- wire to -->        3
EngineX1 Direction      6                                 D5      -- wire to -->        1
EngineX2 Direction      7                                 D6     -- wire to -->        8
EngineY1 Direction      8                                 D7     -- wire to -->        7
EngineY2 Direction      9                                 D8      -- wire to -->        6
All Engines On/Off      -                                 D0      -- wire to -->       17; 4 and 5
Heating On/off          -                                 N/A     
Heating PWM             -                                 N/A    
+5V                     -                                 5V       -- wire to -->  SubD 15 Pin 15
Ground                  -                                  G        -- wire to -->  SubD 15 Pin 14
(this is to be configured in Jedicut/Tools/Comunication).
