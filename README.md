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

***Make sure you have in the same folder as Jedicut commport.ini
https://github.com/jedicut/jedicut-devices-extensions/blob/master/USBSerial/comport.ini
or USBSerial.dll will not know which com port to use***

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

This is because Jedicut is just transmiting this commands over the Serial and it is the Arduino that decodes these commands in the  phisical motors connections. See the thread https://www.jedicut.com/forums/viewtopic.php?f=6&t=8582
Maybe you already were there...

The rest of parameters in this page can be ignored.

Jedicut/Tools/CNC:

-Set the mm per step of your motors, mine are 0,000625 mm/step, that equals 1600 steps per mm (or turn in my case since I use a M6 threaded bar as spindle screw.

-Set cut Speed to "255"
-Set fast speed to "1"

USBserial provides a stream of commands in the foemat A,M,H,F and a byte like A1 (enable motors) or M35 (step in the direction desired) or F1 (fast speed).
I have noticed the USB driver does only command F values (frequency) toggling between the fast and cut values and only when a speed change is needed. As well surprisingly I realizaed that a "266-n" was transmited as an F command when a PAUSE was needed in the Cycle Cut Manager.
This is implemented in the arduino code so when a Fx when x is between 2 and 254 a pause of x tenths of second is done by the table. Do not place Pauses higher than 254 or less than 2 (tenths os seconds) or maybe the cut speed could change!

In this area configue the dimensions of your table acordingly, mine is hot wire length 912 mm and Length of X axis 400 mm.


Jedicut/Tools/Heating:
My board never had a heating control so I cannot advise here very much on Jedicut Heating control. I set my table speed and tune manually the wire heating intensity. I control the wire intensity because I think it will control the wire temperature more acurately.... And is much to write about this. On the other hand the electronics you need for it is more complicated.
The infrastucture for Heating control is in the driver and in the arduino code if you feel brave you can use the TX or RX pins of D1-mini as PWM output (in the wire less version). My recomendation for upgrading this SW would be use another D1-mini as an webserver that would receive Heating commands... Something todo... But as today Heating comands are just ignored.

# The Arduino Side

To manage the Arduino code you need Arduino IDE: https://www.arduino.cc/en/Main/Software (I used 1.8.3)
And the Esp8266 board https://github.com/esp8266/Arduino adde in the boards manager.
Please do not forget to install in your PC the painfull to install driver for th CH340 usb-to-uart chip.
Then you need one or two WeMos D1-mini https://es.aliexpress.com/store/product/D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/1331105_32529101036.html?spm=a219c.12010612.0.0.3d8e6607QP3g1u

First the pinout for controlling the board

Function               Number in jedicut              Arduino Pin            e.g. TB6560 SubD25 pin
                           configuration
                           (fixed !!)
EngineX1 Clock               2                                 D1      -- wire to -->       16   
EngineX2 Clock               3                                 D2      -- wire to -->        9
EngineY1 Clock               4                                 D3      -- wire to -->        14
EngineY2 Clock               5                                 D4      -- wire to -->        3
EngineX1 Direction           6                                 D5      -- wire to -->        1
EngineX2 Direction           7                                 D6      -- wire to -->        8
EngineY1 Direction           8                                 D7      -- wire to -->        7
EngineY2 Direction           9                                 D8      -- wire to -->        6
All Engines On/Off           -                                 D0      -- wire to -->       17; 4 and 5
Heating On/off               -                                 N/A     
Heating PWM                  -                                 N/A    
+5V                          -                                 5V       -- wire to -->  SubD 15 Pin 15
Ground                       -                                  G       -- wire to -->  SubD 15 Pin 14
The Arduino configuration and pinout are at the right part of the table, this is the configuration I made to work but will depend of your actual wiring.
Important here:
You have to ground the arduino, at least, the +5V is for the wireless version only.
Also you have to be aware that ESP8266 and the D1-mini aswell is a 3,3V chip so its output '1' will be 3,3V very most of board will interpet this as a genuine '1' if you experience problems you can install a logic level shifter chip (0,5Eur) but I do not recommend as a start.

