BMA020-vibration-modul
======================
This project is targeted to measure vibrations of remote-controlled helicopters.
The acceleration sensor I use is a Bosch BMA020, quite old, but I hope it will fit my needs.

The microcontroller is a Arduino micro. I connected the BMA020 to 3.3V from the Arduino, sensor data
is transmitted via I2C on digital ports 2 and 3 of the Arduino.


Hardware descriptions can be found here:<br/>
http://arduino.cc/de/Main/ArduinoBoardMicro<br/>
http://www.mikrocontroller.net/attachment/51241/BMA020_DataSheet_1.1_080114.pdf
