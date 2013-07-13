/*
  Copyright under GPL
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

 This file reads data from a BMA020 3-achses acceleration sensor
 and prints it via Serial-library over USB
*/

#include <Wire.h>

#define ACCELEROMETER 0x38

#define X_OUT1 0x02
#define X_OUT2 0x03

#define Y_OUT1 0x04
#define Y_OUT2 0x05

#define Z_OUT1 0x06
#define Z_OUT2 0x07


void setup() {
  // initialize the serial communications:
  Serial.begin(19200);
  Wire.begin();
  //set acc sensor to update data with 1.5KHz
  byte bma_settings = accRead(0x14);
  accWrite((bma_settings|6));
}

void loop() {
  // print the sensor values:
  printXVal();
  Serial.print("\t\t");
  printYVal();
  Serial.print("\t\t");
  printZVal();
  Serial.print("\t\t");
  Serial.println();
  // delay before next reading:
  delay(5);
}

void printXVal() {
  Serial.print("x: ");
  int raw_x1 = (int)accRead(X_OUT1);
  int raw_x2 = (int)accRead(X_OUT2);
  byte  low_bits[8] = {0,0,0,0,0,0,0,0};
  byte high_bits[8] = {0,0,0,0,0,0,0,0};
  uint2bitAry(raw_x1, low_bits);
  uint2bitAry(raw_x2, high_bits);
  int negative_flag = high_bits[7];
  int raw_acceleration = negative_flag<<15;
  if(negative_flag) raw_acceleration >>= 6;
  byte value_ary[9] = {low_bits[6], low_bits[7], high_bits[0], high_bits[1], high_bits[2], high_bits[3], high_bits[4], high_bits[5], high_bits[6]};
  
  int acceleration_value = bitarray2int(value_ary, 9);
  raw_acceleration |= acceleration_value;

  Serial.print(raw_acceleration);
}

void printYVal() {
  Serial.print("y: ");
  int raw_y1 = (int)accRead(Y_OUT1);
  int raw_y2 = (int)accRead(Y_OUT2);
  byte  low_bits[8] = {0,0,0,0,0,0,0,0};
  byte high_bits[8] = {0,0,0,0,0,0,0,0};
  uint2bitAry(raw_y1, low_bits);
  uint2bitAry(raw_y2, high_bits);
  int negative_flag = high_bits[7];
  int raw_acceleration = negative_flag<<15;
  if(negative_flag) raw_acceleration >>= 6;
  byte value_ary[9] = {low_bits[6], low_bits[7], high_bits[0], high_bits[1], high_bits[2], high_bits[3], high_bits[4], high_bits[5], high_bits[6]};
  
  int acceleration_value = bitarray2int(value_ary, 9);
  raw_acceleration |= acceleration_value;
  
  Serial.print(raw_acceleration);
}

void printZVal() {
  Serial.print("z: ");
  int raw_z1 = (int)accRead(Z_OUT1);
  int raw_z2 = (int)accRead(Z_OUT2);
  byte  low_bits[8] = {0,0,0,0,0,0,0,0};
  byte high_bits[8] = {0,0,0,0,0,0,0,0};
  uint2bitAry(raw_z1, low_bits);
  uint2bitAry(raw_z2, high_bits);
  int negative_flag = high_bits[7];
  int raw_acceleration = negative_flag<<15;
  if(negative_flag) raw_acceleration >>= 6;
  byte value_ary[9] = {low_bits[6], low_bits[7], high_bits[0], high_bits[1], high_bits[2], high_bits[3], high_bits[4], high_bits[5], high_bits[6]};
  
  int acceleration_value = bitarray2int(value_ary, 9);
  raw_acceleration |= acceleration_value;
  
  Serial.print(raw_acceleration);
}

void uint2bitAry(unsigned int number, byte* ary) {
  unsigned int original_number = number;
  byte i = 0;
  for (i = 0; i < 8; i++) {
    number = original_number;
    byte bit = (number & (1<<i)) >> i;
    ary[i] = bit;
  }
}

int bitarray2int(byte* ary, byte length) {
  int number = 0;
  byte i = 0;
  for (i = 0; i < length; i++) {
    if( ary[i] ) {
      number += 1<<i;
    }
  }
  return number;
}

byte accRead(byte address) {
  byte val = 0x00;
  Wire.beginTransmission(ACCELEROMETER);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(ACCELEROMETER, 1);
  val = Wire.read();
  Wire.endTransmission();
  return val;
}

void accWrite(byte value) {
  Wire.beginTransmission(ACCELEROMETER);
  Wire.write(value);
  Wire.endTransmission();
}


