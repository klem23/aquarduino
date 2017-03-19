#ifndef FREEREEF_H
#define FREEREEF_H

#include "osmolib.h"
#include "ledlightlib.h"
#include "temperature.h"
#include "scheduler.h"

class FreeReef{
  private:
    OsmoLib* osmo;
    LEDLightLib* lll;
    Temperature* temp;
    Scheduler*   sched;

  public:

    setOsmo();
    setLightSchedule();
    setLightSchedule2();
    setTemperature();
    setScheduler();
    void run();
}

#endif
