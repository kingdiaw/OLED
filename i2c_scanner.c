/*
 * File:   i2c_scanner.c
 * Author: Acer
 *
 * Created on May 15, 2021, 9:09 AM
 */
#include "picuno.h" 
#include "Wire.h"

char buf[32];

void setup(){
Serial_begin(9600);  
Wire_begin(100000);
Serial_println("\nI2C Scanner");
}
void loop(){
  byte error, address;
  int nDevices;
  
Serial_println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
      Wire_beginTransmission(address);
      error = Wire_endTransmission();
      
      if(error == 0){
          sprintf(buf,"I2C device found at address 0x%.2X!",address);
          Serial_println(buf);
          nDevices++;
      }      
  }
  if (nDevices == 0)
    Serial_println("No I2C devices found\n");
  else
    Serial_println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan  
}