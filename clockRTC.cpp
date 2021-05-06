#include "clockRTC.h"
#include <Wire.h>


#ifdef I2C_2
  #define WIRE Wire1
#else
  #define WIRE Wire
#endif

ClockRTC::ClockRTC(){ 
  WIRE.begin();
  Serial.begin(9600);
}

ClockRTC::ClockRTC(byte address){
  addr  = address; 
  WIRE.begin();

  int i = 0;
  
  WIRE.beginTransmission(addr);
  WIRE.write(i);   // Register 0x00 holds the oscillator start/stop bit
  WIRE.endTransmission();
  WIRE.requestFrom((int)addr, 1);
  int sec = WIRE.read() & 0x7f;       // save actual seconds and AND sec with bit 7 (sart/stop bit) = clock started
  WIRE.beginTransmission(addr);
  WIRE.write(i);
  WIRE.write(sec);                    // write seconds back and start the clock
  WIRE.endTransmission();
}

void ClockRTC::setAddr(byte address){
  addr  = address;
}

Date ClockRTC::getDate(){
   WIRE.beginTransmission(addr);
   WIRE.write(0x00);
   WIRE.endTransmission();
   
   WIRE.requestFrom((int)addr, 7);
   uint8_t sec = BDC2Bin(WIRE.read() & 0x7F);
   uint8_t mn = BDC2Bin(WIRE.read() & 0x7F);
   uint8_t h = BDC2Bin(WIRE.read() & 0x3F);
   WIRE.read();
   uint8_t d = BDC2Bin(WIRE.read()& 0x3F);
   uint8_t m = BDC2Bin(WIRE.read() & 0x1F);
   uint8_t y = BDC2Bin(WIRE.read());

   return Date(y, m, d, h, mn, sec);
}

void ClockRTC::setDate(Date d){
   WIRE.beginTransmission(addr);
   WIRE.write(0x00);
   
   WIRE.write(bin2BDC(d.sec));
   WIRE.write(bin2BDC(d.mn));
   WIRE.write(bin2BDC(d.h));
   WIRE.write(0);
   WIRE.write(bin2BDC(d.d));
   WIRE.write(bin2BDC(d.m));
   WIRE.write(bin2BDC(d.y));
   
   WIRE.endTransmission();
  
}

Date ClockRTC::getTime(){
   WIRE.beginTransmission(addr);
   WIRE.write(0x00);
   WIRE.endTransmission();
   
   WIRE.requestFrom((int)addr, 7);
   uint8_t sec = BDC2Bin(WIRE.read() & 0x7F);
   uint8_t mn = BDC2Bin(WIRE.read() & 0x7F);
   uint8_t h = BDC2Bin(WIRE.read() & 0x3F);
   WIRE.read();
   uint8_t d = BDC2Bin(WIRE.read() & 0x3F);
   uint8_t m = BDC2Bin(WIRE.read() & 0x1F);
   uint8_t y = BDC2Bin(WIRE.read());

   return Date(h, mn, sec);
}

void ClockRTC::setTime(Date d){
   WIRE.beginTransmission(addr);
   WIRE.write(0x00);
   
   WIRE.write(bin2BDC(d.sec));
   WIRE.write(bin2BDC(d.mn));
   WIRE.write(bin2BDC(d.h));
   
   WIRE.endTransmission();
  
}

uint8_t ClockRTC::BDC2Bin(uint8_t bdc){
  return (((bdc & 0xF0) >> 4)*10 + (bdc & 0x0F));
}

uint8_t ClockRTC::bin2BDC(uint8_t i){
  return (((i / 10) << 4) + (i & 0x0F));
}


Date ClockRTC::getStubTime(){
   tmp = tmp + 15;
   return tmp; 
}


void ClockRTC::printDate(){

  Date now = getDate();
  Serial.println("printDate :");
  Serial.print(now.d);
  Serial.print("/");
  Serial.print(now.m);
  Serial.print("/20");
  Serial.print(now.y);
  Serial.print("   ");
  Serial.print(now.h);
  Serial.print(":");
  Serial.print(now.mn);
  Serial.print(":");
  Serial.println(now.sec);
  Serial.println("end printDate");
  
}  
