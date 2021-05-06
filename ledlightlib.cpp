#include "ledlightlib.h"


LedLightLib::LedLightLib()
:nbGrp(0),
fanPin(-1),
shift(0),
forcePin(-1),
lp(nullptr),
ck(new ClockRTC(0x68))
{

}

LedLightLib::LedLightLib(int light_pin, byte max_power)
:nbGrp(1),
fanPin(-1),
shift(0),
forcePin(-1),
lp(new lightParam),
ck(new ClockRTC(0x68)){

    lp->ledPin = light_pin;
    lp->maxPower = max_power;
    lp->next = NULL;
} 


void LedLightLib::add(lightParam* ptr){
    if(lp == NULL){
       lp = ptr;
       lp->next = NULL; 
       return;
    }
  
    lightParam* tmp = lp;
    lightParam* tmp_save = lp;
    while(tmp != NULL){
       tmp_save = tmp;
       tmp = (lightParam*)tmp->next; 
    }
    
    tmp_save->next = ptr;
    ptr->next = NULL;
}

lightParam* LedLightLib::getEntryByPin(int pin){
    lightParam* tmp = lp;
    while(tmp != NULL){
      if(tmp->ledPin == pin){
        return tmp;
      }else{
       tmp = (lightParam*)tmp->next; 
      }
    }
    return NULL;
}

void LedLightLib::setShift(byte shift_value){
     shift = shift_value; 
}

void LedLightLib::setSchedule(int pin_num, byte max_power, Date start_time, Date stop_time, int fade_time, byte power_start){
  pinMode(pin_num, OUTPUT);
  
  lightParam* tmp = getEntryByPin(pin_num);
  if(tmp == NULL){
    tmp = new lightParam;
    tmp->ledPin = pin_num;
    add(tmp);
  }

  tmp->type = 0;
  tmp->maxPower = max_power;
  tmp->powStart = power_start;
  tmp->startTime = start_time;
  tmp->startLgth = fade_time;
  tmp->stopTime = stop_time;
  tmp->stopLgth = fade_time;
  tmp->ephem = false;
  
}

void LedLightLib::setSchedule(int pin_num, byte max_power, Date start_time, int start_length, Date stop_time, int stop_length, byte power_start, boolean ephemerid){
  pinMode(pin_num, OUTPUT);
  
  lightParam* tmp = getEntryByPin(pin_num);
  if(tmp == NULL){
    tmp = new lightParam;
    tmp->ledPin = pin_num;
    add(tmp);
  }

  tmp->type = 0;
  tmp->maxPower = max_power;
  tmp->powStart = power_start;
  tmp->startTime = start_time;
  tmp->startLgth = start_length;
  tmp->stopTime = stop_time;
  tmp->stopLgth = stop_length;
  tmp->ephem = ephemerid;
  
}


void LedLightLib::setSchedule2(int pin_num, byte max_power, Date start_time, Date stop_time, byte power_start){
  pinMode(pin_num, OUTPUT);
  
  lightParam* tmp = getEntryByPin(pin_num);
  if(tmp == NULL){
    tmp = new lightParam;
    tmp->ledPin = pin_num;
    add(tmp);
  }

  tmp->type = 1;
  tmp->maxPower = max_power;
  tmp->powStart = power_start;
  tmp->startTime = start_time;
  tmp->stopTime = stop_time;
  tmp->ephem = false;

}

void LedLightLib::setFanPin(int pin){
   fanPin = pin; 
   pinMode(fanPin, OUTPUT);
   digitalWrite(fanPin, LOW); 
}

void LedLightLib::setForcePin(int pin, boolean on){
  if(on){
    forcePin = pin; 
  }else{
    forcePin = -1;
    pinMode(forcePin, OUTPUT);
  }

}

void LedLightLib::run(){
  bool fan = false;
  
  
  Date now = ck->getTime();
  /*for testing Light effect in accelerate*/
  //Date now = ck->getStubTime();
  
  Serial.print("LLL time ");
  Serial.print(now.h);
  Serial.print(":");
  Serial.println(now.mn);

  if(now.h > 24) return;

  lightParam* tmp = lp;
  uint8_t powL;
  while(tmp != NULL){

  switch(tmp->type){
        /*LINEAR*/
	case 0:
	 if(now < tmp->startTime){
                powL = 0;
	 }else if((now >= tmp->startTime)&&(now <= tmp->startTime + tmp->startLgth )){
        	powL = (tmp->maxPower - shift) * (float) (now - tmp->startTime) / (float)tmp->startLgth + shift;
	 }else if((now >= tmp->startTime + tmp->startLgth)&&(now <= tmp->stopTime - tmp->stopLgth)){
                powL = tmp->maxPower;
	 }else if((now >= tmp->stopTime - tmp->stopLgth)&&(now <= tmp->stopTime)){
      		powL = (tmp->maxPower - shift) * (1.0 - (float)(now - (tmp->stopTime - tmp->stopLgth))/(float)tmp->stopLgth) + shift;
	 }else if((now >= tmp->stopTime)){
		powL = 0;
	 }else{
		powL = 0;
	 }
	 break;
        /*Linear without constant*/
	case 1:
	 if(now < tmp->startTime){
                powL = 0;
    	 }else if((now <= tmp->startTime + (float)(tmp->stopTime - tmp->startTime) / 2)){
                  powL = 127;
    	 }else if((now >= tmp->startTime + (float)(tmp->stopTime - tmp->startTime) / 2 )&&(now <= tmp->stopTime)){
                 powL = 127;
    	 }else if((now >= tmp->stopTime)){
                powL = 0;
    	 }else{
                powL = 0;
    	 }
     }

    if(forcePin != -1){
      Serial.print("LLL FORCE pin : ");
      Serial.println(forcePin);
      if(forcePin == tmp->ledPin){
        powL = tmp->maxPower;
      }else{
        powL = 0;
      }
    }

    Serial.print("LLL pin : ");
    Serial.print(tmp->ledPin);
    Serial.print("  power : ");
    Serial.println(powL);

    analogWrite(tmp->ledPin, powL);
    
    if(powL > 0){
      fan = true; 
    }

    tmp = (lightParam*)tmp->next;
  } 

  if((fanPin != -1)&&(fan)){
    digitalWrite(fanPin, HIGH); 
  }else{
    digitalWrite(fanPin, LOW); 
  }
  
}
