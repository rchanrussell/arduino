arduino
=======
/*
 * I2C Bit Bang Project using Arduino Uno
 * Path: I2C_bitbang_write_read 
 */

Provided is the code to bitbang out I2C reads and writes without using the Wire library.
Pin 12 is the clock, SCL
Pin 13 is the data, SDA
Board used, Arduino Uno Rev3
I2C device, 24AA1025 from Microchip, digikey PN: 24AA1024-I/P-ND, IC EEPROM 1MBIT 400KHZ 8DIP
No pull-up resistors were added, as the Arduino has this built in.
24AA1025 pinout (pin#, meaning, connection):
1 - A0  - VSS (address bit 0)
2 - A1  - VSS (address bit 1)
3 - A2  - VCC (address bit 3, must be VCC)
4 - VSS - VSS
5 - SDA - SDA (pin 13 of Arduino)
6 - SCL - SCL (pin 12 of Arduino)
7 - WP  - VSS (if VCC writes disabled)
8 - VCC - VCC

VCC is 5V from Arduino Uno 5V output header


