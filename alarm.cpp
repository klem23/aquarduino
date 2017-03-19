#include "alarm.h"
#include "Arduino.h"
#include "multilang.h"


Alarm::Alarm(){
	redLedPin = 255;
	greenLedPin = 255;
}



Alarm* Alarm::getInstance(){
  
        if(single == NULL){
           single = new Alarm();
        }
        return single;       
}

void Alarm::checkStatus(){
	bool ok = true;

	for(int i = 0; i < MAX_PROB; i++){
		if(problem[i]){
			ok = false;
		}
	}

	if(ok){
		digitalWrite(redLedPin, LOW);
		digitalWrite(greenLedPin, HIGH);
	}else{
		digitalWrite(redLedPin, HIGH);
		digitalWrite(greenLedPin, LOW);
	}
}


void Alarm::add(uint32_t nb){
	problem[nb] = true;
	checkStatus();
}

void Alarm::remove(uint32_t nb){
	problem[nb] = false;
	checkStatus();
}



void Alarm::getProblems(char** mess, uint32_t* nb){
	uint32_t nb_elem = 0;

	char** temp = new char*[MAX_PROB];

	for(int i = 0; i < MAX_PROB; i++){
		if(problem[i]){
			switch(i){
				case TEMP_HIGH:
					temp[nb_elem] = TEMP_HIGH_MESS;
					break;
				case TEMP_LOW:
					temp[nb_elem] = TEMP_LOW_MESS;
					break;
				case OSMO_EMPTY : 	
					temp[nb_elem] = OSMO_EMPTY_MESS;
					break;
				case OSMO_SECU : 	
					temp[nb_elem] = OSMO_SECU_MESS;
					break;
			}
			nb_elem++;
		}
	} 

	*nb = nb_elem;
	mess = new char*[nb_elem];
	for(int i = 0; i < nb_elem; i++){
		mess[i] = temp[i];
	}

	delete temp;


}

void Alarm::setRedLed(int pin){
	redLedPin = pin;
	pinMode(redLedPin, OUTPUT);
}

void Alarm::setGreenLed(int pin){
	greenLedPin = pin;
	pinMode(greenLedPin, OUTPUT);
}

