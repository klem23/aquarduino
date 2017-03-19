 #include "temperature.h"

#include <OneWire.h>

//OneWire wp(13);

Temperature::Temperature(int thermo_pin){
   thermoPin = thermo_pin;
   thermoAddrSet = false;
   sumpThermoPin = 0;
   sumpThermoAddrSet = false;
   heaterPin = 0; 
   fanPin = 0;
   maxTemp = 28;
   minTemp = 22;
   boundSet = false;
   
   for(int i = 0; i < 8; i++){
          thermoAddr[i] = 0; 
          sumpThermoAddr[i] = 0; 
   }

   pinMode(thermoPin, INPUT);
}

void Temperature::setThermoPin(int pin, byte* addr){
  thermoPin = pin;
  pinMode(thermoPin, INPUT);
  
  if(addr != NULL){
    for(int i = 0; i < 8; i++){
       thermoAddr[i] = addr[i];
    } 
    thermoAddrSet = true;
  }
}

void Temperature::setSumpThermoPin(int pin, byte* addr){
  sumpThermoPin = pin;
  pinMode(sumpThermoPin, INPUT);
  
    if(addr != NULL){
      for(int i = 0; i < 8; i++){
        sumpThermoAddr[i] = addr[i];
      } 
      sumpThermoAddrSet = false;
  }
}
  
void Temperature::setHeaterPin(int pin, float startTemperature){
  heaterPin = pin;
  heatTemp = startTemperature;
  if(boundSet == false){
    minTemp = startTemperature;
  }
  
  pinMode(heaterPin, OUTPUT);
}
  
void Temperature::setFanPin(int pin, float startTemperature){
  fanPin = pin;
  fanTemp = startTemperature;
   
  if(boundSet == false){
    maxTemp = startTemperature;
  }
  
  pinMode(fanPin, OUTPUT);
}

void Temperature::setAlarmBound(float minTemperature, float maxTemperature){
  
     minTemp = minTemperature;
     maxTemp = maxTemperature;
     boundSet = true;
}

float Temperature::getOWTemp(int pin, byte* address){
  
  byte addr[8];
  byte data[12];
  byte type_s;
  
  OneWire wp(pin);
  
  /*
    do{ 
      wp.search(addr);
      
    while(
  
  */
  if ( !wp.search(addr)) {
    Serial.println("No more addresses for Temperature probe");
    Serial.println();
    wp.reset_search();
    delay(250);
    return 0;
  }
   
   
  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid for temperature probe!");
      return 0;
  }


  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return 0;
  }

  
  
  wp.reset();
  wp.select(addr);
  wp.write(0x44, 1); 
  
  delay(1000); 
  
  wp.reset();
  wp.select(addr);
  wp.write(0xBE);
  
  for (int i = 0; i < 9; i++) {
    data[i] = wp.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  float celsius = (float)raw / 16.0;

  return celsius;
}

float Temperature::getTemperature(){
  return getOWTemp(thermoPin, thermoAddr);
}

float Temperature::getSumpTemperature(){
    return getOWTemp(sumpThermoPin, sumpThermoAddr);
}

void Temperature::run(){
  
  float temp = getTemperature();
 
  if(temp < minTemp){
    //alarm
  }
  if(temp > maxTemp){
    //alarm
  }
 
  if(heaterPin != 0){
    if(temp < heatTemp){
      digitalWrite(heaterPin, HIGH);
    }else{
      digitalWrite(heaterPin, LOW); 
    }
  }
  
  if(fanPin != 0){
    if(temp >= fanTemp){
     digitalWrite(fanPin, HIGH);
    }else{
     digitalWrite(fanPin, LOW); 
    }
  }
  
  
}
