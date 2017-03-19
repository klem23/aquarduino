#include "scheduler.h"

Scheduler::Scheduler(){
    ck = new ClockRTC(0x68);
}

void Scheduler::add(sched* ptr){
    if(tab == NULL){
       tab = ptr;
       tab->next = NULL; 
       return;
    }
  
    sched* tmp = tab;
    sched* tmp_save = tab;
    while(tmp != NULL){
       tmp_save = tmp;
       tmp = (sched*)tmp->next; 
    }
    
    tmp_save->next = ptr;
    ptr->next = NULL;
}

sched* Scheduler::getEntryByPin(int pin){
    sched* tmp = tab;
    while(tmp != NULL){
      if(tmp->pin == pin){
        return tmp;
      }else{
       tmp = (sched*)tmp->next; 
      }
    }
    return NULL;
}

void Scheduler::setSchedule(int pin, Date event, uint32_t duration){
  pinMode(pin, OUTPUT);
  
  sched* tmp = getEntryByPin(pin);
  if(tmp == NULL){
    tmp = new sched;
    tmp->pin = pin;
    add(tmp);
  }

//  event.type = TIME;
  tmp->type = true;
  tmp->event = event;
  tmp->duration = duration;
  tmp->next = NULL;     
}

void Scheduler::setSchedule(int pin, uint32_t repeat, uint32_t duration){
  pinMode(pin, OUTPUT);
  
  sched* tmp = getEntryByPin(pin);
  if(tmp == NULL){
    tmp = new sched;
    tmp->pin = pin;
    add(tmp);
  }

  tmp->type = false;
  tmp->repeat = repeat;
  tmp->duration = duration;
  tmp->next = NULL; 
}

void Scheduler::run(){
   Date now = ck->getTime();
  /*for testing Light effect in accelerate*/
  //date now = ck->getStubTime();
  
  Serial.print("Scheduler time ");
  Serial.print(now.h);
  Serial.print(":");
  Serial.println(now.mn);
  
  sched* tmp = tab;
  
  while(tmp != NULL){
    if(tmp->type){
        if((now >= tmp->event)&&(now <= tmp->event + tmp-> duration)){
            digitalWrite(tmp->pin, HIGH);
        }else{
            digitalWrite(tmp->pin, LOW);
        }
    }else{
        if((now.mn % tmp->repeat >= 0)&&(now.mn % tmp->repeat <= tmp->duration)){
            digitalWrite(tmp->pin, HIGH);
        }else{
            digitalWrite(tmp->pin, LOW);
        } 
      
    }
    tmp = (sched*)tmp->next;
  }

}
