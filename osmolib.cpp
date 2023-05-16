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
   pumpRepeat = 0;
   
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
     Serial.println("Osmo HIGH");
   else
     Serial.println("Osmo LOW");

   if(level == levelTriggerState){
      if(levelWaveBounce == 0){
        levelWaveBounce = millis(); 
      }else if(((millis() - levelWaveBounce) > BOUNCE_TIME)&&(pumpStartTime == 0)&&(!pumpDisabled)){
        digitalWrite(pumpTriggerPin, HIGH);
        pumpStartTime = millis();
      }
   }
   
   if((pumpStartTime != 0)&&(millis() - pumpStartTime > PUMP_TIME)&&(!pumpDisabled)){
       level = digitalRead(levelPin);
       if(level != levelTriggerState){
         digitalWrite(pumpTriggerPin, LOW);
         pumpStartTime = 0;
         levelWaveBounce = 0;
         pumpRepeat = 0;
       }else if(pumpRepeat > 3){
         digitalWrite(pumpTriggerPin, LOW);
         pumpDisabled = true;
       }else{
         pumpRepeat++;
         pumpStartTime = millis();
       }
   }

  if((pumpDisabled)&&(millis() - pumpStartTime > ONE_HOUR)){
      pumpStartTime = 0;
      levelWaveBounce = 0;
      pumpRepeat = 0;
  }else if((pumpDisabled)&&(millis() - pumpStartTime < 0)){
      pumpStartTime = 0;
      levelWaveBounce = 0;
      pumpRepeat = 0;
      pumpDisabled = false;
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
