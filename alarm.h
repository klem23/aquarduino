#ifndef ALARM_H
#define ALARM_H

#include "Arduino.h"

#define TEMP_HIGH 0
#define TEMP_LOW 1
#define OSMO_EMPTY 2
#define OSMO_SECU 3

#define MAX_PROB 4

class Alarm{
	private:
         static Alarm* single;
	 boolean problem[MAX_PROB];		
	 int redLedPin;
	 int greenLedPin;

         Alarm();
	 void checkStatus();

	public:

         Alarm* getInstance();
	 void add(uint32_t nb);
	 void remove(uint32_t nb);

	 void getProblems(char** mess, uint32_t* nb);
	 void setRedLed(int pin);
	 void setGreenLed(int pin);
};

#endif
