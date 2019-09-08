#include "Arduino.h"
#include "osmolib.h"

OsmoLib::OsmoLib(int level_pin, int pump_trigger_pin, int trigger_state){
   levelPin = level_pin;
   pumpTriggerPin = pump_trigger_pin; 
   levelTriggerState = trigger_state;
   pumpBurnLevelPin = 255;
   securityLevelPin = 255;

   levelWaveBounce = 0;
   pumpStartTime = 0;
   
   pumpDisabled = false;
   
   pinMode(levelPin, INPUT);
   pinMode(pumpTriggerPin, OUTPUT);
   digitalWrite(pumpTriggerPin, LOW);
}

void OsmoLib::setPumpBurnLevelPin(int pin, int trigger_state){
   pumpBurnLevelPin = pin; 
   burnTriggerState = trigger_state;
   pinMode(pumpBurnLevelPin, INPUT);
}


void OsmoLib::setSecurityLevelPin(int pin, int trigger_state){
  securityLevelPin = pin;
  secuTriggerState = trigger_state;
  pinMode(securityLevelPin, INPUT);
}

void OsmoLib::run(){
   level = digitalRead(levelPin);
   
   if(level == HIGH)
     Serial.println("HIGH");
   else
      Serial.println("LOW");

   if(level == levelTriggerState){
      if(levelWaveBounce == 0){
        levelWaveBounce = millis(); 
      }else if(((millis() - levelWaveBounce) > BOUNCE_TIME)&&(pumpStartTime == 0)&&(pumpDisabled == false)){
        digitalWrite(pumpTriggerPin, HIGH);
        pumpStartTime = millis();
      }
   }
   
   if((pumpStartTime != 0)&&(millis() - pumpStartTime > PUMP_TIME)){
       level = digitalRead(levelPin);
       if(level != levelTriggerState){
         digitalWrite(pumpTriggerPin, LOW);
         pumpStartTime = 0;
         levelWaveBounce = 0;
       }else{
         pumpStartTime = millis();
       }
   }
   
   if(pumpBurnLevelPin != 255){
      int burn = digitalRead(pumpBurnLevelPin);
      if(burn == burnTriggerState){
        pumpDisabled = true;
        digitalWrite(pumpTriggerPin, LOW);
      }else{
        pumpDisabled = false;
      }
   }
   
   if(securityLevelPin != 255){
      int secu = digitalRead(securityLevelPin);
      if(secu == secuTriggerState){
        pumpDisabled = true;
        digitalWrite(pumpTriggerPin, LOW);
      }else{
        pumpDisabled = false;
      }
   }
}
