#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Arduino.h"
#include "clockRTC.h"

typedef struct{
  int      pin;
  boolean  type;
  uint32_t repeat;
  Date     event;
  uint32_t duration;
  void*    next;
}sched;

class Scheduler{
  private:
    sched* tab;
    ClockRTC* ck;
  
    sched* getEntryByPin(int pin);
    void   add(sched* ptr);
    
  public:
    Scheduler();
    void setSchedule(int pin, Date event, uint32_t duration); 
    void setSchedule(int pin, uint32_t repeat, uint32_t duration);
    void run();
};

#endif
