#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Arduino.h"
#include <Wire.h>

class Temperature{
  private:
    int thermoPin;
    byte thermoAddr[8];
    boolean thermoAddrSet;
    int sumpThermoPin;
    byte sumpThermoAddr[8];
    boolean sumpThermoAddrSet;
    
    int heaterPin;
    int fanPin;
    
    float minTemp;
    float maxTemp;
    boolean boundSet;
    float fanTemp;
    float heatTemp;
    
    float getOWTemp(int pin, byte* address = NULL);

  public:  
    Temperature(int thermo_pin);
    
    void setThermoPin(int pin, byte* addr = NULL);
    void setSumpThermoPin(int pin, byte* addr = NULL);
    void setAlarmBound(float minTemperature, float maxTemperature);
    void setFanPin(int pin, float startTemperature = 28.0);
    void setHeaterPin(int pin, float startTemperature = 25.0);
    
    float getTemperature();
    float getSumpTemperature();
    
    void run();
  
};

#endif
