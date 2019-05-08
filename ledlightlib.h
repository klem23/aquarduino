#ifndef LED_LIGHT_LIB_H
#define LED_LIGHT_LIB_H

#include "Arduino.h"
#include "clockRTC.h"

typedef struct{
      uint8_t type;

      int ledPin;
      byte maxPower;
      byte powStart;
      
      Date startTime;
      int startLgth;
      Date stopTime;
      int stopLgth;
      
      boolean ephem;
      
      void* next;
}lightParam;

class LedLightLib{

  private:
    lightParam* lp;
    
    int nbGrp;
    int fanPin;
    byte shift;
    int forcePin;
    
    ClockRTC* ck;

    lightParam* getEntryByPin(int pin);
    void add(lightParam* ptr);

  public:  
    LedLightLib();
    LedLightLib(int light_pin, byte max_power);
    
    /*Multiple Schedule*/
    void setSchedule(int pin_num, byte max_power, Date start_time, Date stop_time, int fade_time = 30, byte power_start = 0);
    void setSchedule(int pin_num, byte max_power, Date start_time, int start_length, Date stop_time, int stop_length, byte power_start = 0, boolean epehmerid = false);
    
    /*type2 Schedule*/
    void setSchedule2(int pin_num, byte max_poxer, Date start_time, Date stop_time, byte power_start = 0);
    
    void setFanPin(int pin);
  
    void setShift(byte shift_value);
    void setForcePin(int pin, boolean on);

    void run();  
  
  
};

#endif
