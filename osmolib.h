#ifndef OSMOLIB_H
#define OSMOLIB_H

#include "Arduino.h"

#define BOUNCE_TIME 30000
#define PUMP_TIME 2000

class OsmoLib
{
  private:
    int levelPin;
    int pumpBurnLevelPin;
    int securityLevelPin;
    int pumpTriggerPin;
  
    int levelTriggerState;
    int burnTriggerState;
    int secuTriggerState;
  
    int level;
    int pumpStartTime;
    int levelWaveBounce;
    
    boolean pumpDisabled;
  
  public:
    OsmoLib(int level_pin, int pump_trigger_pin, int trigger_state = HIGH);
    void setPumpBurnLevelPin(int pin, int trigger_state = HIGH);
    void setSecurityLevelPin(int pin, int trigger_state = HIGH);
    void run();
};

#endif
