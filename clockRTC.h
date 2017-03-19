#ifndef CLOCKRTC_H
#define CLOCKRTC_H

#include "Arduino.h"
#include "date.h"


class ClockRTC{
  public:
   ClockRTC();
   ClockRTC(byte address);
    
   //void setAddr(byte address);
   Date getDate();
   void setDate(Date d);
    
   Date getTime();
   void setTime(Date d);
   
   void printDate();
   Date getStubTime();
   
   void setAddr(byte address);
  
  private:
    byte addr;
    Date tmp;
    
  
    uint8_t BDC2Bin(uint8_t bdc);
    uint8_t bin2BDC(uint8_t i);
};

#endif
