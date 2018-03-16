# Jedicut_over_USB_ESP8266
Extension pluging to use Jedicut with SerialUSB.dll and an Arduino ESP8266

ESP8266 chip has brought to Arduino world a new perspective for connectivity.
I have been a user of JEDICUT since 2011, very successfully, for hot wire cutting the foam wings of my aeromodels. Most of CNC controllers, and Jedicut was, only had a parallel port I/F and that is the way I connected my board... It has been since summer 2015 that I bumped somehow to the ESP8266 environment.
I was just starting to use Arduino Uno as a curiosity then I found ESP8266 environment that was fast developing by then, I felt dizzy on what was coming and that has became much reality.
So I did develop for myself and friends several nice applications, but I had to keep alive my XP computer and every day I crossed my fingers nothing happened to its motherboard... and when I returned by Jedicut pages I discovered that a USB interface was available and an aplication was done for Arduino!
Unfortunately I discovered that since the Source code Martin kindly shared was written for "genuine" Arduinos both the pinout and the way interrupts were handled were different.
So this is why I am sharing this adaptation for the ESP8266 processor.

# Hardware requirements
