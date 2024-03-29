#include "osmolib.h"
#include "ledlightlib.h"
#include "temperature.h"
#include "scheduler.h"
#include "clockRTC.h"

#define BUTTON     2
#define GREEN_LED  3
#define RED_LED    4

#define BLUE_PIN   9
#define WHITE_PIN  10

#define OSMO_LEVEL_PIN  11
#define OSMO_BURN_PIN   12
#define OSMO_SECU_PIN   13
#define OSMO_PUMP       5
#define FAN_PIN         6
#define CABIN_FAN       7


#include <OneWire.h>

OsmoLib* osmo;
LedLightLib* lll;
Temperature* temp;
Scheduler* sch;


ClockRTC* ck1;
boolean blue_force;

void setup() {


  pinMode(BUTTON, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(CABIN_FAN, OUTPUT);
  pinMode(OSMO_LEVEL_PIN, INPUT);
  pinMode(OSMO_PUMP, OUTPUT);
  ck1 = new ClockRTC(0x68);

  
  // put your setup code here, to run once:
    osmo = new OsmoLib(OSMO_LEVEL_PIN, OSMO_PUMP, HIGH);
    //osmo = new OsmoLib(BUTTON, OSMO_PUMP);
    //osmo->setPumpBurnLevelPin(OSMO_BURN_PIN);
    //osmo->setSecurityLevelPin(OSMO_SECU_PIN);


    Date startTime(9, 0, 0);
    Date stopTime(23, 50, 0);
    Date startTime2(12, 00, 0);
    Date stopTime2(21, 30, 0);
    lll = new LedLightLib();
    lll->setSchedule(BLUE_PIN, 220, startTime, 180, stopTime, 180);
    lll->setSchedule(WHITE_PIN, 180, startTime2, 120, stopTime2, 90);
    lll->setFanPin(FAN_PIN);
    //lll->setShift(25);
    
    //sch = new Scheduler(); 
    //sch->setSchedule(CABIN_FAN, 30, 1);

  blue_force = false;
    
  Serial.begin(9600);

  
  
  //Date d(2013, 6, 8, 14, 22, 45);
  //ck1->setDate(d);
}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);


  int blue_butt = digitalRead(BUTTON);
  if(blue_butt == HIGH){
      if(blue_force){
          blue_force = false;
          Serial.print("Blue force Mode Off\n");
          lll->setForcePin(BLUE_PIN, false);
      }else{
          blue_force = true;
          Serial.print("Blue force Mode On\n");
          lll->setForcePin(BLUE_PIN, true);
      }
  }
  
  osmo->run();
  lll->run();
  //sch->run();

   
  ck1->printDate();
  
  /*Cabinet Fan*/
  /*Date d = ck1->getTime();
  
  if((d.mn > 0)&&(d.mn < 2)){
    digitalWrite(CABIN_FAN, HIGH);
  }else{
    digitalWrite(CABIN_FAN, LOW);
  }*/

  /*Osmo schedule*/
  /*Date d = ck1->getTime();
  if((d.mn == 0)&&(d.sec > 0)&&(d.sec < 4)){
    digitalWrite(OSMO_PUMP, HIGH);
  }else{
    digitalWrite(OSMO_PUMP, LOW);
  }*/

  digitalWrite(GREEN_LED, LOW);
  delay(2000);
  
  
}
